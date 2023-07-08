#include "clock_config.h"
#include "serial.h"

#include "uart_drv.h"
#include "int_drv.h"

/*
  PTA3 - PTC0   Master Tx
  PTA2 - PTC1   Master Rx
*/

#define INTERRUPT_CALLBACK 0

/*
  1:UART
  0:LIN
*/
#define UART_LIN_MODE 0

#define UART0_EN 1
#define UART2_EN 1

#define UART_0_2_EN (UART0_EN * UART2_EN)

#define User_Delay(cycle) for(volatile uint32_t i = 0;i < cycle;i++){}


#define J4_Pin1_Set() GPIO_B_Pin_Set(18)
#define J4_Pin1_Clr() GPIO_B_Pin_Clr(18)

#define J4_Pin2_Set() GPIO_B_Pin_Set(20)
#define J4_Pin2_Clr() GPIO_B_Pin_Clr(20)

#define J4_Pin3_Set() GPIO_B_Pin_Set(21)
#define J4_Pin3_Clr() GPIO_B_Pin_Clr(21)

#define J4_Pin4_Set() GPIO_C_Pin_Set(1)
#define J4_Pin4_Clr() GPIO_C_Pin_Clr(1)

#define J4_Pin5_Set() GPIO_C_Pin_Set(0)
#define J4_Pin5_Clr() GPIO_C_Pin_Clr(0)

#define J4_Pin6_Set() GPIO_C_Pin_Set(17)
#define J4_Pin6_Clr() GPIO_C_Pin_Clr(17)

#define J4_Pin7_Set() GPIO_C_Pin_Set(16)
#define J4_Pin7_Clr() GPIO_C_Pin_Clr(16)

#define J4_Pin8_Set() GPIO_B_Pin_Set(22)
#define J4_Pin8_Clr() GPIO_B_Pin_Clr(22)


#if UART0_EN
/* UART0 Registers definition */
#define UART0_BASE_ADDRESS 0x4006A000U

#define UART0_RBR *((volatile uint32_t*)(UART0_BASE_ADDRESS + 0x00U))
#define UART0_THR *((volatile uint32_t*)(UART0_BASE_ADDRESS + 0x00U))
#define UART0_DLL *((volatile uint32_t*)(UART0_BASE_ADDRESS + 0x00U))
#define UART0_DLH *((volatile uint32_t*)(UART0_BASE_ADDRESS + 0x04U))
#define UART0_IER *((volatile uint32_t*)(UART0_BASE_ADDRESS + 0x04U))
#define UART0_IIR *((volatile uint32_t*)(UART0_BASE_ADDRESS + 0x08U))
#define UART0_FCR *((volatile uint32_t*)(UART0_BASE_ADDRESS + 0x08U))
#define UART0_LCR *((volatile uint32_t*)(UART0_BASE_ADDRESS + 0x0CU))
#define UART0_AFCR *((volatile uint32_t*)(UART0_BASE_ADDRESS + 0x10U))
#define UART0_LSR *((volatile uint32_t*)(UART0_BASE_ADDRESS + 0x14U))
#define UART0_MSR *((volatile uint32_t*)(UART0_BASE_ADDRESS + 0x18U))
#define UART0_USR *((volatile uint32_t*)(UART0_BASE_ADDRESS + 0x7CU))
#define UART0_FD *((volatile uint32_t*)(UART0_BASE_ADDRESS + 0xC0U))
#define UART0_RAR *((volatile uint32_t*)(UART0_BASE_ADDRESS + 0xC4U))
#define UART0_TAR *((volatile uint32_t*)(UART0_BASE_ADDRESS + 0xC8U))
#define UART0_LCR_EXT *((volatile uint32_t*)(UART0_BASE_ADDRESS + 0xCCU))

#define UART0_LIN_CTL *((volatile uint32_t*)(UART0_BASE_ADDRESS + 0x100U))
#define UART0_LIN_RSP_LENGTH *((volatile uint32_t*)(UART0_BASE_ADDRESS + 0x104U))
#define UART0_LIN_PID_VALUE *((volatile uint32_t*)(UART0_BASE_ADDRESS + 0x108U))
#define UART0_LIN_CHECKSUM *((volatile uint32_t*)(UART0_BASE_ADDRESS + 0x10CU))
#define UART0_LIN_DEL_LENGTH *((volatile uint32_t*)(UART0_BASE_ADDRESS + 0x110U))
#define UART0_LIN_PID_FILTER_VAGUE *((volatile uint32_t*)(UART0_BASE_ADDRESS + 0x124U))
#define UART0_LIN_PID_FILTER_CTRL *((volatile uint32_t*)(UART0_BASE_ADDRESS + 0x128U))
#endif

#if UART2_EN
/* UART2 Registers definition */
#define UART2_BASE_ADDRESS 0x4006C000U

