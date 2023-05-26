#include "stm32f103x6.h"
#include "stm32f1xx_hal_gpio.h"
#include "stm32f1xx_hal_usart.h"
#include "stm32f1xx_hal_rcc.h"

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

int main()
{
	GpioInit();
	USART_Init(USART1);
	GPIO_ResetBits(GPIOC, GPIO_Pin_13);
	while (1)
	{
		if ((USART1->SR) & (1 << 7))
		{
			// USART1->DR = RCC->CFGR;
			// USART1->DR = RCC->CFGR >> 8;
			USART1->DR = 0x11;
			// USART1->DR = RCC->CFGR >> 24;
		}
		delay(100);
		GPIOC->ODR ^= (1 << 13);
	}
}
