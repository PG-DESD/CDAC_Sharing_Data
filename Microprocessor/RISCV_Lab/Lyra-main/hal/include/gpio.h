/** @file gpio.h
 *  @brief Header file for APIs to use GPIO Ports.
 *  @author Arif B <arif.dev@pm.me>
 */
#ifndef GPIO_H
#define GPIO_H

#include <vega/thejas32.h>
#include <vega/interrupt.h>

#include <stdint.h>

#define GPIOA 			(0U)
#define GPIOB		    (1U)

#define GPIO_OUT        (1U)
#define GPIO_IN         (0U)

/*---------------------------------------------------------------------------------------------------*/

/* Initialize GPIO pin to be used in digital input or output according to Direction */
int GPIO_Init(uint16_t GPIOx, uint16_t pin, uint16_t dir);

/*---------------------------------------------------------------------------------------------------*/

/* Set GPIO pin logical High */
int GPIO_SetPin(uint16_t GPIOx, uint16_t pin);

/*---------------------------------------------------------------------------------------------------*/

/* Set GPIO pin logical Low */
int GPIO_ResetPin(uint16_t GPIOx, uint16_t pin);

/*---------------------------------------------------------------------------------------------------*/

/* Toggle GPIO pin from last state */
int GPIO_TogglePin(uint16_t GPIOx, uint16_t pin);

/*---------------------------------------------------------------------------------------------------*/

/* Read data at GPIO pin */
int GPIO_ReadPin(uint16_t GPIOx, uint16_t pin);

/*---------------------------------------------------------------------------------------------------*/

/* Enable interrupt on GPIO(A) pin */
int GPIO_IT_Enable(uint16_t pin);

/*---------------------------------------------------------------------------------------------------*/

/* Disable interrupt on GPIO(A) pin */
int GPIO_IT_Disable(uint16_t pin);

/*---------------------------------------------------------------------------------------------------*/

/* GPIO(A) External interrupt callback function */
void GPIO_EXTICallback(uint16_t pin);

/*---------------------------------------------------------------------------------------------------*/

#endif /* GPIO_H */
