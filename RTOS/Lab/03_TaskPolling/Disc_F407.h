/*
 * Disc_F407.h
 *
 *  Created on: Jun 23, 2024
 *      Author: Z665059
 */

#ifndef INC_DISC_F407_H_
#define INC_DISC_F407_H_

#include <stdint.h>


//Create a typedef defining a simple function pointer
//to be used for LED's
typedef void (*GPIOFunc)(void);

//this struct holds function pointers to turn each LED
//on and off
typedef struct LED LED;
struct LED
{
	const GPIOFunc On;
	const GPIOFunc Off;
};

uint_fast8_t ReadPushButton( void );

extern LED BlueLed;
extern LED GreenLed;
extern LED RedLed;

void rngInit(void);
uint32_t StmRand( uint32_t Max, uint32_t Min );


#endif /* INC_DISC_F407_H_ */
