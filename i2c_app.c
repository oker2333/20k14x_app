
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

#define OSC40M_ENABLE 1

#define I2C_MASTER_ADDR 0x0F
#define I2C_SLAVE_ADDR 0x1F

I2C_config_t masterConfig = 
{
  I2C_7BitAddr,
  I2C_MASTER_ADDR,
  I2C_Standard,
  Master_Slave_Mode,
  Enable
};

I2C_config_t slaveConfig = 
{
  I2C_7BitAddr,
  I2C_SLAVE_ADDR,
  I2C_Standard,
  Master_Slave_Mode,
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
  CLK_ModuleSrc(CLK_I2C0, CLK_SRC_OSC40M);
  SYSCTRL_EnableModule(SYSCTRL_I2C0);
  
  I2C_init(I2C0, &masterConfig);
}

void I2C1_init(void)
{
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

void I2C0_Interrupt_Handler(void)
{
  
}

void I2C1_Interrupt_Handler(void)
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
    
    I2C_DMAWatermarkSet(I2C0,&DMAConfig);
    I2C_DMAWatermarkSet(I2C1,&DMAConfig);
    
    I2C_enable(I2C0,Enable);
    I2C_enable(I2C1,Enable);
    
    I2C_DMAEnable(I2C0, Disbale, Disbale);
    I2C_DMAEnable(I2C1, Disbale, Disbale);
    
    I2C_transmitCmd(I2C0, Normal_Dest_Addr, I2C_SLAVE_ADDR, 0x0A, I2C_RESET_STOP_DIS);
    I2C_transmitData(I2C0, 0x0B, I2C_RESET_STOP_EN);
    I2C_transmitData(I2C0, 0x0C, I2C_STOP_EN);

    /* Print example name*/
    printf("20k14x_app I2C start.\n");
    
    while(1);
}
