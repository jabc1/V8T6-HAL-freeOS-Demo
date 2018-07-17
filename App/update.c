#include "update.h"
#include "crc.h"
#include "flash.h"

#pragma pack(push,1)
typedef struct
{
	u32 JumpFlag;				//Bootloader_0������ת���
	u32 bootloader_Version;		//Bootloader�汾
	u8 bootloader0_Flag;		//bootloader1����汾
	u8 bootloader1_Flag;		//bootloader1����汾��С
}_UpdateF;
#pragma pack(pop)
_UpdateF UpdateF;

#pragma pack(push,2)
typedef struct
{
	u16 update_crc;
	u32 update_len;
	u16 segnum;
}_Update_info;
#pragma pack(pop)
_Update_info Update_info;


void update_function(u8 *data,u32 len)
{
	static u16 count=0;
	u16 crc1=0;
	uint32_t update_addr;
	uint8_t *paddr;

	count++;
	if(count <= ((Update_info.segnum) - 1))//��һ���������ڶ���
	{
		update_addr = Flash_IAP_ADDR + (count-1)*len;			  
		IAP_Write_App_Bin(update_addr,data,len);
	}
	else if(count == Update_info.segnum)//���һ��
	{
		update_addr = Flash_IAP_ADDR + (count-1)*960;			  
		IAP_Write_App_Bin(update_addr,data,960);
		paddr = (uint8_t *)(Flash_IAP_ADDR);
		crc1 = ChkCrcValueEx(paddr,Update_info.update_len,0xFFFF);
		if(Update_info.update_crc == crc1) //check��ȷ
		{
			//����flash��־�������λ
			UpdateIAP_succ();//�ı��־λ�����λ��ת��iap����
		}
		else
		{
			count = 0;//����ʧ�ܣ�����������������
		}
	}
	
}
void UpdateIAP_succ(void)
{
	UpdateF.JumpFlag = JUMP_IAP;//��־��ת��IAP����
//	UpdateF.boot1_Version = Boot1Ver;
//	UpdateF.boot1_Flag = 0;
//	UpdateF.bootloader0Flag = 0;
	STMFLASH_Write(Bootloader_flag_ADD, (uint16_t *)&UpdateF,2);
	NVIC_SystemReset();// ��λ
}
void UpdateBOOT1_restart()
{
	UpdateF.JumpFlag = JUMP_IAP;//���ı�־λ�����λ����APP׼������boot1
//	UpdateF.bootloader_Version = SOFTVer;
//	UpdateF.bootloader1Flag = 0;
//	UpdateF.bootloader0Flag = 0;
	STMFLASH_Write(Bootloader_flag_ADD, (uint16_t *)&UpdateF,2);
	NVIC_SystemReset();// ��λ
}
void update_parameter(u8 *data,u32 len)//��һ������ǰ16���ֽ�
{
	_Update *pData;
	pData = (_Update *)data;
	if(pData->boardType == BoardType)
	{
		Update_info.update_crc = pData->crc16;
		Update_info.update_len = pData->upDataLen;
		Update_info.segnum = Update_info.update_len % 960 \
							  ? (Update_info.update_len/960) + 1 \
							  : (Update_info.update_len/960); //���512���ֽڣ���¼�ܵ�����������
		ProgramReady(Update_info.update_len);//����APP flash
	}
}
static u16 ulBufFlashApp[1024];
void IAP_Write_App_Bin ( uint32_t ulStartAddr, uint8_t * pBin_DataBuf, uint32_t ulBufLength )
{
	uint16_t us, usCtr=0, usTemp;
	uint32_t ulAdd_Write = ulStartAddr;                                //��ǰд��ĵ�ַ
	uint8_t * pData = pBin_DataBuf;
	
	for ( us = 0; us < ulBufLength; us += 2 )
	{						    
		usTemp =  ( uint16_t ) pData[1]<<8;
		usTemp += ( uint16_t ) pData[0];	  
		pData += 2;                                                      //ƫ��2���ֽ�
		ulBufFlashApp [ usCtr ++ ] = usTemp;	    
		if ( usCtr == 1024 )
		{
			usCtr = 0;
			STMFLASH_Write ( ulAdd_Write, ulBufFlashApp, 1024 );	
			ulAdd_Write += 2048;                                           //ƫ��2048  16=2*8.����Ҫ����2.
		}
	}
	if ( usCtr ) 
    STMFLASH_Write ( ulAdd_Write, ulBufFlashApp, usCtr );//������һЩ�����ֽ�д��ȥ.  
}