#define UART2_RBR *((volatile uint32_t*)(UART2_BASE_ADDRESS + 0x00U))
#define UART2_THR *((volatile uint32_t*)(UART2_BASE_ADDRESS + 0x00U))
#define UART2_DLL *((volatile uint32_t*)(UART2_BASE_ADDRESS + 0x00U))
#define UART2_DLH *((volatile uint32_t*)(UART2_BASE_ADDRESS + 0x04U))
#define UART2_IER *((volatile uint32_t*)(UART2_BASE_ADDRESS + 0x04U))
#define UART2_IIR *((volatile uint32_t*)(UART2_BASE_ADDRESS + 0x08U))
#define UART2_FCR *((volatile uint32_t*)(UART2_BASE_ADDRESS + 0x08U))
#define UART2_LCR *((volatile uint32_t*)(UART2_BASE_ADDRESS + 0x0CU))
#define UART2_AFCR *((volatile uint32_t*)(UART2_BASE_ADDRESS + 0x10U))
#define UART2_LSR *((volatile uint32_t*)(UART2_BASE_ADDRESS + 0x14U))
#define UART2_MSR *((volatile uint32_t*)(UART2_BASE_ADDRESS + 0x18U))
#define UART2_USR *((volatile uint32_t*)(UART2_BASE_ADDRESS + 0x7CU))
#define UART2_FD *((volatile uint32_t*)(UART2_BASE_ADDRESS + 0xC0U))
#define UART2_RAR *((volatile uint32_t*)(UART2_BASE_ADDRESS + 0xC4U))
#define UART2_TAR *((volatile uint32_t*)(UART2_BASE_ADDRESS + 0xC8U))
#define UART2_LCR_EXT *((volatile uint32_t*)(UART2_BASE_ADDRESS + 0xCCU))

#define UART2_LIN_CTL *((volatile uint32_t*)(UART2_BASE_ADDRESS + 0x100U))
#define UART2_LIN_RSP_LENGTH *((volatile uint32_t*)(UART2_BASE_ADDRESS + 0x104U))
#define UART2_LIN_PID_VALUE *((volatile uint32_t*)(UART2_BASE_ADDRESS + 0x108U))
#define UART2_LIN_CHECKSUM *((volatile uint32_t*)(UART2_BASE_ADDRESS + 0x10CU))
#define UART2_LIN_DEL_LENGTH *((volatile uint32_t*)(UART2_BASE_ADDRESS + 0x110U))
#define UART2_LIN_PID_FILTER_VAGUE *((volatile uint32_t*)(UART2_BASE_ADDRESS + 0x124U))
#define UART2_LIN_PID_FILTER_CTRL *((volatile uint32_t*)(UART2_BASE_ADDRESS + 0x128U))
#endif

static uart_reg_t * uart0RegPtr = (uart_reg_t *)UART0_BASE_ADDR;
//static uart_reg_t * uart1RegPtr = (uart_reg_t *)UART1_BASE_ADDR;
static uart_reg_t * uart2RegPtr = (uart_reg_t *)UART2_BASE_ADDR;
//static uart_reg_t * uart3RegPtr = (uart_reg_t *)UART3_BASE_ADDR;
//static uart_reg_t * uart4RegPtr = (uart_reg_t *)UART4_BASE_ADDR;

//static uart_reg_w_t * uart0WRegPtr = (uart_reg_w_t *)UART0_BASE_ADDR;
//static uart_reg_w_t * uart1WRegPtr = (uart_reg_w_t *)UART1_BASE_ADDR;
//static uart_reg_w_t * uart2WRegPtr = (uart_reg_w_t *)UART2_BASE_ADDR;
//static uart_reg_w_t * uart3WRegPtr = (uart_reg_w_t *)UART3_BASE_ADDR;
//static uart_reg_w_t * uart4WRegPtr = (uart_reg_w_t *)UART4_BASE_ADDR;

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
    
    SYSCTRL_EnableModule(SYSCTRL_PORTA);
    SYSCTRL_EnableModule(SYSCTRL_PORTB);
    SYSCTRL_EnableModule(SYSCTRL_PORTC);
    SYSCTRL_EnableModule(SYSCTRL_PORTD);
    SYSCTRL_EnableModule(SYSCTRL_PORTE);
    SYSCTRL_EnableModule(SYSCTRL_GPIO);
    
    PORT_PinmuxConfig(PORT_B, GPIO_18, PTB18_GPIO);
    GPIO_SetPinDir(PORT_B, GPIO_18, GPIO_OUTPUT);
    
    PORT_PinmuxConfig(PORT_B, GPIO_20, PTB20_GPIO);
    GPIO_SetPinDir(PORT_B, GPIO_20, GPIO_OUTPUT);
    
    PORT_PinmuxConfig(PORT_D, GPIO_3, PTD3_GPIO);
    GPIO_SetPinDir(PORT_D, GPIO_3, GPIO_INPUT);
}

