/**************************************************************************************************/
/**
 * @file     regfile_drv.c
 * @brief    This module driver file.
 * @version  V1.0.0
 * @date     1-Jan-2021
 * @author   Zhixin Semiconductor
 *
 * @note
 * Copyright (C) 2021-2023 Zhixin Semiconductor Ltd. All rights reserved.
 *
 **************************************************************************************************/

#include "regfile_drv.h"

/** @addtogroup  Z20K14XM_Peripheral_Driver
 *  @{
 */

/** @defgroup REGFILE REGFILE
 *  @brief REGFILE driver modules
 *  @{
 */

/** @defgroup REGFILE_Private_Type
 *  @{
 */

/** @}end of group REGFILE_Private_Type*/

/** @defgroup REGFILE_Private_Defines
 *  @{
 */
#define REGFILE_TOTAL_NUMBER        (32U)

/**
 *  @brief REGFILE interrupt IID definition
 */
static regfile_reg_w_t *const regfileRegWPtr = 
                                                (regfile_reg_w_t *)REGFILE_BASE_ADDR;/*PRQA S 0303*/

/** @}end of group REGFILE_Private_Defines */

/** @defgroup REGFILE_Private_Variables
 *  @{
 */

/** @}end of group REGFILE_Private_Variables */

/** @defgroup REGFILE_Global_Variables
 *  @{
 */

/** @}end of group REGFILE_Global_Variables */

/** @defgroup REGFILE_Private_FunctionDeclaration
 *  @{
 */


/** @}end of group REGFILE_Private_FunctionDeclaration */

/** @defgroup REGFILE_Private_Functions
 *  @{
 */

/** @} end of group REGFILE_Private_Functions */

/** @defgroup REGFILE_Public_Functions
 *  @{
 */

/**
 * @brief      Write into the REGFILE by regID
 * @param[in]  regID: the regID of the regfile, the scope is [0-31]
 * @param[in]  data: the data to be written
 *
 * @return Write into the REGFILE Status:
 *         - SUCC: Operation is successful
 *         - ERR:  Operation fails, input param is invalid
 *
 */
ResultStatus_t REGFILE_WriteByRegId(uint8_t regID, uint32_t *data)
{
    ResultStatus_t ret;

    if(regID >= REGFILE_TOTAL_NUMBER)
    {
        ret = ERR;
    }
    else
    {
        if(NULL != data)
        {
            regfileRegWPtr->REGFILE_REGn[regID] = *data;
            ret = SUCC;
        }
        else
        {
            ret = ERR;
        }
    }

    return ret;
}

/**
 * @brief        Read from the REGFILE by regID
 * @param[in]    regID: the regID of the regfile, the scope is [0-31]
 * @param[inout] data: the data to be read
 *
 *
 * @return Read from the REGFILE Status:
 *         - SUCC: Operation is successful
 *         - ERR:  Operation fails, input param is invalid
 *
 */
ResultStatus_t REGFILE_ReadByRegId(uint8_t regID, uint32_t *data)
{
    ResultStatus_t ret;

    if(regID >= REGFILE_TOTAL_NUMBER)
    {
        ret = ERR;
    }
    else
    {
        *data = regfileRegWPtr->REGFILE_REGn[regID];
        ret = SUCC;
    }

    return ret;
}

/** @}end of group REGFILE_Public_Functions */

/** @}end of group REGFILE_definitions */

/** @}end of group Z20K14XM_Peripheral_Driver */
