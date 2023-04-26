/**************************************************************************************************/
/**
 * @file     regfile_drv.h
 * @brief    REGFILE driver module header file.
 * @version  V1.0.0
 * @date     December-2022
 * @author   Zhixin Semiconductor
 *
 * @note
 * Copyright (C) 2021-2023 Zhixin Semiconductor Ltd. All rights reserved.
 *
 **************************************************************************************************/

#ifndef REGFILE_DRV_H
#define REGFILE_DRV_H

#include "common_drv.h"

/** @addtogroup  Z20K14XM_Peripheral_Driver
 *  @{
 */

/** @addtogroup  REGFILE
 *  @{
 */

/** @defgroup REGFILE_Public_Types
 *  @{
 */

/** @}end of group REGFILE_Public_Types */

/** @defgroup REGFILE_Public_Constants
 *  @{
 */

/** @}end of group REGFILE_Public_Constants */

/** @defgroup REGFILE_Public_Macro
 *  @{
 */

/** @}end of group REGFILE_Public_Macro */

/** @defgroup REGFILE_Public_FunctionDeclaration
 *  @brief REGFILE functions declaration
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
ResultStatus_t REGFILE_WriteByRegId(uint8_t regID, uint32_t *data);

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
ResultStatus_t REGFILE_ReadByRegId(uint8_t regID, uint32_t *data);

/** @}end of group REGFILE_Public_FunctionDeclaration */

/** @}end of group REGFILE  */

/** @}end of group Z20K14XM_Peripheral_Driver */

#endif /* REGFILE_DRV_H */
