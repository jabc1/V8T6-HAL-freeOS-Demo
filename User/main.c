/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx.h"   
#include "stm32f1xx_hal.h"
#include "Sys.h"
#include "gpio.h"
#include "usart1.h"
#include "tim3.h"
#include "flash.h"
#ifdef free_os
/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"  
#include "task.h"  
#include "queue.h"  

#define START_TASK_PRIO		1
#define START_STK_SIZE 		128  
TaskHandle_t StartTask_Handler;
void start_task(void *pvParameters);
#endif

int main(void)
{
	NVIC_SetVectorTable(NVIC_VectTab_FLASH,0x6400);
	HAL_Init();
	SystemClock_Config();
	GPIO_init();
	MX_USART1_UART_Init();
	USART1_Printf("APP Start!\r\n");
#ifdef free_os	
	//创建开始任务
	xTaskCreate((TaskFunction_t )start_task,            //任务函数
				(const char*    )"start_task",          //任务名称
				(uint16_t       )START_STK_SIZE,        //任务堆栈大小
				(void*          )NULL,                  //传递给任务函数的参数
				(UBaseType_t    )START_TASK_PRIO,       //任务优先级
				(TaskHandle_t*  )&StartTask_Handler);   //任务句柄              
	vTaskStartScheduler();          //开启任务调度	
#else
	while(1)
	{
		printf("whileuart1test");
		HAL_Delay(500);
	}
#endif
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
