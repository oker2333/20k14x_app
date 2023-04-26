/****************************************************************************//**
 * @file     drv_common.c
 * @brief    This file provides Z20K14X driver common functions.
 * @version  V1.0.0
 * @date     March-2021
 * @author   Zhixin Semiconductor
 *
 * @note
 * Copyright (C) 2021 Zhixin Semiconductor Ltd. All rights reserved.
 * 
 *******************************************************************************/

#include "drv_common.h"
#include "device_mem.h"

/** @addtogroup  Z20K14XM_Peripheral_Driver
 *  @{
 */

/** @defgroup DRV_COMMON
 *  @brief Z20K14X driver common functions
 *  @{
 */

/** @defgroup DRV_Private_Type
 *  @{
 */


/** @} end of group DRV_Private_Type*/

/** @defgroup DRV_Private_Defines
 *  @{
 */


/** @} end of group DRV_Private_Defines */


/** @defgroup DRV_Private_Variables
 *  @{
 */

                                  
  		      
/** @} end of group DRV_Private_Variables */

/** @defgroup DRV_Global_Variables
 *  @{
 */
  


/** @} end of group DRV_Global_Variables */


/** @defgroup DRV_Private_FunctionDeclaration
 *  @{
 */


/** @} end of group DRV_Private_FunctionDeclaration */

/** @defgroup DRV_Private_Functions
 *  @{
 */


/** @} end of group DRV_Private_Functions */

/** @defgroup DRV_Public_Functions
 *  @{
 */
 


#ifdef  DEBUG
/*******************************************************************************
* @brief		Reports the name of the source file and the source line number
* 				where the CHECK_PARAM error has occurred.

* @param[in]	file: Pointer to the source file name
* @param[in]    line: assert_param error line source number

* @return	none
*******************************************************************************/
void check_failed(uint8_t *file, uint32_t line)
{
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

    /* Infinite loop */
    while(1);
}
#endif /* DEBUG */

/***************************************************************************//**
 * @brief      Delay for some cycles
 *
 * @param[in]  delayCount: the cycles to delay
 *
 * @return     None
 *
 ******************************************************************************/
void Drv_Delay(uint32_t delayCount)
{
    volatile uint32_t cnt = 0U;

    while(cnt++ < delayCount)
    {
    }
}

/****************************************************************************//**
 * @brief      convert 4 byte into a word. The first byte is the lowest byte in 
 *             the word(little end).
 *
 * @param[in]  bytes: it points to an array with 4 bytes.
 *
 * @return     none
 *
 *******************************************************************************/
uint32_t BytesToWord(uint8_t bytes[4])
{
    uint32_t result;
    
    result = bytes[0] | ((uint32_t)bytes[1] << 8U) | ((uint32_t)bytes[2] << 16U)
             | ((uint32_t)bytes[3] << 24U);
    
    return result;
}

/** @} end of group DRV_Public_Functions */

/** @} end of group DRV_COMMON */

/** @} end of group Z20K14XM_Peripheral_Driver */
