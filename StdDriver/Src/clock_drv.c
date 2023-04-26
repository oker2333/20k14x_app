/**************************************************************************************************/
/**
 * @file     clock_drv.c
 * @brief    CLOCK module driver file.
 * @version  V1.0.0
 * @date     December-2022
 * @author   Zhixin Semiconductor
 *
 * @note
 * Copyright (C) 2021-2023 Zhixin Semiconductor Ltd. All rights reserved.
 *
 **************************************************************************************************/

#include "clock_drv.h"

/** @addtogroup  Z20K14XM_Peripheral_Driver
 *  @{
 */

/** @defgroup Clock
 *  @brief Clock driver modules
 *  @{
 */

/** @defgroup Clock_Private_Type
 *  @{
 */

/** @} end of group Clock_Private_Type*/

/** @defgroup Clock_Private_Defines
 *  @{
 */


/** @} end of group Clock_Private_Defines */


/** @defgroup Clock_Private_Variables
 *  @{
 */
 
/**
 *  @brief RTC Register address array
 */
/*PRQA S 0303 ++*/
static rtc_reg_t * const rtcRegBfPtr = (rtc_reg_t *)RTC_BASE_ADDR;
static rtc_reg_w_t * const rtcRegWPtr = (rtc_reg_w_t *)RTC_BASE_ADDR;
/*PRQA S 0303 --*/

/**
 *  @brief PARCC Register address array
 */
/*PRQA S 0303 ++*/
static ModuleClk_t *parccRegPtr[]=
{
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_WDOG),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_EWDT),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_STIM),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_TIM0),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_TIM1),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_TIM2),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_TIM3),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_MCPWM0),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_MCPWM1),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_TDG0),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_TDG1),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_CAN0),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_CAN1),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_CAN2),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_CAN3),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_CAN4),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_CAN5),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_CAN6),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_CAN7),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_UART0),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_UART1),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_UART2),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_UART3),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_UART4),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_UART5),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_SPI0),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_SPI1),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_SPI2),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_SPI3),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_I2C0),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_I2C1),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_I2S0),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_I2S1),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_I2S1+0x4U),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_ADC0),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_ADC1),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_CMP),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_CRC),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_AES),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_TRNG),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_FLASH),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_FLASH+0x4U),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_DMA),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_DMAMUX),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_PORTA),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_PORTB),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_PORTC),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_PORTD),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_PORTE),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_TMU),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_REGFILE),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_SMPU),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_GPIO),
};
/*PRQA S 0303 --*/

/**
 *  @brief SCM Register address array
 */
/*PRQA S 0303 ++*/
static scm_reg_t * const scmRegBfPtr = (scm_reg_t *)SCM_BASE_ADDR;
/*PRQA S 0303 --*/

/**
 *  @brief SCC Register address array
 */
/*PRQA S 0303 ++*/
static scc_reg_t * const sccRegBfPtr = (scc_reg_t *)SCC_BASE_ADDR;
static scc_reg_w_t * const sccRegWPtr = (scc_reg_w_t *)SCC_BASE_ADDR;
/*PRQA S 0303 --*/

/**
 *  @brief PMU Register address array
 */
/*PRQA S 0303 ++*/
static pmu_reg_t * const pmuRegBfPtr = (pmu_reg_t *)PMU_BASE_ADDR;
static pmu_reg_w_t * const pmuRegWPtr = (pmu_reg_w_t *)PMU_BASE_ADDR;
/*PRQA S 0303 --*/

/**
 *  @brief SCC IRQHandler callback function pointer array
 */
static isr_cb_t * sccIsrCbFunc[CLK_INT_ALL]= {NULL, NULL};

/** @} end of group Clock_Private_Variables */

/** @defgroup Clock_Global_Variables
 *  @{
 */

/** @} end of group Clock_Global_Variables */

/** @defgroup Clock_Private_FunctionDeclaration
 *  @{
 */
void SCC_DriverIRQHandler(void);

/** @} end of group Clock_Private_FunctionDeclaration */

/** @defgroup Clock_Private_Functions
 *  @{
 */
/**
 * @brief      get system clock frequency before divider
 *
 * @param[in]  oscFreq: frequency of the OSC clock
 *
 * @return    ret: the clock frequency. If return 0, there is some error.
 *
 */
static uint32_t CLK_GetSysClkFreq(uint32_t oscFreq);

/**
 * @brief  SCC IRQHandler function
 *
 * @param  none
 *
 * @return none
 *
 */
void SCC_DriverIRQHandler(void)
{
    if(sccRegBfPtr->SCC_OSCCS.OSCLOC != 0U)
    {
        if(sccRegBfPtr->SCC_OSCCS.LOCK != 0U)
        {
            /* unlock this register */
            sccRegWPtr->SCC_OSCCS = 0x5B000000U;
        }
        /* clear int status */
        sccRegBfPtr->SCC_OSCCS.OSCLOC = 1U;
        /* lock */
        sccRegBfPtr->SCC_OSCCS.LOCK = 1U;
        
        if(sccIsrCbFunc[CLK_INT_OSCLOC] != NULL)
        {
            sccIsrCbFunc[CLK_INT_OSCLOC]();
        }
        else
        {
            CLK_OSC40MMonitorDisable();
        }
    }
    
    if(sccRegBfPtr->SCC_FIRCCS.FIRCLOC != 0U)
    {
        if(sccRegBfPtr->SCC_FIRCCS.LOCK != 0U)
        {
            /* unlock this register */
            sccRegWPtr->SCC_FIRCCS = 0x5B000000U;
        }
        /* clear int status */
        sccRegBfPtr->SCC_FIRCCS.FIRCLOC = 1U;
        /* lock */
        sccRegBfPtr->SCC_FIRCCS.LOCK = 1U;
        
        if(sccIsrCbFunc[CLK_INT_FIRCLOC] != NULL)
        {
            sccIsrCbFunc[CLK_INT_FIRCLOC]();
        }
        else
        {
            CLK_FIRC64MMonitorDisable();
        }
    }

    COMMON_DSB();
}

/**
 * @brief      Get system clock frequency before divider
 *
 * @param[in]  oscFreq: frequency of the OSC clock
 *
 * @return    ret: the clock frequency. If return 0, there is some error.
 *
 */
