#ifndef _command_h
#define _command_h
#include "stm32f1xx.h"
#include "485_function.h"

#define		HEAD					0X7E//��ͷ
#define 	TAIL 					0xE7//��δ

#define 	SOFT_VER				0X01//����汾
#define		HARD_VER				0X01//Ӳ���汾
#define		HARD_TYPE				0X0A//�豸����

#define	 	MAX_PROTOCOL_EX_LEN	 	21			/*One pack's Max Length(exclude data region)*/
#define 	DATALEN_FIX_LENGTH   	15          /*Fixed length of data fields*/
#define 	CRC_REGION_OFFSET		(MAX_PROTOCOL_EX_LEN - 3)//crcλ��
#define 	CRC_OFFSET           	2        //crc���
#define 	PACK_TAIL_REGION_OFFSET (MAX_PROTOCOL_EX_LEN - 1)//��β

#pragma pack(push,1)
typedef struct{
	u8 PackHead;//ͷ
	u16 DataLength;//���ݳ���
	u8 SoftVer;//����汾
	u8 HardType;//�豸����
	u8 CmdCode;//��������
	u32 SrcAddr;//Դ��ַ
	u32 DesAddr;//Ŀ���ַ
	u16 SerialNO;//���к�
	u8 TotalPackNum;//�ܱ���
	u8 CurrentPackNO;//��ǰ����
	u8 CmdData[1000];//����
//	u8 * CmdData;
}_Cmd_data;
typedef struct
{
//	u8 GetBuff[1000];
	u8 Buff[1000];
}_Data;
#pragma pack(pop)
extern _Cmd_data Cmd_data;
extern _Data Data;
extern struct fifo_data TransmitFIFO;
extern struct fifo_data ReceiveFIFO;
void Init_FIFO(void);
void Receive_function(void);
void Transport_function(void);
bool Analysis(u32 *add,u8 *cmd,u8 *Data,u32 *DataLen,u8 *Content,u32 ContentLen);
bool unpack(u8 cmd,u32 targetadd,u8 *data,u32 datalen);
void Command_Parse(u8 *command_str);
void Report_function(void);

#endif



