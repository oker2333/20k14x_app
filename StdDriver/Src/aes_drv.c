/**************************************************************************************************/
/**
 * @file     aes_drv.c
 * @brief    AES module driver file.
 * @version  V1.0.0
 * @date     December-2022
 * @author   Zhixin Semiconductor
 *
 * @note
 * Copyright (C) 2021-2023 Zhixin Semiconductor Ltd. All rights reserved.
 * 
 **************************************************************************************************/

#include "aes_drv.h"

/** @addtogroup  Z20K14XM_Peripheral_Driver
 *  @{
 */

/** @defgroup AES
 *  @brief AES driver modules
 *  @{
 */

/** @defgroup AES_Private_Defines
 *  @{
 */

#define AES_CONFIG_ALG_MASK           0xFF000000U
#define AES_CONFIG_BS_MASK            0x00FF0000U
#define AES_CONFIG_MODE_MASK          0x0000FF00U
#define AES_CONFIG_SP_MASK            0x00000008U
#define AES_CONFIG_KSS_MASK           0x00000006U
#define AES_CONFIG_CD_MASK            0x00000001U

#define AES_CONTROL_RND_MASK          0x0000001EU
#define AES_CONTROL_S_MASK            0x00000001U

#define AES_CONFIG_ALG_SHIFT          24U
#define AES_CONFIG_BS_SHIFT           16U
#define AES_CONFIG_MODE_SHIFT         8U
#define AES_CONFIG_SP_SHIFT           3U
#define AES_CONFIG_KSS_SHIFT          1U
#define AES_CONFIG_CD_SHIFT           0U

#define AES_CONTROL_RND_SHIFT         1U
#define AES_CONTROL_S_SHIFT           0U

#define AES_CONFIG_ALG_SET(x) \
        (((uint32_t)(x) & 0xFFUL) << AES_CONFIG_ALG_SHIFT)
        
#define AES_CONFIG_BS_SET(x) \
        (((uint32_t)(x) & 0xFFUL) << AES_CONFIG_BS_SHIFT)
        
#define AES_CONFIG_MODE_SET(x) \
        (((uint32_t)(x) & 0xFFUL) << AES_CONFIG_MODE_SHIFT)
        
#define AES_CONFIG_SP_SET(x) \
        (((uint32_t)(((uint32_t)(x)) << AES_CONFIG_SP_SHIFT)) & AES_CONFIG_SP_MASK)
        
#define AES_CONFIG_KSS_SET(x) \
        (((uint32_t)(((uint32_t)(x)) << AES_CONFIG_KSS_SHIFT)) & AES_CONFIG_KSS_MASK)
        
#define AES_CONFIG_CD_SET(x) \
        ((uint32_t)(x) & AES_CONFIG_CD_MASK)
        
#define AES_CONTROL_RND_SET(x) \
        (((uint32_t)(((uint32_t)(x)) << AES_CONTROL_RND_SHIFT)) & AES_CONTROL_RND_MASK)

#define AES_CONTROL_S_SET(x) \
        ((uint32_t)(x) & AES_CONTROL_S_MASK)

/** @} end of group AES_Private_Defines */


/** @defgroup AES_Private_Type
 *  @{
 */

/** @} end of group AES_Private_Type*/



/** @defgroup AES_Private_Variables
 *  @{
 */
/*PRQA S 0303 ++*/
static aes_reg_t *const aesRegPtr = (aes_reg_t *) AES_BASE_ADDR;
static aes_reg_w_t *const aesRegWPtr = (aes_reg_w_t *) AES_BASE_ADDR;
/*PRQA S 0303 --*/

/*! @brief AES ISR CallBack VECTOR structure */
static isr_cb_t * aesIsrCb = NULL;

/** @} end of group AES_Private_Variables */

/** @defgroup AES_Global_Variables
 *  @{
 */

/** @} end of group AES_Global_Variables */

/** @defgroup AES_Private_FunctionDeclaration
 *  @{
 */
void AES_DriverIRQHandler(void);
/** @} end of group AES_Private_FunctionDeclaration */

/** @defgroup AES_Private_Functions
 *  @{
 */

/** @} end of group AES_Private_Functions */


/** @defgroup AES_Public_Functions
 *  @{
 */

/**
 * @brief      aes operation config Function
 *
 * @param[in]  config:   Pointer to aes operation configuration structure.
 *
 * @return none
 *
 */
