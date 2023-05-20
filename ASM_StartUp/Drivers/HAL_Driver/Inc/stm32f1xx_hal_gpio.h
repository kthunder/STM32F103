#ifndef __STM32F1xx_HAL_GPIO_H
#define __STM32F1xx_HAL_GPIO_H

#include "stm32f10x.h"

/*GPIO外设基地址*/
#define GPIOA_BASE (APB2PERIPH_BASE + 0x0800U)
#define GPIOB_BASE (APB2PERIPH_BASE + 0x0C00U)
#define GPIOC_BASE (APB2PERIPH_BASE + 0x1000U)
#define GPIOD_BASE (APB2PERIPH_BASE + 0x1400U)
#define GPIOE_BASE (APB2PERIPH_BASE + 0x1800U)
#define GPIOF_BASE (APB2PERIPH_BASE + 0x1C00U)
#define GPIOG_BASE (APB2PERIPH_BASE + 0x2000U)

/*GPIO外设声明*/
#define GPIOA ((GPIO_TypeDef*)GPIOA_BASE)
#define GPIOB ((GPIO_TypeDef*)GPIOB_BASE)
#define GPIOC ((GPIO_TypeDef*)GPIOC_BASE)
#define GPIOD ((GPIO_TypeDef*)GPIOD_BASE)
#define GPIOE ((GPIO_TypeDef*)GPIOE_BASE)
#define GPIOF ((GPIO_TypeDef*)GPIOF_BASE)
#define GPIOG ((GPIO_TypeDef*)GPIOG_BASE)

typedef struct
{
	__IO u32 CRL;  // 端口配置低寄存器			地址偏移0x00
	__IO u32 CRH;  // 端口配置高寄存器			地址偏移0x04
	__IO u32 IDR;  // 端口数据输入寄存器		地址偏移0x08
	__IO u32 ODR;  // 端口数据输出寄存器		地址偏移0x0C
	__IO u32 BSRR; // 端口位设置/清除寄存器		地址偏移0x10
	__IO u32 BRR;  // 端口位清除寄存器			地址偏移0x14
	__IO u32 LCKR; // 端口配置锁定寄存器		地址偏移0x18
} GPIO_TypeDef;

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

#endif