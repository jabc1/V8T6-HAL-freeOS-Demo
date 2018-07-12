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
//����Process��ʼ����
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
����  ��:   void CMDProcessInit(void)
����˵��:   ���������ʼ��
��    ��:   void
����  ֵ:   void
˵    ��:   ��
*****************************************************************************/
void CMDProcessInit(void)
{
    FIFO_Uart1_Init();
    
    PROCESS_INIT(&uart1rcv_pd, 0, NORMAL, Msg_Process, cmd_get);
    PROCESS_INIT(&uart1send_pd, 0, NORMAL, Send_Process, cmd_get);
		
    Thread_Login(FOREVER, 0, 40, &DataSend_Thread);
}

/*****************************************************************************
����  ��:   void Start_Task(void)
����˵��:   ������
��    ��:   void
����  ֵ:   void
˵    ��:   ��
*****************************************************************************/
void Process_RecieveFIFO_Task(void)
{
    Process_FIFOData(&rcvuart1fifo, &uart1rcv_pd);        	//����֡����fifo����
}

/*****************************************************************************
����  ��:   DataSend_Thread
����˵��:   ���ݷ����߳�
��    ��:   void
����  ֵ:   void
*****************************************************************************/
void DataSend_Thread(void)
{
    Process_FIFOData(&senduart1fifo, &uart1send_pd);          //������FIFO
}

/*******************************************************************
�� �� ����  Send_FIFOData
����˵����  ��uart�����е�����ͨ��uart���ͳ�ȥ
��    ����  fifo:   ����Ŀ��FIFO
            send:   �����͵���������
            fun:    ���ͺ���
�� �� ֵ��  ��
*******************************************************************/
void Process_FIFOData(struct fifo_data *fifo, struct process_data *prc)
{
    switch (prc->flag)
    {
    case 0:
        if (0 == (prc->len = prc->get_msg(prc->data, fifo))) //��FIFO�л�ȡһ��ָ��ʧ��
        {
            break;
        }

    case 1:
        if (FALSE == (prc->process_msg(prc->data, prc->len))) //���ݴ���δ���
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
�� �� ����  Msg_Process
����˵����  ��Ϣ������
��    ����  pMsg:   ��Ϣ����
            *data;  ����������
�� �� ֵ��  ��
*******************************************************************/
u8 Msg_Process(u8 *sdata, u32 len)
{
	MsgResult_t result = NO_CMD;
	struct comdata *p_msg = (struct comdata*)sdata;  

	if ((result = Object_Check(p_msg, len)) == COMPLETE) //Ŀ��˶Գɹ�
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

