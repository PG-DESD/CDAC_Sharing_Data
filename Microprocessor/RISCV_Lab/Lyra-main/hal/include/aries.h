#ifndef ARIES_H
#define ARIES_H

#include <vega/thejas32.h>
#include <vega/gpio.h>

#define RGB_RED             (8)
#define RGB_BLUE            (7)
#define RGB_GREEN           (6)
#define LED_2               (5)
#define LED_3               (4)
#define BTN0                (3)
#define BTN1                (2)
#define SWITCH0             (0)
#define SWITCH1             (1)

#define RGB_RED_SET         (GPIO_ResetPin(GPIOB, RGB_RED))
#define RGB_RED_RST         (GPIO_SetPin(GPIOB, RGB_RED))

#define RGB_GREEN_SET       (GPIO_ResetPin(GPIOB, RGB_GREEN))
#define RGB_GREEN_RST       (GPIO_SetPin(GPIOB, RGB_GREEN))

#define RGB_BLUE_SET        (GPIO_ResetPin(GPIOB, RGB_BLUE))
#define RGB_BLUE_RST        (GPIO_SetPin(GPIOB, RGB_BLUE))

#endif