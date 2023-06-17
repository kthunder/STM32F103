#include "log.h"
#include "stm32f103x6.h"
#include "stm32f1xx.h"
#include "stm32f1xx_hal_flash.h"
#include "stm32f1xx_hal_gpio.h"
#include "stm32f1xx_hal_rcc.h"
#include "stm32f1xx_hal_usart.h"
#include "tools.h"
#include <stdint.h>
#include <stdio.h>

void SystemInit()
{
    RCC_Init();
    SysTick_Config(72 * 1000 * 1000 / 1000);
}

void GpioInit()
{
    GPIO_InitTypeDef ucGpioConfig[] = {
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

    GPIO_Init(GPIOA, &ucGpioConfig[0]);
    GPIO_Init(GPIOA, &ucGpioConfig[1]);
    GPIO_Init(GPIOC, &ucGpioConfig[2]);
}

int main()
{
    GpioInit();
    USART_Init(USART1);

    while (1)
    {
        log_info("heart beat");
        GPIO_TogglePin(GPIOC, GPIO_Pin_13);
        delay_ms(3000);
    }
}