static uint32_t CLK_GetSysClkFreq(uint32_t oscFreq)
{
    uint32_t ret = 0U;

    if(2U == sccRegBfPtr->SCC_CST.SCS)
    {
        ret = oscFreq;
    }

    else if(1U == sccRegBfPtr->SCC_CST.SCS)
    {
        ret = 64000000U;
    }

    else if(3U == sccRegBfPtr->SCC_CST.SCS)
    {
        if(0U == sccRegBfPtr->SCC_SPLLCFG1.REFCKS)
        {
            ret = CLK_GetPLLFreq(PLL_FIRC64M_CLK, oscFreq);
        }
        /* 1U == sccRegBfPtr->SCC_SPLLCFG1.REFCKS */
        else
        {
            ret = CLK_GetPLLFreq(PLL_OSC_CLK, oscFreq);
        }
    }

    else
    {
        /* Do nothing */
    }
    return ret;
}

/** @} end of group Clock_Private_Functions */

/** @defgroup Clock_Public_Functions
 *  @{
 */

/**
 * @brief      Config and enable FIRC64M clock
 *
 * @param[in]  stopModeEn:  Enable/Disable FIRC64M in stop mode
 *                              -ENABLE
 *                              -DISABLE
 *
 * @return none
 *
 */
void CLK_FIRC64MEnable(ControlState_t stopModeEn)
{
    if(sccRegBfPtr->SCC_FIRCCS.LOCK != 0U)
    {
        /* unlock this register */
        sccRegWPtr->SCC_FIRCCS = 0x5B000000U;
    }

    sccRegBfPtr->SCC_FIRCCS.FIRCSTOPEN = (uint32_t)stopModeEn;
    sccRegBfPtr->SCC_FIRCCS.FIRCEN = 1U;

    /* lock this register */
    sccRegBfPtr->SCC_FIRCCS.LOCK = 1U;
}

/**
 * @brief      Config and enable PLL clock
 *
 * @param[in]  stopModeEn:  Enable/Disable PLL in stop mode.
 *                              -ENABLE
 *                              -DISABLE
 *
 * @return none
 *
 */
void CLK_PLLEnable(ControlState_t stopModeEn)
{
    if(sccRegBfPtr->SCC_SPLLCS.LOCK != 0U)
    {
        /* unlock this register */
        sccRegWPtr->SCC_SPLLCS = 0x5B000000U;
    }

    sccRegBfPtr->SCC_SPLLCS.RDYEN = 1U;
    sccRegBfPtr->SCC_SPLLCS.SPLLSTOPEN = (uint32_t)stopModeEn;
    sccRegBfPtr->SCC_SPLLCS.SPLLEN = 1U;

    /* lock this register */
    sccRegBfPtr->SCC_SPLLCS.LOCK = 1U;
    if (SUCC == CLK_WaitClkReady(CLK_SRC_PLL))
    {
        sccRegWPtr->SCC_SPLLCS = 0x5B000000U;
        sccRegBfPtr->SCC_SPLLCS.OUTEN = 1U;
        sccRegBfPtr->SCC_SPLLCS.RDYEN = 0U;
        sccRegBfPtr->SCC_SPLLCS.LOCK = 1U;
    }

}

/**
 * @brief      Config and enable  OSC40M clock
 *
 * @param[in]  freqMode:  It selects the frequency mode of OSC40M
 * @param[in]  stopModeEn:  Enable/Disable OSC40M in stop mode.
 * @param[in]  mode: select OSC mode. It selects from crystal oscillator or 
 *                   external square wave clock source.
 *
 * @return status
 *         ERR - some error.
 *         SUCC - successful
 *
 */
ResultStatus_t CLK_OSC40MEnable(CLK_OscFreqMode_t freqMode, 
                                 ControlState_t stopModeEn, 
                                 CLK_OscMode_t mode)
{
    if(sccRegBfPtr->SCC_OSCCFG.LOCK != 0U)
    {
        /* unlock this register */
        sccRegWPtr->SCC_OSCCFG = 0x5B000000U;
    }
    sccRegBfPtr->SCC_OSCCFG.HFREQ = (uint32_t)freqMode;
    sccRegBfPtr->SCC_OSCCFG.EXCLKS = (uint32_t)mode;
    sccRegBfPtr->SCC_OSCCFG.OLMEN = 1U;
    /* lock */
    sccRegBfPtr->SCC_OSCCFG.LOCK = 1U;

    if(sccRegBfPtr->SCC_OSCCS.LOCK != 0U)
    {
        /* unlock this register */
        sccRegWPtr->SCC_OSCCS = 0x5B000000U;
    }
    sccRegBfPtr->SCC_OSCCS.OSCSTOPEN = (uint32_t)stopModeEn;

    sccRegBfPtr->SCC_OSCCS.OSCEN = 1U;
    sccRegBfPtr->SCC_OSCCS.LOCK = 1U;
    /* wait for clock ready */
    return CLK_WaitClkReady(CLK_SRC_OSC40M);
}

/**
 * @brief      Select system clock.
 *
 * @param[in]  clk: select the clock source
 *                  -CLK_SYS_OSC40M
 *                  -CLK_SYS_FIRC64M
 *                  -CLK_SYS_PLL
 *
 * @return  ret:
 *        -SUCC: the system clock is selected successfully
 *        -ERR: fail
 * @note The selected clock source has to be ready
 *       before call this function.
 *
 */
