#include "stm32f10x.h"

void SystemInit()
{
}

int main()
{
	RCC_APB2ENR |= (1 << 3);
	*(unsigned int *)0x40021018 |= (1 << 4);

	GPIOC_CRH &= ~(0x0F << (4 * 5));
	GPIOC_CRH |= (1 << 4 * 5);

	GPIOC_ODR &= ~(1 << 13);

	// *(unsigned int *)0x40021018 |=(1<<4);
	// //打开gpio c端口的时钟
	// *(unsigned int *)0x40011004 &=~(1111<<(4*5));
	// *(unsigned int *)0x40011004 |=(1<<(4*5));
	// //配置io口为输出，10MHz
	// *(unsigned int *)0x4001100C &=~(1<<13);
	//控制odr寄存器输出低电平

	while (1)
		;
}
