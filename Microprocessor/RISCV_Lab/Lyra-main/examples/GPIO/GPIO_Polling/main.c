/* This example assumes ARIESv2 board being used */

#include <vega/hal.h>
#include <vega/aries.h>

int main()
{

    for (int i = 6; i < 9; i++) {
        GPIO_Init(GPIOB, i, GPIO_OUT);
        GPIO_SetPin(GPIOB, i);
    }

    GPIO_Init(GPIOB, 3, GPIO_IN);
    GPIO_Init(GPIOB, 2, GPIO_IN);
    
    while (1) {
        // Check Button 0 is pressed
        if (GPIO_ReadPin(GPIOB, BTN0) == 0) {
            RGB_RED_RST;
            RGB_BLUE_RST;
            RGB_GREEN_SET;
        }

        // Check Button 1 is pressed
        else if (GPIO_ReadPin(GPIOB, BTN1) == 0) {
            RGB_RED_RST;
            RGB_GREEN_RST;
            RGB_BLUE_SET;
        }
        else {
            RGB_GREEN_RST;
            RGB_BLUE_RST;
            RGB_RED_SET;
        }
    }

    return 0;
}