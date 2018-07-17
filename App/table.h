#ifndef _table_h
#define _table_h
#include "stm32f1xx.h"
#include "Command_Parse.h"

#define 	OpenLock					0x01//����ָ��

#define		ReportLockStatus			0x0b//�ϱ���״ָ̬��

#define		id_1						0x01
#define		id_2						0x02
#define		id_3						0x03

typedef struct{
	u8 id;
	u8 status;
}_Msg_Lock;
typedef enum
{
	Normal=0x01,//����ָ��
	Abnormal=0x02,//�쳣ָ��
	Error=0x03,//����
}MsgResult;

struct attr_exe_data
{
    u32 cmd;                              //ָ���
    MsgResult (*exe_attr)(u8 ,u8 *,u32); //����˵�����·�����·��������ݣ��·��������ݳ���                     
};

bool Msg(u8 *data,u32 len);
u8 GetAttrNum(void);
MsgResult Msg_Execute(u8 cmd,u8 *data, u32 len);
MsgResult test_function(u8 cmd,u8 *data,u32 len);
MsgResult Lock_function(u8 cmd,u8 *data,u32 len);
MsgResult State_function(u8 cmd,u8 *data,u32 len);
MsgResult SoftVer_funtion(u8 cmd,u8 *data,u32 len);
#endif

