#include <vega/hal.h>
#include <vega/aries.h>

int main()
{
    GPIO_Init(GPIOB, RGB_RED, GPIO_OUT);
    RGB_RED_RST;

    GPIO_Init(GPIOA, 3, GPIO_IN);

    GPIO_IT_Enable(3);

    while (1) {
        //infinite loop
    }

    return 0;
}

void GPIO_EXTICallback(uint16_t pin)
{
    if (pin == 3) {
        delayms(150);
        GPIO_TogglePin(GPIOB, RGB_RED);
    }
}