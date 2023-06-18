#include "tools.h"
#include "stm32f1xx.h"
#include <stdint.h>
#include "log.h"

uint32_t HAL_GetUsTick_Prv()
{
    static uint8_t init = 0;

    if (!init)
    {
        init++;
        log_info("init");
        // enable DWT
        SET_BIT(CoreDebug->DEMCR, CoreDebug_DEMCR_TRCENA_Msk);
        // clear DWT CYCCNT( not need )
        DWT->CYCCNT = 0;
        // enable DWT CYCCNT
        SET_BIT(DWT->CTRL, DWT_CTRL_CYCCNTENA_Msk);
    }

    return DWT->CYCCNT / 72;
}

uint32_t HAL_GetTick()
{
    return HAL_GetUsTick_Prv() / 1000;
}

void delay_ms(uint32_t ms)
{
    uint32_t currentUsTick = HAL_GetUsTick_Prv();

    while ((HAL_GetUsTick_Prv() - currentUsTick) < (ms * 1000))
        ;
}

void Active_Soft_EXIT(IRQn_Type nIRQ)
{
    // __ASM volatile("SVC 0x01");
    NVIC_EnableIRQ(nIRQ);
    SET_BIT(SCB->CCR, SCB_CCR_USERSETMPEND_Msk);
    WRITE_REG(NVIC->STIR, nIRQ);
}