#include "flash.h"
/* ˽�����Ͷ��� --------------------------------------------------------------*/
/* ˽�к궨�� ----------------------------------------------------------------*/
#if STM32_FLASH_SIZE < 256
  #define STM_SECTOR_SIZE  1024 //�ֽ�
#else 
  #define STM_SECTOR_SIZE	 2048
#endif

/* ˽�б��� ------------------------------------------------------------------*/
#if STM32_FLASH_WREN	//���ʹ����д 
static uint16_t STMFLASH_BUF [ STM_SECTOR_SIZE / 2 ];//�����2K�ֽ�
static FLASH_EraseInitTypeDef EraseInitStruct;
#endif

/**
  * ��������: ��ȡָ����ַ�İ���(16λ����)
  * �������: faddr:����ַ(�˵�ַ����Ϊ2�ı���!!)
  * �� �� ֵ: ����ֵ:��Ӧ����.
  * ˵    ������
  */
uint16_t STMFLASH_ReadHalfWord ( uint32_t faddr )
{
	return *(__IO uint16_t*)faddr; 
}
#if STM32_FLASH_WREN	//���ʹ����д   
/**
  * ��������: ������д��
  * �������: WriteAddr:��ʼ��ַ
  *           pBuffer:����ָ��
  *           NumToWrite:����(16λ)��
  * �� �� ֵ: ��
  * ˵    ������
  */
void STMFLASH_Write_NoCheck ( uint32_t WriteAddr, uint16_t * pBuffer, uint16_t NumToWrite )   
{ 			 		 
	uint16_t i;	
	//HAL_FLASH_Unlock();						//����
	for(i=0;i<NumToWrite;i++)
	{		
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD,WriteAddr,pBuffer[i]);
		WriteAddr+=2;                                    //��ַ����2.
	} 
	//HAL_FLASH_Lock();//����	
} 
/**
  * ��������: ��ָ����ַ��ʼд��ָ�����ȵ�����
  * �������: WriteAddr:��ʼ��ַ(�˵�ַ����Ϊ2�ı���!!)
  *           pBuffer:����ָ��
  *           NumToWrite:����(16λ)��(����Ҫд���16λ���ݵĸ���.)
  * �� �� ֵ: ��
  * ˵    ������
  */
