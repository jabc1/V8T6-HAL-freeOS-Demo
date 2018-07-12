/******************************Copyright(C) Nubo*******************************
File name  : sysexeattr.c
Description: this source used for system command execute
Platform   : MDK V5.23.0.0
Version    : V1.0
Author     : Joey
Create Time: 2017-12-23
Modify     : 
Modify Time: 
******************************************************************************/

#include "sysexeattr.h"
#include "Update.h"
#include "CMDProcess.h"

//const struct attr_exe_data SysAttrTable[] =
//{
//	{0x40, Set_TemperatureUnit_Attr    , Get_TemperatureUnit_Attr          },//unit of temperature
//	{0x41, Set_SampleInterval_Att      , Get_SampleInterval_Att            },//sample interval
//	{0x42, Set_StorageStrategy_Attr    , Get_StorageStrategy_Attr          },//storage strategy
//	{0x43, Set_AlarmThreshold_Attr     , Set_AlarmThreshold_Attr           },//alarm threshold
//	{0x44, NULL                        , Get_LockStatus_Attr               },//lock status
//	{0x45, NULL                        , Get_HistorySampleValue_Att        },//history sample value
//	{0x46, Set_ScreenContent_Attr      , NULL                              },//screen content
//	{0x47, Set_HandOffAlarm_Attr       , NULL                              },//hand off alarm

//	{0xA0, Set_ProgramUpdate_Attr      , NULL                              },//program update
//};

const struct attr_exe_data SysAttrTable[] =
{
	{0x40, Set_TemperatureUnit_Attr    },//set unit of temperature
	{0x41, Get_TemperatureUnit_Attr    },//get unit of temperature
//	{0x42, Set_SampleInterval_Att      },//set sample interval
//	{0x43, Get_SampleInterval_Att      },//get sample interval
//	{0x44, Set_StorageStrategy_Attr    },//set storage strategy
//	{0x45, Get_StorageStrategy_Attr    },//get storage strategy
//	{0x46, Set_AlarmThreshold_Attr     },//set alarm threshold
//	{0x47, Get_AlarmThreshold_Attr     },//get alarm threshold
//	{0x49, Get_LockStatus_Attr         },//get lock status
//	{0x4B, Get_HistorySampleValue_Att  },//get history sample value
//	{0x4C, Set_ScreenContent_Attr      },//set screen content
//	{0x4E, Set_HandOffAlarm_Attr       },//set hand off alarm
    {0xA0, Set_ProgramUpdate_Attr      },//set program update
};

/******************************************************************************
Function   : u8 GetAttrNum(void)
Description: get command number 
Input      : void
Output     : u8 - number
Author     : Joey
Time       : 2018-1-4
******************************************************************************/
u8 GetAttrNum(void)
{
	return (sizeof(SysAttrTable)/sizeof(struct attr_exe_data));
}

/******************************************************************************
Function   : MsgResult_t Set_TemperatureUnit_Attr(u8* sdata, u8* rlen, u8* rpara)
Description: set temperature unit 
Input      : sdata - temperature unit parameters
             rlen  - return parameters length
             rpara - return parameters
Output     : MsgResult_t - check enum table result
Author     : Joey
Time       : 2018-1-3
******************************************************************************/
MsgResult_t Set_TemperatureUnit_Attr(u8* sdata, u16 slen, u8* rlen, u8* rpara)
{
	volatile unsigned char tmp;

	tmp = sdata[0];
	
	return COMPLETE;
}

/******************************************************************************
Function   : MsgResult_t Get_TemperatureUnit_Attr(u8* sdata)
Description: get temperature unit 
Input      : sdata - input parameters
             rlen  - return parameters length
             rpara - return parameters
Output     : MsgResult_t - check enum table result
Author     : Joey
Time       : 2018-1-3
******************************************************************************/
MsgResult_t Get_TemperatureUnit_Attr(u8* sdata, u16 slen, u8* rlen, u8* rpara)
{
	*rlen = 1;
	*rpara = 0x32;
	
	return COMPLETE;
}


/******************************************************************************
Function   : MsgResult_t Set_ProgramUpdate_Attr(u8* sdata, u8* rlen, u8* rpara)
Description: program update command, used for IAP
Input      : sdata - program parameters
             rlen  - return parameters length
             rpara - return parameters
Output     : MsgResult_t - check enum table result
Author     : Joey
Time       : 2017-12-23
******************************************************************************/
MsgResult_t Set_ProgramUpdate_Attr(u8* sdata, u16 slen, u8* rlen, u8* rpara)
{
	struct ProgramDataFrame *pdata;
	struct UpdateRam *udata;

	pdata = (struct ProgramDataFrame*)sdata;
	udata = (struct UpdateRam *)pdata->data;
	
	if(udata->ver == VERSION)
	{
		return UPGRADE_VER_ERR;
	}
	else if(pdata->segno == 0x00 &&    //first package check
			pdata->lenno == UPGRADE_LENGTH_FIRST_SECTION && //first package length is 16
			pdata->data[0] == 0x03 )
	{
		//�޸�flash��־���´���root������������ת��app
		SetProgramStatus();
		GenerateSystemReset();
	}
	return COMPLETE;
}

