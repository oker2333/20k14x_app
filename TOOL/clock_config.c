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
void Ex_ClockInit(void)
{
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
