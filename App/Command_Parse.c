#include "Command_Parse.h"
#include "usart1.h"
#include "fifo.h"
#include "CRC.h"
#include "table.h"
#include "update.h"
#define MAX_TRANSMIT_QUEUE_LENGTH 	1000
#define MAX_RECEIVE_QUEUE_LENGTH  	1000

#pragma pack(push,1)
typedef struct{
	u32 add;
	u8 cmd;
	u32 datalen;
	u8 data[1000];
//	u8 *data;
}_Cmd_Analysis;
#pragma pack(pop)

u8 TransmitQueue[MAX_TRANSMIT_QUEUE_LENGTH];
u8 ReceiveQueue[MAX_RECEIVE_QUEUE_LENGTH];
struct fifo_data TransmitFIFO;
struct fifo_data ReceiveFIFO;
_Cmd_data Cmd_data;
_Data Data;
_Cmd_Analysis Cmd_Analysis;
void Init_FIFO()
{
	fifo_Init(&ReceiveFIFO, ReceiveQueue, MAX_RECEIVE_QUEUE_LENGTH);
	fifo_Init(&TransmitFIFO, TransmitQueue, MAX_TRANSMIT_QUEUE_LENGTH);
}

void Receive_function()
{
	static u32 Length = 0;
	if (!fifo_empty(&ReceiveFIFO))
	{
		memset(Data.Buff,0,sizeof(Data.Buff));
		if (fifo_get_frame(&ReceiveFIFO,&Data.Buff[0],&Length))
		{
			if(true == Analysis(&Cmd_Analysis.add,&Cmd_Analysis.cmd,&Cmd_Analysis.data[0],\
								&Cmd_Analysis.datalen,Data.Buff,Length))
			{
				if(Cmd_Analysis.cmd == 0xa3)//APP��������Ϣcrc,len����app����
				{
					update_parameter(Cmd_Analysis.data,Cmd_Analysis.datalen);
				}				
				if(Cmd_Analysis.cmd == 0xa5)//APP����������
				{
					update_function(Cmd_Analysis.data,Cmd_Analysis.datalen);
				}				
				
				
//				if(Msg(Data.Buff,Length) == false)
//					return;				

//				if(Cmd_Analysis.cmd == 0x0a)
//				{
//					//USART1_Printf("Rcmd=%s\r\n",Cmd_Analysis.data);
//					unpack(0x0a,0x00,Cmd_Analysis.data,Cmd_Analysis.datalen);
//				}
//				if(Cmd_Analysis.cmd == 0x0b)
//				{
//					//USART1_Printf("Rcmd=%s\r\n",Cmd_Analysis.cmd);	
//					unpack(0x0b,0x00,Cmd_Analysis.data,Cmd_Analysis.datalen);
//				}
			}			
		}
	}
}
void Transport_function()
{
	static u32 Len,i;
	if (!fifo_empty(&TransmitFIFO))
	{
		memset(Data.Buff,0,sizeof(Data.Buff));
		if (fifo_get_frame(&TransmitFIFO,&Data.Buff[0], &Len))
        {
			#if 1
			DW_485_Send();
			for(i=0;i<Len;i++)
			{
				while((USART1->SR&0X40)==0);//�ȴ����ͽ���             
				USART1->DR=Data.Buff[i];
			}    
			while((USART1->SR&0X40)==0);
			DW_485_Receive();
			#else
//			for(i=0;i<Len;i++)
//			{
//				if(Data.Buff[i]==0x00)
//					Data.Buff[i] = 0x30;
//			}
//			USART1_Printf("%s",&Data.Buff[0]);
			#endif
        }
	}
}
void Report_function()
{
	u8 temp[2];
	if(0)
	{
		temp[0] = Read_IO_H();
		temp[1] = Read_IO_L();
		unpack(0x04,0x00,temp,sizeof(temp));
	}
}
/*
 *��������������Ǵ���ָ�����
 */
