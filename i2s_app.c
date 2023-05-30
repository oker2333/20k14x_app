#include "clock_config.h"
#include "serial.h"

#include "i2s_drv.h"
#include "int_drv.h"

#define OSC40M_ENABLE 1

I2S_ChannelsEnableConfig_t I2S0ChannelsConfigStruct =
{
    I2S_CHANNEL_ENABLE,                              /* I2S channel0 transmit function */
    I2S_CHANNEL_ENABLE,                              /* I2S channel1 transmit function */
    I2S_CHANNEL_ENABLE,                             /* I2S channel2 receive function */
    I2S_CHANNEL_ENABLE,                             /* I2S channel3 receive function */
};

/* I2S config structure*/
I2S_Config_t i2s0_transmit_config =
{
  .mode = I2S_MODE_SLAVE,                                   /* I2S master mode */
  .i2sNumBclkGate = I2S_NO_BCLK_GATING,                      /* No gated after the number of bclk cycles */
  .i2sBclkNum = I2S_BCLK_32_CYCLES,                          /* 32 number of bclk cycles during left or right word line */
  .masterClkDiv = 19,                                         /* Actual division value is (masterClkDiv+1)*2 */
  .audioResolution = I2S_AUDIO_RESOLUTION_32BIT,             /* Configure I2S channel 32 bit audio resolution */
  .rxfifoFullTriggerLevel = I2S_TRIGGER_LEVEL_DEPTH_15,      /* Configure I2S channel receive FIFO full trigger level 15 */
  .txfifoEmptyTriggerLevel = I2S_TRIGGER_LEVEL_DEPTH_8,      /* Configure I2S channel transmit FIFO empty trigger level 8 */
};

I2S_Config_t i2s0_receive_config =
{
  .mode = I2S_MODE_SLAVE,                                   /* I2S master mode */
  .i2sNumBclkGate = I2S_NO_BCLK_GATING,                      /* No gated after the number of bclk cycles */
  .i2sBclkNum = I2S_BCLK_32_CYCLES,                          /* 32 number of bclk cycles during left or right word line */
  .masterClkDiv = 19,                                         /* Actual division value is (masterClkDiv+1)*2 */
  .audioResolution = I2S_AUDIO_RESOLUTION_32BIT,             /* Configure I2S channel 32 bit audio resolution */
  .rxfifoFullTriggerLevel = I2S_TRIGGER_LEVEL_DEPTH_15,      /* Configure I2S channel receive FIFO full trigger level 15 */
  .txfifoEmptyTriggerLevel = I2S_TRIGGER_LEVEL_DEPTH_8,      /* Configure I2S channel transmit FIFO empty trigger level 8 */
};

I2S_ChannelsEnableConfig_t I2S1ChannelsConfigStruct =
{
    I2S_CHANNEL_ENABLE,                              /* I2S channel0 transmit function */
    I2S_CHANNEL_ENABLE,                              /* I2S channel1 transmit function */
    I2S_CHANNEL_ENABLE,                              /* I2S channel2 receive function */
    I2S_CHANNEL_ENABLE,                              /* I2S channel3 receive function */
};

I2S_Config_t i2s1_transmit_config =
{
  .mode = I2S_MODE_SLAVE,                                   /* I2S master mode */
  .i2sNumBclkGate = I2S_NO_BCLK_GATING,                      /* No gated after the number of bclk cycles */
  .i2sBclkNum = I2S_BCLK_32_CYCLES,                          /* 32 number of bclk cycles during left or right word line */
  .masterClkDiv = 19,                                         /* Actual division value is (masterClkDiv+1)*2 */
  .audioResolution = I2S_AUDIO_RESOLUTION_32BIT,             /* Configure I2S channel 32 bit audio resolution */
  .rxfifoFullTriggerLevel = I2S_TRIGGER_LEVEL_DEPTH_15,      /* Configure I2S channel receive FIFO full trigger level 15 */
  .txfifoEmptyTriggerLevel = I2S_TRIGGER_LEVEL_DEPTH_8,      /* Configure I2S channel transmit FIFO empty trigger level 8 */
};

