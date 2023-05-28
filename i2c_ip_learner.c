
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

#define I2C_MASTER_REG  I2C0_base_addr
#define I2C_SLAVE_REG   I2C1_base_addr

#define I2C_MASTER_CLK  CLK_I2C0
#define I2C_SLAVE_CLK   CLK_I2C1

#define I2C_MASTER_SYSCTRL  SYSCTRL_I2C0
#define I2C_SLAVE_SYSCTRL   SYSCTRL_I2C1

#define I2C_MASTER_ADDR 0x0F
#define I2C_SLAVE_ADDR  0x1F

static I2C_TypeDef * I2C_Master = I2C_MASTER_DEV;
static I2C_TypeDef * I2C_Slave = I2C_SLAVE_DEV;

static I2C_Reg_t * I2C_Master_Viewer = I2C_MASTER_REG;
static I2C_Reg_t * I2C_Slave_Viewer = I2C_SLAVE_REG;

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

#define SCL_DURATION_CNT 5000

I2C_SCLDurationParam_t SCLDurationConfig = 
{
  SCL_DURATION_CNT,
  SCL_DURATION_CNT
};

I2C_holdTimeParam_t SDAMasterHoldTimeConfig = 
{
  SCL_DURATION_CNT/2,
  SCL_DURATION_CNT/5
};

I2C_holdTimeParam_t SDASlaveHoldTimeConfig = 
{
  SCL_DURATION_CNT/2,
  SCL_DURATION_CNT/5
};

I2C_SpikeLengthParam_t spike_config = 
{
  5,
  5
};

/******I2C Master IRQ Handler******/

void I2C_Master_RxFullIRQHandler(void)
{
  if(I2C_intStatusGet(I2C_MASTER_DEV, I2C_RX_FULL_IE) == Set)
  {
    while(I2C_RxFIFOCountGet(I2C_MASTER_DEV) != 0x00UL)
    {
      uint8_t data_byte = I2C_receiveData(I2C_MASTER_DEV);
      if(Byte_parityBitCheck(data_byte) == false)
      {
        printf("[%d]%d parity check is invalid",__LINE__,data_byte);
      }
    }
  }
}

void I2C_Master_RxOverflowRQHandler(void)
{
  if(I2C_intStatusGet(I2C_MASTER_DEV, I2C_RX_OVF_IE) == Set)
  {
    printf("I2C Master Rx overflow,fifo count is %d\n",I2C_RxFIFOCountGet(I2C_MASTER_DEV));
  }
}

void I2C_Master_RxUnderflowRQHandler(void)
{
  if(I2C_intStatusGet(I2C_MASTER_DEV, I2C_RX_UNDER_IE) == Set)
  {
    printf("I2C Master Rx underflow,fifo count is %d\n",I2C_RxFIFOCountGet(I2C_MASTER_DEV));
  }
}

void I2C_Master_TxEmptyIRQHandler(void)
{
  if(I2C_intStatusGet(I2C_MASTER_DEV, I2C_TX_EMPTY_IE) == Set)
  {
    static uint32_t Tx_Counter = 0x00UL;
    
    while(I2C_TxFIFOCountGet(I2C_MASTER_DEV) != I2C_TX_FIFO_DEPTH)
    {
      I2C_transmitData(I2C_MASTER_DEV, Byte_parityBitGenerate(Tx_Counter), I2C_RESET_STOP_DIS);
    }
  }
}

void I2C_Master_TxOverflowIRQHandler(void)
{
  if(I2C_intStatusGet(I2C_MASTER_DEV, I2C_TX_OVF_IE) == Set)
  {
    printf("I2C Master Tx overflow,fifo count is %d\n",I2C_TxFIFOCountGet(I2C_MASTER_DEV));
  }
}

static uint32_t master_error_flag = 0x00;

void I2C_Master_ErrorAbortIRQHandler(void)
{
  printf("I2C Master Error Status = 0x%x\n",I2C_Master->ERROR_STATUS);
  I2C_AllErrorStatusClear(I2C_MASTER_DEV);
  
  master_error_flag++;
}


