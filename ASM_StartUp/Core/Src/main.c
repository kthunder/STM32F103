#include "stm32f103x6.h"
#include "stm32f1xx_hal_gpio.h"
#include "stm32f1xx_hal_usart.h"
#include "stm32f1xx_hal_rcc.h"
#include <stdio.h>

int __io_putchar(int ch)
{
	return USART_Transmit(USART1, (uint8_t*)&ch, 1);
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

void delay(unsigned int ms)
{
	unsigned int count = 0;
	while (ms--)
	{
		count = 72000;
		while (count--)
			;
	}
}

uint8_t pDate[] = {'c'};

int main()
{
	GpioInit();
	USART_Init(USART1);
	GPIO_ResetBits(GPIOC, GPIO_Pin_13);
	while (1)
	{
		USART_Transmit(USART1, pDate, 1);
		// printf("1234\n");
		USART_Transmit(USART1, pDate, 1);
		delay(100);
		GPIOC->ODR ^= (1 << 13);
	}
}
