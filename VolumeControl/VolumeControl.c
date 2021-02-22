#include "Main.h"
#include "Slider.h"
#include "Timer.h"
#include "Display.h"





tWord __at(0x2007) CONFIG = _HS_OSC & _WDT_OFF & _PWRTE_ON & _BODEN_OFF & _LVP_OFF & _CPD_OFF & _WRT_OFF & _DEBUG_OFF & _CP_OFF;


void main (void)
{
    /* Initialization */
    SLID_Init();
    DISP_Init();
    TMR_Init();
    TMR_Start();

    while (1)
    {
        /* Do nothing */

    }

}

