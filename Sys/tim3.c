#include "tim3.h"
#ifdef free_os
#include "FreeRTOS.h"  
#include "task.h"  
#endif

TIM_HandleTypeDef htim3;

#ifdef free_os
volatile unsigned long long FreeRTOSRunTimeTicks;
extern void xPortSysTickHandler(void);
void SysTick_Handler(void)
{
	HAL_IncTick();
    if(xTaskGetSchedulerState()!=taskSCHEDULER_NOT_STARTED)//系统已经运行
    {
        xPortSysTickHandler();	
    }	
}
void ConfigureTimeForRunTimeStats(void)
{
	//定时器3初始化，定时器时钟为72M，分频系数为72-1，所以定时器3的频率
	//为72M/72=1M，自动重装载为50-1，那么定时器周期就是50us
	FreeRTOSRunTimeTicks=0;
	MX_TIM3_Init();
}
#endif

void TIM3_IRQHandler(void)
{
	//HAL_TIM_IRQHandler(&htim3);
	/* TIM Update event */
	if(__HAL_TIM_GET_FLAG(&htim3, TIM_FLAG_UPDATE) != RESET)
	{
		if(__HAL_TIM_GET_IT_SOURCE(&htim3, TIM_IT_UPDATE) !=RESET)
		{
			__HAL_TIM_CLEAR_IT(&htim3, TIM_IT_UPDATE);
			//HAL_TIM_PeriodElapsedCallback(&htim3);
			FreeRTOSRunTimeTicks++;
		}
	}
}
//回调函数，定时器中断服务函数调用
//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
//{
//    if(htim->Instance == TIM3)//100us
//    {
//		FreeRTOSRunTimeTicks++;
//    }
//}








/* TIM3 init function */
void MX_TIM3_Init(void)
{
	TIM_ClockConfigTypeDef sClockSourceConfig;
	TIM_MasterConfigTypeDef sMasterConfig;

	htim3.Instance = TIM3;
	htim3.Init.Prescaler = 72-1;
	htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim3.Init.Period = 100-1;//100us
	htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
	{
		;//_Error_Handler(__FILE__, __LINE__);
	}
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
	{
		;//_Error_Handler(__FILE__, __LINE__);
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
	{
		;//_Error_Handler(__FILE__, __LINE__);
	}
	HAL_TIM_Base_Start_IT(&htim3);
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* tim_baseHandle)
{

	if(tim_baseHandle->Instance==TIM3)
	{
		/* TIM3 clock enable */
		__HAL_RCC_TIM3_CLK_ENABLE();

		/* TIM3 interrupt Init */
		HAL_NVIC_SetPriority(TIM3_IRQn, 5, 0);
		HAL_NVIC_EnableIRQ(TIM3_IRQn);
	}
}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* tim_baseHandle)
{
	if(tim_baseHandle->Instance==TIM3)
	{
		/* Peripheral clock disable */
		__HAL_RCC_TIM3_CLK_DISABLE();

		/* TIM3 interrupt Deinit */
		HAL_NVIC_DisableIRQ(TIM3_IRQn);
	}
} 



