#include <stdint.h>
#include <string.h>

#include "stm32f1xx.h"
#include "stm32f1xx_hal_def.h"
#include "stm32f1xx_hal_flash.h"

#include "log.h"
#include "tools.h"

#define RDPRTKEY 0x000000A5U
#define KEY1 0x45670123U
#define KEY2 0xCDEF89ABU

#define FLASH_SIZE (FLASH_BANK1_END - FLASH_BASE + 1)

/* private func */
static HAL_StatusTypeDef FLASH_Unlock_Prv()
{
    HAL_StatusTypeDef status = HAL_OK;

    if (READ_BIT(FLASH->CR, FLASH_CR_LOCK) != RESET)
    {
        WRITE_REG(FLASH->KEYR, KEY1);
        WRITE_REG(FLASH->KEYR, KEY2);
    }

    if (READ_BIT(FLASH->CR, FLASH_CR_LOCK) != RESET)
    {
        status = HAL_ERROR;
    }

    return status;
}

static HAL_StatusTypeDef FLASH_Lock_Prv()
{
    HAL_StatusTypeDef status = HAL_OK;

    if (READ_BIT(FLASH->CR, FLASH_CR_LOCK) != SET)
    {
        SET_BIT(FLASH->CR, FLASH_CR_LOCK);
    }

    if (READ_BIT(FLASH->CR, FLASH_CR_LOCK) != SET)
    {
        status = HAL_ERROR;
    }

    return status;
}

HAL_StatusTypeDef FLASH_Waite_Idle_Prv(uint32_t Timeout)
{
    HAL_StatusTypeDef status = HAL_OK;
    uint32_t tickstart = HAL_GetTick();

    // waite idle
    while (READ_BIT(FLASH->SR, FLASH_SR_BSY))
    {
        // when timeout do
        if (HAL_GetTick() - tickstart >= Timeout)
        {
            status = HAL_TIMEOUT;
            break;
        }
    }

    return status;
}

HAL_StatusTypeDef FLASH_Validate_Addr_Prv(uint32_t addr, uint32_t len)
{
    if (addr % 2 != 0)
    {
        log_error("addr % 2 != 0 => addr : 0x%X", addr);
        return HAL_ERROR;
    }

    if ((addr + len) > FLASH_SIZE)
    {
        log_error("addr out of bound => addr : 0x%X , len : %d", addr, len);
        return HAL_ERROR;
    }

    return HAL_OK;
}

static inline void FLASH_Progarm_HalfWord(uint32_t addr, uint16_t data)
{
    assert_param(FLASH_Validate_Addr_Prv(addr, 2) == HAL_OK);

    log_info("addr : 0x%X, data %d", addr, data);

    // start program
    SET_BIT(FLASH->CR, FLASH_CR_PG);

    // write data
    *(__IO uint16_t *)(FLASH_BASE + addr) = data;

    // write idle
    FLASH_Waite_Idle_Prv(HAL_MAX_DELAY);

    // clear STRT bit ()
    CLEAR_BIT(FLASH->CR, FLASH_CR_PG);
}

/* pubilc func */
uint32_t FLASH_Write(uint32_t addr, void *ptr, uint32_t len)
{
    assert_param(ptr != NULL);
    assert_param(FLASH_Validate_Addr_Prv(addr, 2) == HAL_OK);

    if (FLASH_Blank_Check(addr, len))
    {
        log_warn("FLASH_Blank_Check FAILED ADDR:0x%X LEN:%d", addr, len);
        return HAL_ERROR;
    }

    // unlock flash
    FLASH_Unlock_Prv();

    for (uint32_t i = 0; i < len; i += 2)
    {
        FLASH_Progarm_HalfWord(addr + i, *(uint16_t *)(ptr + i));
    }

    // lock flash
    FLASH_Lock_Prv();

    return HAL_OK;
}

uint32_t FLASH_Read(uint32_t addr, void *ptr, uint32_t len)
{
    assert_param(ptr != NULL);
    assert_param(FLASH_Validate_Addr_Prv(addr, 2) == HAL_OK);

    memcpy(ptr, (const void *)(addr + FLASH_BASE), len);
    return HAL_OK;
}

uint32_t FLASH_Blank_Check(uint32_t addr, uint32_t len)
{
    assert_param(FLASH_Validate_Addr_Prv(addr, 2) == HAL_OK);

    for (uint32_t i = 0; i < len; i++)
    {
        if (*(uint8_t *)(FLASH_BASE + addr + i) != 0xFF)
            return HAL_ERROR;
    }
    return HAL_OK;
}

uint32_t FLASH_Erase(uint32_t addr)
{
    assert_param(addr <= (FLASH_BANK1_END - FLASH_BASE));

    uint32_t pageStartAddr = addr - addr % 1024;

    log_info("FLASH_Erase ADDR:0x%X", addr + FLASH_BASE);
    log_info("FLASH_Erase pageStartAddr:0x%X", pageStartAddr + FLASH_BASE);

    // need erase page
    if (FLASH_Blank_Check(pageStartAddr, 1024))
    {
        // unlock flash
        FLASH_Unlock_Prv();

        // write idle
        FLASH_Waite_Idle_Prv(HAL_MAX_DELAY);

        // start page erase
        SET_BIT(FLASH->CR, FLASH_CR_PER);

        // select page
        WRITE_REG(FLASH->AR, addr + FLASH_BASE);

        // start erase
        SET_BIT(FLASH->CR, FLASH_CR_STRT);

        // write idle
        FLASH_Waite_Idle_Prv(HAL_MAX_DELAY);

        // over page erase
        CLEAR_BIT(FLASH->CR, FLASH_CR_PER);

        // lock flash
        FLASH_Lock_Prv();
    }

    return FLASH_Blank_Check(pageStartAddr, 1024);
}
