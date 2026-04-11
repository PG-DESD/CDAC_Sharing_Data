#include <vega/hal.h>
#include <vega/aries.h>

#define MICROS(time)        (time * 100)
#define MILLIS(time)        (time * 100000)          

int main()
{
    for (int i = 6; i < 9; i++) {
        GPIO_Init(GPIOB, i, GPIO_OUT);
        GPIO_SetPin(GPIOB, i);
    }

    htimer0.LoadCount = MILLIS(250);
    htimer1.LoadCount = MILLIS(500);
    htimer2.LoadCount = MILLIS(750);

    TIMER_Init(&htimer0);
    TIMER_Init(&htimer1);
    TIMER_Init(&htimer2);

    TIMER_Start_IT(&htimer0);
    TIMER_Start_IT(&htimer1);
    TIMER_Start_IT(&htimer2); 

    while (1) {
        //infinite loop
    }
    
    return 0;
}



void TIMER_ElapsedCallback(TIMER_Handle_t *htimer)
{
    if (htimer == &htimer0) {
        GPIO_TogglePin(GPIOB, RGB_RED);
    }
    else if (htimer == &htimer1) {
        GPIO_TogglePin(GPIOB, RGB_GREEN);
    }
    else if (htimer == &htimer2) {
        GPIO_TogglePin(GPIOB, RGB_BLUE);
    }
    else {
        return;
    }
}