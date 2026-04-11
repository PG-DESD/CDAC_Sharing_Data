/** @file hal_interrupt.c
 *  @brief Interrupt handler routines for THEJAS32
 *  @author Arif B <arif.dev@pm.me>
 */

#include <stdint.h>
#include <vega/csr.h>
#include <vega/interrupt.h>
#include <vega/thejas32.h>


/* Platform-Level Interrupt Controller - vector table */

static void (* plic_vtable[32])(void) = {
    UART0_IRQHandler,
    UART1_IRQHandler,
    UART2_IRQHandler,
    SPI0_IRQHandler,
    SPI1_IRQHandler,
    I2C0_IRQHandler,
    I2C1_IRQHandler,
    TIMER0_IRQHandler,
    TIMER1_IRQHandler,
    TIMER2_IRQHandler,
    GPIO0_IRQHandler,
    GPIO1_IRQHandler,
    GPIO2_IRQHandler,
    GPIO3_IRQHandler,
    GPIO4_IRQHandler,
    GPIO5_IRQHandler,
    GPIO6_IRQHandler,
    GPIO7_IRQHandler,
    GPIO8_IRQHandler,
    GPIO9_IRQHandler,
    GPIO10_IRQHandler,
    GPIO11_IRQHandler,
    I2C2_IRQHandler,
    SPI2_IRQHandler,
    PWMChannel1_IRQHandler,
    PWMChannel2_IRQHandler,
    PWMChannel3_IRQHandler,
    PWMChannel4_IRQHandler,
    PWMChannel5_IRQHandler,
    PWMChannel6_IRQHandler,
    PWMChannel7_IRQHandler,
    PWMChannel8_IRQHandler,
};

/*---------------------------------------------------------------------------------------------------*/

void __enable_irq(void)
{
    csr_setbit(mie, MIE_EIE);
    csr_setbit(mstatus, MSTATUS_MIE);
}

/*---------------------------------------------------------------------------------------------------*/

void __disable_irq(void)
{
    csr_clrbit(mie, MIE_EIE);
    csr_clrbit(mstatus, MSTATUS_MIE);
}

/*---------------------------------------------------------------------------------------------------*/

__attribute__((weak))void _exception_handler(void)
{
    return;
}

void _interrupt_handler(void)
{
    uint32_t intstat = PLIC->ISR;

    for (uint32_t i = 0; i < 32; i++) {
        if ((intstat >> i) & 0x1UL) {
            // Call ISR for each triggered interrupt, according to priority
            plic_vtable[i]();
        }
    }
}

void _trap_handler(void)
{
    int cause;

    cause = (csr_read(mcause) >> 31);

    if (cause) {
        _interrupt_handler();
    }
    else {
        _exception_handler();
    }
}

/*---------------------------------------------------------------------------------------------------*/

void InfiniteLoop(void)
{
    while (1);
}


void UART0_IRQHandler(void)     __attribute__((weak,alias("InfiniteLoop")));
void UART1_IRQHandler(void)     __attribute__((weak,alias("InfiniteLoop")));
void UART2_IRQHandler(void)     __attribute__((weak,alias("InfiniteLoop")));

void SPI0_IRQHandler(void)      __attribute__((weak,alias("InfiniteLoop")));
void SPI1_IRQHandler(void)      __attribute__((weak,alias("InfiniteLoop")));
void SPI2_IRQHandler(void)      __attribute__((weak,alias("InfiniteLoop")));

void I2C0_IRQHandler(void)      __attribute__((weak,alias("InfiniteLoop")));
void I2C1_IRQHandler(void)      __attribute__((weak,alias("InfiniteLoop")));
void I2C2_IRQHandler(void)      __attribute__((weak,alias("InfiniteLoop")));


void TIMER0_IRQHandler(void)    __attribute__((weak,alias("InfiniteLoop")));
void TIMER1_IRQHandler(void)    __attribute__((weak,alias("InfiniteLoop")));
void TIMER2_IRQHandler(void)    __attribute__((weak,alias("InfiniteLoop")));

void GPIO0_IRQHandler(void)     __attribute__((weak,alias("InfiniteLoop")));
void GPIO1_IRQHandler(void)     __attribute__((weak,alias("InfiniteLoop")));
void GPIO2_IRQHandler(void)     __attribute__((weak,alias("InfiniteLoop")));
void GPIO3_IRQHandler(void)     __attribute__((weak,alias("InfiniteLoop")));
void GPIO4_IRQHandler(void)     __attribute__((weak,alias("InfiniteLoop")));
void GPIO5_IRQHandler(void)     __attribute__((weak,alias("InfiniteLoop")));
void GPIO6_IRQHandler(void)     __attribute__((weak,alias("InfiniteLoop")));
void GPIO7_IRQHandler(void)     __attribute__((weak,alias("InfiniteLoop")));
void GPIO8_IRQHandler(void)     __attribute__((weak,alias("InfiniteLoop")));
void GPIO9_IRQHandler(void)     __attribute__((weak,alias("InfiniteLoop")));
void GPIO10_IRQHandler(void)    __attribute__((weak,alias("InfiniteLoop")));
void GPIO11_IRQHandler(void)    __attribute__((weak,alias("InfiniteLoop")));
void GPIO12_IRQHandler(void)    __attribute__((weak,alias("InfiniteLoop")));

void PWMChannel1_IRQHandler(void)   __attribute__((weak,alias("InfiniteLoop")));
void PWMChannel2_IRQHandler(void)   __attribute__((weak,alias("InfiniteLoop")));
void PWMChannel3_IRQHandler(void)   __attribute__((weak,alias("InfiniteLoop")));
void PWMChannel4_IRQHandler(void)   __attribute__((weak,alias("InfiniteLoop")));
void PWMChannel5_IRQHandler(void)   __attribute__((weak,alias("InfiniteLoop")));
void PWMChannel6_IRQHandler(void)   __attribute__((weak,alias("InfiniteLoop")));
void PWMChannel7_IRQHandler(void)   __attribute__((weak,alias("InfiniteLoop")));
void PWMChannel8_IRQHandler(void)   __attribute__((weak,alias("InfiniteLoop")));


/*---------------------------------------------------------------------------------------------------*/