/** 
 @file timer.h
 @brief THEJAS32 Timer APIs
 @author Arif B (arif.dev@pm.me)
*/
#ifndef TIMER_H
#define TIMER_H

#include <vega/thejas32.h>
#include <stdint.h>
#include <stddef.h>

#define TIMER_MODE_FREERUN      (0)
#define TIMER_MODE_PERIODIC     (1)

typedef struct {
    Timer_Reg_t *Instance;
    uint32_t LoadCount;
    uint32_t Mode;
    uint32_t State;
} TIMER_Handle_t;

extern TIMER_Handle_t htimer0;
extern TIMER_Handle_t htimer1;
extern TIMER_Handle_t htimer2;

/*---------------------------------------------------------------------------------------------------*/

/* Initialize the Timer module */
int TIMER_Init(TIMER_Handle_t *htimer);

/*---------------------------------------------------------------------------------------------------*/

/* Start the Timer counter */
int TIMER_Start(TIMER_Handle_t *htimer);

/*---------------------------------------------------------------------------------------------------*/

/* Start the Timer counter with interrupt enabled */
int TIMER_Start_IT(TIMER_Handle_t *htimer);

/*---------------------------------------------------------------------------------------------------*/

/* Stop the Timer counter */
int TIMER_Stop(TIMER_Handle_t *htimer);

/*---------------------------------------------------------------------------------------------------*/

/* Read the current value of counter in Timer */
int TIMER_GetCount(TIMER_Handle_t *htimer);

/*---------------------------------------------------------------------------------------------------*/

/* Timer counter period elapsed callback */
void TIMER_ElapsedCallback(TIMER_Handle_t *htimer);

/*---------------------------------------------------------------------------------------------------*/

#endif