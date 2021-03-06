#ifndef	 _gpio_h
#define  _gpio_h
#include "stm32f1xx_hal.h"
#define 	DE_WD_PIN		GPIO_PIN_12		
#define		DE_WD_PROE		GPIOA
#define		DE_WD_CLK()		__HAL_RCC_GPIOA_CLK_ENABLE()

#define 	RE_WD_PIN		GPIO_PIN_11		
#define		RE_WD_PROE		GPIOA
#define		RE_WD_CLK()		__HAL_RCC_GPIOA_CLK_ENABLE()

#define		PWR_CON_1_PIN	GPIO_PIN_0
#define		PWR_CON_1_PROE	GPIOC
#define		PWR_CON_1_CLK()	__HAL_RCC_GPIOC_CLK_ENABLE()
#define		IF_LOAD_1_PIN	GPIO_PIN_13
#define		IF_LOAD_1_PROE	GPIOC
#define		IF_LOAD_1_CLK()	__HAL_RCC_GPIOC_CLK_ENABLE()
#define		SIGN_1_PIN		GPIO_PIN_6
#define		SIGN_1_PROE		GPIOE
#define		SIGN_1_CLK()	__HAL_RCC_GPIOE_CLK_ENABLE()

#define		PWR_CON_2_PIN	GPIO_PIN_5
#define		PWR_CON_2_PROE	GPIOE
#define		PWR_CON_2_CLK()	__HAL_RCC_GPIOE_CLK_ENABLE()
#define		IF_LOAD_2_PIN	GPIO_PIN_4
#define		IF_LOAD_2_PROE	GPIOE
#define		IF_LOAD_2_CLK()	__HAL_RCC_GPIOE_CLK_ENABLE()
#define		SIGN_2_PIN		GPIO_PIN_3
#define		SIGN_2_PROE		GPIOE
#define		SIGN_2_CLK()	__HAL_RCC_GPIOE_CLK_ENABLE()

#define		PWR_CON_3_PIN	GPIO_PIN_2
#define		PWR_CON_3_PROE	GPIOE
#define		PWR_CON_3_CLK()	__HAL_RCC_GPIOE_CLK_ENABLE()
#define		IF_LOAD_3_PIN	GPIO_PIN_1
#define		IF_LOAD_3_PROE	GPIOE
#define		IF_LOAD_3_CLK()	__HAL_RCC_GPIOE_CLK_ENABLE()
#define		SIGN_3_PIN		GPIO_PIN_0
#define		SIGN_3_PROE		GPIOE
#define		SIGN_3_CLK()	__HAL_RCC_GPIOE_CLK_ENABLE()

#define		PWR_CON_4_PIN	GPIO_PIN_9
#define		PWR_CON_4_PROE	GPIOB
#define		PWR_CON_4_CLK()	__HAL_RCC_GPIOB_CLK_ENABLE()
#define		IF_LOAD_4_PIN	GPIO_PIN_8
#define		IF_LOAD_4_PROE	GPIOB
#define		IF_LOAD_4_CLK()	__HAL_RCC_GPIOB_CLK_ENABLE()
#define		SIGN_4_PIN		GPIO_PIN_7
#define		SIGN_4_PROE		GPIOB
#define		SIGN_4_CLK()	__HAL_RCC_GPIOB_CLK_ENABLE()

#define		PWR_CON_5_PIN	GPIO_PIN_6
#define		PWR_CON_5_PROE	GPIOB
#define		PWR_CON_5_CLK()	__HAL_RCC_GPIOB_CLK_ENABLE()
#define		IF_LOAD_5_PIN	GPIO_PIN_5
#define		IF_LOAD_5_PROE	GPIOB
#define		IF_LOAD_5_CLK()	__HAL_RCC_GPIOB_CLK_ENABLE()
#define		SIGN_5_PIN		GPIO_PIN_4
#define		SIGN_5_PROE		GPIOB
#define		SIGN_5_CLK()	__HAL_RCC_GPIOB_CLK_ENABLE()

