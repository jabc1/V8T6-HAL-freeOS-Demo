#include "stm32f1xx.h"
#include <stdlib.h>
#include <string.h>

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

#define TASK2_TASK_PRIO		4
#define TASK2_STK_SIZE 		128  
TaskHandle_t Task2Task_Handler;
void task2_task(void *pvParameters);

//��ʼ����������
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           //�����ٽ���
	//����KEY����
	xTaskCreate((TaskFunction_t )key_task,             
                (const char*    )"key_task",           
                (uint16_t       )KEY_STK_SIZE,        
                (void*          )NULL,                  
                (UBaseType_t    )KEY_TASK_PRIO,        
                (TaskHandle_t*  )&KeyTask_Handler);  
    //����TASK1����
    xTaskCreate((TaskFunction_t )task1_task,             
                (const char*    )"task1_task",           
                (uint16_t       )TASK1_STK_SIZE,        
                (void*          )NULL,                  
                (UBaseType_t    )TASK1_TASK_PRIO,        
                (TaskHandle_t*  )&Task1Task_Handler);   
    //����TASK2����
    xTaskCreate((TaskFunction_t )task2_task,     
                (const char*    )"task2_task",   
                (uint16_t       )TASK2_STK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )TASK2_TASK_PRIO,
                (TaskHandle_t*  )&Task2Task_Handler); 

    vTaskDelete(StartTask_Handler); //ɾ����ʼ����
    taskEXIT_CRITICAL();            //�˳��ٽ���
}
void ts()
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
//key������
void key_task(void *pvParameters)
{
	while(1)
	{
		printf("key task printf\r\n");
		vTaskDelay(500);
	}
}

//task1������
void task1_task(void *pvParameters)
{
	while(1)
	{
		printf("task1\r\n");
		vTaskDelay(1000);
	}
}

//task2������
void task2_task(void *pvParameters)
{
	while(1)
	{
		printf("task2\r\n");
		vTaskDelay(1200);
	}
}
#endif




