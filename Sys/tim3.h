#ifndef _tim3_h
#define _tim3_h
#include "stm32f1xx_hal.h"
extern TIM_HandleTypeDef htim3;
void MX_TIM3_Init(void);
#ifdef free_os
extern volatile unsigned long long FreeRTOSRunTimeTicks;
void ConfigureTimeForRunTimeStats(void);
#endif
#endif

