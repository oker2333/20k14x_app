/**************************************************************************************************/
/**
 * @file     serial.h
 * @brief    Example serial file.
 * @version  V1.0.0
 * @date     December-2022
 * @author   Zhixin Semiconductor
 *
 * @note
 * Copyright (C) 2021-2023 Zhixin Semiconductor Ltd. All rights reserved.
 *
 **************************************************************************************************/
 
#ifndef SERIAL_H
#define SERIAL_H

#include "gpio_drv.h"
#include "uart_drv.h"
#include "clock_drv.h"
#include "sysctrl_drv.h"
#include <stdio.h>

/* UART init for board*/
void Ex_BoardUartInit(void);
#endif /* SERIAL_H */