I2S_Config_t i2s1_receive_config =
{
  .mode = I2S_MODE_SLAVE,                                   /* I2S master mode */
  .i2sNumBclkGate = I2S_NO_BCLK_GATING,                      /* No gated after the number of bclk cycles */
  .i2sBclkNum = I2S_BCLK_32_CYCLES,                          /* 32 number of bclk cycles during left or right word line */
  .masterClkDiv = 19,                                         /* Actual division value is (masterClkDiv+1)*2 */
  .audioResolution = I2S_AUDIO_RESOLUTION_32BIT,             /* Configure I2S channel 32 bit audio resolution */
  .rxfifoFullTriggerLevel = I2S_TRIGGER_LEVEL_DEPTH_15,      /* Configure I2S channel receive FIFO full trigger level 15 */
  .txfifoEmptyTriggerLevel = I2S_TRIGGER_LEVEL_DEPTH_8,      /* Configure I2S channel transmit FIFO empty trigger level 8 */
};

/***I2S0 init***/

void Ex_I2S0TxCyclicCallback(void)
{

}

void Ex_I2S0RxCyclicCallback(void)
{

}

void Ex_I2S0TxEmptyChannel0Callback(void)
{

}

void Ex_I2S0TxOverflowChannel0Callback(void)
{
    printf("I2S0 Channel0 TxFIFO Overflow\n");
}

void Ex_I2S0TxEmptyChannel1Callback(void)
{

}

void Ex_I2S0TxOverflowChannel1Callback(void)
{
    printf("I2S0 Channel1 TxFIFO Overflow\n");
}

void Ex_I2S0TxEmptyChannel2Callback(void)
{

}

void Ex_I2S0TxOverflowChannel2Callback(void)
{
    printf("I2S0 Channel2 TxFIFO Overflow\n");
}

void Ex_I2S0TxEmptyChannel3Callback(void)
{

}

void Ex_I2S0TxOverflowChannel3Callback(void)
{
    printf("I2S0 Channel3 TxFIFO Overflow\n");
}

/***I2S1 init***/

void Ex_I2S1TxCyclicCallback(void)
{

}

void Ex_I2S1RxCyclicCallback(void)
{

}

void Ex_I2S1RxOverflowChannel0Callback(void)
{
    printf("I2S1 Channel0 RxFIFO Overflow\n");
}

void Ex_I2S1RxAvailableChannel0Callback(void)
{

}

void Ex_I2S1RxOverflowChannel1Callback(void)
{
    printf("I2S1 Channel1 RxFIFO Overflow\n");
}

void Ex_I2S1RxAvailableChannel1Callback(void)
{

}

void Ex_I2S1RxOverflowChannel2Callback(void)
{
    printf("I2S1 Channel2 RxFIFO Overflow\n");
}

void Ex_I2S1RxAvailableChannel2Callback(void)
{

}

void Ex_I2S1RxOverflowChannel3Callback(void)
{
    printf("I2S1 Channel3 RxFIFO Overflow\n");
}

void Ex_I2S1RxAvailableChannel3Callback(void)
{

}

void Ex_GPIO_Init(void)
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

    /*I2S0 PIN MUX*/
    PORT_PinmuxConfig(PORT_A, GPIO_16, PTA16_I2S0_WS);
    PORT_PinmuxConfig(PORT_A, GPIO_15, PTA15_I2S0_SCLK);

    PORT_PinmuxConfig(PORT_B, GPIO_11, PTB11_I2S0_SD0);
    PORT_PinmuxConfig(PORT_B, GPIO_10, PTB10_I2S0_SD1);
    PORT_PinmuxConfig(PORT_B, GPIO_9, PTB9_I2S0_SD2);
    PORT_PinmuxConfig(PORT_B, GPIO_8, PTB8_I2S0_SD3);

    /*I2S1 PIN MUX*/
    PORT_PinmuxConfig(PORT_E, GPIO_19, PTE19_I2S1_SD0);
    PORT_PinmuxConfig(PORT_E, GPIO_20, PTE20_I2S1_SD1);
    PORT_PinmuxConfig(PORT_E, GPIO_21, PTE21_I2S1_SD2);
    PORT_PinmuxConfig(PORT_E, GPIO_22, PTE22_I2S1_SD3);

    PORT_PinmuxConfig(PORT_E, GPIO_23, PTE23_I2S1_SCLK);
    PORT_PinmuxConfig(PORT_E, GPIO_24, PTE24_I2S1_WS);
}

