#include "usart1.h"
#include <string.h>
#include "fifo.h"
#include "Command_Parse.h"
#ifdef free_os
#include "FreeRTOS.h"  
#include "task.h"  
#include "queue.h" 
#endif
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart3;
void MX_USART1_UART_Init(void)
{
	huart1.Instance = USART1;
	huart1.Init.BaudRate = 115200;
	huart1.Init.WordLength = UART_WORDLENGTH_8B;
	huart1.Init.StopBits = UART_STOPBITS_1;
	huart1.Init.Parity = UART_PARITY_NONE;
	huart1.Init.Mode = UART_MODE_TX_RX;
	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart1.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart1) != HAL_OK)
	{
		while(1);//_Error_Handler(__FILE__, __LINE__);
	}
	Uart1_Init();
	Re_start_uart1_idle();
}
void MX_USART3_UART_Init(void)
{
	huart3.Instance = USART3;
	huart3.Init.BaudRate = 115200;
	huart3.Init.WordLength = UART_WORDLENGTH_8B;
	huart3.Init.StopBits = UART_STOPBITS_1;
	huart3.Init.Parity = UART_PARITY_NONE;
	huart3.Init.Mode = UART_MODE_TX_RX;
	huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart3.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart3) != HAL_OK)
	{
		while(1);//_Error_Handler(__FILE__, __LINE__);
	}
}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct;
  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspInit 0 */

  /* USER CODE END USART1_MspInit 0 */
    /* USART1 clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();
  
    /**USART1 GPIO Configuration    
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USART1 interrupt Init */
    HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspInit 1 */
	__HAL_UART_ENABLE_IT(&huart1,UART_IT_RXNE); 
  /* USER CODE END USART1_MspInit 1 */
  }
  else if(uartHandle->Instance==USART3)
  {
  /* USER CODE BEGIN USART3_MspInit 0 */

  /* USER CODE END USART3_MspInit 0 */
    /* USART3 clock enable */
    __HAL_RCC_USART3_CLK_ENABLE();
  
    /**USART3 GPIO Configuration    
    PB10     ------> USART3_TX
    PB11     ------> USART3_RX 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* USART3 interrupt Init */
    HAL_NVIC_SetPriority(USART3_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART3_IRQn);
  /* USER CODE BEGIN USART3_MspInit 1 */

  /* USER CODE END USART3_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspDeInit 0 */

  /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();
  
    /**USART1 GPIO Configuration    
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX 
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9|GPIO_PIN_10);

    /* USART1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }
  else if(uartHandle->Instance==USART3)
  {
  /* USER CODE BEGIN USART3_MspDeInit 0 */

  /* USER CODE END USART3_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART3_CLK_DISABLE();
  
    /**USART3 GPIO Configuration    
    PB10     ------> USART3_TX
    PB11     ------> USART3_RX 
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_10|GPIO_PIN_11);

    /* USART3 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART3_IRQn);
  /* USER CODE BEGIN USART3_MspDeInit 1 */

  /* USER CODE END USART3_MspDeInit 1 */
  }
} 

_Uart1 Uart1;

_uart1RxState uart1RxState;
/**
* @brief This function handles USART1 global interrupt.
*/
void USART1_IRQHandler(void)
{
	//HAL_UART_IRQHandler(&huart1);
	user_Uart1Handler();
}
//extern QueueHandle_t Message_Queue;	//��Ϣ���о��
void user_Uart1Handler()
{
//	BaseType_t xHigherPriorityTaskWoken;
	u8 temp=0;
	if((__HAL_UART_GET_FLAG(&huart1,UART_FLAG_RXNE)!=RESET))
	{
		temp = (uint8_t)(huart1.Instance->DR&(uint8_t)0x00FF);
		__HAL_UART_CLEAR_FLAG(&huart1,UART_FLAG_RXNE);
//		fifo_putc(&ReceiveFIFO,temp);
		if(uart1RxState == UART_RX_STATE_READY)//���յ�һ֡�еĵ�һ���ֽ�
		{
			__HAL_UART_ENABLE_IT(&huart1,UART_IT_IDLE);  //�򿪿����ж�
			uart1RxState = UART_RX_STATE_START;
			Uart1.Len = 0;
			Uart1.RxBuff[Uart1.Len++] = temp;			
		}
		else if(uart1RxState == UART_RX_STATE_START) 
		{
			Uart1.RxBuff[Uart1.Len++] = temp;//���յ�һ��ָ��,������Ӳ���			
		}
	}
	if((__HAL_UART_GET_FLAG(&huart1,UART_FLAG_IDLE)!=RESET)) //��������ж�
	{         
//		__HAL_UART_CLEAR_FLAG(&huart1,UART_FLAG_IDLE);
		__HAL_UART_DISABLE_IT(&huart1,UART_IT_IDLE);   //���˿����ж�
		__HAL_UART_DISABLE_IT(&huart1,UART_IT_RXNE);   //���˽�������ж�
		fifo_puts(&ReceiveFIFO,&Uart1.RxBuff[0],Uart1.Len);
		Uart1.over = true;
//		if(Message_Queue!=NULL)
//		{
//			xQueueSendFromISR(Message_Queue,Uart1.over,&xHigherPriorityTaskWoken);//������з�������	
//			memset(Uart1.over,0,sizeof(Uart1.over));
//			portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
//		}
	}	
}
void Uart1_Init()
{
	Uart1.Len = 0;
	Uart1.over = 0;
	memset(Uart1.RxBuff,0,sizeof(Uart1.RxBuff));
//    /* Enable the UART Parity Error Interrupt */
//    __HAL_UART_ENABLE_IT(&huart1, UART_IT_PE);//ʹ��
//    /* Enable the UART Error Interrupt: (Frame error, noise error, overrun error) */
//    __HAL_UART_ENABLE_IT(&huart1, UART_IT_ERR);//ʹ�ܴ��ڴ����ж�
    /* Enable the UART Data Register not empty Interrupt */
    __HAL_UART_ENABLE_IT(&huart1, UART_IT_RXNE);//ʹ�ܴ��ڽ����ж�
}
void Re_start_uart1_idle()
{
	uart1RxState = UART_RX_STATE_READY;
    /* Enable the UART Parity Error Interrupt */
//    __HAL_UART_ENABLE_IT(&huart1, UART_IT_PE);//ʹ��
//    /* Enable the UART Error Interrupt: (Frame error, noise error, overrun error) */
//    __HAL_UART_ENABLE_IT(&huart1, UART_IT_ERR);//ʹ�ܴ��ڴ����ж�
    /* Enable the UART Data Register not empty Interrupt */
    __HAL_UART_ENABLE_IT(&huart1, UART_IT_RXNE);//ʹ�ܴ��ڽ����ж�
}





struct __FILE 
{ 
	int handle; 
}; 
FILE __stdout;       
void _sys_exit(int x) 
{ 
	x = x; 
} 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);
	USART1->DR = (uint8_t) ch;      
	return ch;
}


