/* Polling the timer counter gives inaccurate and inconsistent
results since the timer counter count-down and CPU execution share
the same tick rate. Therefore it is NOT recommended to use the timer
in this manner. */

#include <vega/hal.h>
#include <vega/aries.h>
#include <vega/timer.h>

#define MICROS(time)        (time * 100)
#define MILLIS(time)        (time * 100000)  

int main()
{

    for (int i = 6; i < 9; i++) {
        GPIO_Init(GPIOB, i, GPIO_OUT);
        GPIO_SetPin(GPIOB, i);
    }

    GPIO_Init(GPIOB, RGB_RED , GPIO_OUT);

    htimer0.LoadCount = MILLIS(500);

    TIMER_Init(&htimer0);
    
    TIMER_Start(&htimer0);

    while (1) {
        GPIO_TogglePin(GPIOB, RGB_RED);
        //wait till timer counter decrements to 0
        while (TIMER_GetCount(&htimer0) != 0);  
    }
    
    return 0;
}


