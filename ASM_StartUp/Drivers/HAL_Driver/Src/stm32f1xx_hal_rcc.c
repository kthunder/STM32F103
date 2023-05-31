#include "stm32f1xx.h"
#include "stm32f1xx_hal_rcc.h"


void RCC_Init()
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

	// 打开gpio A C 、 USART1端口的时钟
	RCC->APB2ENR |= (RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPCEN | RCC_APB2ENR_USART1EN);
}