void AES_CryptConfig(const AES_CryptConfig_t * config)
{
    aesRegWPtr->AES_CONFIG = AES_CONFIG_ALG_SET(config->cryptAlg) |
                       AES_CONFIG_BS_SET(config->blockSize) |  /*PRQA S 2985 */
                       AES_CONFIG_MODE_SET(config->cryptOptMode) |
                       AES_CONFIG_CD_SET(config->cryptOpt);
}

/**
 * @brief      set aes operation key Function
 *
 * @param[in]  key:     Pointer to aes key array, key length must be 128 bits.
 *
 * @return none
 *
 */
void AES_SetKey(const uint32_t key[])
{
    aesRegWPtr->AES_KEY0 = key[0];
    aesRegWPtr->AES_KEY1 = key[1];
    aesRegWPtr->AES_KEY2 = key[2];
    aesRegWPtr->AES_KEY3 = key[3];
}

/**
 * @brief      set aes operation iv Function
 *
 * @param[in]  iv:     Pointer to aes iv array, iv length must be 128 bits.
 *
 * @return none
 *
 */
void AES_SetIv(const uint32_t iv[])
{
    aesRegWPtr->AES_IV0 = iv[0];
    aesRegWPtr->AES_IV1 = iv[1];
    aesRegWPtr->AES_IV2 = iv[2];
    aesRegWPtr->AES_IV3 = iv[3];
}

/**
 * @brief      set aes operation input data Function
 *
 * @param[in]  data:     Pointer to aes input data array, data length must be 128 bits.
 *
 * @return none
 *
 */
void AES_SetInputData(const uint32_t data[])
{
    aesRegWPtr->AES_DATA_I0 = data[0];
    aesRegWPtr->AES_DATA_I1 = data[1];
    aesRegWPtr->AES_DATA_I2 = data[2];
    aesRegWPtr->AES_DATA_I3 = data[3];
}

/**
 * @brief      start aes operation Function
 *
 * @param[in]  rnd:     4-bit random data to be used by the Block Cipher IP SCA countermeasure.
 *
 * @return function execution result
 *
 */
ResultStatus_t AES_StartOpt(uint8_t rnd)
{
    ResultStatus_t stat = SUCC;
    uint32_t aesReady = aesRegPtr->AES_STATUS.R;

    if (1U != aesReady)
    {
        stat = ERR;
    }

    aesRegWPtr->AES_CONTROL = AES_CONTROL_RND_SET(rnd) |
                        AES_CONTROL_S_SET(0x1U);
    
    return stat;
}

/**
 * @brief      get aes operation status Function
 *
 * @param[in]  error:     Point to the variable used to store the error status.
 *
 * @return whether aes operation ready flag is asserted or not.
 *
 */
FlagStatus_t AES_GetOptStatus(AES_StatusError_t * error)
{
    *error = (AES_StatusError_t)aesRegPtr->AES_STATUS.ERR;
    return ((FlagStatus_t)aesRegPtr->AES_STATUS.R);
}

/**
 * @brief      get aes operation output data Function
 *
 * @param[in]  error:     Point to the buffer used to store the output data.
 *
 * @return whether aes operation ready flag is asserted or not.
 *
 */
void AES_GetOutputData(uint32_t data[])
{
    data[0] = aesRegWPtr->AES_DATA_O0;
    data[1] = aesRegWPtr->AES_DATA_O1;
    data[2] = aesRegWPtr->AES_DATA_O2;
    data[3] = aesRegWPtr->AES_DATA_O3;
}

/**
 * @brief      Install callback function
 *
 * @param[in]  cbFun: indicate callback function
 *
 * @return    none
 *
 */ 
void AES_InstallCallBackFunc(isr_cb_t * const cbFun)
{
    aesIsrCb = cbFun;
}

/**
 * @brief      AES done interrupt handle
 *
 * @param[in]  none
 *
 * @return     none
 *
 */
void AES_DriverIRQHandler(void)
{
    if ((1U == aesRegPtr->AES_STATUS.R) && (aesIsrCb != NULL))
    {
        aesIsrCb();
    }

    COMMON_DSB();
}

/** @} end of group AES_Public_Functions */

/** @} end of group AES driver modules */

/** @} end of group Z20K14XM_Peripheral_Driver */
