#include "stm32f10x.h"
#include "stm32f1xx_hal_gpio.h"
#include "stm32f1xx_hal_usart.h"

void SystemInit()
{
}

void delay(unsigned int ms)
{
	unsigned int count = 12000;
	while (ms--)
	{
		count = 12000;
		while (count--)
			;
	}
}

int main()
{
	RCC->CR |= (1 << 16);

	while (RCC->CR & (1 << 17))
	{
		RCC->CFGR |= (1 << 20 | 1 << 18 | 1 << 16 | 1 << 14 | 1 << 10);
		RCC->CR |= (1 << 24);

		while (RCC->CR & (1 << 25))
		{
			RCC->CFGR |= (1 << 1);
		}
	}

	GPIO_InitTypeDef GPIO_InitConfig1;
	GPIO_InitConfig1.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitConfig1.GPIO_Mode = GPIO_Mode_OUT_PP;
	GPIO_InitConfig1.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_InitTypeDef GPIO_InitConfig;
	GPIO_InitConfig.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitConfig.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitConfig.GPIO_Speed = GPIO_Speed_50MHz;

	// 打开gpio A端口的时钟
	RCC->APB2ENR |= (1 << 2);
	// 打开gpio c端口的时钟
	RCC->APB2ENR |= (1 << 4);
	// 打开USART1端口的时钟
	RCC->APB2ENR |= (1 << 14);
	GPIO_Init(GPIOA, &GPIO_InitConfig);
	GPIO_Init(GPIOC, &GPIO_InitConfig1);
	USART_Init(USART1);
	while (1)
	{
		if ((USART1->SR) & (1 << 7))
		{
			USART1->DR = 0x20u;

			// GPIO_SetBits(GPIOC, GPIO_Pin_13);
			delay(100);
			GPIOC->ODR ^= (1 << 13);
		}
	}
}
