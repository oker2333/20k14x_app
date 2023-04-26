/****************************************************************************//**
 * @file     drv_common.h
 * @brief    Drv common module header file.
 * @version  V1.0.0
 * @date     March-2021
 * @author   Zhixin Semiconductor
 *
 * @note
 * Copyright (C) 2021 Zhixin Semiconductor Ltd. All rights reserved.
 *******************************************************************************/
#ifndef DRV_COMMON_H
#define DRV_COMMON_H

#include "device_mem.h"
/** @addtogroup  Z20K14XM_Peripheral_Driver
 *  @{
 */

/** @addtogroup  DRV_COMMON
 *  @{
 */

/** @defgroup DRV_Public_Types
 *  @brief DRV type definition
 *  @{
 */

/**
 * @brief Control State Type Definition
 */
typedef enum
{
    DISABLE  = 0U,
    ENABLE   = 1U
}ControlState_t;

/**
 * @brief Result status Type definition
 */
typedef enum
{
    SUCC = 0U,
    ERR = 1U,
    BUSY = 2U
}ResultStatus_t;

/**
 * @brief Flag/Int status Type definition
 */
typedef enum
{
    RESET = 0U,
    SET = 1U
}FlagStatus_t, IntStatus_t;

/**
 * @brief interrupt mask Type definition
 */
typedef enum
{
    UNMASK = 0U,
    MASK = 1U
}IntMask_t;

/**
 * @brief level Type definition
 */
typedef enum
{
    LEVEL_LOW = 0U,
    LEVEL_HIGH = 1U
}Level_t;



/**
 *  @brief ISR callback function type
 */
typedef void (isr_cb_t)(void);


/** @} end of group DRV_Public_Types */


/** @defgroup DRV_Public_Constants
 *  @{
 */


/** @defgroup DRV_ISR_INDEX
 *  @{
 */
#define IS_ISR_INDEX(INDEX)       ((INDEX) < ISR_INDEX_NUM)
/** @} end of group DRV_INT_PERIPH */

/** @defgroup DRV_INT_MASK
 *  @{
 */
#define IS_INTMASK(INTMASK)          (((INTMASK) == MASK) || ((INTMASK) == UNMASK))
/** @} end of group DRV_INT_MASK */

/** @} end of group DRV_Public_Constants */

/** @defgroup DRV_Public_Macro
 *  @{
 */
/*
* Memory barrier used for ARM ERRATA-838869: Store immediate overlapping
* exception return operation might vector to incorrect interrupt.
* Cortex-M4, Cortex-M4F affected.
* Use dsb instruction intrinsic implementation for __CC_ARM,__ARMCC_VERSION(version6-armclang),
* __ICCARM__ and __GNUC__ compilers
*/
#if defined ( __CC_ARM ) || defined ( __ARMCC_VERSION ) || defined ( __ICCARM__ ) || ( __GNUC__ )
    #define ISR_MEMORY_BARRIER __DSB()
#else  /* For other compiler, it is empty */
    #define ISR_MEMORY_BARRIER 
#endif

#ifdef  DEBUG
/*************************************************************************************//**
* @brief		The CHECK_PARAM macro is used for function's parameters check.
* 				It is used only if the library is compiled in DEBUG mode.
* @param[in]	expr: - If expr is false, it calls check_failed() function
*               which reports the name of the source file and the source
*               line number of the call that failed.
*                     - If expr is true, it returns no value.
* @return  none
*****************************************************************************************/
void check_failed(uint8_t *file, uint32_t line);
#define CHECK_PARAM(expr) ((expr) ? (void)0 : check_failed((uint8_t *)__FILE__, __LINE__))
#else
#define CHECK_PARAM(expr) ((void)0)
#endif /* DEBUG */

/**
 * @brief Reverse byte order in a word
 */
#if defined (__ICCARM__)
#define REV_BYTES_32(a, b) __asm volatile ("rev %0, %1" : "=r" (b) : "r" (a))
#else
#define REV_BYTES_32(a, b) (b = ((a & 0xFF000000U) >> 24U) | ((a & 0xFF0000U) >> 8U) \
                                | ((a & 0xFF00U) << 8U) | ((a & 0xFFU) << 24U))
#endif

/** @} end of group DRV_Public_Macro */

/** @defgroup DRV_Public_FunctionDeclaration
 *  @brief DRV functions declaration
 *  @{
 */
     
/****************************************************************************//**
 * @brief      convert 4 byte into a word. The first byte is the lowest byte in 
 *             the word(little end).
 *
 * @param[in]  bytes: it points to an array with 4 bytes.
 *
 * @return     none
 *
 *******************************************************************************/
uint32_t BytesToWord(uint8_t bytes[4]);

/***************************************************************************//**
 * @brief      Delay for some cycles
 *
 * @param[in]  delayCount: the cycles to delay
 *
 * @return     None
 *
 ******************************************************************************/
#if( DRV_DELAY_FUNC_IN_RAM == 1)
START_FUNCTION_DECLARATION_RAMSECTION
void Drv_Delay(uint32_t delayCount)
END_FUNCTION_DECLARATION_RAMSECTION
#else
void Drv_Delay(uint32_t delayCount);
#endif

/** @} end of group DRV_Public_FunctionDeclaration */

/** @} end of group DRV_COMMON  */

/** @} end of group Z20K14XM_Peripheral_Driver */

#endif /* DRV_COMMON_H */
