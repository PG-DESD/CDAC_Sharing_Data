/*
 * Code   : External Interrupt & Sleep Mode.
 * Author : SWAPNIL A. CHALLANI
 * Date   : 13/04/2022 @ 12:08 PM
 */

#include <stdio.h>
#include <stdint.h>

// Memory Mapped SFR Pointers
volatile uint32_t *const GPIOA_MODER_p = (uint32_t *const)0x40020000;
volatile uint32_t *const GPIOD_MODER_p = (uint32_t *const)0x40020C00;
volatile uint32_t *const GPIOD_ODR_p   = (uint32_t *const)0x40020C14;
volatile uint32_t *const AHB1ENR_p     = (uint32_t *const)0x40023830;
volatile uint32_t *const APB2ENR_p     = (uint32_t *const)0x40023844;
volatile uint32_t *const EXTICR1_p     = (uint32_t *const)0x40013808;
volatile uint32_t *const IMR_p         = (uint32_t *const)0x40013C00;
volatile uint32_t *const EXTIPENDR_p   = (uint32_t *const)0x40013C14;
volatile uint32_t *const EDGECTRL_p    = (uint32_t *const)0x40013C08;
volatile uint32_t *const NVICIRQEN_p   = (uint32_t *const)0xE000E100;
volatile uint32_t *const SCR_p         = (uint32_t *const)0xE000ED10;

// Function Declarations
void config_rcc_gpio(void);
void config_scr(void);
void config_exti(void);
void delay(unsigned long);
void EXTI0_IRQHandler(void);

int main(void)
{
	config_rcc_gpio();  // Configure GPIO & RCC Registers
	config_exti();      // Configure EXTI (External Interrupt) Registers

	for(;;);
}

void config_rcc_gpio(void)
{
	*APB2ENR_p |= (1 << 14);                          // SYSCFG Clock Enable

	*AHB1ENR_p |= (1 << 0);                           // GPIOA Clock Enabled
	*GPIOA_MODER_p &= ~(0x03 << 0);                   // GPIOA PA0 - Input

	*AHB1ENR_p |= (1 << 3);                           // GPIOD Clock Enabled
	*GPIOD_MODER_p &= ~(0x03 << 24) & ~(0x03 << 26);  // GPIOD - PD12, PD13 - RESET
	*GPIOD_MODER_p |=  (0x01 << 24) | (0x01 << 26);   // GPIOD - PD12, PD13 - Output
}

void config_scr(void)
{
	*SCR_p |=  (1 << 2); // SLEEPDEEP   : 1 - Select DEEPSLEEP Mode
	*SCR_p &= ~(1 << 4); // SEVONPEND   : 0 - Only enabled interrupts or events can wake-up the processor
	*SCR_p |=  (1 << 1); // SLEEPONEXIT : 1 - Enter Sleep Mode
}

void config_exti(void)
{
	*EXTICR1_p &= ~(0x0F << 0);  // EXTI0 - PA0
	*IMR_p |=  (1 << 0);         // EXTI0 Mask Disabled
	*EDGECTRL_p |= ( 1 << 0);    // EXTI0 Edge Control
	*NVICIRQEN_p |= (1 << 6);    // NVIC IRQ Enable for EXTI0 (6)
}

void delay(unsigned long _del)
{
	unsigned long i = _del * 2000;
	while((i--) > 1);
}

void EXTI0_IRQHandler(void) // 6th Interrupt Source
{
	*GPIOD_ODR_p |= (1 << 12) | (1 << 13);     // LEDs ON
	delay(4000);
	*GPIOD_ODR_p &= ~(1 << 12) & ~(1 << 13);   // LEDs OFF

	config_scr();                              // Enter Deep Sleep Mode
	*EXTIPENDR_p |= (1 << 0);                  // Clear EXTI0 Interrupt Pending Bit
}