bool Analysis(u32 *add,u8 *cmd,u8 *Data,u32 *DataLen,u8 *Content,u32 ContentLen)
{
	_Cmd_data *pPack;
	u16 CRCValue;
	u16 *pCRCValueRegion;
	
	if(ContentLen < MAX_PROTOCOL_EX_LEN)
	{
		return false;
	}
	pPack = (_Cmd_data *)Content;//�ṹ������
	
	if( (HEAD != pPack->PackHead) || \
		(SOFT_VER != pPack->SoftVer)|| \
		(HARD_TYPE != pPack->HardType)|| \
		(TAIL != *((u8 *)((u8 *)pPack + PACK_TAIL_REGION_OFFSET \
					+  pPack->DataLength - DATALEN_FIX_LENGTH))))
	{
		return false;
	}
	
	CRCValue = ChkCrcValueEx(&(pPack->SoftVer), (pPack->DataLength),0xFFFF);
	pCRCValueRegion = (u16 *)((u8*)pPack + CRC_REGION_OFFSET \
								+(pPack->DataLength - DATALEN_FIX_LENGTH));
	
	if (*pCRCValueRegion != CRCValue)
	{
		return false;
	}	
	
	memcpy(Data,&(pPack->CmdData), pPack->DataLength - DATALEN_FIX_LENGTH);//�������ݴ���
	*DataLen = pPack->DataLength - DATALEN_FIX_LENGTH;//�������ݳ���
	*cmd = pPack->CmdCode;//��������
    *add = pPack->DesAddr;//������ַ
	
	return true;
}

/*
*���ڴ������Ҫ���͵�����
 */
bool unpack(u8 cmd,u32 targetadd,u8 *data,u32 datalen)
{
	_Cmd_data *pPack;
	u16 CRCValue;
	u16 *pCRCValueRegion;
	u8 *pPackTail;
	pPack = (_Cmd_data *)malloc(datalen + MAX_PROTOCOL_EX_LEN);//�����ڴ泤��
	if(pPack == NULL)
	{
		return false;
	}

	pPack->PackHead = HEAD;
	pPack->DataLength = datalen + MAX_PROTOCOL_EX_LEN - 6;
	pPack->SoftVer = SOFT_VER;
	pPack->HardType = HARD_TYPE;
	pPack->CmdCode = cmd;
	//pPack->SrcAddr = 0x12000000;//����ID��
	pPack->SrcAddr = 0x00000000;//����ID��
	pPack->DesAddr = targetadd;
	pPack->DesAddr = 0x00000000;//Ŀ��ID��
	pPack->SerialNO = 0;//���к�
	pPack->TotalPackNum = 1;//��ǰ����
	pPack->CurrentPackNO = 1;//�ܱ���
	
	memcpy(&(pPack->CmdData), data, datalen);//�����������ݵ�pPack�ṹ����
	
	CRCValue = ChkCrcPack(&(pPack->SoftVer), (pPack->DataLength),0xFFFF);//����crc
	pCRCValueRegion = (u16 *)((u8 *)pPack + datalen + CRC_REGION_OFFSET); 
	*pCRCValueRegion = CRCValue;
	
	pPackTail = (u8 *)((u8 *)pPack + datalen + PACK_TAIL_REGION_OFFSET);
	*pPackTail = TAIL;	
	/*Add to Transmit FIFO*/   
    if (!fifo_puts(&TransmitFIFO, (u8 *)pPack, datalen + MAX_PROTOCOL_EX_LEN))
    {
        free(pPack);
        return false;
    }
	free(pPack);
	return true;	
}









void Command_Parse(u8 *command_str)
{
	char *token,*segment_ptr[12],i;
	// ��������ָ��
	for(i = 0; i < 12; i++)
	{
		segment_ptr[i] = NULL;
	}
	if(command_str[0] == 'W' || command_str[0] == 'R' || command_str[0] == 'C' \
		|| command_str[0] == 'S' || command_str[0] == 'Q')
	{
		memcpy(Uart1.BackBuff,command_str,strlen((char *)command_str));
		i = 0;
		token = strtok((char *)command_str, ",=");
		while(token != NULL && i < 12)
		{
			segment_ptr[i] = token;	
			USART1_Printf("%s\r\n",segment_ptr[i]);
			i++;
			token = strtok(NULL,",=");			
		}	
		USART1_Printf("%s",(u8 *)Uart1.BackBuff);
		memset((u8 *)Uart1.BackBuff,0,sizeof(Uart1.BackBuff));
	}
}


