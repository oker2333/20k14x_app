#include "clock_config.h"
#include "serial.h"

#include "uart_drv.h"
#include "int_drv.h"

void Ex_Module_Init(void)
{
    CLK_SetClkDivider(CLK_PORTA, CLK_DIV_1);
    CLK_SetClkDivider(CLK_PORTB, CLK_DIV_1);
    CLK_SetClkDivider(CLK_PORTC, CLK_DIV_1);
    CLK_SetClkDivider(CLK_PORTD, CLK_DIV_1);
    CLK_SetClkDivider(CLK_PORTE, CLK_DIV_1);
    CLK_SetClkDivider(CLK_GPIO, CLK_DIV_1);
    
    CLK_ModuleSrc(CLK_PORTA, CLK_SRC_OSC40M);
    CLK_ModuleSrc(CLK_PORTB, CLK_SRC_OSC40M);
    CLK_ModuleSrc(CLK_PORTC, CLK_SRC_OSC40M);
    CLK_ModuleSrc(CLK_PORTD, CLK_SRC_OSC40M);
    CLK_ModuleSrc(CLK_PORTE, CLK_SRC_OSC40M);
    CLK_ModuleSrc(CLK_GPIO, CLK_SRC_OSC40M);
                
    SYSCTRL_ResetModule(SYSCTRL_PORTA);
    SYSCTRL_ResetModule(SYSCTRL_PORTB);
    SYSCTRL_ResetModule(SYSCTRL_PORTC);
    SYSCTRL_ResetModule(SYSCTRL_PORTD);
    SYSCTRL_ResetModule(SYSCTRL_PORTE);
    SYSCTRL_ResetModule(SYSCTRL_GPIO);
    
    SYSCTRL_EnableModule(SYSCTRL_PORTA);
    SYSCTRL_EnableModule(SYSCTRL_PORTB);
    SYSCTRL_EnableModule(SYSCTRL_PORTC);
    SYSCTRL_EnableModule(SYSCTRL_PORTD);
    SYSCTRL_EnableModule(SYSCTRL_PORTE);
    SYSCTRL_EnableModule(SYSCTRL_GPIO);
}

void UART0_Param_Init(void)
{
  CLK_SetClkDivider(CLK_UART0, CLK_DIV_1);
  CLK_ModuleSrc(CLK_UART0, CLK_SRC_OSC40M);
  SYSCTRL_ResetModule(SYSCTRL_UART0);
  SYSCTRL_EnableModule(SYSCTRL_UART0);
  
  PORT_PinmuxConfig(PORT_C, GPIO_2, PTC2_UART0_RX);
  PORT_PinmuxConfig(PORT_C, GPIO_3, PTC3_UART0_TX);
  
  UART_FIFOConfig_t uart0FIFOConfig =
  {
    ENABLE,
    ENABLE,
    ENABLE,
    UART_TX_FIFO_CHAR_2,
    UART_RX_FIFO_LESS_2
  };
  
  UART_FIFOConfig(UART0_ID, &uart0FIFOConfig);
  
  UART_Config_t uart0Config = 
  {
    115200U,
    UART_DATABITS_8,
    UART_PARITY_NONE,
    UART_STOPBITS_1,
    DISABLE,
    40000000U
  };
  
  UART_Init(UART0_ID, &uart0Config);
}

void UART2_Param_Init(void)
{
  CLK_SetClkDivider(CLK_UART2, CLK_DIV_1);
  CLK_ModuleSrc(CLK_UART2, CLK_SRC_OSC40M);
  SYSCTRL_ResetModule(SYSCTRL_UART2);
  SYSCTRL_EnableModule(SYSCTRL_UART2);
  
  PORT_PinmuxConfig(PORT_C, GPIO_0, PTC0_UART2_RX);
  PORT_PinmuxConfig(PORT_C, GPIO_1, PTC1_UART2_TX);
  
  UART_FIFOConfig_t uart2FIFOConfig =
  {
    ENABLE,
    ENABLE,
    ENABLE,
    UART_TX_FIFO_CHAR_2,
    UART_RX_FIFO_LESS_2
  };
  
  UART_FIFOConfig(UART2_ID, &uart2FIFOConfig);
  
  UART_Config_t uart2Config = 
  {
    115200U,
    UART_DATABITS_8,
    UART_PARITY_NONE,
    UART_STOPBITS_1,
    DISABLE,
    40000000U
  };
  
  UART_Init(UART2_ID, &uart2Config);
}

int main(void)
{
#if OSC40M_ENABLE
    OSC40M_ClockInit();
#else
    PLL80M_ClockInit();
#endif
    
    Ex_Module_Init();
    Ex_BoardUartInit();
    
    /************UART Configure************/
    
    UART0_Param_Init();    
    UART2_Param_Init();
    
//    INT_EnableIRQ(UART0_IRQn);
//    INT_EnableIRQ(UART2_IRQn);
    
    printf("20k14x_app UART start.\n");

    while(1)
    {
      if(SET == UART_GetLineStatus(UART0_ID, UART_LINESTA_TEMT))
      {
//        UART_SendByte(UART0_ID, 0x55);
      }
      
      if(SET == UART_GetLineStatus(UART2_ID, UART_LINESTA_TEMT))
      {
        UART_SendByte(UART2_ID, 0xAA);
      }
    }
}