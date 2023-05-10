#include "clock_config.h"
#include "serial.h"

#include "tim_drv.h"
#include "gpio_drv.h"
#include "clock_drv.h"
#include "sysctrl_drv.h"
#include "int_drv.h"

#define OSC40M_ENABLE 1

#define DBUG_TIM1

#ifdef DBUG_TIM0
#define TIM_ID TIM0_ID
#elif defined DBUG_TIM1
#define TIM_ID TIM1_ID
#elif defined DBUG_TIM2
#define TIM_ID TIM2_ID
#else
#define TIM_ID TIM3_ID
#endif

/* TIM software control output config struct definition */ 
const TIM_OutputSWCtrlConfig_t config2 = 
{
    ENABLE, LEVEL_HIGH
};

const TIM_OutputSWCtrlConfig_t config3 = 
{
    ENABLE, LEVEL_LOW
};

/* work in complementary: COMB = 1 */
void sw_test()
{   
    /* output software control config */
    TIM_OutputSWCtrlConfig(TIM_ID, TIM_CHANNEL_2, &config2);
    TIM_OutputSWCtrlConfig(TIM_ID, TIM_CHANNEL_3, &config3);
        
    /*start counter*/
    TIM_StartCounter(TIM_ID, TIM_CLK_SOURCE_SYSTEM, TIM_CLK_DIVIDE_1);
    /* reload flag clear */
    TIM_IntClear(TIM_ID, TIM_INT_RLD);
           
    printf("the software control value is %x  \n",TIM_GetOutputSwCtrlVal(TIM_ID));
    while(1);
}

int main(void)
{
    /* CLock init*/
    #if OSC40M_ENABLE
    OSC40M_ClockInit();
    #else
    PLL80M_ClockInit();
    #endif
    
    /* Serial port init*/
    Ex_BoardUartInit();

    /* Print example name*/
    printf("20k14x_app Timer start.\n");

    #ifdef DBUG_TIM0
     /* module enable  */ 
    CLK_ModuleSrc(CLK_TIM0, CLK_SRC_OSC40M);
    CLK_SetClkDivider(CLK_TIM0, CLK_DIV_1);
    SYSCTRL_EnableModule(SYSCTRL_TIM0);
    CLK_ModuleSrc(CLK_PORTC, CLK_SRC_OSC40M);
    SYSCTRL_EnableModule(SYSCTRL_PORTC);
    /* config gpio*/
    PORT_PinmuxConfig(PORT_D, GPIO_0, PTD0_TIM0_CH2);
    PORT_PinmuxConfig(PORT_C, GPIO_3, PTC3_TIM0_CH3);
     /* enable IRQ*/
    NVIC_EnableIRQ(TIM0_Ch_IRQn);
    #endif
    
    /* TIM1*/
    #ifdef DBUG_TIM1
     /* module enable  */ 
    CLK_ModuleSrc(CLK_TIM1, CLK_SRC_OSC40M);
    CLK_SetClkDivider(CLK_TIM1, CLK_DIV_1);
    SYSCTRL_EnableModule(SYSCTRL_TIM1);
    CLK_ModuleSrc(CLK_PORTA, CLK_SRC_OSC40M);
    SYSCTRL_EnableModule(SYSCTRL_PORTA);
    PORT_PinmuxConfig(PORT_A, GPIO_15, PTA15_TIM1_CH2);
    PORT_PinmuxConfig(PORT_A, GPIO_16, PTA16_TIM1_CH3);
     /* enable IRQ*/
    INT_EnableIRQ(TIM1_Ch_IRQn);
    #endif
    
       /*TIM2*/
    #ifdef DBUG_TIM2 
    /* module enable  */ 
    CLK_ModuleSrc(CLK_TIM2, CLK_SRC_OSC40M);
    CLK_SetClkDivider(CLK_TIM2, CLK_DIV_1);
    SYSCTRL_EnableModule(SYSCTRL_TIM2);
    SYSCTRL_EnableModule(SYSCTRL_PORTD);
    PORT_PinmuxConfig(PORT_D, GPIO_12, PTD12_TIM2_CH2);
    PORT_PinmuxConfig(PORT_D, GPIO_5, PTD5_TIM2_CH3);
     /* enable IRQ*/
    INT_EnableIRQ(TIM2_Ch_IRQn);
    #endif
    
    /*TIM3*/
    #ifdef DBUG_TIM3 
    /* module enable  */ 
    CLK_ModuleSrc(CLK_TIM3, CLK_SRC_OSC40M);
    CLK_SetClkDivider(CLK_TIM3, CLK_DIV_1);
    SYSCTRL_EnableModule(SYSCTRL_TIM3);
    SYSCTRL_EnableModule(SYSCTRL_PORTB);
    PORT_PinmuxConfig(PORT_B, GPIO_10, PTB10_TIM3_CH2);
    PORT_PinmuxConfig(PORT_B, GPIO_11, PTB11_TIM3_CH3);
     /* enable IRQ*/
    INT_EnableIRQ(TIM3_Ch_IRQn);
    #endif
    
    /* OUTPUT ENABLE*/
    TIM_ChannelOutputEnable(TIM_ID, TIM_CHANNEL_2);
    TIM_ChannelOutputEnable(TIM_ID, TIM_CHANNEL_3);
    
    sw_test();    
    
    while(1);
}
