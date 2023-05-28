
/*

SCL Line:Green
SDA Line:White

I2C0
I2C0_SCL --- PTA3
I2C0_SDA --- PTA2

mode:Master
I2C0_MASTER_ADDR:0x0F
7-bit address


I2C1
I2C1_SCL --- PTA0
I2C1_SDA --- PTA1
mode:Slave
I2C1_SLAVE_ADDR:0x1F
7-bit address

*/

#include "clock_config.h"
#include "serial.h"
#include "parity_bit.h"

#include "z20k14x_i2c.h"

#include "gpio_drv.h"
#include "int_drv.h"

#define OSC40M_ENABLE 1

#if OSC40M_ENABLE
#define SYSTEM_CLOCK_FREQUENCE 10
#else
#define SYSTEM_CLOCK_FREQUENCE 20
#endif

#define I2C_MASTER_DEV  I2C0
#define I2C_SLAVE_DEV   I2C1

#define I2C_MASTER_ADDR 0x0F
#define I2C_SLAVE_ADDR 0x1F

I2C_config_t masterConfig = 
{
  I2C_7BitAddr,
  I2C_MASTER_ADDR,
  I2C_Standard,
  Master_Mode
};

I2C_config_t slaveConfig = 
{
  I2C_7BitAddr,
  I2C_SLAVE_ADDR,
  I2C_Standard,
  Slave_Mode
};

I2C_FIFOParam_t FIFOConfig = 
{
  3,
  3
};

I2C_DMAParam_t DMAConfig = 
{
  3,
  3
};

#define SCL_DURATION_CNT 50000

I2C_SCLDurationParam_t SCLDurationConfig = 
{
  SCL_DURATION_CNT,
  SCL_DURATION_CNT
};

I2C_holdTimeParam_t SDAMasterHoldTimeConfig = 
{
  SCL_DURATION_CNT/2,
  0
};

I2C_holdTimeParam_t SDASlaveHoldTimeConfig = 
{
  SCL_DURATION_CNT/2,
  0
};

I2C_SpikeLengthParam_t spike_config = 
{
  SCL_DURATION_CNT*2/100,
  SCL_DURATION_CNT*2/100
};

static uint32_t master_error_flag = 0x00;
static uint32_t slave_error_flag = 0x00;

void I2C_Master_ErrorAbortIRQHandler(void)
{
  master_error_flag++;
  printf("I2C0_ERROR_STATUS = 0x%x\n",I2C0_ERROR_STATUS);
  I2C_AllErrorStatusClear(I2C_MASTER_DEV);

}

void I2C_Slave_ErrorAbortIRQHandler(void)
{
  slave_error_flag++;
  printf("I2C1_ERROR_STATUS = 0x%x\n",I2C1_ERROR_STATUS);
  I2C_AllErrorStatusClear(I2C_SLAVE_DEV);
}

#define I2S_TX_BUFFER_SIZE 0xFF
#define I2S_RX_BUFFER_SIZE 0xFF

static uint8_t i2s_txBuffer[I2S_TX_BUFFER_SIZE] = {0};
static uint8_t i2s_rxBuffer[I2S_RX_BUFFER_SIZE] = {0};

void I2C_Master_TxEmptyIRQHandler(void)
{
  if(I2C_intStatusGet(I2C_MASTER_DEV, I2C_TX_EMPTY_IE) == Set)
  {
    static uint32_t Tx_Counter = 0x00UL;
    
    while(I2C_TxFIFOCountGet(I2C_MASTER_DEV) != I2C_TX_FIFO_DEPTH)
    {
      I2C_transmitData(I2C_MASTER_DEV, i2s_txBuffer[Tx_Counter++], I2C_RESET_STOP_DIS);
      
      if(Tx_Counter == I2S_TX_BUFFER_SIZE)
      {
        Tx_Counter = 0x00UL;
      }
    }
  }
}

void I2C_Master_TxOverflowIRQHandler(void)
{
  if(I2C_intStatusGet(I2C_MASTER_DEV, I2C_TX_OVF_IE) == Set)
  {
    printf("I2C Tx overflow,fifo count is %d\n",I2C_TxFIFOCountGet(I2C_MASTER_DEV));
  }
}