ResultStatus_t CLK_SysClkSrc(CLK_System_t clk)
{
    ResultStatus_t ret = SUCC;
    if(CLK_SYS_FIRC64M == clk)
    {
        if(CLK_WaitClkReady(CLK_SRC_FIRC64M) != SUCC)
        {
            ret= ERR;
        }
        if(SUCC == ret)
        {
            if(sccRegBfPtr->SCC_CFG.LOCK != 0U)
            {
                /* unlock this register */
                sccRegWPtr->SCC_CFG = 0x5B000000U;
            }
            /* select sys clock source */
            sccRegWPtr->SCC_CFG = (sccRegWPtr->SCC_CFG & 0xFFF8FFFFU) | (1UL << 16U);
            sccRegBfPtr->SCC_CFG.LOCK = 1U;
        }
        
    }
    else if(CLK_SYS_OSC40M == clk)
    {
        if(CLK_WaitClkReady(CLK_SRC_OSC40M) != SUCC)
        {
            ret= ERR;
        }
        if(SUCC == ret)
        {
            if(sccRegBfPtr->SCC_CFG.LOCK != 0U)
            {
                /* unlock this register */
                sccRegWPtr->SCC_CFG = 0x5B000000U;
            }
            /* select sys clock source */
            sccRegWPtr->SCC_CFG = (sccRegWPtr->SCC_CFG & 0xFFF8FFFFU) | (1UL << 17U);
            sccRegBfPtr->SCC_CFG.LOCK = 1;
        }
    }
    else if(CLK_SYS_PLL == clk)
    {
        if(CLK_WaitClkReady(CLK_SRC_PLL) != SUCC)
        {
            ret= ERR;
        }
        if(SUCC == ret)
        {
            if(sccRegBfPtr->SCC_CFG.LOCK != 0U)
            {
                /* unlock this register */
                sccRegWPtr->SCC_CFG = 0x5B000000U;
            }
            /* select sys clock source */
            sccRegWPtr->SCC_CFG = (sccRegWPtr->SCC_CFG & 0xFFF8FFFFU) | (3UL << 16U);
            sccRegBfPtr->SCC_CFG.LOCK = 1;
        }
    }
    else
    {
        ret= ERR;
    }
    return ret;
}

/**
 * @brief      Get system clock source.
 *
 * @param[in]  none.
 *
 * @return  ret:
 *          -CLK_SYS_FIRC64M
 *          -CLK_SYS_OSC40M
 *          -CLK_SYS_PLL
 *
 */
CLK_System_t CLK_GetSysClkSrc(void)
{
    CLK_System_t ret;
    if(sccRegBfPtr->SCC_CST.SCS == (uint32_t)CLK_SYS_FIRC64M)
    {
        ret = CLK_SYS_FIRC64M;
    }
    else if(sccRegBfPtr->SCC_CST.SCS == (uint32_t)CLK_SYS_OSC40M)
    {
        ret = CLK_SYS_OSC40M;
    }
    /* sccRegBfPtr->SCC_CST.SCS == CLK_SYS_PLL */
    else
    {
        ret = CLK_SYS_PLL;
    }
    return ret;
}

/**
 * @brief      Disable FIRC64M clock
 *
 * @param[in]  none.
 *
 * @return none
 *
 */
void CLK_FIRC64MDisable(void)
{
    if(sccRegBfPtr->SCC_FIRCCS.LOCK != 0U)
    {
        /* unlock this register */
        sccRegWPtr->SCC_FIRCCS = 0x5B000000;
    }

    sccRegBfPtr->SCC_FIRCCS.FIRCEN = 0;

    /* lock this register */
    sccRegBfPtr->SCC_FIRCCS.LOCK = 1;
}

/**
 * @brief      Disable PLL clock
 *
 * @param[in]  none.
 *
 * @return none
 *
 */
void CLK_PLLDisable(void)
{
    if(sccRegBfPtr->SCC_SPLLCS.LOCK != 0U)
    {
        /* unlock this register */
        sccRegWPtr->SCC_SPLLCS = 0x5B000000;
    }

    sccRegBfPtr->SCC_SPLLCS.SPLLEN = 0;

    sccRegBfPtr->SCC_SPLLCS.OUTEN = 0;

    /* lock this register */
    sccRegBfPtr->SCC_SPLLCS.LOCK = 1;
}

/**
 * @brief      Select PLL reference clock
 *
 * @param[in]  pll_ref_clk: PLL reference clock
 *                              -PLL_OSC_CLK
 *                              -PLL_FIRC64M_CLK
 *
 * @return none
 *
 */
void CLK_PLLRefClockSelect(CLK_PLLRefClk_t pll_ref_clk)
{
    scc_reg_w_t * sccRegBfPtrw = (scc_reg_w_t *)(sccRegWPtr);
    if(sccRegBfPtr->SCC_SPLLCFG1.LOCK != 0U)
    {
        /* unlock this register */
        sccRegBfPtrw->SCC_SPLLCFG1 = 0x5B000000;
    }

    /*Select OSC or FIRC as PLL reference clock*/
    sccRegBfPtr->SCC_SPLLCFG1.REFCKS = (uint32_t)pll_ref_clk;

    /* lock this register */
    sccRegBfPtr->SCC_SPLLCFG1.LOCK = 1;
}

/**
 * @brief      Get PLL output freqency
 *
 * @param[in]  pll_ref_clk: PLL reference clock
 *                              -PLL_OSC_CLK
 *                              -PLL_FIRC64M_CLK
 *
 *             oscFreq: oscillator frequence when PLL uses OSC as reference clock
 *
 * @return  pllOutFreq: PLL output freqency.
 *
 */
uint32_t CLK_GetPLLFreq(CLK_PLLRefClk_t pll_ref_clk, uint32_t oscFreq)
{
    uint32_t postDiv;
    uint32_t preDiv;
    uint32_t mult;
    uint32_t preScaler = 0U;
    uint32_t pllOutFreq = 0U;
    scc_reg_w_t * sccRegBfPtrw = (scc_reg_w_t *)(sccRegWPtr);
    if(sccRegBfPtr->SCC_SPLLCFG1.LOCK != 0U)
    {
        /* unlock this register */
        sccRegBfPtrw->SCC_SPLLCFG1 = 0x5B000000;
    }

    postDiv = sccRegBfPtr->SCC_SPLLCFG1.POSTDIV;
    preDiv = sccRegBfPtr->SCC_SPLLCFG1.PREDIV;
    mult = sccRegBfPtr->SCC_SPLLCFG1.MULT;
    if(sccRegBfPtr->SCC_SPLLCFG1.FBPRESEN == 1U)
    {
        preScaler = 2;
    }
    /* SCC_SPLLCFG1.FBPRESEN == 0U */
    else
    {
        preScaler = 1;
    }
    /* lock this register */
    sccRegBfPtr->SCC_SPLLCFG1.LOCK = 1;

    if(pll_ref_clk == PLL_OSC_CLK)
    {
        pllOutFreq = oscFreq*mult*preScaler/((postDiv*2U)*((uint32_t)1U<<preDiv));
    }
    if(pll_ref_clk == PLL_FIRC64M_CLK)
    {
        pllOutFreq = 64000000U*mult*preScaler/((postDiv*2U)*((uint32_t)1U<<preDiv));
    }

    return pllOutFreq;
}

