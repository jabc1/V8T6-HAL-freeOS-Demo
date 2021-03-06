#include "gpio.h"

u8 Read_IO_H()
{
	u8 temp;
	
	return temp;
}

u8 Read_IO_L()
{
	u8 temp;
	
	return temp;
}



void GPIO_init()
{
	GPIO_InitTypeDef   GPIO_InitStruct;
	DE_WD_CLK();	
	RE_WD_CLK();
	
	HAL_GPIO_WritePin(DE_WD_PROE, DE_WD_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(RE_WD_PROE, RE_WD_PIN, GPIO_PIN_RESET);
	
	GPIO_InitStruct.Pin = DE_WD_PIN|RE_WD_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(DE_WD_PROE, &GPIO_InitStruct);	
	
}
void LockGPIO_Init()
{
	GPIO_InitTypeDef   GPIO_InitStruct;

	IF_LOAD_1_CLK();
	SIGN_1_CLK();	
	
	HAL_GPIO_WritePin(IF_LOAD_1_PROE, IF_LOAD_1_PIN, GPIO_PIN_RESET);
	GPIO_InitStruct.Pin = IF_LOAD_1_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(IF_LOAD_1_PROE, &GPIO_InitStruct);
	
	HAL_GPIO_WritePin(SIGN_1_PROE, SIGN_1_PIN, GPIO_PIN_RESET);
	GPIO_InitStruct.Pin = SIGN_1_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(SIGN_1_PROE, &GPIO_InitStruct);
}





