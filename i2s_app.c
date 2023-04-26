#include "common_drv.h"
#include "wdog_drv.h"
#include "stim_drv.h"
#include "i2s_drv.h"
#include "int_drv.h"
#include "clock_config.h"
#include "serial.h"

int main(void)
{
    /* CLock init*/
    Ex_ClockInit();

    /* Disable wdog (wdog is enabled when default)*/
    WDOG_Disable();

    /* Serial port init*/
    Ex_BoardUartInit();

    /* Print example name*/
    printf("I2S app start.\n");
    
    while(1);
}