/**
 * @brief      Set PLL output clock configuration
 *
 * @param[in]  pll_config: pointer to the PLL configure struct
 *
 * @return  none
 *
 * @note    According to the following formula to configure the desired PLL out freqency:
 *
 *           pllOutFreq = refClock * mult * preScaler / (postDivEnum*preDivEnum)
 *
 *           1. 80M PLL output configuration(use OSC40M as clock reference)
 *              CLK_PLLConfig_t PLLOSC40MSet80M =
 *              {
 *                  .pllPreDivider = PLL_PRE_DIV_VALUE_4,         
 *                  .pllPostDivider = PLL_POST_DIV_VALUE_12,        
 *                  .pllMultiplier = 48,                           
 *                  .pllRefClock = PLL_OSC_CLK,                  
 *                  .pllPreScaler = PLL_SCALER_VALUE_2,       
 *              };
 *
 *           2. 120M PLL output configuration(use OSC40M as clock reference)
 *              CLK_PLLConfig_t PLLOSC40MSet120M =
 *              {
 *                  .pllPreDivider = PLL_PRE_DIV_VALUE_4,              
 *                  .pllPostDivider = PLL_POST_DIV_VALUE_8,            
 *                  .pllMultiplier = 48,                            
 *                  .pllRefClock = PLL_OSC_CLK,                  
 *                  .pllPreScaler = PLL_SCALER_VALUE_2,             
 *              };
 *
 */
void CLK_PLLConfig(CLK_PLLConfig_t *pll_config)
{
    scc_reg_w_t * sccRegBfPtrw = (scc_reg_w_t *)(sccRegWPtr);
    if(sccRegBfPtr->SCC_SPLLCFG1.LOCK != 0U)
    {
        /* unlock this register */
        sccRegBfPtrw->SCC_SPLLCFG1 = 0x5B000000;
    }

    /*Set up the PLL configuration register*/
    sccRegBfPtr->SCC_SPLLCFG1.POSTDIV = (uint32_t)(pll_config->pllPostDivider);
    sccRegBfPtr->SCC_SPLLCFG1.PREDIV = (uint32_t)(pll_config->pllPreDivider);
    sccRegBfPtr->SCC_SPLLCFG1.MULT = pll_config->pllMultiplier;
    sccRegBfPtr->SCC_SPLLCFG1.FBPRESEN = (uint32_t)(pll_config->pllPreScaler);
    sccRegBfPtr->SCC_SPLLCFG1.REFCKS = (uint32_t)(pll_config->pllRefClock);

    /* lock this register */
    sccRegBfPtr->SCC_SPLLCFG1.LOCK = 1;
}

/**
 * @brief      Disable OSC40M clock
 *
 * @param[in]  none.
 *
 * @return none
 *
 */
void CLK_OSC40MDisable(void)
{
    if(sccRegBfPtr->SCC_OSCCS.LOCK != 0U)
    {
        /* unlock this register */
        sccRegWPtr->SCC_OSCCS = 0x5B000000;
    }
    if(sccRegBfPtr->SCC_OSCCFG.LOCK != 0U)
    {
        /* unlock this register */
        sccRegWPtr->SCC_OSCCFG = 0x5B000000U;
    }
    
    sccRegBfPtr->SCC_OSCCS.OSCEN = 0U;
    sccRegBfPtr->SCC_OSCCFG.OLMEN = 0U;

    /* lock */
    sccRegBfPtr->SCC_OSCCS.LOCK = 1U;
    sccRegBfPtr->SCC_OSCCFG.LOCK = 1U;
}

/**
 * @brief      Config and Enable OSC40M loss of clock monitor
 *
 * @param[in]  act: select the action when loss of clock is detected.
 *                  -CLK_MON_INT
 *                  -CLK_MON_RST
 *
 * @return none
 *
 */
void CLK_OSC40MMonitorEnable(CLK_MonitorAct_t act)
{
    if(sccRegBfPtr->SCC_OSCCS.LOCK != 0U)
    {
        /* unlock this register */
        sccRegWPtr->SCC_OSCCS = 0x5B000000;
    }

    sccRegBfPtr->SCC_OSCCS.OSCCMRE = (uint32_t)act;

    sccRegBfPtr->SCC_OSCCS.OSCCME = 1;
    sccRegBfPtr->SCC_OSCCS.OSCLOCINTEN = 1;
    /* lock */
    sccRegBfPtr->SCC_OSCCS.LOCK = 1;
}

/**
 * @brief      Disable OSC40M loss of clock monitor
 *
 * @param[in]  none.
 *
 * @return none
 *
 */
void CLK_OSC40MMonitorDisable(void)
{
    if(sccRegBfPtr->SCC_OSCCS.LOCK != 0U)
    {
        /* unlock this register */
        sccRegWPtr->SCC_OSCCS = 0x5B000000;
    }

    sccRegBfPtr->SCC_OSCCS.OSCCME = 0;
    /* lock */
    sccRegBfPtr->SCC_OSCCS.LOCK = 1;
}

/**
 * @brief      Config and Enable FIRC64M loss of clock monitor
 *
 * @param[in]  act: select the action when loss of clock is detected.
 *                  -CLK_MON_INT
 *                  -CLK_MON_RST
 *
 * @return none
 *
 */
void CLK_FIRC64MMonitorEnable(CLK_MonitorAct_t act)
{
    if(sccRegBfPtr->SCC_FIRCCS.LOCK != 0U)
    {
        /* unlock this register */
        sccRegWPtr->SCC_FIRCCS = 0x5B000000;
    }

    sccRegBfPtr->SCC_FIRCCS.FIRCCMRE = (uint32_t)act;

    sccRegBfPtr->SCC_FIRCCS.FIRCCME = 1;
    sccRegBfPtr->SCC_FIRCCS.FIRCLOCINTEN = 1;
    /* lock */
    sccRegBfPtr->SCC_FIRCCS.LOCK = 1;
}

/**
 * @brief      Config and Enable FIRC64M loss of clock monitor
 *
 * @param[in]  none
 *
 * @return none
 *
 */
void CLK_FIRC64MMonitorDisable(void)
{
    if(sccRegBfPtr->SCC_FIRCCS.LOCK != 0U)
    {
        /* unlock this register */
        sccRegWPtr->SCC_FIRCCS = 0x5B000000;
    }

    sccRegBfPtr->SCC_FIRCCS.FIRCCME = 0;
    /* lock */
    sccRegBfPtr->SCC_FIRCCS.LOCK = 1;
}

