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
	//������ʼ����
	xTaskCreate((TaskFunction_t )start_task,            //������
				(const char*    )"start_task",          //��������
				(uint16_t       )START_STK_SIZE,        //�����ջ��С
				(void*          )NULL,                  //���ݸ��������Ĳ���
				(UBaseType_t    )START_TASK_PRIO,       //�������ȼ�
				(TaskHandle_t*  )&StartTask_Handler);   //������              
	vTaskStartScheduler();          //�����������	
#else
	while(1)
	{
		printf("whileuart1test");
		HAL_Delay(500);
	}
#endif
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
