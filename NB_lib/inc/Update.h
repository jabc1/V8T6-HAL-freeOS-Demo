/******************************Copyright(C) Nubo*******************************
File name  : Update.c
Description: program update execute function
Platform   : MDK V5.23.0.0
Version    : V1.0
Author     : Joey
Create Time: 2017-12-23
Modify     : 
Modify Time: 
******************************************************************************/
#ifndef _UPDATE_H
#define _UPDATE_H

#include "NbType.h"
#include "NbLibConfig.h"
//#include <NB_conf.h>
/****************************Variable Declaration*****************************/
extern const struct attr_exe_data SysAttrTable[];

#define PROGRAM_UPGRADE_MODE       0x55FFFF55 //upgrade mode��run in bootload 
#define PROGRAM_NORMAL_MODE        0xAA0000AA //normal mode��run to app

#define UPGRADE_FLAG_FLASH_ADDR    0x8006000//upgrade flag flash store address

#define UPGRADE_LENGTH_PER_SECTION     960  //upgrade length per section
#define UPGRADE_LENGTH_FIRST_SECTION   16   //upgrade first section length

#pragma pack(1)
//program data frame
struct ProgramDataFrame 
{
	u8  type;          //board type
	u32 lentl;         //total file length
	u8  segtl;         //total sections
	u8  segno;         //local section
	u16 lenno;         //local section length
	u8  data[CMD_SIZE];    //proram data
};

//struct update flag in flash
struct	UpdateFlash
{
	u32 flag;   //upgrade flag,=PROGRAM_UPGRADE_MODE or PROGRAM_UPGRADE_MODE
//	u8  type;   //board type
//	u8  ver;    //upgrade version
};

//struct update flag in ram
struct	UpdateRam
{
	u8  type;     //board type
	u8  ver;      //upgrade version
	u16 crc16;    //crc16
	u32 length;   //total program package length
};
#pragma pack()

/****************************Function Declaration*****************************/ 

/******************************************************************************
Function   : void GenerateSystemReset(void)
Description: system software reset
Input      : void
Output     : void
Author     : Joey
Time       : 2017-12-23
******************************************************************************/
void GenerateSystemReset(void);

/******************************************************************************
Function   : void SetProgramStatus(void)
Description: set program update mode flag
Input      : void
Output     : void
Author     : Joey
Time       : 2017-12-23
******************************************************************************/
void SetProgramStatus(void);

#endif



