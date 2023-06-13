#ifndef __TOOLS_H
#define __TOOLS_H
#include <stdint.h>
#include <stdio.h>

void delay_ms(uint32_t ms);

uint32_t HAL_GetTick();

#define assert_param(expr)                                                     \
  ((expr) ? (void)0U : assert_failed((uint8_t *)__FILE__, __LINE__))
/* Exported functions ------------------------------------------------------- */
static inline void assert_failed(uint8_t *file, uint32_t line) {
  printf("Wrong parameters value: file %s on line %u\n", file, line);

  while (1) {
  }
}

#endif