/**
 * @brief      Config and Enable LPO32K clock
 *
 * @param[in]  none
 *
 * @return none
 *
 */
void CLK_LPO32KEnable(void)
{
    pmuRegWPtr->PMU_LOCK = (uint32_t)PMU_UNLOCK_SEQUENCE;
    pmuRegBfPtr->PMU_LPO_32K_CFG.LPO_CLK_DIS = 0;
    pmuRegBfPtr->PMU_LOCK.LOCK = 1U;
}

/**
 * @brief      Disable LPO32K clock
 *
 * @param[in]  none.
 *
 * @return none
 *
 */
void CLK_LPO32KDisable(void)
{
    pmuRegWPtr->PMU_LOCK = (uint32_t)PMU_UNLOCK_SEQUENCE;
    pmuRegBfPtr->PMU_LPO_32K_CFG.LPO_CLK_DIS = 1;
    pmuRegBfPtr->PMU_LOCK.LOCK = 1U;
}

/**
 * @brief      Config and Enable OSC32K clock
 *
 * @param[in]  mode:  Select internal/external mode.
 *                    -CLK_OSC_XTAL
 *                    -CLK_OSC_EXT_SRC
 *
 * @return none
 *
 */
void CLK_OSC32KEnable(CLK_OscMode_t mode)
{
    if(rtcRegBfPtr->RTC_LOCKR.LOCK != 0U)
    {
        rtcRegWPtr->RTC_LOCKR = 0x98670000U;
    }
    if( CLK_OSC_XTAL == mode)
    {
        rtcRegBfPtr->RTC_CSR.EXTAL_32K_EN = 0U;
        rtcRegBfPtr->RTC_CSR.CRYSTAL_EN = 1U;
    }
    else
    {
        rtcRegBfPtr->RTC_CSR.EXTAL_32K_EN = 1U;
        rtcRegBfPtr->RTC_CSR.CRYSTAL_EN = 0U;
    }
    rtcRegBfPtr->RTC_LOCKR.LOCK = 1U;
}

/**
 * @brief      Disable OSC32K clock
 *
 * @param[in]  none
 *
 * @return none
 *
 */
void CLK_OSC32KDisable(void)
{
    if(rtcRegBfPtr->RTC_LOCKR.LOCK != 0U)
    {
        rtcRegWPtr->RTC_LOCKR = 0x98670000U;
    }
    rtcRegBfPtr->RTC_CSR.EXTAL_32K_EN = 0U;
    rtcRegBfPtr->RTC_CSR.CRYSTAL_EN = 0U;
    rtcRegBfPtr->RTC_LOCKR.LOCK = 1U;
}
/**
 * @brief      Set clock divider
 *
 * @param[in]  module: select which module clock to enable.
 *                     
 * @param[in] divider: Select the clock divider: CLK_DIV_1...CLK_DIV_16.
 * @return     none
 *
 */
void CLK_SetClkDivider(CLK_Module_t module, CLK_Divider_t divider)
{
    ModuleClk_t *mod_p = (ModuleClk_t *)(parccRegPtr[((uint32_t)module>> 2U)]);
    switch(module)
    {
        case CLK_EWDT:
        case CLK_STIM:
        case CLK_TIM0:
        case CLK_TIM1:
        case CLK_TIM2:
        case CLK_TIM3:
        case CLK_MCPWM0:
        case CLK_MCPWM1:
        case CLK_TDG0:
        case CLK_TDG1:
        case CLK_CAN0:
        case CLK_CAN1:
        case CLK_CAN2:
        case CLK_CAN3:
#if (CAN_INSTANCE_NUM == 6) || (CAN_INSTANCE_NUM == 8) 
        case CLK_CAN4:
        case CLK_CAN5:
#endif
#if (CAN_INSTANCE_NUM == 8)
        case CLK_CAN6:
        case CLK_CAN7:
#endif
        case CLK_UART0:
        case CLK_UART1:
        case CLK_UART2:
        case CLK_UART3:
        case CLK_UART4:
        case CLK_UART5:
        case CLK_SPI0:
        case CLK_SPI1:
        case CLK_SPI2:
        case CLK_SPI3:
        case CLK_I2C0:
#if (I2C_INSTANCE_NUM == 2)		
        case CLK_I2C1: 
#endif
        case CLK_I2S0:
#if (I2S_INSTANCE_NUM == 2)
        case CLK_I2S1:
#endif
        case CLK_ADC0:
        case CLK_ADC1:
        case CLK_FLASH:
        case CLK_PORTA:
        case CLK_PORTB:
        case CLK_PORTC:
        case CLK_PORTD:
        case CLK_PORTE:
            if(mod_p->BF.LOCK != 0U)
            {
                /* unlock this register */
                mod_p->WORDVAL = 0x5B000000U;
            }

            mod_p->BF.CLKDIV = (uint32_t)divider;
            mod_p->BF.LOCK = 1U;
            break;

        case CLK_CORE:
            if(sccRegBfPtr->SCC_CFG.LOCK != 0U)
            {
                /* unlock this register */
                sccRegWPtr->SCC_CFG = 0x5B000000U;
            }

            sccRegWPtr->SCC_CFG = (sccRegWPtr->SCC_CFG & 0xFFFFF0FFU) | ((uint32_t)divider << 8U);
            sccRegBfPtr->SCC_CFG.LOCK = 1;
            break;

        case CLK_BUS:
            if(sccRegBfPtr->SCC_CFG.LOCK != 0U)
            {
                /* unlock this register */
                sccRegWPtr->SCC_CFG = 0x5B000000U;
            }

            sccRegWPtr->SCC_CFG = (sccRegWPtr->SCC_CFG & 0xFFFFFF0FU) | ((uint32_t)divider << 4U);
            sccRegBfPtr->SCC_CFG.LOCK = 1U;
            break;

        case CLK_SLOW:
            if(sccRegBfPtr->SCC_CFG.LOCK != 0U)
            {
                /* unlock this register */
                sccRegWPtr->SCC_CFG = 0x5B000000U;
            }

            sccRegWPtr->SCC_CFG = (sccRegWPtr->SCC_CFG & 0xFFFFFFF0U) | (uint32_t)divider;
            sccRegBfPtr->SCC_CFG.LOCK = 1U;
            break;

        default:
            /*Nothing to do*/
            break;
    }
}

