#ifndef __STM32F1xx_HAL_GPIO_H
#define __STM32F1xx_HAL_GPIO_H

#include "stm32f103x6.h"

typedef enum
{
	GPIO_Speed_10MHz = 0x01,
	GPIO_Speed_2MHz = 0x01,
	GPIO_Speed_50MHz = 0x01,
} GPIO_Speed_TypeDef;

typedef enum
{
	GPIO_Mode_AIN = 0x00,			// 模拟输入
	GPIO_Mode_IN_FLOATING = 0x04,	// 浮空输入
	GPIO_Mode_IPD = 0x28,			// 下拉输入
	GPIO_Mode_IPU = 0x48,			// 上拉输入

	GPIO_Mode_OUT_OD = 0x14,		// 开漏输出
	GPIO_Mode_OUT_PP = 0x10,		// 推挽输出
	GPIO_Mode_AF_Od = 0x1C,			// 复用开漏输出
	GPIO_Mode_AF_PP = 0x18,			// 复用推挽输出
} GPIO_Mode_TypeDef;

typedef struct
{
	u16 GPIO_Pin;					//引脚

	GPIO_Speed_TypeDef GPIO_Speed;	//速度

	GPIO_Mode_TypeDef GPIO_Mode;	//模式
} GPIO_InitTypeDef;


#define GPIO_Pin_0 ((u16)1 << 0)
#define GPIO_Pin_1 ((u16)1 << 1)
#define GPIO_Pin_2 ((u16)1 << 2)
#define GPIO_Pin_3 ((u16)1 << 3)
#define GPIO_Pin_4 ((u16)1 << 4)
#define GPIO_Pin_5 ((u16)1 << 5)
#define GPIO_Pin_6 ((u16)1 << 6)
#define GPIO_Pin_7 ((u16)1 << 7)
#define GPIO_Pin_8 ((u16)1 << 8)
#define GPIO_Pin_9 ((u16)1 << 9)
#define GPIO_Pin_10 ((u16)1 << 10)
#define GPIO_Pin_11 ((u16)1 << 11)
#define GPIO_Pin_12 ((u16)1 << 12)
#define GPIO_Pin_13 ((u16)1 << 13)
#define GPIO_Pin_14 ((u16)1 << 14)
#define GPIO_Pin_15 ((u16)1 << 15)
#define GPIO_Pin_16 ((u16)1 << 16)
#define GPIO_Pin_All ((u16)0xFFFF)

void GPIO_SetBits(GPIO_TypeDef* GPIOx, u16 GPIO_Pin);

void GPIO_ResetBits(GPIO_TypeDef* GPIOx, u16 GPIO_Pin);

void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitConfig);

#endif