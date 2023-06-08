#include "stm32f1xx.h"
#include "stm32f1xx_hal_gpio.h"
#include "stm32f1xx_hal_usart.h"
#include "stm32f1xx_hal_rcc.h"
#include <stdio.h>
#include "tools.h"

// 系统初始化
void SystemInit()
{
    RCC_Init();
    SysTick_Config(72 * 1000 * 1000 / 1000);
}

void GpioInit()
{
    GPIO_InitTypeDef ucGpio[] = {
        {
            .GPIO_Pin = GPIO_Pin_9,
            .GPIO_Mode = GPIO_Mode_AF_PP,
            .GPIO_Speed = GPIO_Speed_50MHz,
        },
        {
            .GPIO_Pin = GPIO_Pin_8,
            .GPIO_Mode = GPIO_Mode_AF_PP,
            .GPIO_Speed = GPIO_Speed_50MHz,
        },
        {
            .GPIO_Pin = GPIO_Pin_13,
            .GPIO_Mode = GPIO_Mode_OUT_PP,
            .GPIO_Speed = GPIO_Speed_50MHz,
        },
    };

    GPIO_Init(GPIOA, &ucGpio[0]);
    GPIO_Init(GPIOA, &ucGpio[1]);
    GPIO_Init(GPIOC, &ucGpio[2]);
}

int main()
{
    GpioInit();
    USART_Init(USART1);
    GPIO_ResetBits(GPIOC, GPIO_Pin_13);
    while (1)
    {
        GPIOC->ODR ^= (1 << 13);
        _write(0, "123456789\n", 10);
        delay_ms(1000);
    }
}