#define		PWR_CON_6_PIN	GPIO_PIN_3
#define		PWR_CON_6_PROE	GPIOB
#define		PWR_CON_6_CLK()	__HAL_RCC_GPIOB_CLK_ENABLE()
#define		IF_LOAD_6_PIN	GPIO_PIN_7
#define		IF_LOAD_6_PROE	GPIOD
#define		IF_LOAD_6_CLK()	__HAL_RCC_GPIOD_CLK_ENABLE()
#define		SIGN_6_PIN		GPIO_PIN_6
#define		SIGN_6_PROE		GPIOD
#define		SIGN_6_CLK()	__HAL_RCC_GPIOD_CLK_ENABLE()

#define		PWR_CON_7_PIN	GPIO_PIN_5
#define		PWR_CON_7_PROE	GPIOD
#define		PWR_CON_7_CLK()	__HAL_RCC_GPIOD_CLK_ENABLE()
#define		IF_LOAD_7_PIN	GPIO_PIN_4
#define		IF_LOAD_7_PROE	GPIOD
#define		IF_LOAD_7_CLK()	__HAL_RCC_GPIOD_CLK_ENABLE()
#define		SIGN_7_PIN		GPIO_PIN_3
#define		SIGN_7_PROE		GPIOD
#define		SIGN_7_CLK()	__HAL_RCC_GPIOD_CLK_ENABLE()

#define		PWR_CON_8_PIN	GPIO_PIN_2
#define		PWR_CON_8_PROE	GPIOD
#define		PWR_CON_8_CLK()	__HAL_RCC_GPIOD_CLK_ENABLE()
#define		IF_LOAD_8_PIN	GPIO_PIN_1
#define		IF_LOAD_8_PROE	GPIOD
#define		IF_LOAD_8_CLK()	__HAL_RCC_GPIOD_CLK_ENABLE()
#define		SIGN_8_PIN		GPIO_PIN_0
#define		SIGN_8_PROE		GPIOD
#define		SIGN_8_CLK()	__HAL_RCC_GPIOD_CLK_ENABLE()

#define		PWR_CON_9_PIN	GPIO_PIN_3
#define		PWR_CON_9_PROE	GPIOC
#define		PWR_CON_9_CLK()	__HAL_RCC_GPIOC_CLK_ENABLE()
#define		IF_LOAD_9_PIN	GPIO_PIN_2
#define		IF_LOAD_9_PROE	GPIOC
#define		IF_LOAD_9_CLK()	__HAL_RCC_GPIOC_CLK_ENABLE()
#define		SIGN_9_PIN		GPIO_PIN_1
#define		SIGN_9_PROE		GPIOC
#define		SIGN_9_CLK()	__HAL_RCC_GPIOC_CLK_ENABLE()

#define		PWR_CON_10_PIN		GPIO_PIN_9
#define		PWR_CON_10_PROE		GPIOE
#define		PWR_CON_10_CLK()	__HAL_RCC_GPIOE_CLK_ENABLE()
#define		IF_LOAD_10_PIN		GPIO_PIN_10
#define		IF_LOAD_10_PROE		GPIOE
#define		IF_LOAD_10_CLK()	__HAL_RCC_GPIOE_CLK_ENABLE()
#define		SIGN_10_PIN			GPIO_PIN_11
#define		SIGN_10_PROE		GPIOE
#define		SIGN_10_CLK()		__HAL_RCC_GPIOE_CLK_ENABLE()

#define		PWR_CON_11_PIN		GPIO_PIN_12
#define		PWR_CON_11_PROE		GPIOE
#define		PWR_CON_11_CLK()	__HAL_RCC_GPIOE_CLK_ENABLE()
#define		IF_LOAD_11_PIN		GPIO_PIN_13
#define		IF_LOAD_11_PROE		GPIOE
#define		IF_LOAD_11_CLK()	__HAL_RCC_GPIOE_CLK_ENABLE()
#define		SIGN_11_PIN			GPIO_PIN_14
#define		SIGN_11_PROE		GPIOE
#define		SIGN_11_CLK()		__HAL_RCC_GPIOE_CLK_ENABLE()