/******I2C Slave IRQ Handler******/

void I2C_Slave_RxFullIRQHandler(void)
{
  if(I2C_intStatusGet(I2C_SLAVE_DEV, I2C_RX_FULL_IE) == Set)
  {        
    while(I2C_RxFIFOCountGet(I2C_SLAVE_DEV) != 0x00UL)
    {
      uint8_t data_byte = I2C_receiveData(I2C_SLAVE_DEV);
      if(Byte_parityBitCheck(data_byte) == false)
      {
        printf("[%d]%d parity check is invalid",__LINE__,data_byte);
      }
    }
  }
}

void I2C_Slave_RxOverflowRQHandler(void)
{
  if(I2C_intStatusGet(I2C_SLAVE_DEV, I2C_RX_OVF_IE) == Set)
  {
    printf("I2C Slave Rx overflow,fifo count is %d\n",I2C_RxFIFOCountGet(I2C_SLAVE_DEV));
  }
}

void I2C_Slave_RxUnderflowRQHandler(void)
{
  if(I2C_intStatusGet(I2C_SLAVE_DEV, I2C_RX_UNDER_IE) == Set)
  {
    printf("I2C Slave Rx underflow,fifo count is %d\n",I2C_RxFIFOCountGet(I2C_SLAVE_DEV));
  }
}

void I2C_Slave_TxEmptyIRQHandler(void)
{
  if(I2C_intStatusGet(I2C_SLAVE_DEV, I2C_TX_EMPTY_IE) == Set)
  {
    static uint32_t Tx_Counter = 0x00UL;
    
    while(I2C_TxFIFOCountGet(I2C_SLAVE_DEV) != I2C_TX_FIFO_DEPTH)
    {
      I2C_transmitData(I2C_SLAVE_DEV, Byte_parityBitGenerate(Tx_Counter), I2C_RESET_STOP_DIS);
    }
  }
}

void I2C_Slave_TxOverflowIRQHandler(void)
{
  if(I2C_intStatusGet(I2C_SLAVE_DEV, I2C_TX_OVF_IE) == Set)
  {
    printf("I2C Slave Tx overflow,fifo count is %d\n",I2C_TxFIFOCountGet(I2C_SLAVE_DEV));
  }
}

static uint32_t slave_error_flag = 0x00;

void I2C_Slave_ErrorAbortIRQHandler(void)
{
  printf("I2C Slave Error Status = 0x%x\n",I2C_Slave->ERROR_STATUS);
  I2C_AllErrorStatusClear(I2C_SLAVE_DEV);
  
  slave_error_flag++;
}

/******I2C GPIO Init******/

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

/******I2C Dev Init******/

void I2C_Master_init(void)
{
  CLK_SetClkDivider(I2C_MASTER_CLK, CLK_DIV_4);
  CLK_ModuleSrc(I2C_MASTER_CLK, CLK_SRC_OSC40M);
  SYSCTRL_ResetModule(I2C_MASTER_SYSCTRL);
  SYSCTRL_EnableModule(I2C_MASTER_SYSCTRL);
  
  I2C_init(I2C_MASTER_DEV, &masterConfig);
  
  (void)I2C_Master_Viewer->I2C_PARAMETER;
}

void I2C_Slave_init(void)
{
  CLK_SetClkDivider(I2C_SLAVE_CLK, CLK_DIV_4);
  CLK_ModuleSrc(I2C_SLAVE_CLK, CLK_SRC_OSC40M);
  SYSCTRL_ResetModule(I2C_SLAVE_SYSCTRL);
  SYSCTRL_EnableModule(I2C_SLAVE_SYSCTRL);
  
  I2C_init(I2C_SLAVE_DEV, &slaveConfig);
  
  (void)I2C_Slave_Viewer->I2C_PARAMETER;
}

/******I2C DMA Init******/

