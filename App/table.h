#ifndef _table_h
#define _table_h
#include "stm32f1xx.h"
#include "Command_Parse.h"

#define 	OpenLock					0x01//开锁指令

#define		ReportLockStatus			0x0b//上报锁状态指令

#define		id_1						0x01
#define		id_2						0x02
#define		id_3						0x03

typedef struct{
	u8 id;
	u8 status;
}_Msg_Lock;
typedef enum
{
	Normal=0x01,//正常指令
	Abnormal=0x02,//异常指令
	Error=0x03,//错误
}MsgResult;

struct attr_exe_data
{
    u32 cmd;                              //指令号
    MsgResult (*exe_attr)(u8 ,u8 *,u32); //参数说明，下发命令，下发数据内容，下发数据内容长度                     
};

bool Msg(u8 *data,u32 len);
u8 GetAttrNum(void);
MsgResult Msg_Execute(u8 cmd,u8 *data, u32 len);
MsgResult test_function(u8 cmd,u8 *data,u32 len);
MsgResult Lock_function(u8 cmd,u8 *data,u32 len);
MsgResult State_function(u8 cmd,u8 *data,u32 len);
MsgResult SoftVer_funtion(u8 cmd,u8 *data,u32 len);
#endif

