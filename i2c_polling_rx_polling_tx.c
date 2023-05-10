
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

#define Polling_Tx 0
#define Interrupt_Tx 1

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

I2C_SCLDurationParam_t SCLDurationConfig = 
{
  5000,
  5000
};

I2C_holdTimeParam_t SDAMasterHoldTimeConfig = 
{
  2500,
  0
};

I2C_holdTimeParam_t SDASlaveHoldTimeConfig = 
{
  2500,
  0
};

#if Interrupt_Tx

void I2C0_TxEmptyIRQHandler(void)
{
  if(I2C_intStatusGet(I2C0, TX_EMPTY_IE) == Set)
  {
    static uint8_t count = 0x00;
    I2C_transmitData(I2C0, ++count, I2C_RESET_STOP_DIS);
  }
}

#endif

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
    
#if Interrupt_Tx
    
    I2C_intCallbackRegister(I2C0,TX_EMPTY_IE,I2C0_TxEmptyIRQHandler);
    I2C_intEnable(I2C0, TX_EMPTY_IE, Enable);
    I2C_intFlagClear(I2C0, TX_EMPTY_IE);
    INT_EnableIRQ(I2C0_IRQn);
    
#endif

#if Polling_Tx
        
    for(uint32_t count = 0;count <= 0xFF;count++)
    {
      I2C_restartStop_t cmd = I2C_RESET_STOP_DIS;
      if(count == 255)
      {
        cmd = I2C_STOP_EN;
      }
      while(I2C_TxFIFOCountGet(I2C0) == I2C_TX_FIFO_DEPTH);
      I2C_transmitData(I2C0, count, cmd);
    }
    
#endif

    printf("20k14x_app I2C start.\n");
    
    while(1);
}