void DMA_I2C_Master_Configure(void)
{
  
}

void DMA_I2C_Slave_Configure(void)
{
  
}

int main(void)
{    
#if OSC40M_ENABLE
    OSC40M_ClockInit();
#else
    PLL80M_ClockInit();
#endif
    
    Ex_BoardUartInit();
        
    I2C_Master_GPIO_init();
    I2C_Slave_GPIO_init();
    
    I2C_Master_init();
    I2C_Slave_init();
    
    I2C_targetAddressSet(I2C_MASTER_DEV, I2C_SLAVE_ADDR,Single_Target_Addr);
    
    I2C_FIFOLevelSet(I2C_MASTER_DEV,&FIFOConfig);
    I2C_FIFOLevelSet(I2C_SLAVE_DEV,&FIFOConfig);
    
    I2C_DMAWatermarkSet(I2C_MASTER_DEV, &DMAConfig);
    I2C_DMAWatermarkSet(I2C_SLAVE_DEV, &DMAConfig);
    
    I2C_SDASetupTimeConfig(I2C_MASTER_DEV, SCL_DURATION_CNT/2,SYSTEM_CLOCK_FREQUENCE);
    I2C_SDASetupTimeConfig(I2C_SLAVE_DEV, SCL_DURATION_CNT/2,SYSTEM_CLOCK_FREQUENCE);
    
    I2C_SDAHoldTimeConfig(I2C_MASTER_DEV, &SDAMasterHoldTimeConfig, SYSTEM_CLOCK_FREQUENCE);
    I2C_SDAHoldTimeConfig(I2C_SLAVE_DEV, &SDASlaveHoldTimeConfig, SYSTEM_CLOCK_FREQUENCE);

    I2C_spikeSuppressionLimitConfig (I2C_MASTER_DEV, &spike_config);
    I2C_spikeSuppressionLimitConfig (I2C_SLAVE_DEV, &spike_config);

    I2C_SCLHighLowDurationConfig(I2C_MASTER_DEV, &SCLDurationConfig, SYSTEM_CLOCK_FREQUENCE);
    
    I2C_DMAEnable(I2C_MASTER_DEV, Disable, Disable);
    I2C_DMAEnable(I2C_SLAVE_DEV, Disable, Disable);
    
    /***Master Interrupt Configure***/
       
    /***I2C_MASTER_DEV Tx Empty Interrupt Configure***/
    I2C_intCallbackRegister(I2C_MASTER_DEV,I2C_TX_EMPTY_IE,I2C_Master_TxEmptyIRQHandler);
    I2C_intEnable(I2C_MASTER_DEV, I2C_TX_EMPTY_IE, Disable);
    I2C_intFlagClear(I2C_MASTER_DEV, I2C_TX_EMPTY_IE);
    
    /***I2C_MASTER_DEV Tx Overflow Interrupt Configure***/
    I2C_intCallbackRegister(I2C_MASTER_DEV,I2C_TX_OVF_IE,I2C_Master_TxOverflowIRQHandler);
    I2C_intEnable(I2C_MASTER_DEV, I2C_TX_OVF_IE, Disable);
    I2C_intFlagClear(I2C_MASTER_DEV, I2C_TX_OVF_IE);
    
    /***I2C_MASTER_DEV Rx Full Interrupt Configure***/
    I2C_intCallbackRegister(I2C_MASTER_DEV,I2C_RX_FULL_IE,I2C_Master_RxFullIRQHandler);
    I2C_intEnable(I2C_MASTER_DEV, I2C_RX_FULL_IE, Disable);
    I2C_intFlagClear(I2C_MASTER_DEV, I2C_RX_FULL_IE);
    
    /***I2C_MASTER_DEV Rx Overflow Interrupt Configure***/
    I2C_intCallbackRegister(I2C_MASTER_DEV,I2C_RX_OVF_IE,I2C_Master_RxOverflowRQHandler);
    I2C_intEnable(I2C_MASTER_DEV, I2C_RX_OVF_IE, Disable);
    I2C_intFlagClear(I2C_MASTER_DEV, I2C_RX_OVF_IE);
    
    /***I2C_MASTER_DEV Rx Underflow Interrupt Configure***/
    I2C_intCallbackRegister(I2C_MASTER_DEV,I2C_RX_UNDER_IE,I2C_Master_RxUnderflowRQHandler);
    I2C_intEnable(I2C_MASTER_DEV, I2C_RX_UNDER_IE, Disable);
    I2C_intFlagClear(I2C_MASTER_DEV, I2C_RX_UNDER_IE);
    
    /***I2C_MASTER_DEV Error Abort Interrupt Configure***/
    I2C_intCallbackRegister(I2C_MASTER_DEV,I2C_ERROR_ABORT_IE,I2C_Master_ErrorAbortIRQHandler);
    I2C_intEnable(I2C_MASTER_DEV, I2C_ERROR_ABORT_IE, Enable);
    I2C_intFlagClear(I2C_MASTER_DEV, I2C_ERROR_ABORT_IE);
    
    /***Slave Interrupt Configure***/
    
    /***I2C_SLAVE_DEV Tx Empty Interrupt Configure***/
    I2C_intCallbackRegister(I2C_SLAVE_DEV,I2C_TX_EMPTY_IE,I2C_Slave_TxEmptyIRQHandler);
    I2C_intEnable(I2C_SLAVE_DEV, I2C_TX_EMPTY_IE, Disable);
    I2C_intFlagClear(I2C_SLAVE_DEV, I2C_TX_EMPTY_IE);
    
    /***I2C_SLAVE_DEV Tx Overflow Interrupt Configure***/
    I2C_intCallbackRegister(I2C_SLAVE_DEV,I2C_TX_OVF_IE,I2C_Slave_TxOverflowIRQHandler);
    I2C_intEnable(I2C_SLAVE_DEV, I2C_TX_OVF_IE, Disable);
    I2C_intFlagClear(I2C_SLAVE_DEV, I2C_TX_OVF_IE);
    
    /***I2C_SLAVE_DEV Rx Full Interrupt Configure***/
    I2C_intCallbackRegister(I2C_SLAVE_DEV,I2C_RX_FULL_IE,I2C_Slave_RxFullIRQHandler);
    I2C_intEnable(I2C_SLAVE_DEV, I2C_RX_FULL_IE, Disable);
    I2C_intFlagClear(I2C_SLAVE_DEV, I2C_RX_FULL_IE);
    
    /***I2C_SLAVE_DEV Rx Overflow Interrupt Configure***/
    I2C_intCallbackRegister(I2C_SLAVE_DEV,I2C_RX_OVF_IE,I2C_Slave_RxOverflowRQHandler);
    I2C_intEnable(I2C_SLAVE_DEV, I2C_RX_OVF_IE, Disable);
    I2C_intFlagClear(I2C_SLAVE_DEV, I2C_RX_OVF_IE);
    
    /***I2C_SLAVE_DEV Rx Underflow Interrupt Configure***/
    I2C_intCallbackRegister(I2C_SLAVE_DEV,I2C_RX_UNDER_IE,I2C_Slave_RxUnderflowRQHandler);
    I2C_intEnable(I2C_SLAVE_DEV, I2C_RX_UNDER_IE, Disable);
    I2C_intFlagClear(I2C_SLAVE_DEV, I2C_RX_UNDER_IE);

    /***I2C_SLAVE_DEV Error Abort Interrupt Configure***/
    I2C_intCallbackRegister(I2C_SLAVE_DEV,I2C_ERROR_ABORT_IE,I2C_Slave_ErrorAbortIRQHandler);
    I2C_intEnable(I2C_SLAVE_DEV, I2C_ERROR_ABORT_IE, Enable);
    I2C_intFlagClear(I2C_SLAVE_DEV, I2C_ERROR_ABORT_IE);
    
    I2C_enable(I2C_MASTER_DEV, Enable);
    I2C_enable(I2C_SLAVE_DEV, Enable);
    
    INT_EnableIRQ(I2C0_IRQn);
    INT_EnableIRQ(I2C1_IRQn);
    
    printf("I2C Master SDA Setup Time = %d\n",I2C_Master->SDA_SETUP_TIMING);
    printf("I2C Slave SDA Setup Time = %d\n",I2C_Slave->SDA_SETUP_TIMING);

    printf("I2C Master SDA Hold Time = %d\n",I2C_Master->SDA_HOLD_TIMING);
    printf("I2C Slave SDA Hold Time = %d\n",I2C_Slave->SDA_HOLD_TIMING);

    printf("I2C Master Fast/Std Spike Count = %d\n",I2C_Master->FSTD_SPKCNT);
    printf("I2C Slave Fast/Std Spike Count = %d\n",I2C_Slave->FSTD_SPKCNT);

    printf("I2C Master High Spike Count = %d\n",I2C_Master->HS_SPKCNT);
    printf("I2C Slave High Spike Count = %d\n",I2C_Slave->HS_SPKCNT);

    printf("I2C Master Std SCL High Count = %d\n",I2C_Master->STD_SCL_HCNT);
    printf("I2C Master Std SCL Low Count = %d\n",I2C_Slave->STD_SCL_LCNT);

    printf("I2C Master Fast SCL High Count = %d\n",I2C_Master->FST_SCL_HCNT);
    printf("I2C Master Fast SCL Low Count = %d\n",I2C_Slave->FST_SCL_LCNT);
    
    printf("I2C Master High SCL High Count = %d\n",I2C_Master->HS_SCL_HCNT);
    printf("I2C Master High SCL Low Count = %d\n",I2C_Slave->HS_SCL_LCNT);
    
    printf("20k14x_app I2C start.\n");
    
//    I2C_masterBlockTxFIFO(I2C_MASTER_DEV);

    /***********************  I2C write  *****************************/    
    for(int index = 0;index <= 255;index++)
    {
      while(I2C_TxFIFOCountGet(I2C_MASTER_DEV) >= 0x01);
      I2C_transmitData(I2C_MASTER_DEV, Byte_parityBitGenerate(index), I2C_RESET_STOP_DIS);

      if(index == 100)
      {
//        I2C_slaveACK(I2C_SLAVE_DEV,Disable);
//        I2C_masterTransferAbort(I2C_MASTER_DEV);
        break;
      }
      
      while(I2C_RxFIFOCountGet(I2C_SLAVE_DEV) == 0);
      
      uint8_t data_byte = I2C_receiveData(I2C_SLAVE_DEV);
      if(Byte_parityBitCheck(data_byte) == false)
      {
        printf("[%d]%d parity check is invalid",__LINE__,data_byte);
      }
    }
    
//    while(Reset == I2C_flagStatus0Get(I2C_SLAVE_DEV, STOP_DETECT));
//    I2C_intFlagClear(I2C_SLAVE_DEV,I2C_STOP_DET_IE);
    
    while(I2C_TxFIFOCountGet(I2C_MASTER_DEV) != 0x00);

    
    /***********************  I2C read  *****************************/
    I2C_receiveDirection(I2C_MASTER_DEV,ACK);
    while(Reset == I2C_flagStatus0Get(I2C_SLAVE_DEV, SLAVE_READ_REQ));
    
    for(int i = 0;i <= 255;i++)
    {
      I2C_transmitData(I2C_SLAVE_DEV, Byte_parityBitGenerate(i),I2C_RESET_STOP_DIS);
      while(I2C_RxFIFOCountGet(I2C_MASTER_DEV) == 0);
      
      uint8_t data_byte = I2C_receiveData(I2C_MASTER_DEV);
      if(Byte_parityBitCheck(data_byte) == false)
      {
        printf("[%d]%d parity check is invalid",__LINE__,data_byte);
      }
      
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
