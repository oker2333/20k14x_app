/**************************************************************************************************/
/**
 * @file     aes_drv.h
 * @brief    AES driver module header file.
 * @version  V1.0.0
 * @date     December-2022
 * @author   Zhixin Semiconductor
 *
 * @note
 * Copyright (C) 2021-2023 Zhixin Semiconductor Ltd. All rights reserved.
 * 
 **************************************************************************************************/

#ifndef AES_DRV_H
#define AES_DRV_H

#include "common_drv.h"

/** @addtogroup  Z20K14XM_Peripheral_Driver
 *  @{
 */

/** @addtogroup  AES
 *  @{
 */

/** @defgroup AES_Public_Types 
 *  @{
 */

/*! @brief cryptographic algorithm type definition
 * Implements : AES_Algorithm_t_Class
 */
typedef enum 
{
    AES_ALG_AES = 0U                     /*!< aes algorithm */
} AES_Algorithm_t;

/*! @brief aes operation mode type definition
 * Implements : AES_OptMode_t_Class
 */
typedef enum 
{
    AES_ECB_INIT       = 0x00U,          /*!< ecb init */
    AES_ECB_UPDATE     = 0x01U,          /*!< ecb update */
    AES_CBC_INIT       = 0x10U,          /*!< cbc init */
    AES_CBC_UPDATE     = 0x11U,          /*!< cbc update */
    AES_OFB_INIT       = 0x20U,          /*!< ofb init */
    AES_OFB_UPDATE     = 0x21U,          /*!< ofb update */
    AES_CTR_INIT       = 0x30U,          /*!< ctr init */
    AES_CTR_UPDATE     = 0x31U,          /*!< ctr update */
    AES_CFB_INIT       = 0x40U,          /*!< cfb init */
    AES_CFB_UPDATE     = 0x41U,          /*!< cbf update */
    AES_GCM_INIT       = 0x50U,          /*!< gcm init */
    AES_GCM_GHASH      = 0x51U,          /*!< gcm ghash */
    AES_GCM_UPDATE     = 0x52U,          /*!< gcm update */
    AES_GCM_FINISH_IV  = 0x53U,          /*!< gcm finish with iv */
    AES_GCM_FINISH     = 0x54U,          /*!< gcm finish */
    AES_CCM_INIT       = 0x60U,          /*!< ccm init */
    AES_CCM_MAC        = 0x61U,          /*!< ccm mac */
    AES_CCM_UPDATE     = 0x62U,          /*!< ccm update */
    AES_CCM_FINISH     = 0x63U,          /*!< ccm finish */
    AES_XTS_TWEAK_ENC  = 0x70U,          /*!< xts tweak enc */
    AES_XTS_INIT       = 0x71U,          /*!< xts init */
    AES_XTS_UPDATE     = 0x72U,          /*!< xts update */
    AES_CMAC_INTI      = 0x80U,          /*!< cmac init */
    AES_CMAC_UPDATE    = 0x81U,          /*!< cmac update */
    AES_CMAC_FINISH_K1 = 0x82U,          /*!< cmac finish k1 */
    AES_CMAC_FINISH_K2 = 0x83U           /*!< cmac finish k2 */
} AES_OptMode_t;

/*! @brief AES status error type definition 
 * Implements : AES_StatusError_t_Class
 */
