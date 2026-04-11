/** @file gpio.h
 *  @brief Header file for APIs to use GPIO Ports.
 *  @author Arif B <arif.dev@pm.me>
 */

#ifndef INTERRUPT_H
#define INTERRUPT_H

#include <stdint.h>

/* Interrupt Numbers */
#define UART0_IRQn              0
#define UART1_IRQn              1
#define UART2_IRQn              2
#define SPI0_IRQn               3
#define SPI1_IRQn               4
#define I2C0_IRQn               5
#define I2C1_IRQn               6
#define TIMER0_IRQn             7
#define TIMER1_IRQn             8
#define TIMER2_IRQn             9

#define GPIO0_IRQn              10
#define GPIO1_IRQn              11
#define GPIO2_IRQn              12
#define GPIO3_IRQn              13
#define GPIO4_IRQn              14
#define GPIO5_IRQn              15
#define GPIO6_IRQn              16
#define GPIO7_IRQn              17
#define GPIO8_IRQn              18
#define GPIO9_IRQn              19
#define GPIO10_IRQn             20
#define GPIO11_IRQn             21

#define I2C2_IRQn               22
#define SPI2_IRQn               23
#define PWMChannel1_IRQn        24
#define PWMChannel2_IRQn        25
#define PWMChannel3_IRQn        26
#define PWMChannel4_IRQn        27
#define PWMChannel5_IRQn        28
#define PWMChannel6_IRQn        29
#define PWMChannel7_IRQn        30
#define PWMChannel8_IRQn        31

/*---------------------------------------------------------------------------------------------------*/

/* Global interrupt Enable */
void __enable_irq(void);

/* Global interrupt Disable */
void __disable_irq(void);

/*---------------------------------------------------------------------------------------------------*/
/* IRQ Handlers for every interrupt */
/*---------------------------------------------------------------------------------------------------*/

/**/

void UART0_IRQHandler(void);
void UART1_IRQHandler(void);    
void UART2_IRQHandler(void);
void SPI0_IRQHandler(void);
void SPI1_IRQHandler(void);
void I2C0_IRQHandler(void);
void I2C1_IRQHandler(void);
void TIMER0_IRQHandler(void);
void TIMER1_IRQHandler(void);
void TIMER2_IRQHandler(void);
void GPIO0_IRQHandler(void);
void GPIO1_IRQHandler(void);
void GPIO2_IRQHandler(void);
void GPIO3_IRQHandler(void);
void GPIO4_IRQHandler(void);
void GPIO5_IRQHandler(void);
void GPIO6_IRQHandler(void);
void GPIO7_IRQHandler(void);
void GPIO8_IRQHandler(void);
void GPIO9_IRQHandler(void);
void GPIO10_IRQHandler(void);
void GPIO11_IRQHandler(void);
void I2C2_IRQHandler(void);
void SPI2_IRQHandler(void);
void PWMChannel1_IRQHandler(void);
void PWMChannel2_IRQHandler(void);
void PWMChannel3_IRQHandler(void);
void PWMChannel4_IRQHandler(void);
void PWMChannel5_IRQHandler(void);
void PWMChannel6_IRQHandler(void);
void PWMChannel7_IRQHandler(void);
void PWMChannel8_IRQHandler(void);

#endif // INTERRUPT_H