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
// #include "FreeRTOS.h"

void SystemInit()
{
	RCC_Init();
	// SysTick_Config(72 * 1000 * 1000 / 1000);
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

void task_heart_beat(void *pvParameters)
{
	while (1)
	{
		log_info("heart beat %d ms", HAL_GetTick());
		GPIO_TogglePin(GPIOC, GPIO_Pin_13);
		delay_ms(3000);
	}
}

uint32_t testSVC(uint32_t arg0, uint32_t arg1, uint32_t arg2, uint32_t arg3)
{
	__NOP();
	__ASM __volatile("svc #1\n");
	__NOP();
	return 0;
}

int main()
{
	GpioInit();
	USART_Init(USART1);
	testSVC(0, 1, 2, 3);
	task_heart_beat(NULL);
}
