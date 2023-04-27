#include "clock_config.h"
#include "serial.h"

#define OSC40M_ENABLE 1

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
    
    /* clock out configure */
    CLKOUT_Configure();

    /* Print example name*/
    printf("20k14x_app SCM start.\n");
    
    while(1);
}