void STMFLASH_Write ( uint32_t WriteAddr, uint16_t * pBuffer, uint16_t NumToWrite )	
{
	uint32_t SECTORError = 0;
	uint16_t secoff;	   //������ƫ�Ƶ�ַ(16λ�ּ���)
	uint16_t secremain; //������ʣ���ַ(16λ�ּ���)	   
 	uint16_t i;    
	uint32_t secpos;	   //������ַ
	uint32_t offaddr;   //ȥ��0X08000000��ĵ�ַ
	
	if(WriteAddr<FLASH_BASE||(WriteAddr>=(FLASH_BASE+1024*STM32_FLASH_SIZE)))return;//�Ƿ���ַ
	
	HAL_FLASH_Unlock();						//����
	
	offaddr=WriteAddr-FLASH_BASE;		//ʵ��ƫ�Ƶ�ַ.
	secpos=offaddr/STM_SECTOR_SIZE;			//������ַ  0~127 for STM32F103RBT6
	secoff=(offaddr%STM_SECTOR_SIZE)/2;		//�������ڵ�ƫ��(2���ֽ�Ϊ������λ.)
	secremain=STM_SECTOR_SIZE/2-secoff;		//����ʣ��ռ��С   
	
	if(NumToWrite<=secremain)secremain=NumToWrite;//�����ڸ�������Χ
	
	while(1) 
	{	
		STMFLASH_Read(secpos*STM_SECTOR_SIZE+FLASH_BASE,STMFLASH_BUF,STM_SECTOR_SIZE/2);//������������������
		for(i=0;i<secremain;i++)//У������
		{
			if(STMFLASH_BUF[secoff+i]!=0XFFFF)break;//��Ҫ����  	  
		}
		if(i<secremain)//��Ҫ����
		{
			//�����������
			/* Fill EraseInit structure*/
			EraseInitStruct.TypeErase     = FLASH_TYPEERASE_PAGES;
			EraseInitStruct.PageAddress   = secpos*STM_SECTOR_SIZE+FLASH_BASE;
			EraseInitStruct.NbPages       = 1;
			HAL_FLASHEx_Erase(&EraseInitStruct, &SECTORError);
			for(i=0;i<secremain;i++)//����
			{
				STMFLASH_BUF[i+secoff]=pBuffer[i];	  
			}
			STMFLASH_Write_NoCheck(secpos*STM_SECTOR_SIZE+FLASH_BASE,STMFLASH_BUF,STM_SECTOR_SIZE/2);//д����������  
		}
		else
		{
			STMFLASH_Write_NoCheck(WriteAddr,pBuffer,secremain);//д�Ѿ������˵�,ֱ��д������ʣ������. 				   
		}
		if(NumToWrite==secremain)break;//д�������
		else//д��δ����
		{
#ifndef BIN_960            
			secpos++;				//������ַ��1
			secoff=0;				//ƫ��λ��Ϊ0 	 
		    pBuffer+=secremain;  	//ָ��ƫ��
            secremain *= 2;
			WriteAddr+=secremain;	//д��ַƫ��
            secremain /= 2;            
		   	NumToWrite-=secremain;	//�ֽ�(16λ)���ݼ�
			if(NumToWrite>(STM_SECTOR_SIZE/2))secremain=STM_SECTOR_SIZE/2;//��һ����������д����
			else secremain=NumToWrite;//��һ����������д����
#else
            secpos++;				//������ַ��1
			secoff=0;				//ƫ��λ��Ϊ0 	 
		    pBuffer+=secremain;  	//ָ��ƫ��
			WriteAddr+=secremain;	//д��ַƫ��	   
		   	NumToWrite-=secremain;	//�ֽ�(16λ)���ݼ�
			if(NumToWrite>(STM_SECTOR_SIZE/2))secremain=STM_SECTOR_SIZE/2;//��һ����������д����
			else secremain=NumToWrite;//��һ����������д����
#endif   
		}	 
	};	
	HAL_FLASH_Lock();//����
}
#endif
/**
  * ��������: ��ָ����ַ��ʼ����ָ�����ȵ�����
  * �������: ReadAddr:��ʼ��ַ
  *           pBuffer:����ָ��
  *           NumToRead:����(16λ)��
  * �� �� ֵ: ��
  * ˵    ������
  */
void STMFLASH_Read ( uint32_t ReadAddr, uint16_t *pBuffer, uint16_t NumToRead )   	
{
	uint16_t i;
	
	for(i=0;i<NumToRead;i++)
	{
		pBuffer[i]=STMFLASH_ReadHalfWord(ReadAddr);//��ȡ2���ֽ�.
		ReadAddr+=2;//ƫ��2���ֽ�.	
	}
}
void  ProgramReady(uint16_t _lenth)
{
	uint16_t lenth = _lenth;
	uint8_t block;
	uint32_t i;
	uint32_t SECTORError = 0;
	block = lenth%1024 ? (lenth>>10) + 1 : (lenth>>10);
	HAL_FLASH_Unlock();
	for(i=0; i<block; i++)
	{
		EraseInitStruct.TypeErase     = FLASH_TYPEERASE_PAGES;
		EraseInitStruct.PageAddress   = i*1024+Flash_IAP_ADDR;
		EraseInitStruct.NbPages       = 1;
		HAL_FLASHEx_Erase(&EraseInitStruct, &SECTORError);	
	}	
	HAL_FLASH_Lock(); 
}



void NVIC_SetVectorTable(uint32_t NVIC_VectTab, uint32_t Offset)
{ 
	assert_param(IS_NVIC_VECTTAB(NVIC_VectTab));
	assert_param(IS_NVIC_OFFSET(Offset));  

	SCB->VTOR = NVIC_VectTab | (Offset & (uint32_t)0x1FFFFF80);
}
/*
��ʼ��ַд��4byte
*/
void CPU_FLASH_TEST()
{
	uint16_t buff[2]={0xeecc,0x55aa};
	uint32_t add,i;
	add = 0x0800D400;
	i=0;
	for(i=0;i<1024;i++){
		STMFLASH_Write(add,buff,2);
		HAL_Delay(500);
		buff[0] = 0x1230+i;
		buff[1] = 0xaa10+i;		
		//add = add + 8;
	}
//	STMFLASH_Read(0x0800D400,Rbuff,2);
//	Rbuff[0] = STMFLASH_ReadHalfWord(0x0800D400);
//	Rbuff[1] = STMFLASH_ReadHalfWord(0x0800D400+2);
}









