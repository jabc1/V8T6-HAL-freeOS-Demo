#ifndef _flash_h
#define _flash_h
#include "stm32f1xx.h" 

#define NVIC_VectTab_FLASH				0X08000000
#define Bootloader_flag_ADD				0X08006000//flag data
#define Flash_APP_ADDR					0x08006400//app start add
#define	Flash_IAP_ADDR					0x08000400//iap start add

#define PROGRAM_UPGRADE_MODE      		0x55FFFF55 //upgrade mode��run in bootload 
#define PROGRAM_NORMAL_MODE      		0xAA0000AA //normal mode��run to app


/* ���Ͷ��� ------------------------------------------------------------------*/
/* �궨�� --------------------------------------------------------------------*/
/************************** STM32 �ڲ� FLASH ���� *****************************/
#define STM32_FLASH_SIZE        64  // ��ѡSTM32��FLASH������С(��λΪK)
#define STM32_FLASH_WREN        1    // stm32оƬ����FLASH д��ʹ��(0������;1��ʹ��)

/* ��չ���� ------------------------------------------------------------------*/

/* �������� ------------------------------------------------------------------*/
uint16_t STMFLASH_ReadHalfWord(uint32_t faddr);		  //��������

void STMFLASH_WriteLenByte(uint32_t WriteAddr, uint32_t DataToWrite, uint16_t Len );	      //ָ����ַ��ʼд��ָ�����ȵ�����
uint32_t STMFLASH_ReadLenByte(uint32_t ReadAddr, uint16_t Len );					                    	//ָ����ַ��ʼ��ȡָ����������
void STMFLASH_Write( uint32_t WriteAddr, uint16_t * pBuffer, uint16_t NumToWrite );		//��ָ����ַ��ʼд��ָ�����ȵ�����
void STMFLASH_Read( uint32_t ReadAddr, uint16_t * pBuffer, uint16_t NumToRead );   	//��ָ����ַ��ʼ����ָ�����ȵ�����
void NVIC_SetVectorTable(uint32_t NVIC_VectTab, uint32_t Offset);
void  ProgramReady(uint16_t _lenth);

void CPU_FLASH_TEST(void);

#endif

