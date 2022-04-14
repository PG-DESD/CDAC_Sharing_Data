/*
 * Code   : Software Interrupt & Sleep Mode.
 * Author : SWAPNIL A. CHALLANI
 * Date   : 13/04/2022 @ 10:30 AM
 */

#include <stdio.h>
#include <stdint.h>


// Memory Mapped SFR Pointers
volatile uint32_t *const STIR_p = (uint32_t *const)0xE000EF00;
volatile uint32_t *const ISER_p = (uint32_t *const)0xE000E100;
volatile uint32_t *const SCR_p  = (uint32_t *const)0xE000ED10;

// Function Declarations
void config_scr(void);
void config_sti(void);
void delay(unsigned long);
void RTC_WKUP_IRQHandler(void);

int main(void)
{
	printf("Before Entering In Sleep Mode.\n");

	delay(5000);   // Comment Line - For Debugging, Uncomment Line - For Testing Power Consumption
	config_sti();  // Configure SW Triggered Interrupt

	// Lets Waste Some Program Space ....
	printf("After Entering In Sleep Mode Via RTC WakeUp Handler.\n");
	printf("After Entering In Sleep Mode Via RTC WakeUp Handler.\n");
	printf("After Entering In Sleep Mode Via RTC WakeUp Handler.\n");
	printf("After Entering In Sleep Mode Via RTC WakeUp Handler.\n");
	for(;;);
}

void config_scr(void)
{
	*SCR_p |=  (1 << 2); // SLEEPDEEP   : 1 - Select DEEPSLEEP Mode
	*SCR_p &= ~(1 << 4); // SEVONPEND   : 0 - Only enabled interrupts or events can wake-up the processor
	*SCR_p |=  (1 << 1); // SLEEPONEXIT : 1 - Enter Sleep Mode
}

void config_sti(void)
{
	*ISER_p |= (1 << 3);  // RTC WakeUp Interrupt Enable
	*STIR_p = 3;          // Software Triggered Interrupt - RTC WakeUp (3rd)
}

void delay(unsigned long _del)
{
	unsigned long i = _del * 2000;
	while((i--) > 1);
}

void RTC_WKUP_IRQHandler(void) // 3rd Interrupt Source
{
	config_scr(); // Enter Deep Sleep Mode.
}
