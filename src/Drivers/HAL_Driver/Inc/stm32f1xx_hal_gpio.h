#ifndef __STM32F1xx_HAL_GPIO_H
#define __STM32F1xx_HAL_GPIO_H

#ifdef __cplusplus
extern "C"
{
#endif

// #include "stm32f1xx.h"
#include "stm32f103x6.h"

    typedef enum
    {
        GPIO_Speed_10MHz = 0x01,
        GPIO_Speed_2MHz = 0x01,
        GPIO_Speed_50MHz = 0x01,
    } GPIO_Speed_TypeDef;

    typedef enum
    {
        GPIO_Mode_AIN = 0x00,         // 模拟输入
        GPIO_Mode_IN_FLOATING = 0x04, // 浮空输入
        GPIO_Mode_IPD = 0x28,         // 下拉输入
        GPIO_Mode_IPU = 0x48,         // 上拉输入

        GPIO_Mode_OUT_OD = 0x14, // 开漏输出
        GPIO_Mode_OUT_PP = 0x10, // 推挽输出
        GPIO_Mode_AF_Od = 0x1C,  // 复用开漏输出
        GPIO_Mode_AF_PP = 0x18,  // 复用推挽输出
    } GPIO_Mode_TypeDef;

    typedef struct
    {
        uint16_t GPIO_Pin; // 引脚

        GPIO_Speed_TypeDef GPIO_Speed; // 速度

        GPIO_Mode_TypeDef GPIO_Mode; // 模式
    } GPIO_InitTypeDef;

#define GPIO_Pin_0 ((uint16_t)1 << 0)
#define GPIO_Pin_1 ((uint16_t)1 << 1)
#define GPIO_Pin_2 ((uint16_t)1 << 2)
#define GPIO_Pin_3 ((uint16_t)1 << 3)
#define GPIO_Pin_4 ((uint16_t)1 << 4)
#define GPIO_Pin_5 ((uint16_t)1 << 5)
#define GPIO_Pin_6 ((uint16_t)1 << 6)
#define GPIO_Pin_7 ((uint16_t)1 << 7)
#define GPIO_Pin_8 ((uint16_t)1 << 8)
#define GPIO_Pin_9 ((uint16_t)1 << 9)
#define GPIO_Pin_10 ((uint16_t)1 << 10)
#define GPIO_Pin_11 ((uint16_t)1 << 11)
#define GPIO_Pin_12 ((uint16_t)1 << 12)
#define GPIO_Pin_13 ((uint16_t)1 << 13)
#define GPIO_Pin_14 ((uint16_t)1 << 14)
#define GPIO_Pin_15 ((uint16_t)1 << 15)
#define GPIO_Pin_16 ((uint16_t)1 << 16)
#define GPIO_Pin_All ((uint16_t)0xFFFF)

    void GPIO_SetBits(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

    void GPIO_ResetBits(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

    void GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

    void GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef *GPIO_InitConfig);

#ifdef __cplusplus
}
#endif

#endif