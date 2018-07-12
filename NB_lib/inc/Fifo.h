/******************************Copyright(C) Nubo*******************************
File name  : fifo.h
Description: fifo source code
Platform   : MDK V5.23.0.0
Version    : V1.0
Author     : Joey
Create Time: 2018-1-3
Modify     : 
Modify Time: 
******************************************************************************/

#ifndef __FIFO_H
#define __FIFO_H
#include "NbType.h"

/***********************************�궨��************************************/
/*�ݴ��*/
#define ERRR(conf, ret)      do              \
                            {                \
                                if (conf)    \
                                {            \
                                    ret;     \
                                }            \
                            } while(0) 
                            
#define MIN(a, b)           ((a) > (b) ? (b) : (a))

/*******************************�������ݽṹ**********************************/
struct fifo_data
{
    u8   *data;
    u32   size;
    u32   front;
    u32   rear;
};

/*********************************��������*************************************/
u8 fifo_Init(struct fifo_data *head, u8 *buf, u32 len); //���г�ʼ��
void fifo_Rst(struct fifo_data *head);                        //��ն���
u32 fifo_validSize(struct fifo_data *head);     //���ݿ��ÿռ��С
u8 fifo_empty(struct fifo_data *head);        //�ӿ��ж�
u8 fifo_puts(struct fifo_data *head, u8 *data, u32 len);
u8 fifo_gets(struct fifo_data *head, u8 *data, u32 len);
u8 fifo_putc(struct fifo_data *head, u8 data);
u8 fifo_getc(struct fifo_data *head, u8 *data);
u32 fifo_find(struct fifo_data *head, const u8 *data, u32 len);
u8 fifo_cmp(const struct fifo_data *fifo, u32 seat, const u8 *cmp, u32 cmpsize);
u8 fifo_get_frame(struct fifo_data *head, u8 *data, u32 *len);
                            
#endif 

