#include <vega/delay.h>
#include <vega/timer.h>
#include <vega/interrupt.h>
#include <vega/thejas32.h>

/*---------------------------------------------------------------------------------------------------*/

__attribute__((weak)) void delayus(uint32_t time)
{
    PLIC->IER &= ~(0x1 << TIMER0_IRQn);
    htimer0.State = STATE_BUSY;
    TIMER0->CTRL = 0;
    TIMER0->LOAD = time * 100;
    TIMER0->CTRL |= TIMER_CTRL_MODE_1 | TIMER_CTRL_EN;
    while (! (TIMER0->ISR & 0x1UL));
    htimer0.State = STATE_READY;
}

/*---------------------------------------------------------------------------------------------------*/

__attribute__((weak)) void delayms(uint32_t time)
{
    PLIC->IER &= ~(0x1 << TIMER0_IRQn);
    htimer0.State = STATE_BUSY;
    TIMER0->CTRL = 0;
    TIMER0->LOAD = time * 100000;
    TIMER0->CTRL |= TIMER_CTRL_MODE_1 | TIMER_CTRL_EN;
    while (! (TIMER0->ISR & 0x1UL));
    htimer0.State = STATE_READY;
}

/*---------------------------------------------------------------------------------------------------*/