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

#ifndef CLOCK_CONFIG_H
#define CLOCK_CONFIG_H

#include "sysctrl_drv.h"
#include "clock_drv.h"

void CLKOUT_Configure(void);

/* Board clock init function */
void PLL80M_ClockInit(void);
void OSC40M_ClockInit(void);

#endif /* CLOCK_CONFIG_H */
