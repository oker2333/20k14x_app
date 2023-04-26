/**************************************************************************************************/
/**
 * @file     serial.c
 * @brief    Example serial file.
 * @version  V1.0.0
 * @date     December-2022
 * @author   Zhixin Semiconductor
 *
 * @note
 * Copyright (C) 2021-2023 Zhixin Semiconductor Ltd. All rights reserved.
 *
 **************************************************************************************************/
#include "serial.h"

/* UART configuration*/
 static const UART_Config_t uartConfig = 
{
    .baudRate = 9600,               /* UART baud rate: 9600 */
    .dataBits = UART_DATABITS_8,    /* UART data bits length: 8 bits */
    .parity = UART_PARITY_NONE,     /* UART parity: none */
    .stopBits = UART_STOPBITS_1,    /* UART stop bits length: 1 bit */
    .autoFlowControl = DISABLE,     /* UART flow control: disable */
    .oscFreq = 40000000             /* UART function clock freq: 40000000 */
};

 void Ex_BoardUartInit(void)
{
    /* Set and enable UART clock */
    CLK_ModuleSrc(CLK_UART1, CLK_SRC_OSC40M);
    CLK_SetClkDivider(CLK_UART1, CLK_DIV_1);
    SYSCTRL_EnableModule(SYSCTRL_UART1);
    
    /* Set and enable PORT clock */
    CLK_ModuleSrc(CLK_PORTC, CLK_SRC_OSC40M);
    SYSCTRL_EnableModule(SYSCTRL_PORTC);

    /* Set port pin for UART */
    PORT_PinmuxConfig(PORT_C, GPIO_6, PTC6_UART1_RX);
    PORT_PinmuxConfig(PORT_C, GPIO_7, PTC7_UART1_TX);

    /* Inital UART */
    UART_Init(UART1_ID, &uartConfig);

    /*Set printf not buffered*/
#if defined(__GNUC__) | defined(__ghs__)
    setbuf(stdout, NULL);
#endif
}