/**
 * @brief      Select clock source for module
 *
 * @param[in]  module: select which module clock to enable.
 *                     
 * @param[in]  clockSource: select clock source
 *                          -CLK_SRC_NO
 *                          -CLK_SRC_LPO32K
 *                          -CLK_SRC_OSC32K
 *                          -CLK_SRC_FIRC64M
 *                          -CLK_SRC_OSC40M
 *                          -CLK_SRC_PLL
 * @return  res:
 *         - SUCC
 *         - ERR: the input parameter is unreasonable.
 *
 */
ResultStatus_t CLK_ModuleSrc(CLK_Module_t module, CLK_Src_t clockSource)
{
    ModuleClk_t *mod_p = (ModuleClk_t *)(parccRegPtr[((uint32_t)module>>2U)]);
    volatile ResultStatus_t res = SUCC;

    switch(module)
    {
        case CLK_STIM:
        case CLK_TIM0:
        case CLK_TIM1:
        case CLK_TIM2:
        case CLK_TIM3:
        case CLK_MCPWM0:
        case CLK_MCPWM1:
        case CLK_TDG0:
        case CLK_TDG1:
        case CLK_UART0:
        case CLK_UART1:
        case CLK_UART2:
        case CLK_UART3:
        case CLK_UART4:
        case CLK_UART5:
        case CLK_SPI0:
        case CLK_SPI1:
        case CLK_SPI2:
        case CLK_SPI3:
        case CLK_I2C0:   
#if (I2C_INSTANCE_NUM == 2)	
        case CLK_I2C1:
#endif
        case CLK_I2S0:
#if (I2S_INSTANCE_NUM == 2)
        case CLK_I2S1:
#endif
        
            if(mod_p->BF.LOCK != 0U)
            {
                /* unlock this register */
                mod_p->WORDVAL = 0x5B000000U;
            }
            if(CLK_SRC_LPO32K == clockSource)
            {
                mod_p->BF.CLKMUX = (uint32_t)clockSource;
            }
            else if(CLK_SRC_OSC32K == clockSource)
            {
                mod_p->BF.CLKMUX = (uint32_t)clockSource;
            }
            else if(CLK_SRC_FIRC64M == clockSource)
            {
                mod_p->BF.CLKMUX = (uint32_t)clockSource;
            }
            else if(CLK_SRC_OSC40M == clockSource)
            {
                mod_p->BF.CLKMUX = (uint32_t)clockSource;
            }
            else if(CLK_SRC_PLL == clockSource)
            {
                mod_p->BF.CLKMUX = (uint32_t)clockSource;
            }
            else if(CLK_SRC_NO == clockSource)
            {
                mod_p->BF.CLKMUX = (uint32_t)clockSource;
            }
            else
            {
                res = ERR;
            }
            mod_p->BF.LOCK = 1U;
            break;
        case CLK_CAN0:
        case CLK_CAN1:
        case CLK_CAN2:
        case CLK_CAN3:
#if (CAN_INSTANCE_NUM == 6) || (CAN_INSTANCE_NUM == 8) 
        case CLK_CAN4:
        case CLK_CAN5:
#endif
#if (CAN_INSTANCE_NUM == 8) 
        case CLK_CAN6:
        case CLK_CAN7:
#endif
            if(mod_p->BF.LOCK != 0U)
            {
                /* unlock this register */
                mod_p->WORDVAL = 0x5B000000U;
            }
            if(CLK_SRC_FIRC64M == clockSource)
            {
                mod_p->BF.CLKMUX = (uint32_t)clockSource;
            }
            else if(CLK_SRC_OSC40M == clockSource)
            {
                mod_p->BF.CLKMUX = (uint32_t)clockSource;
            }
            else if(CLK_SRC_PLL == clockSource)
            {
                mod_p->BF.CLKMUX = (uint32_t)clockSource;
            }
            else if(CLK_SRC_NO == clockSource)
            {
                mod_p->BF.CLKMUX = (uint32_t)clockSource;
            }
            else
            {
                res = ERR;
            }
            mod_p->BF.LOCK = 1U;
            break;

        case CLK_FLASH:
            if(mod_p->BF.LOCK  != 0U)
            {
                /* unlock this register */
                mod_p->WORDVAL = 0x5B000000U;
            }
            if(CLK_SRC_FIRC64M == clockSource)
            {
                mod_p->BF.CLKMUX = (uint32_t)clockSource;
            }
            else if(CLK_SRC_OSC40M == clockSource)
            {
                mod_p->BF.CLKMUX = (uint32_t)clockSource;
            }
            else if(CLK_SRC_PLL == clockSource)
            {
                mod_p->BF.CLKMUX = (uint32_t)clockSource;
            }
            else if(CLK_SRC_SLOW == clockSource)
            {
                mod_p->BF.CLKMUX = (uint32_t)clockSource;
            }
            else if(CLK_SRC_NO == clockSource)
            {
                mod_p->BF.CLKMUX = (uint32_t)clockSource;
            }
            else
            {
                res = ERR;
            }
            mod_p->BF.LOCK = 1U;
            break;

        case CLK_EWDT:
        case CLK_ADC0:
        case CLK_ADC1:
        case CLK_PORTA:
        case CLK_PORTB:
        case CLK_PORTC:
        case CLK_PORTD:
        case CLK_PORTE:
            if(mod_p->BF.LOCK  != 0U)
            {
                /* unlock this register */
                mod_p->WORDVAL = 0x5B000000U;
            }
            if(CLK_SRC_LPO32K == clockSource)
            {
                mod_p->BF.CLKMUX = (uint32_t)clockSource;
            }
            else if(CLK_SRC_OSC32K == clockSource)
            {
                mod_p->BF.CLKMUX = (uint32_t)clockSource;
            }
            else if(CLK_SRC_FIRC64M == clockSource)
            {
                mod_p->BF.CLKMUX = (uint32_t)clockSource;
            }
            else if(CLK_SRC_OSC40M == clockSource)
            {
                mod_p->BF.CLKMUX = (uint32_t)clockSource;
            }
            else if(CLK_SRC_NO == clockSource)
            {
                mod_p->BF.CLKMUX = (uint32_t)clockSource;
            }
            else
            {
                res = ERR;
            }
            mod_p->BF.LOCK = 1U;
            break;

        default:
            res = ERR;
            break;
    }
    return res;
}


