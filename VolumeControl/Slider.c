#include "Main.h"
#include "Timer.h"
#include "ADC.h"
#include "Slider.h"

/* SLID_Update period */
#define SLID_PERIOD_MS   (20)

#define SLIDER_CHANNEL (1)

static tWord  Slider = 0;

void SLID_Init(void)
{
    ADC_Init(ADC_FOSC_BY_8);
}
void SLID_Update(void)
{

    static tWord SLID_counter = 0;


    /* Check if it is time for the DISP_Update to run */
    SLID_counter += TMR_TICK_MS;

    if (SLID_counter != SLID_PERIOD_MS)
    {
        return;
    }
    SLID_counter = 0;

    Slider =  ADC_Convert(SLIDER_CHANNEL, ADC_ADJUST_RESULT_LEFT);
}

tWord SLID_GetSlider(void)
{
    return Slider;
}
