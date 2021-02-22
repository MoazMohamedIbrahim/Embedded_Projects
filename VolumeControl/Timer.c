#include "Main.h"
#include "Timer.h"
#include "Display.h"
#include "Slider.h"

void TMR_Init(void)
{
	
	TMR_SET_PRESCALER_256;
	TMR_DISABLE_CLOCK;
	
}
void TMR_Start(void)
{
	
	TMR_CLEAR_FLAG;
	TMR_UPDATE_REGISTER(TMR_TICK_MS);
	TMR_ENABLE_INTERRUPT;
	GLOBAL_INTERRUPT_ENABLE;
	TMR_ENABLE_CLOCK;
	
}
tByte TMR_CheckOverFlow(void)
{
	
	return TMR_GET_FLAG;
	
}
void TMR_Stop(void)
{
	
	TMR_DISABLE_CLOCK;
	
}

void TMR_Update(void) __interrupt 0
{
	
	/* Call Tasks */
	SLID_Update();
	DISP_Update();
	/* Reload timer */
	TMR_CLEAR_FLAG;
	TMR_UPDATE_REGISTER(TMR_TICK_MS);
	

}