int main(void)
{
#if OSC40M_ENABLE
    OSC40M_ClockInit();
#else
    PLL80M_ClockInit();
#endif
    
    Ex_BoardUartInit();

    /******I2S0 Configure******/
    I2S_Init(I2S_ID_0, &i2s0_transmit_config);
    I2S_EnableTransmitter(I2S_ID_0, ENABLE);
    I2S_EnableChannelTx(I2S_ID_0, I2S0ChannelsConfigStruct);

    /*I2S0 Channel0 Interrupt*/
    I2S_InstallCallBackFunc(I2S_ID_0, I2S_CHANNEL0_ID, I2S_TXFIFO_EMPTY_INT,Ex_I2S0TxEmptyChannel0Callback);
    I2S_IntMask(I2S_ID_0, I2S_CHANNEL0_ID, I2S_TXFIFO_EMPTY_INT,UNMASK);
    I2S_InstallCallBackFunc(I2S_ID_0, I2S_CHANNEL0_ID, I2S_TXFIFO_OVERRUN_INT,Ex_I2S0TxOverflowChannel0Callback);
    I2S_IntMask(I2S_ID_0, I2S_CHANNEL0_ID, I2S_TXFIFO_OVERRUN_INT,UNMASK);

    /*I2S0 Channel1 Interrupt*/
    I2S_InstallCallBackFunc(I2S_ID_0, I2S_CHANNEL1_ID, I2S_TXFIFO_EMPTY_INT,Ex_I2S0TxEmptyChannel1Callback);
    I2S_IntMask(I2S_ID_0, I2S_CHANNEL1_ID, I2S_TXFIFO_EMPTY_INT,UNMASK);
    I2S_InstallCallBackFunc(I2S_ID_0, I2S_CHANNEL1_ID, I2S_TXFIFO_OVERRUN_INT,Ex_I2S0TxOverflowChannel1Callback);
    I2S_IntMask(I2S_ID_0, I2S_CHANNEL1_ID, I2S_TXFIFO_OVERRUN_INT,UNMASK);

    /*I2S0 Channel2 Interrupt*/
    I2S_InstallCallBackFunc(I2S_ID_0, I2S_CHANNEL2_ID, I2S_TXFIFO_EMPTY_INT,Ex_I2S0TxEmptyChannel2Callback);
    I2S_IntMask(I2S_ID_0, I2S_CHANNEL2_ID, I2S_TXFIFO_EMPTY_INT,UNMASK);
    I2S_InstallCallBackFunc(I2S_ID_0, I2S_CHANNEL2_ID, I2S_TXFIFO_OVERRUN_INT,Ex_I2S0TxOverflowChannel2Callback);
    I2S_IntMask(I2S_ID_0, I2S_CHANNEL2_ID, I2S_TXFIFO_OVERRUN_INT,UNMASK);

    /*I2S0 Channel3 Interrupt*/
    I2S_InstallCallBackFunc(I2S_ID_0, I2S_CHANNEL3_ID, I2S_TXFIFO_EMPTY_INT,Ex_I2S0TxEmptyChannel3Callback);
    I2S_IntMask(I2S_ID_0, I2S_CHANNEL3_ID, I2S_TXFIFO_EMPTY_INT,UNMASK);
    I2S_InstallCallBackFunc(I2S_ID_0, I2S_CHANNEL3_ID, I2S_TXFIFO_OVERRUN_INT,Ex_I2S0TxOverflowChannel3Callback);
    I2S_IntMask(I2S_ID_0, I2S_CHANNEL3_ID, I2S_TXFIFO_OVERRUN_INT,UNMASK);

    INT_EnableIRQ(I2S0_IRQn);

    /******I2S1 Configure******/
    I2S_Init(I2S_ID_1, &i2s1_receive_config);
    I2S_EnableReceiver(I2S_ID_1, ENABLE);
    I2S_EnableChannelRx(I2S_ID_1, I2S1ChannelsConfigStruct);

    /*I2S1 Channel0 Interrupt*/
    I2S_InstallCallBackFunc(I2S_ID_1, I2S_CHANNEL0_ID, I2S_RXFIFO_DATA_AVAILIABLE_INT,Ex_I2S1RxAvailableChannel0Callback);
    I2S_IntMask(I2S_ID_1, I2S_CHANNEL0_ID, I2S_RXFIFO_DATA_AVAILIABLE_INT,UNMASK);
    I2S_InstallCallBackFunc(I2S_ID_1, I2S_CHANNEL0_ID, I2S_RXFIFO_OVERRUN_INT,Ex_I2S1RxOverflowChannel0Callback);
    I2S_IntMask(I2S_ID_1, I2S_CHANNEL0_ID, I2S_RXFIFO_OVERRUN_INT,UNMASK);

    /*I2S1 Channel1 Interrupt*/
    I2S_InstallCallBackFunc(I2S_ID_1, I2S_CHANNEL1_ID, I2S_RXFIFO_DATA_AVAILIABLE_INT,Ex_I2S1RxAvailableChannel1Callback);
    I2S_IntMask(I2S_ID_1, I2S_CHANNEL1_ID, I2S_RXFIFO_DATA_AVAILIABLE_INT,UNMASK);
    I2S_InstallCallBackFunc(I2S_ID_1, I2S_CHANNEL1_ID, I2S_RXFIFO_OVERRUN_INT,Ex_I2S1RxOverflowChannel1Callback);
    I2S_IntMask(I2S_ID_1, I2S_CHANNEL1_ID, I2S_RXFIFO_OVERRUN_INT,UNMASK);

    /*I2S1 Channel2 Interrupt*/
    I2S_InstallCallBackFunc(I2S_ID_1, I2S_CHANNEL2_ID, I2S_RXFIFO_DATA_AVAILIABLE_INT,Ex_I2S1RxAvailableChannel2Callback);
    I2S_IntMask(I2S_ID_1, I2S_CHANNEL2_ID, I2S_RXFIFO_DATA_AVAILIABLE_INT,UNMASK);
    I2S_InstallCallBackFunc(I2S_ID_1, I2S_CHANNEL2_ID, I2S_RXFIFO_OVERRUN_INT,Ex_I2S1RxOverflowChannel2Callback);
    I2S_IntMask(I2S_ID_1, I2S_CHANNEL2_ID, I2S_RXFIFO_OVERRUN_INT,UNMASK);

    /*I2S1 Channel3 Interrupt*/
    I2S_InstallCallBackFunc(I2S_ID_1, I2S_CHANNEL3_ID, I2S_RXFIFO_DATA_AVAILIABLE_INT,Ex_I2S1RxAvailableChannel3Callback);
    I2S_IntMask(I2S_ID_1, I2S_CHANNEL3_ID, I2S_RXFIFO_DATA_AVAILIABLE_INT,UNMASK);
    I2S_InstallCallBackFunc(I2S_ID_1, I2S_CHANNEL3_ID, I2S_RXFIFO_OVERRUN_INT,Ex_I2S1RxOverflowChannel3Callback);
    I2S_IntMask(I2S_ID_1, I2S_CHANNEL3_ID, I2S_RXFIFO_OVERRUN_INT,UNMASK);

    INT_EnableIRQ(I2S1_IRQn);

    printf("20k14x_app I2S start.\n");

    
    while(1);
}