typedef enum 
{
    AES_NO_ERR               = 0x0U,      /*!< NO_ERR */
    AES_ALG_ERR              = 0x1U,      /*!< UNAUTHORIZED_ALGORITHM */
    AES_KEYSIZE_ALG_ERR      = 0x2U,      /*!< UNAUTHORIZED_KEY_SIZE_FOR_ALGORITHM */
    AES_CIPHER_DIRECTION_ERR = 0x3U,      /*!< UNAUTHORIZED_CIPHER_DIRECTION */
    AES_MODE_ERR             = 0x4U,      /*!< UNAUTHORIZED_MODE */
    AES_ALG_MODE_ERR         = 0x5U,      /*!< UNAUTHORIZED_ALGORITHM_FOR_MODE */
    AES_DIRECTION_MODE_ERR   = 0x6U,      /*!< UNAUTHORIZED_DIRECTION_FOR_MODE */
    AES_KEYSIZE_MODE_ERR     = 0x7U,      /*!< UNAUTHORIZED_KEY_SIZE_FOR_MODE */
    AES_UNKNOWN_SETUP_ERR    = 0xFFU      /*!< UNKNOWN_SETUP_ERROR */
} AES_StatusError_t;

/*! @brief aes cryptographic operation type definition
 * Implements : AES_CryptOpt_t_Class
 */
typedef enum 
{
    AES_ENCRYPTION           = 0U,        /*!< aes encryption */
    AES_DECRYPTION                        /*!< aes decryption */
} AES_CryptOpt_t;

/*!
 * @brief AES operation configuration.
 *
 * This structure configures aes operation attribute.
 * Implements : AES_CryptConfig_t_Class
 */
typedef struct 
{
    AES_Algorithm_t cryptAlg;      /*!< cryptographic algorithm type */
    AES_OptMode_t cryptOptMode;    /*!< operation mode */
    AES_CryptOpt_t cryptOpt;       /*!< cryptographic operation type */
    uint8_t blockSize;             /*!< block size. the default value is 0. */ 
} AES_CryptConfig_t;

/** @} end of group AES_Public_Types */

/** @defgroup AES_Public_Constants
 *  @{
 */

/** @} end of group AES_Public_Constants */

/** @defgroup AES_Public_Macro
 *  @{
 */

/** @} end of group AES_Public_Macro */


/** @defgroup AES_Public_FunctionDeclaration
 *  @brief AES functions declaration
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
void AES_CryptConfig(const AES_CryptConfig_t * config);

/**
 * @brief      set aes operation key Function
 *
 * @param[in]  key:     Pointer to aes key array, key length must be 128 bits.
 *
 * @return none
 *
 */
void AES_SetKey(const uint32_t key[]);

/**
 * @brief      set aes operation iv Function
 *
 * @param[in]  iv:     Pointer to aes iv array, iv length must be 128 bits.
 *
 * @return none
 *
 */
void AES_SetIv(const uint32_t iv[]);

/**
 * @brief      set aes operation input data Function
 *
 * @param[in]  data:     Pointer to aes input data array, data length must be 128 bits.
 *
 * @return none
 *
 */
void AES_SetInputData(const uint32_t data[]);

/**
 * @brief      start aes operation Function
 *
 * @param[in]  rnd:  4-bit random data to be used by the Block Cipher IP 
 * SCA(Side Channel Attack) countermeasure. If you do not consider SCA threats,
 * you can pass in 0 each time by default.
 *
 * @return function execution result
 *
 */
ResultStatus_t AES_StartOpt(uint8_t rnd);

/**
 * @brief      get aes operation status Function
 *
 * @param[in]  error:     Point to the variable used to store the error status.
 *
 * @return whether aes operation ready flag is asserted or not.
 *
 */
FlagStatus_t AES_GetOptStatus(AES_StatusError_t * error);

/**
 * @brief      get aes operation output data Function
 *
 * @param[in]  error:     Point to the buffer used to store the output data.
 *
 * @return whether aes operation ready flag is asserted or not.
 *
 */
void AES_GetOutputData(uint32_t data[]);

/**
 * @brief      Install callback function
 *
 * @param[in]  cbFun: indicate callback function
 *
 * @return    none
 *
 */ 
void AES_InstallCallBackFunc(isr_cb_t * const cbFun);

/** @} end of group AES_Public_FunctionDeclaration */

/** @} end of group AES  */

/** @} end of group Z20K14XM_Peripheral_Driver */

#endif  /* AES_DRV_H */
