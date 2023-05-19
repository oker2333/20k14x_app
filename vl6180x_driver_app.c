
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

#include "z20k14x_i2c.h"
#include "vl6180x_driver.h"

#include "gpio_drv.h"
#include "int_drv.h"

#define OSC40M_ENABLE 1

#if OSC40M_ENABLE
#define SYSTEM_CLOCK_FREQUENCE 40
#else
#define SYSTEM_CLOCK_FREQUENCE 80
#endif

#define I2C_MASTER_ADDR 0x0F
#define I2C_SLAVE_ADDR 0x1F

I2C_config_t masterConfig = 
{
  I2C_7BitAddr,
  I2C_MASTER_ADDR,
  I2C_Standard,
  Master_Mode,
  Enable
};

I2C_config_t slaveConfig = 
{
  I2C_7BitAddr,
  I2C_SLAVE_ADDR,
  I2C_Standard,
  Slave_Mode,
  Enable
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

uint8_t transmit_buffer[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};

i2c_optConfig_t op_config =
{
  .i2c_dev = I2C0,
  .opt = I2C_WRITE_SINGLE_REG,
  .cycle = I2C_READ_SINGLE_REG,
  
  .target_addrInfo = I2C_SLAVE_ADDR,
  .target_addrBytes = 0x01,
  .reg_addrInfo = 0xA0B0,
  .reg_addrBytes = 0x02,
  
  .transmit_buffer = transmit_buffer,
  .transmit_len = sizeof(transmit_buffer)/sizeof(uint8_t),
  
  .i2c_opt_handler = NULL
};

static fsm_struct_t fsm_port;

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

void I2C0_TxEmptyIRQHandler(void)
{
  if(I2C_intStatusGet(I2C0, I2C_TX_EMPTY_IE) == Set)
  {
    I2C_FSM_Service(&fsm_port,I2C_OK);
  }
}

void I2C0_TxOverflowIRQHandler(void)
{
  if(I2C_intStatusGet(I2C0, I2C_TX_OVF_IE) == Set)
  {
    I2C_FSM_Service(&fsm_port,I2C_OVERFLOW);
    printf("I2C Tx overflow,fifo count is %d\n",I2C_TxFIFOCountGet(I2C0));
  }
}

void I2C1_RxFullIRQHandler(void)
{
  if(I2C_intStatusGet(I2C1, I2C_RX_FULL_IE) == Set)
  {
    
  }
}

void I2C1_RxOverflowRQHandler(void)
{
  if(I2C_intStatusGet(I2C1, I2C_RX_OVF_IE) == Set)
  {
    printf("I2C Rx overflow,fifo count is %d\n",I2C_RxFIFOCountGet(I2C1));
  }
}

void I2C1_RxUnderflowRQHandler(void)
{
  if(I2C_intStatusGet(I2C1, I2C_RX_UNDER_IE) == Set)
  {
    printf("I2C Rx underflow,fifo count is %d\n",I2C_RxFIFOCountGet(I2C1));
  }
}

void I2C0_GPIO_init(void)
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

void I2C1_GPIO_init(void)
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

void I2C0_init(void)
{
  CLK_SetClkDivider(CLK_I2C0, CLK_DIV_1);
  CLK_ModuleSrc(CLK_I2C0, CLK_SRC_OSC40M);
  SYSCTRL_EnableModule(SYSCTRL_I2C0);
  
  I2C_init(I2C0, &masterConfig);
}

void I2C1_init(void)
{
  CLK_SetClkDivider(CLK_I2C1, CLK_DIV_1);
  CLK_ModuleSrc(CLK_I2C1, CLK_SRC_OSC40M);
  SYSCTRL_EnableModule(SYSCTRL_I2C1);
  
  I2C_init(I2C1, &slaveConfig);
}

void DMA_I2C0_Configure(void)
{
  
}

void DMA_I2C1_Configure(void)
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
        
    I2C0_GPIO_init();
    I2C1_GPIO_init();
    
    I2C0_init();
    I2C1_init();
    
    I2C_FIFOLevelSet(I2C0,&FIFOConfig);
    I2C_FIFOLevelSet(I2C1,&FIFOConfig);
    
    I2C_DMAWatermarkSet(I2C0, &DMAConfig);
    I2C_DMAWatermarkSet(I2C1, &DMAConfig);
    
    I2C_SCLHighLowDurationConfig(I2C0, &SCLDurationConfig, SYSTEM_CLOCK_FREQUENCE);
    I2C_SCLHighLowDurationConfig(I2C1, &SCLDurationConfig, SYSTEM_CLOCK_FREQUENCE);
    
    I2C_SDAHoldTimeConfig(I2C0, &SDAMasterHoldTimeConfig, SYSTEM_CLOCK_FREQUENCE);
    I2C_SDAHoldTimeConfig(I2C1, &SDASlaveHoldTimeConfig, SYSTEM_CLOCK_FREQUENCE);

    I2C_targetAddressSet(I2C0, I2C_SLAVE_ADDR,Single_Target_Addr);
    I2C_targetAddressSet(I2C1, I2C_MASTER_ADDR,Single_Target_Addr);
    
    I2C_DMAEnable(I2C0, Disable, Disable);
    I2C_DMAEnable(I2C1, Disable, Disable);

    I2C_enable(I2C0, Enable);
    I2C_enable(I2C1, Enable);
    
    /***I2C0 Tx Interrupt Configure***/
    I2C_intCallbackRegister(I2C0,I2C_TX_EMPTY_IE,I2C0_TxEmptyIRQHandler);
    I2C_intEnable(I2C0, I2C_TX_EMPTY_IE, Disable);
    I2C_intFlagClear(I2C0, I2C_TX_EMPTY_IE);
    
    I2C_intCallbackRegister(I2C0,I2C_TX_OVF_IE,I2C0_TxOverflowIRQHandler);
    I2C_intEnable(I2C0, I2C_TX_OVF_IE, Enable);
    I2C_intFlagClear(I2C0, I2C_TX_OVF_IE);
    
    /***I2C1 Rx Interrupt Configure***/
    I2C_intCallbackRegister(I2C1,I2C_RX_FULL_IE,I2C1_RxFullIRQHandler);
    I2C_intEnable(I2C1, I2C_RX_FULL_IE, Enable);
    I2C_intFlagClear(I2C1, I2C_RX_FULL_IE);
    
    I2C_intCallbackRegister(I2C1,I2C_RX_OVF_IE,I2C1_RxOverflowRQHandler);
    I2C_intEnable(I2C1, I2C_RX_OVF_IE, Enable);
    I2C_intFlagClear(I2C1, I2C_RX_OVF_IE);
    
    I2C_intCallbackRegister(I2C1,I2C_RX_UNDER_IE,I2C1_RxUnderflowRQHandler);
    I2C_intEnable(I2C1, I2C_RX_UNDER_IE, Enable);
    I2C_intFlagClear(I2C1, I2C_RX_UNDER_IE);
    
    INT_EnableIRQ(I2C0_IRQn);
    INT_EnableIRQ(I2C1_IRQn);

    printf("20k14x_app I2C start.\n");
    
    I2C_Dev_Operate(&fsm_port,&op_config);
    
    while(1);
}
