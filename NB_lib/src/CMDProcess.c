/******************************Copyright(C) Nubo*******************************
File name  : cmdProcess.c
Description: process command 
Platform   : MDK V5.23.0.0
Version    : V1.0
Author     : Joey
Create Time: 2018-1-3
Modify     : 
Modify Time: 
******************************************************************************/
#include "CMDProcess.h"
#include "Thread.h"
#include "fifo.h"
#include "command.h"
#include "uartfifo.h"
#include "Object.h"
#include "SysExeAttr.h"
#include "MsgPackage.h"

//Private macro define
//定义Process初始化宏
#define   PROCESS_INIT(pStruct,_flag,_con,_prc_msg,_get_msg)  do{(pStruct)->flag = (_flag);\
                                                                 (pStruct)->con = (_con);\
                                                                 (pStruct)->process_msg = (_prc_msg);\
                                                                 (pStruct)->get_msg = (_get_msg);\
                                                                }while(0)

//Public variable define
struct process_data uart1rcv_pd;
struct process_data uart1send_pd;

//Private function declaration
static void DataSend_Thread(void);

/*****************************************************************************
函数  名:   void CMDProcessInit(void)
功能说明:   命令处理函数初始化
参    数:   void
返回  值:   void
说    明:   无
*****************************************************************************/
void CMDProcessInit(void)
{
    FIFO_Uart1_Init();
    
    PROCESS_INIT(&uart1rcv_pd, 0, NORMAL, Msg_Process, cmd_get);
    PROCESS_INIT(&uart1send_pd, 0, NORMAL, Send_Process, cmd_get);
		
    Thread_Login(FOREVER, 0, 40, &DataSend_Thread);
}

/*****************************************************************************
函数  名:   void Start_Task(void)
功能说明:   任务处理
参    数:   void
返回  值:   void
说    明:   无
*****************************************************************************/
void Process_RecieveFIFO_Task(void)
{
    Process_FIFOData(&rcvuart1fifo, &uart1rcv_pd);        	//常规帧接收fifo处理
}

/*****************************************************************************
函数  名:   DataSend_Thread
功能说明:   数据发送线程
参    数:   void
返回  值:   void
*****************************************************************************/
void DataSend_Thread(void)
{
    Process_FIFOData(&senduart1fifo, &uart1send_pd);          //处理发送FIFO
}

/*******************************************************************
函 数 名：  Send_FIFOData
功能说明：  将uart队列中的数据通过uart发送出去
参    数：  fifo:   操作目标FIFO
            send:   将发送的数据内容
            fun:    发送函数
返 回 值：  无
*******************************************************************/
void Process_FIFOData(struct fifo_data *fifo, struct process_data *prc)
{
    switch (prc->flag)
    {
    case 0:
        if (0 == (prc->len = prc->get_msg(prc->data, fifo))) //从FIFO中获取一条指令失败
        {
            break;
        }

    case 1:
        if (FALSE == (prc->process_msg(prc->data, prc->len))) //数据处理还未完成
        {
            prc->flag = 1;
            break;
        }
				
    default:
        prc->flag = 0;
        break;
    }
}

/*******************************************************************
函 数 名：  Msg_Process
功能说明：  消息处理函数
参    数：  pMsg:   消息内容
            *data;  参数区内容
返 回 值：  无
*******************************************************************/
u8 Msg_Process(u8 *sdata, u32 len)
{
	MsgResult_t result = NO_CMD;
	struct comdata *p_msg = (struct comdata*)sdata;  

	if ((result = Object_Check(p_msg, len)) == COMPLETE) //目标核对成功
	{
		result =  Msg_Execute((u8 *)p_msg,len);
		if (result != NO_ACK)
		{
			Msg_Feedback(p_msg);
		}
	}
	return TRUE;
}

/******************************************************************************
Function   : u8 Msg_Execute(u8 *sdata, u32 len)
Description: message execute function
Input      : sdata - communication data frame
             len   - sdata's length
Output     : u8    - 
Author     : Joey
Time       : 2017-12-22
******************************************************************************/
MsgResult_t Msg_Execute(u8 *sdata, u32 len)
{
	u8 ack_len = 0;
	u8 i;
	u8 count = GetAttrNum();
	MsgResult_t result = NO_CMD;
	struct comdata *pdata = (struct comdata *)sdata;
    const struct attr_exe_data* p_attr_exe = SysAttrTable;

	for(i=0; i<count; i++)
	{
		if(p_attr_exe->cmd == pdata->cmd) 
		{
			//differentiate write and read attribute
			if(p_attr_exe->exe_attr != NULL)
			{
				result = p_attr_exe->exe_attr(pdata->data, pdata->length, &ack_len, pdata->data+1);
			}
			break;
		}
		p_attr_exe++;
	}

	if(i == count)//NO_CMD
	{
		return result;
	}

	pdata->length = ack_len + 12;//the number 11 is other inherent length
	*pdata->data  = result;
	return result;
}