/**
 * @brief      Get module clock frequency before divider
 *
 * @param[in]  module: select the module
 * @param[in]  oscFreq: frequency of the OSC clock
 *
 * @return     freq: The clock frequency. If return 0, there is some error.
 *
 */
uint32_t CLK_GetModuleClkFreq(CLK_Module_t module,uint32_t oscFreq)
{
    ModuleClk_t *mod_p = (ModuleClk_t *)(parccRegPtr[((uint32_t)module>> 2U)]);
    uint32_t freq = 0;
    uint32_t divider = 1;

    switch(module)
    {        
        case CLK_EWDT:
        case CLK_STIM:
        case CLK_TIM0:
        case CLK_TIM1:
        case CLK_TIM2:
        case CLK_TIM3:
        case CLK_MCPWM0:
        case CLK_MCPWM1:
        case CLK_TDG0:
        case CLK_TDG1:
        case CLK_CAN0:
        case CLK_CAN1:
        case CLK_CAN2:
        case CLK_CAN3:
#if (CAN_INSTANCE_NUM == 6) || (CAN_INSTANCE_NUM == 8) 
        case CLK_CAN4:
        case CLK_CAN5:
#endif
#if (CAN_INSTANCE_NUM == 8) 
        case CLK_CAN6:
        case CLK_CAN7:
#endif
        case CLK_UART0:
        case CLK_UART1:
        case CLK_UART2:
        case CLK_UART3:
        case CLK_UART4:
        case CLK_UART5:
        case CLK_SPI0:
        case CLK_SPI1:
        case CLK_SPI2:
        case CLK_SPI3:
        case CLK_I2C0:  
#if (I2C_INSTANCE_NUM == 2)
        case CLK_I2C1: 
#endif
        case CLK_I2S0:
#if (I2S_INSTANCE_NUM == 2)
        case CLK_I2S1:
#endif
        case CLK_ADC0:
        case CLK_ADC1:
        case CLK_FLASH:
        case CLK_PORTA:
        case CLK_PORTB:
        case CLK_PORTC:
        case CLK_PORTD:
        case CLK_PORTE:
            divider = (mod_p->BF.CLKDIV + (uint32_t)1U);
            switch((CLK_Src_t)mod_p->BF.CLKMUX)
            {
                case CLK_SRC_LPO32K:
                    freq = 32000U;
                    break;
            
                case CLK_SRC_OSC32K:
                    freq = 32768U;
                    break;

                case CLK_SRC_FIRC64M:
                   freq = 64000000U;
                   break;

                case CLK_SRC_OSC40M:
                    freq = oscFreq;
                    break;
                
                case CLK_SRC_PLL:
                    freq = CLK_GetPLLFreq(PLL_OSC_CLK, oscFreq);
                    break;

                case CLK_SRC_SLOW:
                    divider = (sccRegBfPtr->SCC_CST.DIVCORE + (uint32_t)1U);
                    divider *= (sccRegBfPtr->SCC_CST.DIVSLOW + (uint32_t)1U);
                    freq = CLK_GetSysClkFreq(oscFreq);
                    break;
            
                default:
                    /*nothing to do*/
                    break;
            }
            break;
        
        case CLK_CORE:
            divider = (sccRegBfPtr->SCC_CST.DIVCORE + (uint32_t)1U);
            freq = CLK_GetSysClkFreq(oscFreq);
            break;
        
        case CLK_BUS:
            divider = (sccRegBfPtr->SCC_CST.DIVCORE + (uint32_t)1U);
            divider *= (sccRegBfPtr->SCC_CST.DIVBUS + (uint32_t)1U);
            freq = CLK_GetSysClkFreq(oscFreq);
            break;
        
        case CLK_SLOW:
            divider = (sccRegBfPtr->SCC_CST.DIVCORE + (uint32_t)1U);
            divider *= (sccRegBfPtr->SCC_CST.DIVSLOW + (uint32_t)1U);
            freq = CLK_GetSysClkFreq(oscFreq);
            break;

        default:
            /*nothing to do*/
            break;
    }
    
    return freq/divider;
    
}

/**
 * @brief      Get the clock source status
 *
 * @param[in]  clockSource: clock source
 *                              -CLK_SRC_NO
 *                              -CLK_SRC_LPO32K
 *                              -CLK_SRC_OSC32K
 *                              -CLK_SRC_FIRC64M
 *                              -CLK_SRC_OSC40M
 *                              -CLK_SRC_PLL
 *
 * @return     bitStatus: The clock source status
 *
 */
FlagStatus_t CLK_GetClkStatus(CLK_Src_t clockSource)
{
    FlagStatus_t bitStatus = RESET;
    switch(clockSource)
    {
        case CLK_SRC_LPO32K:
            bitStatus = ((pmuRegBfPtr->PMU_LPO_32K_CFG.LPO_CLK_READY != 0U) ? SET :
                              RESET);
            break;
        
        case CLK_SRC_FIRC64M:
            bitStatus = ((sccRegBfPtr->SCC_FIRCCS.FIRCRDY != 0U) ? SET : RESET);
            break;

        case CLK_SRC_OSC32K:
            bitStatus = ((rtcRegBfPtr->RTC_CSR.OSC_RDY != 0U) ? SET : RESET);
            break;

        case CLK_SRC_OSC40M:
            bitStatus = ((sccRegBfPtr->SCC_OSCCS.OSCRDY != 0U) ? SET : RESET);
            break;

        case CLK_SRC_PLL:
            bitStatus = ((sccRegBfPtr->SCC_SPLLCS.SPLLRDY != 0U) ? SET : RESET);
            break;

        default:
            /*nothing to do*/
            break;
    }

    return bitStatus;
}

/**
 * @brief      Wait the clock source status until it is ready
 *
 * @param[in]  clockSource: the clock source to be waited
 *                              -CLK_SRC_NO
 *                              -CLK_SRC_LPO32K
 *                              -CLK_SRC_OSC32K
 *                              -CLK_SRC_FIRC64M
 *                              -CLK_SRC_OSC40M
 *                              -CLK_SRC_PLL
 *
 * @return   retVal:
              -SUCC -- the clock is ready
 *            -ERR -- time out
 *
 */
