#include "Main.h"
#include "LCD.h"
#include "Timer.h"
#include "Display.h"
#include "Slider.h"



/* DISP_Update period */
#define DISP_PERIOD_MS   (20)



void DISP_Init(void)
{
    LCD_Init();
    LCD_SendString(LCD_LINE_1, "Volume:");
}

void DISP_Update(void)
{
    static tWord DISP_counter = 0;
    tWord slider = SLID_GetSlider();
    tByte VolumeString[LCD_LINE_WIDTH + 1];
    tByte index =0;
    tByte limit = (slider * LCD_LINE_WIDTH) /SLID_MAX_READING;

    /* Check if it is time for the DISP_Update to run */
    DISP_counter += TMR_TICK_MS;

    if (DISP_counter != DISP_PERIOD_MS)
    {
        return;
    }
    DISP_counter = 0;

    for (index = 0; index <limit; index++)
    {
        VolumeString[index] = 0x2A;
    }

    for (index=limit;  index < LCD_LINE_WIDTH; index++)
    {
        VolumeString[index] = ' ';
    }
    VolumeString[LCD_LINE_WIDTH] = '\0';
    LCD_SendString(LCD_LINE_2, VolumeString);


}
