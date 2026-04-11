/** @file hal_timer.c
 *  @brief Timer routines for THEJAS32
 *  @author Arif B <arif.dev@pm.me>
 */

#include <vega/thejas32.h>
#include <vega/timer.h>
#include <vega/interrupt.h>
#include <stddef.h>
#include <errno.h>


TIMER_Handle_t htimer0 = {
    .Instance = TIMER0,
    .LoadCount = 50000000,
    .Mode = TIMER_MODE_PERIODIC,
    .State = STATE_READY
};

TIMER_Handle_t htimer1 = {
    .Instance = TIMER1,
    .LoadCount = 50000000,
    .Mode = TIMER_MODE_PERIODIC,
    .State = STATE_READY
};

TIMER_Handle_t htimer2 = {
    .Instance = TIMER2,
    .LoadCount = 50000000,
    .Mode = TIMER_MODE_PERIODIC,
    .State = STATE_READY
};

/*---------------------------------------------------------------------------------------------------*/

int TIMER_Init(TIMER_Handle_t *htimer)
{
    if (htimer == NULL) {
        errno = EFAULT;
        return FAIL;
    }

    if (htimer->Instance == NULL) {
        errno = EFAULT;
        return FAIL;
    }

    if (htimer->State == STATE_BUSY) {
        return STATE_BUSY;
    }
    
    htimer->Instance->CTRL = 0;

    htimer->Instance->LOAD = htimer->LoadCount;
    
    switch (htimer->Mode) {
        case TIMER_MODE_FREERUN:
            htimer->Instance->CTRL &= ~(0x1UL << TIMER_CTRL_MODE_Pos);
            break;
        case TIMER_MODE_PERIODIC:
            htimer->Instance->CTRL |= (0x1UL << TIMER_CTRL_MODE_Pos);
            break;
        default:
            errno = EINVAL;
            return EINVAL;
    }

    return OK;
}

/*---------------------------------------------------------------------------------------------------*/

int TIMER_Start(TIMER_Handle_t *htimer)
{
    if (htimer == NULL) {
        errno = EFAULT;
        return FAIL;
    }

    if (htimer->Instance == NULL) {
        errno = EFAULT;
        return FAIL;
    }

    if (htimer->State == STATE_BUSY) {
        errno = EBUSY;
        return FAIL;
    }

    htimer->Instance->CTRL |= TIMER_CTRL_EN;
    htimer->State = STATE_BUSY;

    return OK;
}

/*---------------------------------------------------------------------------------------------------*/


int TIMER_Start_IT(TIMER_Handle_t *htimer)
{
    if (htimer == NULL) {
        errno = EFAULT;
        return FAIL;
    }

    if (htimer->Instance == NULL) {
        errno = EFAULT;
        return FAIL;
    }

    if (htimer->State == STATE_BUSY) {
        errno = EBUSY;
        return FAIL;
    }

    int irqn;
    
    if (htimer->Instance == TIMER0) {
       irqn = TIMER0_IRQn; 
    }
    else if (htimer->Instance == TIMER1) {
        irqn = TIMER1_IRQn;
    }
    else if (htimer->Instance == TIMER2) {
        irqn = TIMER2_IRQn;
    }
    else {
        errno = ENXIO;
        return FAIL;
    }

    PLIC->IER |= 0x1UL << irqn;

    htimer->Instance->CTRL |= TIMER_CTRL_EN;
    htimer->State = STATE_BUSY;
    
    return OK;
}

/*---------------------------------------------------------------------------------------------------*/

int TIMER_Stop(TIMER_Handle_t *htimer)
{
    if (htimer == NULL) {
        errno = EFAULT;
        return FAIL;
    }

    if (htimer->Instance == NULL) {
        errno = EFAULT;
        return FAIL;
    }

    htimer->Instance->CTRL &= ~(TIMER_CTRL_EN);

    int irqn;
    
    if (htimer->Instance == TIMER0) {
       irqn = TIMER0_IRQn; 
    }
    else if (htimer->Instance == TIMER1) {
        irqn = TIMER1_IRQn;
    }
    else if (htimer->Instance == TIMER2) {
        irqn = TIMER2_IRQn;
    }
    else {
        errno = ENXIO;
        return FAIL;
    }

    PLIC->IER &= ~(0x1UL << irqn);
    htimer->State = STATE_READY;
    return OK;
}

/*---------------------------------------------------------------------------------------------------*/

int TIMER_GetCount(TIMER_Handle_t *htimer)
{
    if (htimer == NULL) {
        errno = EFAULT;
        return FAIL;
    }

    if (htimer->Instance == NULL) {
        errno = EFAULT;
        return FAIL;
    }

    return htimer->Instance->CVAL;
}

/*---------------------------------------------------------------------------------------------------*/


__attribute__((weak))void TIMER_ElapsedCallback(TIMER_Handle_t *htimer)
{
    return;
}

void __Timer_ISR(TIMER_Handle_t *htimer)
{
    if (htimer == NULL) {
        errno = EFAULT;
        return;
    }

    if (htimer->Instance == NULL) {
        errno = EFAULT;
        return;
    }

    TIMER_ElapsedCallback(htimer);

    // Clear timer interrupt by reading the INTCLR register
    __attribute__((unused)) int clr = htimer->Instance->ICLR;
}

void TIMER0_IRQHandler(void)
{
    __Timer_ISR(&htimer0);
}

void TIMER1_IRQHandler(void)
{
    __Timer_ISR(&htimer1);
}

void TIMER2_IRQHandler(void)
{
    __Timer_ISR(&htimer2);
}