void I2C_Slave_RxFullIRQHandler(void)
{
  if(I2C_intStatusGet(I2C_SLAVE_DEV, I2C_RX_FULL_IE) == Set)
  {
    static uint32_t Rx_Counter = 0x00UL;
        
    while(I2C_RxFIFOCountGet(I2C_SLAVE_DEV) != 0x00UL)
    {
      i2s_rxBuffer[Rx_Counter++] = I2C_receiveData(I2C_SLAVE_DEV);
      
      if(Rx_Counter == I2S_RX_BUFFER_SIZE)
      {
        Rx_Counter = 0x00UL;
      }
      
      (void)i2s_rxBuffer;
    }
  }
}

void I2C_Slave_RxOverflowRQHandler(void)
{
  if(I2C_intStatusGet(I2C_SLAVE_DEV, I2C_RX_OVF_IE) == Set)
  {
    printf("I2C Rx overflow,fifo count is %d\n",I2C_RxFIFOCountGet(I2C_SLAVE_DEV));
  }
}

void I2C_Slave_RxUnderflowRQHandler(void)
{
  if(I2C_intStatusGet(I2C_SLAVE_DEV, I2C_RX_UNDER_IE) == Set)
  {
    printf("I2C Rx underflow,fifo count is %d\n",I2C_RxFIFOCountGet(I2C_SLAVE_DEV));
  }
}

static void I2S_txBufferInit(void)
{
  for(uint32_t i = 0; i <= I2S_TX_BUFFER_SIZE;i++)
  {
    i2s_txBuffer[i] = i;
  }
}

void I2C_Master_GPIO_init(void)
{
  CLK_ModuleSrc(CLK_PORTA, CLK_SRC_OSC40M);
  SYSCTRL_EnableModule(SYSCTRL_PORTA);
  
  PORT_PinmuxConfig(PORT_A, GPIO_3, PTA3_I2C0_SCL);
  PORT_PinmuxConfig(PORT_A, GPIO_2, PTA2_I2C0_SDA);
  
  PORT_OpenDrainConfig(PORT_A, GPIO_3, ENABLE);
  PORT_OpenDrainConfig(PORT_A, GPIO_2, ENABLE);
  
  PORT_PullConfig(PORT_A, GPIO_3,PORT_PULL_UP);
  PORT_PullConfig(PORT_A, GPIO_2,PORT_PULL_UP);
}

void I2C_Slave_GPIO_init(void)
{
  CLK_ModuleSrc(CLK_PORTA, CLK_SRC_OSC40M);
  SYSCTRL_EnableModule(SYSCTRL_PORTA);
  
  PORT_PinmuxConfig(PORT_A, GPIO_0, PTA0_I2C1_SCL);
  PORT_PinmuxConfig(PORT_A, GPIO_1, PTA1_I2C1_SDA);
  
  PORT_OpenDrainConfig(PORT_A, GPIO_0, ENABLE);
  PORT_OpenDrainConfig(PORT_A, GPIO_1, ENABLE);
  
  PORT_PullConfig(PORT_A, GPIO_0,PORT_PULL_UP);
  PORT_PullConfig(PORT_A, GPIO_1,PORT_PULL_UP);
}

void I2C_Master_init(void)
{
  CLK_SetClkDivider(CLK_I2C0, CLK_DIV_4);
  CLK_ModuleSrc(CLK_I2C0, CLK_SRC_OSC40M);
  SYSCTRL_ResetModule(SYSCTRL_I2C0);
  SYSCTRL_EnableModule(SYSCTRL_I2C0);
  
  I2C_init(I2C_MASTER_DEV, &masterConfig);
}

void I2C_Slave_init(void)
{
  CLK_SetClkDivider(CLK_I2C1, CLK_DIV_4);
  CLK_ModuleSrc(CLK_I2C1, CLK_SRC_OSC40M);
  SYSCTRL_ResetModule(SYSCTRL_I2C1);
  SYSCTRL_EnableModule(SYSCTRL_I2C1);
  
  I2C_init(I2C_SLAVE_DEV, &slaveConfig);
}

void DMA_I2C_Master_Configure(void)
{
  
}

void DMA_I2C_Slave_Configure(void)
{
  
}
 