#define		PWR_CON_12_PIN		GPIO_PIN_12
#define		PWR_CON_12_PROE		GPIOB
#define		PWR_CON_12_CLK()	__HAL_RCC_GPIOB_CLK_ENABLE()
#define		IF_LOAD_12_PIN		GPIO_PIN_15
#define		IF_LOAD_12_PROE		GPIOB
#define		IF_LOAD_12_CLK()	__HAL_RCC_GPIOB_CLK_ENABLE()
#define		SIGN_12_PIN			GPIO_PIN_8
#define		SIGN_12_PROE		GPIOB
#define		SIGN_12_CLK()		__HAL_RCC_GPIOB_CLK_ENABLE()

#define		PWR_CON_13_PIN		GPIO_PIN_15
#define		PWR_CON_13_PROE		GPIOD
#define		PWR_CON_13_CLK()	__HAL_RCC_GPIOD_CLK_ENABLE()
#define		IF_LOAD_13_PIN		GPIO_PIN_6
#define		IF_LOAD_13_PROE		GPIOC
#define		IF_LOAD_13_CLK()	__HAL_RCC_GPIOC_CLK_ENABLE()
#define		SIGN_13_PIN			GPIO_PIN_7
#define		SIGN_13_PROE		GPIOC
#define		SIGN_13_CLK()		__HAL_RCC_GPIOC_CLK_ENABLE()

#define		PWR_CON_14_PIN		GPIO_PIN_12
#define		PWR_CON_14_PROE		GPIOD
#define		PWR_CON_14_CLK()	__HAL_RCC_GPIOD_CLK_ENABLE()
#define		IF_LOAD_14_PIN		GPIO_PIN_13
#define		IF_LOAD_14_PROE		GPIOC
#define		IF_LOAD_14_CLK()	__HAL_RCC_GPIOC_CLK_ENABLE()
#define		SIGN_14_PIN			GPIO_PIN_14
#define		SIGN_14_PROE		GPIOC
#define		SIGN_14_CLK()		__HAL_RCC_GPIOC_CLK_ENABLE()

#define		PWR_CON_15_PIN		GPIO_PIN_9
#define		PWR_CON_15_PROE		GPIOD
#define		PWR_CON_15_CLK()	__HAL_RCC_GPIOD_CLK_ENABLE()
#define		IF_LOAD_15_PIN		GPIO_PIN_10
#define		IF_LOAD_15_PROE		GPIOC
#define		IF_LOAD_15_CLK()	__HAL_RCC_GPIOC_CLK_ENABLE()
#define		SIGN_15_PIN			GPIO_PIN_11
#define		SIGN_15_PROE		GPIOC
#define		SIGN_15_CLK()		__HAL_RCC_GPIOC_CLK_ENABLE()

#define		PWR_CON_16_PIN		GPIO_PIN_8
#define		PWR_CON_16_PROE		GPIOD
#define		PWR_CON_16_CLK()	__HAL_RCC_GPIOD_CLK_ENABLE()
#define		IF_LOAD_16_PIN		GPIO_PIN_9
#define		IF_LOAD_16_PROE		GPIOC
#define		IF_LOAD_16_CLK()	__HAL_RCC_GPIOC_CLK_ENABLE()
#define		SIGN_16_PIN			GPIO_PIN_8
#define		SIGN_16_PROE		GPIOA
#define		SIGN_16_CLK()		__HAL_RCC_GPIOA_CLK_ENABLE()

void LockGPIO_Init(void);
void GPIO_init(void);
u8 Read_IO_H(void);
u8 Read_IO_L(void);
#endif

