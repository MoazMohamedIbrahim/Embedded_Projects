#ifndef __SLIDER_H__
#define __SLIDER_H__

#include "Main.h"
#define  SLID_MAX_READING     (1000)

void SLID_Init(void);
void SLID_Update(void);
tWord SLID_GetSlider(void);
#endif // __SLIDER_H__