void user_delay(uint32_t cycle)
{
  for(uint32_t i = 0;i < cycle;i++){}
}

#define TEST_BUFFER_SIZE 256
static uint8_t test_buffer[TEST_BUFFER_SIZE] = {0};

int main(void)
{
    (void)test_buffer;
    
#if OSC40M_ENABLE
    OSC40M_ClockInit();
#else
    PLL80M_ClockInit();
#endif
    
    Ex_BoardUartInit();
    
    I2S_txBufferInit();
    
    I2C_Master_GPIO_init();
    I2C_Slave_GPIO_init();
    
    I2C_Master_init();
    I2C_Slave_init();
    
    I2C_targetAddressSet(I2C_MASTER_DEV, I2C_SLAVE_ADDR,Single_Target_Addr);
    
    I2C_FIFOLevelSet(I2C_MASTER_DEV,&FIFOConfig);
    I2C_FIFOLevelSet(I2C_SLAVE_DEV,&FIFOConfig);
    
    I2C_DMAWatermarkSet(I2C_MASTER_DEV, &DMAConfig);
    I2C_DMAWatermarkSet(I2C_SLAVE_DEV, &DMAConfig);
    

    I2C_SDASetupTimeConfig(I2C_SLAVE_DEV, SCL_DURATION_CNT/2,SYSTEM_CLOCK_FREQUENCE);
    
    I2C_SDAHoldTimeConfig(I2C_MASTER_DEV, &SDAMasterHoldTimeConfig, SYSTEM_CLOCK_FREQUENCE);
    I2C_SDAHoldTimeConfig(I2C_SLAVE_DEV, &SDASlaveHoldTimeConfig, SYSTEM_CLOCK_FREQUENCE);

    I2C_spikeSuppressionLimitConfig (I2C_MASTER_DEV, &spike_config);
    I2C_spikeSuppressionLimitConfig (I2C_SLAVE_DEV, &spike_config);

    I2C_SCLHighLowDurationConfig(I2C_MASTER_DEV, &SCLDurationConfig, SYSTEM_CLOCK_FREQUENCE);
    
    I2C_DMAEnable(I2C_MASTER_DEV, Disable, Disable);
    I2C_DMAEnable(I2C_SLAVE_DEV, Disable, Disable);
    
    I2C_intCallbackRegister(I2C_MASTER_DEV,I2C_ERROR_ABORT_IE,I2C_Master_ErrorAbortIRQHandler);
    I2C_intEnable(I2C_MASTER_DEV, I2C_ERROR_ABORT_IE, Enable);
    I2C_intFlagClear(I2C_MASTER_DEV, I2C_ERROR_ABORT_IE);

    I2C_intCallbackRegister(I2C_SLAVE_DEV,I2C_ERROR_ABORT_IE,I2C_Slave_ErrorAbortIRQHandler);
    I2C_intEnable(I2C_SLAVE_DEV, I2C_ERROR_ABORT_IE, Enable);
    I2C_intFlagClear(I2C_SLAVE_DEV, I2C_ERROR_ABORT_IE);
    
    I2C_enable(I2C_MASTER_DEV, Enable);
    I2C_enable(I2C_SLAVE_DEV, Enable);
    
    /***I2C_MASTER_DEV Tx Interrupt Configure***/
    I2C_intCallbackRegister(I2C_MASTER_DEV,I2C_TX_EMPTY_IE,I2C_Master_TxEmptyIRQHandler);
    I2C_intEnable(I2C_MASTER_DEV, I2C_TX_EMPTY_IE, Disable);
    I2C_intFlagClear(I2C_MASTER_DEV, I2C_TX_EMPTY_IE);
    
    I2C_intCallbackRegister(I2C_MASTER_DEV,I2C_TX_OVF_IE,I2C_Master_TxOverflowIRQHandler);
    I2C_intEnable(I2C_MASTER_DEV, I2C_TX_OVF_IE, Disable);
    I2C_intFlagClear(I2C_MASTER_DEV, I2C_TX_OVF_IE);
    
    /***I2C_SLAVE_DEV Rx Interrupt Configure***/
    I2C_intCallbackRegister(I2C_SLAVE_DEV,I2C_RX_FULL_IE,I2C_Slave_RxFullIRQHandler);
    I2C_intEnable(I2C_SLAVE_DEV, I2C_RX_FULL_IE, Disable);
    I2C_intFlagClear(I2C_SLAVE_DEV, I2C_RX_FULL_IE);
    
    I2C_intCallbackRegister(I2C_SLAVE_DEV,I2C_RX_OVF_IE,I2C_Slave_RxOverflowRQHandler);
    I2C_intEnable(I2C_SLAVE_DEV, I2C_RX_OVF_IE, Disable);
    I2C_intFlagClear(I2C_SLAVE_DEV, I2C_RX_OVF_IE);
    
    I2C_intCallbackRegister(I2C_SLAVE_DEV,I2C_RX_UNDER_IE,I2C_Slave_RxUnderflowRQHandler);
    I2C_intEnable(I2C_SLAVE_DEV, I2C_RX_UNDER_IE, Disable);
    I2C_intFlagClear(I2C_SLAVE_DEV, I2C_RX_UNDER_IE);
    
    INT_EnableIRQ(I2C0_IRQn);
    INT_EnableIRQ(I2C1_IRQn);
    
    printf("I2C0_SDA_SETUP_TIMING = 0x%x\n",I2C0_SDA_SETUP_TIMING);
    printf("I2C1_SDA_SETUP_TIMING = 0x%x\n",I2C1_SDA_SETUP_TIMING);
    
    printf("I2C0_SDA_HOLD_TIMING = 0x%x\n",I2C0_SDA_HOLD_TIMING);
    printf("I2C1_SDA_HOLD_TIMING = 0x%x\n",I2C1_SDA_HOLD_TIMING);
    
    printf("I2C0_FSTD_SPKCNT = 0x%x\n",I2C0_FSTD_SPKCNT);
    printf("I2C1_FSTD_SPKCNT = 0x%x\n",I2C1_FSTD_SPKCNT);

    printf("I2C0_HS_SPKCNT = 0x%x\n",I2C0_HS_SPKCNT);
    printf("I2C1_HS_SPKCNT = 0x%x\n",I2C1_HS_SPKCNT);
    
    printf("20k14x_app I2C start.\n");
    
//    I2C_masterBlockTxFIFO(I2C_MASTER_DEV);

    /***********************  I2C write  *****************************/    
    for(int index = 0;index <= 255;index++)
    {
      while(I2C_TxFIFOCountGet(I2C_MASTER_DEV) >= 0x01);
      I2C_transmitData(I2C_MASTER_DEV, index, I2C_RESET_STOP_DIS);

      if(index == 100)
      {
//        I2C_slaveACK(I2C_SLAVE_DEV,Disable);
//        I2C_masterTransferAbort(I2C_MASTER_DEV);
        break;
      }
      
      while(I2C_RxFIFOCountGet(I2C_SLAVE_DEV) == 0);
      test_buffer[index] = I2C_receiveData(I2C_SLAVE_DEV);
    }
    
//    while(Reset == I2C_flagStatus0Get(I2C_SLAVE_DEV, STOP_DETECT));
//    I2C_intFlagClear(I2C_SLAVE_DEV,I2C_STOP_DET_IE);
    
    while(I2C_TxFIFOCountGet(I2C_MASTER_DEV) != 0x00);

    
    /***********************  I2C read  *****************************/
    I2C_receiveDirection(I2C_MASTER_DEV,ACK);
    while(Reset == I2C_flagStatus0Get(I2C_SLAVE_DEV, SLAVE_READ_REQ));
    
    for(int i = 0;i <= 255;i++)
    {
      I2C_transmitData(I2C_SLAVE_DEV, i,I2C_RESET_STOP_DIS);
      while(I2C_RxFIFOCountGet(I2C_MASTER_DEV) == 0);
      I2C_receiveData(I2C_MASTER_DEV);
      if(i == 254)
      {
        I2C_masterACK(I2C_MASTER_DEV,Disable);
      }
      else if(i < 254)
      {
        I2C_masterACK(I2C_MASTER_DEV,Enable);
      }
    }
    while(Reset == I2C_flagStatus0Get(I2C_SLAVE_DEV, RXFIFO_DONE));
    
    while(1);
}
