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

void printHex(uint8_t *ptr, uint32_t len) {

  for (uint32_t i = 0; i < len; i++) {
    printf("%02X ", ptr[i]);
    if (((i + 1) % 20 == 0) || (i + 1 == len)) {
      printf("\n");
    }
  }
}

// 系统初始化
void SystemInit() {
  RCC_Init();
  SysTick_Config(72 * 1000 * 1000 / 1000);
}

void GpioInit() {
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

int main() {
  uint8_t ucWrite[100] = {0};
  //   uint8_t ucRead[100] = {0};

  GpioInit();
  USART_Init(USART1);
  log_init(0, true, NULL, NULL);

  for (uint32_t i = 0; i < 100; i++) {
    ucWrite[i] = i % 0xFF;
  }
  printHex(ucWrite, 100);

  //   FLASH_Erase(0x6000);
//   for (uint32_t addr = 0x6000, step = 100; addr < FLASH_BANK1_END - FLASH_BASE;
//        addr += step) {
//     log_info("addr : 0x%X, len : %d", addr, step);

//     if (!FLASH_Blank_Check(addr, step)) {
//       FLASH_Write(addr, ucWrite, step);
//       printf("address : 0x%02lX\n", addr);
//       printHex((uint8_t *)(FLASH_BASE + addr), step);
//       break;
//     }
//   }
    __ASM volatile ("SVC 0x01");

  while (1) {
    GPIOC->ODR ^= (1 << 13);
    printf("heart beat\n");
    delay_ms(5000);
  }
}
