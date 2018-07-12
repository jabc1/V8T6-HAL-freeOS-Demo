#ifndef _table_h
#define _table_h
#include "stm32f1xx.h"
#include "Command_Parse.h"

typedef enum
{
	Normal=0x01,//正常指令
	Abnormal=0x02,//异常指令
	Error=0x03,//错误
}MsgResult;

struct attr_exe_data
{
    u32 cmd;                              //指令号
    MsgResult (*exe_attr)(u8,u32); //exe函数入口                      
};

bool Msg(u8 *data,u32 len);
u8 GetAttrNum(void);
MsgResult Msg_Execute(u8 *data, u32 len);
MsgResult test_function(u8 cmd,u32 len);
#endif