#if UART0_EN
void UART0_Param_Init(void)
{
  CLK_SetClkDivider(CLK_UART0, CLK_DIV_1);
  CLK_ModuleSrc(CLK_UART0, CLK_SRC_OSC40M);
  SYSCTRL_ResetModule(SYSCTRL_UART0);
  SYSCTRL_EnableModule(SYSCTRL_UART0);
  
  PORT_PinmuxConfig(PORT_A, GPIO_2, PTA2_UART0_RX);
  PORT_PinmuxConfig(PORT_A, GPIO_3, PTA3_UART0_TX);
  
  UART_FIFOConfig_t uart0FIFOConfig =
  {
    ENABLE,
    ENABLE,
    ENABLE,
    ENABLE,
    UART_TX_FIFO_CHAR_2,
    UART_RX_FIFO_LESS_2
  };
  UART_FIFOConfig(UART0_ID, &uart0FIFOConfig);
  
  UART_IdleDetectConfig_t uart0IdleConfig =
  {
    ENABLE,
    UART_IDLE_DETECT_LENGTH_8
  };
  UART_IdleDetectConfig(UART0_ID,&uart0IdleConfig);
  
  #if UART_LIN_MODE

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

  #else

  UART_LinConfig_t Lin0_Config = 
  {
    115200U,
    40000000U,
    UART_LIN_MASTER,
    ENABLE,
    ENABLE
  };
  UART_LinConfig(UART0_ID, &Lin0_Config);

  #endif
}

#endif

#if UART2_EN
void UART2_Param_Init(void)
{
  CLK_SetClkDivider(CLK_UART2, CLK_DIV_1);
  CLK_ModuleSrc(CLK_UART2, CLK_SRC_OSC40M);
  SYSCTRL_ResetModule(SYSCTRL_UART2);
  SYSCTRL_EnableModule(SYSCTRL_UART2);

  PORT_PinmuxConfig(PORT_C, GPIO_0, PTC0_UART2_RX);
  PORT_PinmuxConfig(PORT_C, GPIO_1, PTC1_UART2_TX);
  
  UART_IdleDetectConfig_t uart2IdleConfig =
  {
    ENABLE,
    UART_IDLE_DETECT_LENGTH_8
  };
    
  UART_IdleDetectConfig(UART2_ID,&uart2IdleConfig);

  UART_FIFOConfig_t uart2FIFOConfig =
  {
    ENABLE,
    ENABLE,
    ENABLE,
    ENABLE,
    UART_TX_FIFO_CHAR_2,
    UART_RX_FIFO_LESS_2
  };

  UART_FIFOConfig(UART2_ID, &uart2FIFOConfig);
  
  #if UART_LIN_MODE
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

  #else

  UART_LinConfig_t Lin2_Config = 
  {
    115200U,
    40000000U,
    UART_LIN_SLAVE,
    ENABLE,
    ENABLE
  };

  UART_LinConfig(UART2_ID, &Lin2_Config);

  #endif
}

#endif

#if UART0_EN
void UART0_DriverIRQHandler(void)
{
  static int uart0_common_sign = 0x00;
  if(uart0_common_sign)
  {
    J4_Pin1_Clr();
    uart0_common_sign = 0x00;
  }
  else
  {
    J4_Pin1_Set();
    uart0_common_sign = 0x01;
  }
  
  uint32_t interrupt_id = uart0RegPtr->UART_IIR_FCR.UART_IIR.IID;
  /*THR empty*/
  if(interrupt_id == 0x02)
  {

  }
  /*Received data available*/
  else if(interrupt_id == 0x04)
  {
    
  }
  /*Character time out*/
  else if(interrupt_id == 0x0C)
  {
    
  }
  /*Receiver line status*/
  else if(interrupt_id == 0x06)
  {
    
  }
  /*CTS flag assert*/
  else if(interrupt_id == 0x00)
  {
    
  }
  /*No interrupt pending*/
  else if(interrupt_id == 0x01)
  {
    
  }
  /*Busy detect*/
  else if((interrupt_id == 0x0B) && (uart0RegPtr->UART_USR.BUSY == 0x01))
  {
    
  }
  /*LIN: header operation done*/
  else if((interrupt_id == 0x0D) && (uart0RegPtr->UART_LSR.HEADER_OP_DONE == 0x01))
  {
    
  }
  /*LIN: response operation done*/
  else if((interrupt_id == 0x0E) && (uart0RegPtr->UART_LSR.RSP_OP_DONE == 0x01))
  {
    
  }
}
#endif

