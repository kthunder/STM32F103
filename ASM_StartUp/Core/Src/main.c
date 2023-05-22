#include "stm32f103x6.h"
#include "stm32f1xx_hal_gpio.h"
#include "stm32f1xx_hal_usart.h"

// 系统初始化
void SystemInit()
{
	// 外部高速时钟使能
	RCC->CR |= RCC_CR_HSEON;

	while (!(RCC->CR & RCC_CR_HSERDY))
		;

	// PLL source HSE
	RCC->CFGR |= RCC_CFGR_PLLSRC;
	// 分频设置
	// PLL X 9
	RCC->CFGR |= RCC_CFGR_PLLMULL9;
	// APB2 DIV 1
	RCC->CFGR |= RCC_CFGR_PPRE2_DIV1;
	// APB1 DIV 2
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;
	// AHB DIV 1
	RCC->CFGR |= RCC_CFGR_HPRE_DIV1;

	FLASH->ACR |= 0x32;

	// MCO out put PLL DIV 2
	RCC->CFGR |= RCC_CFGR_MCOSEL_PLL_DIV2;

	// PLL ON
	RCC->CR |= RCC_CR_PLLON;

	while (!(RCC->CR & RCC_CR_PLLRDY))
		;
	// SYSCLK switch to PLL
	RCC->CFGR |= RCC_CFGR_SW_1;
	// wait for SYSCLK switch to PLL
	while (!(RCC->CFGR & RCC_CFGR_SWS_PLL))
		;

	// 打开gpio A端口的时钟
		RCC->APB2ENR |= (1 << 2);
	// 打开gpio c端口的时钟
	RCC->APB2ENR |= (1 << 4);
	// 打开USART1端口的时钟
		RCC->APB2ENR |= (1 << 14);
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
