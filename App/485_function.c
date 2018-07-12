#include "485_function.h"
#include <stdarg.h>
#include <string.h>
void DW_485_Receive()
{
	HAL_GPIO_WritePin(DE_WD_PROE, DE_WD_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(RE_WD_PROE, RE_WD_PIN, GPIO_PIN_RESET);
}
void DW_485_Send()
{
	HAL_GPIO_WritePin(DE_WD_PROE, DE_WD_PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(RE_WD_PROE, RE_WD_PIN, GPIO_PIN_SET);
}
void USART1_Printf(const char *fmt, ...)
{
	char SendBuff[256];
	va_list ap;      
	va_start(ap, fmt);  
	vsprintf(SendBuff, fmt, ap);
	va_end(ap);
	SendBuff[sizeof(SendBuff) - 1] = '\0';
	RS485_Send_Data(SendBuff,strlen(SendBuff));
}
void RS485_Send_Data(char *buf,unsigned char len)
{
	u8 t;
	DW_485_Send();        //����Ϊ����ģʽ
	for(t=0;t<len;t++)               //ѭ����������
	{
		while((USART1->SR&0X40)==0);  //�ȴ����ͽ���             
		USART1->DR=buf[t];
	}    
	while((USART1->SR&0X40)==0);     //�ȴ����ͽ���    
	DW_485_Receive();        //����Ϊ����ģʽ 	

}