ResultStatus_t CLK_WaitClkReady(CLK_Src_t clockSource)
{
    volatile uint32_t localCnt = 0;
    ResultStatus_t retVal = SUCC;

    switch(clockSource)
    {
        case CLK_SRC_LPO32K:
            while(pmuRegBfPtr->PMU_LPO_32K_CFG.LPO_CLK_READY == 0U)
            {
                if(localCnt > CLK_TIMEOUT_WAIT_CNT)
                {
                    retVal = ERR;
                    break;
                }
                else
                {
                    localCnt++;
                }               
            }
            break;

        case CLK_SRC_FIRC64M:
            while(sccRegBfPtr->SCC_FIRCCS.FIRCRDY == 0U)
            {
                if(localCnt > CLK_TIMEOUT_WAIT_CNT)
                {
                    retVal = ERR;
                    break;
                }
                else
                {
                    localCnt++;
                }                
            }
            break;

        case CLK_SRC_OSC32K:
            while(rtcRegBfPtr->RTC_CSR.OSC_RDY == 0U)
            {
                if(localCnt > CLK_TIMEOUT_WAIT_CNT_OSC32K)
                {
                    retVal = ERR;
                    break;
                }
                else
                {
                    localCnt++;
                }
            }
            break;

        case CLK_SRC_OSC40M:
            while(sccRegBfPtr->SCC_OSCCS.OSCRDY == 0U)
            {
                if(localCnt > CLK_TIMEOUT_WAIT_CNT)
                {
                    retVal = ERR;
                    break;
                }
                else
                {
                    localCnt++;
                }
            }
            break;

        case CLK_SRC_PLL:
            while(sccRegBfPtr->SCC_SPLLCS.SPLLRDY == 0U)
            {
                if(localCnt > CLK_TIMEOUT_WAIT_CNT)
                {
                    retVal = ERR;
                    break;
                }
                else
                {
                    localCnt++;
                }
            }
            break;

        default:
            retVal = ERR;
            break;
    }

    return retVal;
}

/**
 * @brief      Config and Enable clock output
 *
 * @param[in]  outSrc:  Select the clock source to be output.
 *                          -CLK_OUT_FIRC64M
 *                          -CLK_OUT_OSC40M
 *                          -CLK_OUT_PLL
 *                          -CLK_OUT_SLOW
 *                          -CLK_OUT_BUS
 *                          -CLK_OUT_CORE
 *                          -CLK_OUT_OSC32K
 *                          -CLK_OUT_LPO32K
 * @param[in]  divider: output clock divider
 *                          -CLK_OUT_DIV_1
 *                          -CLK_OUT_DIV_2
 *                          -CLK_OUT_DIV_4
 *                          -CLK_OUT_DIV_8
 *
 * @return none
 *
 */
void CLK_ClkOutEnable(CLK_OutSrc_t outSrc, CLK_OutDiv_t divider)
{
    /*Disable clock out first before switching*/
    scmRegBfPtr->SCM_CHIPCTL.CLKOUTEN = 0;

    switch(outSrc)
    {
        case CLK_OUT_OSC40M:
        case CLK_OUT_FIRC64M:
        case CLK_OUT_PLL:
        case CLK_OUT_SLOW:
        case CLK_OUT_BUS:
        case CLK_OUT_CORE:
            scmRegBfPtr->SCM_CHIPCTL.CLKOUTSEL = 0;
            sccRegBfPtr->SCC_CLKOUTCFG.CLKOUTSEL = (uint32_t)outSrc;
            break;

        case CLK_OUT_OSC32K:
            scmRegBfPtr->SCM_CHIPCTL.CLKOUTSEL = 1;
            break;
    
        case CLK_OUT_LPO32K:
            scmRegBfPtr->SCM_CHIPCTL.CLKOUTSEL = 2;
            break;

        default:
            /*nothing to do*/
            break;
    }

    scmRegBfPtr->SCM_CHIPCTL.CLKOUTDIV = (uint32_t)divider;

    /* Enable clock out */
    scmRegBfPtr->SCM_CHIPCTL.CLKOUTEN = 1;
}

/**
 * @brief      Disable clock output
 *
 * @param[in]  none
 *
 * @return none
 *
 */
void CLK_ClkOutDisable(void)
{
    scmRegBfPtr->SCM_CHIPCTL.CLKOUTEN = 0U;
}

/**
 * @brief      Install call back function
 *
 * @param[in]  intId: select the interrupt
 *                      -CLK_INT_OSCLOC
 *                      -CLK_INT_FIRCLOC
 *                      -CLK_INT_ALL
 * @param[in]  cbFun: pointer to callback function
 *
 * @return none
 *
 */
void CLK_InstallCallBackFunc(CLK_Int_t intId,isr_cb_t * cbFun)
{
    sccIsrCbFunc[intId] = cbFun;
}

/**
 * @brief      Clear Interrupt status
 *
 * @param[in]  intId: select the interrupt
 *                      -CLK_INT_OSCLOC
 *                      -CLK_INT_FIRCLOC
 *                      -CLK_INT_ALL
 *
 * @return none
 *
 */
void CLK_IntClear(CLK_Int_t intId)
{
    if(intId == CLK_INT_OSCLOC)
    {
        if(sccRegBfPtr->SCC_OSCCS.LOCK != 0U)
        {
            /* unlock this register */
            sccRegWPtr->SCC_OSCCS = 0x5B000000U;
        }

        /* clear int status */
        sccRegBfPtr->SCC_OSCCS.OSCLOC = 1U;
        /* lock */
        sccRegBfPtr->SCC_OSCCS.LOCK = 1U;
    }
    
    else if(intId == CLK_INT_FIRCLOC)
    {
        if(sccRegBfPtr->SCC_FIRCCS.LOCK != 0U)
        {
            /* unlock this register */
            sccRegWPtr->SCC_FIRCCS = 0x5B000000U;
        }

        /* clear int status */
        sccRegBfPtr->SCC_FIRCCS.FIRCLOC = 1U;
        /* lock */
        sccRegBfPtr->SCC_FIRCCS.LOCK = 1U;
    }
    
    else
    {
        /* Do nothing */
    }
}

/** @} end of group Clock_Public_Functions */

/** @} end of group Clock */

/** @} end of group Z20K14XM_Peripheral_Driver */
