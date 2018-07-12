#include "stm32f1xx.h"
#include "usart1.h"
#include "485_function.h"
#include "Command_Parse.h"
//#include "fifo.h"
#ifdef free_os
#include "MyTask.h"
#include "FreeRTOS.h"  
#include "task.h"  
#include "queue.h" 

extern TaskHandle_t StartTask_Handler;

#define KEY_TASK_PRIO		2
#define KEY_STK_SIZE 		128  
TaskHandle_t KeyTask_Handler;
void key_task(void *pvParameters);

#define TASK1_TASK_PRIO		3
#define TASK1_STK_SIZE 		128  
TaskHandle_t Task1Task_Handler;
void task1_task(void *pvParameters);

//#define TASK2_TASK_PRIO		4
//#define TASK2_STK_SIZE 		128  
//TaskHandle_t Task2Task_Handler;
//void task2_task(void *pvParameters);

//开始任务任务函数
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           //进入临界区
	//创建KEY任务
	xTaskCreate((TaskFunction_t )key_task,             
                (const char*    )"key_task",           
                (uint16_t       )KEY_STK_SIZE,        
                (void*          )NULL,                  
                (UBaseType_t    )KEY_TASK_PRIO,        
                (TaskHandle_t*  )&KeyTask_Handler);  
    //创建TASK1任务
    xTaskCreate((TaskFunction_t )task1_task,             
                (const char*    )"task1_task",           
                (uint16_t       )TASK1_STK_SIZE,        
                (void*          )NULL,                  
                (UBaseType_t    )TASK1_TASK_PRIO,        
                (TaskHandle_t*  )&Task1Task_Handler);   
    //创建TASK2任务
//    xTaskCreate((TaskFunction_t )task2_task,     
//                (const char*    )"task2_task",   
//                (uint16_t       )TASK2_STK_SIZE,
//                (void*          )NULL,
//                (UBaseType_t    )TASK2_TASK_PRIO,
//                (TaskHandle_t*  )&Task2Task_Handler); 

    vTaskDelete(StartTask_Handler); //删除开始任务
    taskEXIT_CRITICAL();            //退出临界区
}
void test_malloc()
{
	typedef struct data_type{
		int age;
		char name[20];
	}data;

	data*bob=NULL;
	bob=(data*)malloc(sizeof(data));
	if(bob!=NULL)
	{
		bob->age=22;
		strcpy(bob->name,"Robert");
		printf("%sis%dyearsold\n",bob->name,bob->age);
	}
	else
	{
		printf("mallocerror!\n");
		exit(-1);
	}
	free(bob);
	bob=NULL;
}
//key任务函数
void key_task(void *pvParameters)
{
	while(1)
	{
		if(Uart1.over == true)
		{
			Uart1.over = false;
			Re_start_uart1_idle();
//			USART1_Printf("Receive=%s\r\n",(u8 *)Uart1.RxBuff);
//			Command_Parse((u8 *)Uart1.RxBuff);
//			memset((u8 *)Uart1.RxBuff,0,sizeof(Uart1.RxBuff));
		}
		vTaskDelay(5);
	}
}

//task1任务函数
void task1_task(void *pvParameters)
{
	Init_FIFO();
	while(1)
	{
		Receive_function();
		Transport_function();
		vTaskDelay(10);
	}
}

//task2任务函数
//void task2_task(void *pvParameters)
//{
//	while(1)
//	{
//		;//printf("task2\r\n");
//		vTaskDelay(1200);
//	}
//}


#endif




