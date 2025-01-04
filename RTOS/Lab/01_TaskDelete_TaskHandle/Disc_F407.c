/**
 * LED implementation for Red, Green, and Blue discrete LED's on
 * Disc-F407
 */

#include <stm32f4xx_hal.h>
#include "Disc_F407.h"

void GreenOn ( void ) {HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);}
void GreenOff ( void ) {HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);}
LED GreenLed = { GreenOn, GreenOff };

void OrangeOn ( void ) {HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET);}
void OrangeOff ( void ) {HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);}
LED OrangeLed = { OrangeOn, OrangeOff };

void RedOn ( void ) {HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);}
void RedOff ( void ) {HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);}
LED RedLed = { RedOn, RedOff };

void BlueOn ( void ) {HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);}
void BlueOff ( void ) {HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);}
LED BlueLed = { BlueOn, BlueOff };

uint_fast8_t ReadPushButton( void ){ return HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);}
