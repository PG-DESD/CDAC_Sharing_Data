/**
 @file hal_uart.c
 @brief Routines for PWM controller
 @author Arif B <arif.dev@pm.me>
 */

#include <vega/pwm.h>
#include <vega/thejas32.h>
#include <stddef.h>
#include <errno.h>

PWM_Handle_t hpwm1 = {
    .Channel = PWMCH1,
    .Mode = PWM_MODE_CONTINUOUS,
    .Period = 0,
    .Duty = 50,
    .Alignment = PWM_ALIGN_LEFT,
    .State = STATE_READY
};

int PWM_Init(PWM_Handle_t *hpwm)
{
    if (hpwm == NULL) {
        errno = EFAULT;
        return EFAULT;
    }

    if (hpwm->Channel == NULL) {
        errno = EFAULT;
        return EFAULT;
    }

    if (hpwm->State == STATE_BUSY) {
        return STATE_BUSY;
    }

    hpwm->State = STATE_BUSY;

    hpwm->Channel->CTRL = 0x0UL;

    hpwm->Channel->PERIOD = hpwm->Period;
    hpwm->Channel->DUTY = hpwm->Duty;

    switch (hpwm->Mode) {
        case PWM_MODE_IDLE:
            hpwm->Channel->CTRL |= PWM_CTRL_MODE_IDLE;
            break;
        
        case PWM_MODE_ONESHOT:
            hpwm->Channel->CTRL |= PWM_CTRL_MODE_ONESHOT;
            break;

        case PWM_MODE_CONTINUOUS:
            hpwm->Channel->CTRL |= PWM_CTRL_MODE_CONTINUOUS;
            break;

        default:
            errno = EINVAL;
            return EINVAL;
    }

    switch (hpwm->Alignment) {
        case PWM_ALIGN_LEFT:
            hpwm->Channel->CTRL |= PWM_CTRL_AC_LEFT;
            break;

        case PWM_ALIGN_RIGHT:
            hpwm->Channel->CTRL |= PWM_CTRL_AC_RIGHT;
            break;
        
        default:
            errno = EINVAL;
            return EINVAL;
    }
    //TO DO - pwm output control





    

    
    return OK;
}


int PWM_Start(PWM_Handle_t *hpwm)
{
    if (hpwm == NULL) {
        errno = EFAULT;
        return EFAULT;
    }

    if (hpwm->Channel == NULL) {
        errno = EFAULT;
        return EFAULT;
    }

    if (hpwm->State == STATE_BUSY) {
        return STATE_BUSY;
    }

    return OK;
}