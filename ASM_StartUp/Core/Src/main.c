#include "stm32f1xx.h"
#include "stm32f1xx_hal_gpio.h"
#include "stm32f1xx_hal_usart.h"
#include "stm32f1xx_hal_rcc.h"
#include <stdio.h>

// int __io_putchar(int ch)
// {
//     return USART_Transmit(USART1, (uint8_t *)&ch, 1);
// }

int _write(int file, char *ptr, int len)
{
    USART_Transmit(USART1, (uint8_t *)ptr, len);
    return len;
}

// 系统初始化
void SystemInit()
{
    RCC_Init();
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

void delay_us(unsigned int us)
{
    CLEAR_BIT(SysTick->CTRL, SysTick_CTRL_ENABLE_Msk);
    SysTick->LOAD = us * 9;
    SET_BIT(SysTick->CTRL, SysTick_CTRL_ENABLE_Msk);
    while (!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk))
    {
        ;
    }
    CLEAR_BIT(SysTick->CTRL, SysTick_CTRL_ENABLE_Msk);
    SysTick->VAL = 0;
}

void delay(unsigned int ms)
{
    while (ms--)
    {
        delay_us(1000);
    }
}

uint8_t pDate[] = {'c'};

int main()
{
    GpioInit();
    USART_Init(USART1);
    GPIO_ResetBits(GPIOC, GPIO_Pin_13);
    uint8_t *str = (uint8_t *)"1234567890";
    while (1)
    {
        USART_Transmit(USART1, str, 10);
        //        printf("11111\r\n");
        _write(1, str, 10);
        delay(500);
        // GPIOC->ODR ^= (1 << 13);
    }
}
