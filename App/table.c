#include "table.h"
const struct attr_exe_data SysAttrTable[] =
{
	{0x01,test_function},//��Ӧ��������
	{0x1a,Lock_function},
	{0x2a,State_function},
	{0xa0,SoftVer_funtion},//��ȡ����汾
	{0x0a,SoftVer_funtion},
};
u8 GetAttrNum(void)
{
	return (sizeof(SysAttrTable)/sizeof(struct attr_exe_data));
}

bool Msg(u8 *data,u32 len)
{
	u8 i,count;
	_Cmd_data *Pack;
	const struct attr_exe_data* p_attr_exe = SysAttrTable;//�ṹ����ά��
	
	count = GetAttrNum();//��ȡ��ά�������
	Pack = (_Cmd_data *)data;//�ṹ����������

	for(i=0;i<count;i++)
	{
		if(p_attr_exe->cmd == Pack->CmdCode)
		{
			if(p_attr_exe->exe_attr != NULL)
				p_attr_exe->exe_attr(Pack->CmdCode,Pack->CmdData,sizeof(&Pack->CmdData[0]));//���������ݽ��д���
			return true;
		}
		p_attr_exe++;
	}
	if(i==count)
	{
		return false;//��������
	}
	return true;	
}
MsgResult SoftVer_funtion(u8 cmd,u8 *data,u32 len)
{
	u8 temp[2];
	temp[0] = 0xaa;//SOFT_VER;
	temp[1] = 0xbb;//HARD_VER;
	unpack(cmd,0x00,temp,sizeof(temp));
}
MsgResult Lock_function(u8 cmd,u8 *data,u32 len)
{
	;
}
MsgResult State_function(u8 cmd,u8 *data,u32 len)
{
	;
}
MsgResult test_function(u8 cmd,u8 *data,u32 len)
{
//	u16 dataLen;
//	dataLen = (u16)(len - 3);//- crc and tail
	
	_Msg_Lock *Pack;
	Pack = (_Msg_Lock *)data;
	switch(Pack->id)
	{
		case id_1:
			if(Pack->status == OpenLock)
				USART1_Printf("OpenLock1\r\n");
			break;
		default:
			break;
	}

	return Normal;
}