#if UART2_EN
void UART2_DriverIRQHandler(void)
{
  static int uart2_common_sign = 0x00;
  if(uart2_common_sign)
  {
    J4_Pin2_Clr();
    uart2_common_sign = 0x00;
  }
  else
  {
    J4_Pin2_Set();
    uart2_common_sign = 0x01;
  }  
  
  uint32_t interrupt_id = uart2RegPtr->UART_IIR_FCR.UART_IIR.IID;

  /*CTS flag assert*/
  if(interrupt_id == 0x00)
  {
    
  }
  /*No interrupt pending*/
  else if(interrupt_id == 0x01)
  {
    
  }
  /*THR empty*/
  else if(interrupt_id == 0x02)
  {
    
  }
  /*Received data available*/
  else if(interrupt_id == 0x04)
  {
    
  }
  /*Receiver line status*/
  else if(interrupt_id == 0x06)
  {
    
  }
  /*Busy detect*/
  else if((interrupt_id == 0x0B) && (uart2RegPtr->UART_USR.BUSY == 0x01))
  {
    
  }
  /*Character time out*/
  else if(interrupt_id == 0x0C)
  {
    
  }
  /*LIN: header operation done*/
  else if((interrupt_id == 0x0D) && (uart2RegPtr->UART_LSR.HEADER_OP_DONE == 0x01))
  {
    
  }
  /*LIN: response operation done*/
  else if((interrupt_id == 0x0E) && (uart2RegPtr->UART_LSR.RSP_OP_DONE == 0x01))
  {
    
  }
}
#endif

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
#if UART0_EN
    UART0_Param_Init();
#endif

#if UART2_EN
    UART2_Param_Init();
#endif

    /************UART Interrupt************/
#if UART0_EN
    UART_IntMask(UART0_ID, UART_INT_RBFI, MASK);
    UART_IntMask(UART0_ID, UART_INT_TBEI, MASK);
    UART_IntMask(UART0_ID, UART_INT_LSI, MASK);
    UART_IntMask(UART0_ID, UART_INT_MODEM, MASK);
    UART_IntMask(UART0_ID, UART_INT_BYDET, MASK);
    UART_IntMask(UART0_ID, UART_INT_RCVRTO, MASK);
    UART_IntMask(UART0_ID, UART_INT_HEADER_DONE, UNMASK);
    UART_IntMask(UART0_ID, UART_INT_RSP_DONE, MASK);
    UART_IntMask(UART0_ID, UART_INT_ASYNC, MASK);
#endif

#if UART2_EN
    UART_IntMask(UART2_ID, UART_INT_RBFI, MASK);
    UART_IntMask(UART2_ID, UART_INT_TBEI, MASK);
    UART_IntMask(UART2_ID, UART_INT_LSI, MASK);
    UART_IntMask(UART2_ID, UART_INT_MODEM, MASK);
    UART_IntMask(UART2_ID, UART_INT_BYDET, MASK);
    UART_IntMask(UART2_ID, UART_INT_RCVRTO, MASK);
    UART_IntMask(UART2_ID, UART_INT_HEADER_DONE, UNMASK);
    UART_IntMask(UART2_ID, UART_INT_RSP_DONE, MASK);
    UART_IntMask(UART2_ID, UART_INT_ASYNC, MASK);
#endif

#if UART0_EN
    INT_EnableIRQ(UART0_IRQn);
#endif

#if UART2_EN
    INT_EnableIRQ(UART2_IRQn);
#endif
    
    printf("20k14x_app UART start.\n");

    while(uart0RegPtr->UART_USR.BUSY == 0x01)
    {
      uart0RegPtr->UART_IIR_FCR.UART_FCR.RFIFOR = 0x01;
      uart0RegPtr->UART_IIR_FCR.UART_FCR.XFIFOR = 0x01;
    }
    while(uart2RegPtr->UART_USR.BUSY == 0x01)
    {
      uart2RegPtr->UART_IIR_FCR.UART_FCR.RFIFOR = 0x01;
      uart2RegPtr->UART_IIR_FCR.UART_FCR.XFIFOR = 0x01;
    }
    
//    #define RESP_BUFFER_LEN 8
//    uint8_t resp_buffer[RESP_BUFFER_LEN] = {0};
//    
//    UART_LinResponse_t Lin2_response =
//    {
//      UART_LIN_CHECKSUM_CLASSIC,
//      RESP_BUFFER_LEN,
//      resp_buffer
//    };
//    
//    UART_LinSendResponse(UART2_ID,&Lin2_response);
        
    while(1)
    {
      if(GPIO_HIGH ==  GPIO_ReadPinLevel(PORT_D, GPIO_3))
      {
          UART_LinHeader_t Lin0_header = 
          {
              0x1F,
              0x0F,
              0x01
          };
          
          UART_LinSendHeader(UART0_ID, &Lin0_header);
          User_Delay(5000000);
      }
    }
}
