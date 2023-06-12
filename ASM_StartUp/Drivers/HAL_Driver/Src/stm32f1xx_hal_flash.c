#include "stm32f1xx_hal_flash.h"
#include "log.h"
#include "stm32f103x6.h"
#include "stm32f1xx.h"
#include <stdint.h>
#include <string.h>

#define RDPRTKEY 0x000000A5U
#define KEY1 0x45670123U
#define KEY2 0xCDEF89ABU

static inline void FLASH_UNLOCK() {
  FLASH->KEYR = KEY1;
  FLASH->KEYR = KEY2;
}

static inline void FLASH_LOCK() { SET_BIT(FLASH->CR, FLASH_CR_LOCK); }

static inline void FLASH_Progarm_HalfWord(uint32_t addr, uint16_t data) {
  // start program
  SET_BIT(FLASH->CR, FLASH_CR_PG);
  // write data
  *(__IO uint16_t *)(FLASH_BASE + addr) = data;
}

uint32_t FLASH_Write(uint32_t addr, void *ptr, uint32_t len) {

  if (FLASH_Blank_Check(addr, len)) {
    log_warn("FLASH_Blank_Check FAILED ADDR:0x%X LEN:%d", addr, len);
    return 1;
  }

  // unlock flash
  if (READ_BIT(FLASH->CR, FLASH_CR_LOCK))
    FLASH_UNLOCK();

  for (uint32_t i = 0; i < len; i += 2) {
    FLASH_Progarm_HalfWord(addr + 2 * i, *(uint16_t *)(ptr + i));
    // waite idle
    while (READ_BIT(FLASH->SR, FLASH_SR_BSY))
      ;
    // clear STRT bit ()
    CLEAR_BIT(FLASH->CR, FLASH_CR_PG);
  }

  // lock flash
  FLASH_LOCK();

  return 0;
}

uint32_t FLASH_Read(uint32_t addr, void *ptr, uint32_t len) {
  memcpy(ptr, (const void *)(addr + FLASH_BASE), len);
  return 0;
}

uint32_t FLASH_Blank_Check(uint32_t addr, uint32_t len) {
  for (uint32_t i = 0; i < len; i++) {
    if (*(uint8_t *)(FLASH_BASE + addr + i) != 0xFF)
      return 1;
  }
  return 0;
}

uint32_t FLASH_Erase(uint32_t addr) {

  uint32_t pageAddr = addr - addr % 1024;

  log_info("FLASH_Erase ADDR:0x%X", addr + FLASH_BASE);
  log_info("FLASH_Erase pageAddr:0x%X", pageAddr + FLASH_BASE);

  // need erase page
  if (FLASH_Blank_Check(pageAddr, 1024)) {
    // unlock flash
    if (READ_BIT(FLASH->CR, FLASH_CR_LOCK))
      FLASH_UNLOCK();

    // waite idle
    while (READ_BIT(FLASH->SR, FLASH_SR_BSY))
      ;
    // start page erase
    SET_BIT(FLASH->CR, FLASH_CR_PER);
    // select page
    WRITE_REG(FLASH->AR, addr + FLASH_BASE);
    // start erase
    SET_BIT(FLASH->CR, FLASH_CR_STRT);
    // waite idle
    while (READ_BIT(FLASH->SR, FLASH_SR_BSY))
      ;
    // over page erase
    CLEAR_BIT(FLASH->CR, FLASH_CR_PER);

    // lock flash
    FLASH_LOCK();
  }

  return FLASH_Blank_Check(pageAddr, 1024);
}
