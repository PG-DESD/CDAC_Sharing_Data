#ifndef _DELAY_H_
#define _DELAY_H_

#include <stdint.h>

/*---------------------------------------------------------------------------------------------------*/

/* Produce a blocking delay in micro-seconds */
void delayus(uint32_t time);

/*---------------------------------------------------------------------------------------------------*/

/* Produce a blocking delay in milli-seconds */
void delayms(uint32_t time);

/*---------------------------------------------------------------------------------------------------*/

#endif //_DELAY_H_