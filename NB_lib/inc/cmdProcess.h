/******************************Copyright(C) Nubo*******************************
File name  : cmdProcess.h
Description: process command 
Platform   : MDK V5.23.0.0
Version    : V1.0
Author     : Joey
Create Time: 2018-1-3
Modify     : 
Modify Time: 
******************************************************************************/

#ifndef __CMDPROCESS_H
#define __CMDPROCESS_H
#include "NbType.h"
#include "fifo.h"
#include "NbLibConfig.h"

/*******************************�������ݽṹ**********************************/
#pragma pack(1)
struct process_data
{
    u8 len;                 //sendBuf�������ݳ���
    u8 flag;                //�����־
    u8 con;                 //��������
    u8 mean;                //��������
//    u8 level;               //��Ϣ�ȼ�
    u8 data[CMD_SIZE];           //Ҫ�����ʵ����������
    u8 (*process_msg)(u8 *buf, u32 len);
    u32(*get_msg)(u8 *cmdBuf, struct fifo_data *fifo);
};
#pragma pack()
typedef enum
{
    NORMAL = 0,             //����ģʽ
    MANY_P = 1,             //��δ���
}CMDcon_t;


typedef enum
{
    COMPLETE                = 0,    //�����������
    FRAME_FORM_ERR          = 1,    //֡��ʽ����
    FRAME_LEN_ERR           = 2,    //֡���ȴ���
    FRAME_CHECKSUM_ERR      = 3,    //֡У�����
    FRAME_REPEAT_ERR        = 4,    //֡�ظ�
    CMD_NOTSUPPORT_ERR      = 5,    //���֧��
    DATA_AREA_ERR           = 6,    //��������Ч
    DEVICE_BUSY_ERR         = 7,    //�豸æ
	UPGRADE_VER_ERR         = 8,    //upgrade version is equal

	NO_CMD                  = 13,   //cmd is not existent
	NO_ACK                  = 14,   //no ack
	NO_EXE                  = 15,   //no execute

} MsgResult_t;                      //��Ϣ�������ö����


struct attr_exe_data
{
    u32 cmd;                              //ָ���
    MsgResult_t (*exe_attr)(u8*,u16,u8*,u8*); //exe�������                      
};

struct attr_exe_data_ex
{
    u32 cmd;                              //ָ���
    MsgResult_t (*set_attr)(u8*,u16);         //set�������
    MsgResult_t (*get_attr)(u8*,u16,u8*,u8*); //get�������                      
};


/**********************************��������**********************************/
extern struct process_data uart1rcv_pd;
extern struct process_data uart1send_pd;

/**********************************��������**********************************/
void CMDProcessInit(void);
void Process_FIFOData(struct fifo_data *fifo, struct process_data *prc);
u8 Msg_Process(u8 *sdata, u32 len);
MsgResult_t Msg_Execute(u8 *sdata, u32 len);

extern u8 Send_Process(u8 *sdata, u32 len);

#endif
