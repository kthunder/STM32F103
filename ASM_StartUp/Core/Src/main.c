#include "stm32f10x.h"
#include "stm32f1xx_hal_gpio.h"

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
	GPIO_InitTypeDef GPIO_InitConfig;
	GPIO_InitConfig.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitConfig.GPIO_Mode = GPIO_Mode_OUT_PP;
	GPIO_InitConfig.GPIO_Speed = GPIO_Speed_50MHz;

	// 打开gpio c端口的时钟
	RCC_APB2ENR |= (1 << 3);
	*(unsigned int*)0x40021018 |= (1 << 4);
	// 配置io口为输出，10MHz
	GPIOC->CRH &= ~(0x0F << (4 * 5));
	GPIOC->CRH |= (1 << 4 * 5);
	// 控制odr寄存器输出低电平
	while (1)
	{
		delay(100);
		GPIOC->ODR ^= (1 << 13);
	}
}
