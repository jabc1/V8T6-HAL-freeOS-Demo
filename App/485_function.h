#ifndef _485_f_h
#define _485_f_h
#include "gpio.h"
void DW_485_Receive(void);
void DW_485_Send(void);
void USART1_Printf(const char *fmt, ...);
void RS485_Send_Data(char *buf,unsigned char len);
#endif
