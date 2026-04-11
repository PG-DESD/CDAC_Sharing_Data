#ifndef _PWM_H_
#define _PWM_H_

#include <vega/thejas32.h>
#include <stdint.h>

#define PWM_MODE_IDLE               (0U)
#define PWM_MODE_ONESHOT            (1U)
#define PWM_MODE_CONTINUOUS         (2U)

#define PWM_ALIGN_LEFT              (0U)
#define PWM_ALIGN_RIGHT             (1U)

#define PWM_OPC_LOW                 (0U)
#define PWM_OPC_HIGH                (1U)

typedef struct __PWM_Handle_t {
    PWM_Reg_t *Channel;
    uint32_t Mode;
    uint32_t Period;
    uint32_t Duty;
    uint32_t Alignment;
    uint32_t State;
} PWM_Handle_t;

/*---------------------------------------------------------------------------------------------------*/

int PWM_Init(PWM_Handle_t *hpwm);

/*---------------------------------------------------------------------------------------------------*/

int PWM_Start(PWM_Handle_t *hpwm);

/*---------------------------------------------------------------------------------------------------*/

#endif