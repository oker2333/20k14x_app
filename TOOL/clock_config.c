/**************************************************************************************************/
/**
 * @file     clock_config.h
 * @brief    Example clock file.
 * @version  V1.0.0
 * @date     December-2022
 * @author   Zhixin Semiconductor
 *
 * @note
 * Copyright (C) 2021-2023 Zhixin Semiconductor Ltd. All rights reserved.
 *
 **************************************************************************************************/

#include "clock_config.h"
#include "flash_drv.h"
#include "gpio_drv.h"
#include "wdog_drv.h"

/* PLL parameter structure*/
CLK_PLLConfig_t PLL80M =
{
    .pllPreDivider = PLL_PRE_DIV_VALUE_4,       /* PLL pre divider value is 4 */
    .pllPostDivider = PLL_POST_DIV_VALUE_12,    /* PLL post divider value is 12 */
    .pllMultiplier = 48,                        /* PLL multiplier value is 48 */
    .pllRefClock = PLL_OSC_CLK,                 /* PLL select OSC as reference clock */
    .pllPreScaler = PLL_SCALER_VALUE_2,         /* PLL prescaler value is 2 */
};

/* Board clock init function */
void PLL80M_ClockInit(void)
{
    /* Disable wdog */
    WDOG_Disable();
    
    /* Set Core and bus clock */
    CLK_SetClkDivider(CLK_CORE, CLK_DIV_1);
    CLK_SetClkDivider(CLK_BUS, CLK_DIV_1);

    /* Enable OSC40M */
    CLK_OSC40MEnable(CLK_OSC_FREQ_MODE_HIGH, ENABLE, CLK_OSC_XTAL);

    /* Init PLL as 80M */
    CLK_PLLConfig(&PLL80M);
    CLK_PLLEnable(ENABLE);

    /* Set Flash wait-state value to AHB clock <=96M mode*/
    FLASH_SetWaitState(2);

    /* Choose PLL as system clock */
    while(CLK_SysClkSrc(CLK_SYS_PLL));

    /*Set Flash clock, please select SLOW clock source when using STOP mode function*/
    SYSCTRL_DisableModule(SYSCTRL_FLASH);
    CLK_ModuleSrc(CLK_FLASH, CLK_SRC_OSC40M);
    CLK_SetClkDivider(CLK_FLASH, CLK_DIV_5);
    SYSCTRL_EnableModule(SYSCTRL_FLASH);
}

void OSC40M_ClockInit(void)
{
    /* Disable wdog */
    WDOG_Disable();

    /* Enable OSC40M clock*/
    CLK_OSC40MEnable(CLK_OSC_FREQ_MODE_HIGH, ENABLE, CLK_OSC_XTAL);
    /* Select OSC40M as system clock*/
    while(CLK_SysClkSrc(CLK_SYS_OSC40M));
    
    /*Set Flash clock, please select SLOW clock source when using STOP mode function*/
    SYSCTRL_DisableModule(SYSCTRL_FLASH);
    CLK_ModuleSrc(CLK_FLASH, CLK_SRC_OSC40M);
    CLK_SetClkDivider(CLK_FLASH, CLK_DIV_5);
    SYSCTRL_EnableModule(SYSCTRL_FLASH);
}

void CLKOUT_Configure(void)
{
    CLK_ModuleSrc(CLK_PORTB, CLK_SRC_OSC40M);
    CLK_SetClkDivider(CLK_PORTB, CLK_DIV_1);
    SYSCTRL_EnableModule(SYSCTRL_PORTB);
    
    PORT_PinmuxConfig(PORT_B, GPIO_4, PTB4_CLKOUT);

    /*
        CLK_OUT_FIRC64M = 1U
        CLK_OUT_OSC40M = 2U
        CLK_OUT_PLL = 3U
        CLK_OUT_SLOW = 8U
        CLK_OUT_BUS = 9U
        CLK_OUT_CORE = 10U
        CLK_OUT_OSC32K = 11U
        CLK_OUT_LPO32K = 12U
    */

    /*
        CLK_OUT_DIV_1 = 0U,
        CLK_OUT_DIV_2 = 1U,
        CLK_OUT_DIV_4 = 2U,
        CLK_OUT_DIV_8 = 3U
    */
    CLK_OutSrc_t outSrc = CLK_OUT_OSC40M;
    CLK_OutDiv_t divider = CLK_OUT_DIV_1;

    CLK_ClkOutEnable(outSrc, divider);
}
