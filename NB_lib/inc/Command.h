/******************************Copyright(C) Nubo*******************************
File name  : command.h
Description: get cmd frame from uart fifo
Platform   : MDK V5.23.0.0
Version    : V1.0
Author     : Joey
Create Time: 2018-1-3
Modify     : 
Modify Time: 
******************************************************************************/

#ifndef __COMMAND_H
#define __COMMAND_H
#include "NbType.h"
#include "fifo.h"
#include "NbLibConfig.h"

/*************************************�궨��************************************/ 
//#define CMD_SIZE                    (1024)          //һ��ָ��������
#define ARGE_SEAT                   (2)             //���ݳ���ռ���ֽ���

#pragma pack(1)
//struct communication data
struct comdata
{
    u8  start;
	u16 length;
	u16 addrsrc;
	u16 addrdest;
	u8  num;
	u8  cmd;
	u8  wait;
	u8  data[CMD_SIZE];
};
#pragma pack()

u32 cmd_get(u8 *cmdBuf, struct fifo_data *fifo);
u32 cmd_put(struct fifo_data *fifo, u8 *cmdBuf, u32 cmdLen);
u8 ChkSum(u8 *buf, u16 len);
u8 CalulateSum(u8 *buf, u16 len);
u8 ChkSumEx(u8 *buf, u8 data, u16 len);
#endif
