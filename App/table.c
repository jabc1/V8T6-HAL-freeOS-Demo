#include "table.h"
const struct attr_exe_data SysAttrTable[] =
{
	{0x0a,test_function},
};



bool Msg(u8 *data,u32 len)
{
	u8 i;
	_Cmd_data *Pack;
	u8 count = GetAttrNum();//��ȡ��ά�������
	Pack = (_Cmd_data *)data;//�ṹ����������
	const struct attr_exe_data* p_attr_exe = SysAttrTable;//�ṹ����ά��
	for(i=0;i<count;i++)
	{
		if(p_attr_exe->cmd == Pack->CmdCode)
		{
			if(p_attr_exe->exe_attr != NULL)
				p_attr_exe->exe_attr(Pack->CmdCode,Pack->DataLength);//���������ݽ��д���
			break;
		}
		p_attr_exe++;
	}
	if(i==count)
	{
		return false;
	}
	return true;	
}

MsgResult Msg_Execute(u8 *data, u32 len)
{
	u8 i;
	_Cmd_data *Pack;
	u8 count = GetAttrNum();//��ȡ��ά�������
	Pack = (_Cmd_data *)data;//�ṹ����������
	const struct attr_exe_data* p_attr_exe = SysAttrTable;//�ṹ����ά��
	for(i=0;i<count;i++)
	{
		if(p_attr_exe->cmd == Pack->CmdCode)
		{
			if(p_attr_exe->exe_attr != NULL)
				p_attr_exe->exe_attr(Pack->CmdCode,Pack->DataLength);//���������ݽ��д���
			break;
		}
		p_attr_exe++;
	}
	return Normal;
}

MsgResult test_function(u8 cmd,u32 len)
{
	if(cmd == 0x0a)
	{
		USART1_Printf("MsgResult\r\n");
	}
	return Normal;
}
u8 GetAttrNum(void)
{
	return (sizeof(SysAttrTable)/sizeof(struct attr_exe_data));
}


