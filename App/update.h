#ifndef _update_h
#define _update_h
#include "stm32f1xx.h"
#define		BoardType			0x0a
#define		SOFTVer				0x01

#define		JUMP_IAP			   0xAABBBBAA
#define		JUMP_AAP			   0xBBAAAABB

#pragma pack(push,1)
typedef struct
{
    u8   boardType;//�豸����
    u8   ver;//����汾
    u16  crc16;//������У��
    u16  upDataLen;//����������
    u8*  binFile;//һ������������
}_Update;
#pragma pack(pop)
void UpdateIAP_succ(void);
void UpdateAPP_restart(void);
void update_function(u8 *data,u32 len);
void update_parameter(u8 *data,u32 len);
void IAP_Write_App_Bin ( uint32_t ulStartAddr, uint8_t * pBin_DataBuf, uint32_t ulBufLength );
#endif

