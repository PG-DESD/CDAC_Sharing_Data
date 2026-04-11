#include <vega/hal.h>
#include <vega/aries.h>

int main()
{
    GPIO_Init(GPIOB, RGB_RED, GPIO_OUT);
    GPIO_Init(GPIOB, RGB_GREEN, GPIO_OUT);
    GPIO_Init(GPIOB, RGB_BLUE, GPIO_OUT);

    RGB_RED_RST;
    RGB_GREEN_RST;
    RGB_BLUE_RST;

    while (1) {
        RGB_RED_SET;
        delayms(500);
        RGB_RED_RST;
        delayms(500);

        RGB_GREEN_SET;
        delayms(500);
        RGB_GREEN_RST;
        delayms(500);

        RGB_BLUE_SET;
        delayms(500);
        RGB_BLUE_RST;
        delayms(500); 
    }
    
    return 0;
}