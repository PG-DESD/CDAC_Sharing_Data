/** @file hal_gpio.c
 *  @brief GPIO routines for THEJAS32
 *  @author Arif B <arif.dev@pm.me>
 */

#include <vega/interrupt.h>
#include <vega/thejas32.h>
#include <vega/gpio.h>

#include <stdint.h>
#include <stddef.h>
#include <errno.h>

/*---------------------------------------------------------------------------------------------------*/

int GPIO_Init(uint16_t GPIOx, uint16_t pin, uint16_t dir)
{
    if (pin > 15) {
        errno = EINVAL;
        return FAIL;
    }

    if (GPIOx == GPIOA) {
        switch (dir) {
            case GPIO_IN:
                GPIOA_DIR &= ~ (1 << pin);
                break;
            case GPIO_OUT:
                GPIOA_DIR |= 1 << pin;
                break;
            default:
                errno = EINVAL;
                return FAIL;
        }
    }
    else if (GPIOx == GPIOB) {
        switch (dir) {
            case GPIO_IN:
                GPIOB_DIR &= ~ (1 << pin);
                break;
            case GPIO_OUT:
                GPIOB_DIR |= 1 << pin;
                break;
            default:
                errno = EINVAL;
                return FAIL;  
        }
    }
    else {
        errno = EINVAL;
        return FAIL;
    }

    return OK;   
}

/*---------------------------------------------------------------------------------------------------*/

int GPIO_SetPin(uint16_t GPIOx, const uint16_t pin)
{
    if (pin > 15) {
        errno = EINVAL;
        return FAIL;
    }

    unsigned long PADDR = (1 << pin) << 2;
    volatile unsigned long *GPIO_DATA = NULL;
    
    switch (GPIOx) {
        case GPIOA:
            GPIO_DATA = (unsigned long *) (GPIOA_BASE | PADDR) ;
            break;
        case GPIOB:
            GPIO_DATA = (unsigned long *) (GPIOB_BASE | PADDR) ;
            break;
        default:
            errno = EINVAL;
            return FAIL;
    }

    *GPIO_DATA = 1 << pin;

    return OK;
}

/*---------------------------------------------------------------------------------------------------*/

int GPIO_ResetPin(uint16_t GPIOx, const uint16_t pin)
{
    if (pin > 15) {
        errno = EINVAL;
        return FAIL;
    }

    unsigned long PADDR = (1 << pin) << 2;
    volatile unsigned long *GPIO_DATA = NULL;

    switch (GPIOx) {
        case GPIOA:
            GPIO_DATA = (unsigned long *) (GPIOA_BASE | PADDR) ;
            break;
        case GPIOB:
            GPIO_DATA = (unsigned long *) (GPIOB_BASE | PADDR) ;
            break;
        default:
            errno = EINVAL;
            return FAIL;
    }    

    *GPIO_DATA = 0 << pin;

    return OK;
}

/*---------------------------------------------------------------------------------------------------*/

int GPIO_TogglePin(uint16_t GPIOx, uint16_t pin)
{
    if (pin > 15) {
        errno = EINVAL;
        return FAIL;
    }

    unsigned long PADDR = (1 << pin) << 2;
    volatile unsigned long *GPIO_DATA = NULL;

    switch (GPIOx) {
        case GPIOA:
            GPIO_DATA = (unsigned long *) (GPIOA_BASE | PADDR) ;
            break;
        case GPIOB:
            GPIO_DATA = (unsigned long *) (GPIOB_BASE | PADDR) ;
            break;
        default:
            errno = EINVAL;
            return FAIL;
    }    
    
    *GPIO_DATA ^= 1 << pin; 
    
    return OK;
}

/*---------------------------------------------------------------------------------------------------*/

int GPIO_ReadPin(uint16_t GPIOx, uint16_t pin) 
{
    if (pin > 15) {
        errno = EINVAL;
        return FAIL;
    }
    
    unsigned long PADDR = (1 << pin) << 2;
    volatile unsigned long *GPIO_DATA = NULL;
    uint16_t data;
    
    switch (GPIOx) {
        case GPIOA:
            GPIO_DATA = (unsigned long *) (GPIOA_BASE | PADDR) ;
            break;
        case GPIOB:
            GPIO_DATA = (unsigned long *) (GPIOB_BASE | PADDR) ;
            break;
        default:
            errno = EINVAL;
            return FAIL;
    } 

    data = *GPIO_DATA;

    if (data) {
        return 1;
    }
    else {
        return 0;
    }
}

/*---------------------------------------------------------------------------------------------------*/

int GPIO_IT_Enable(uint16_t pin) 
{
    if (pin > 11) {
        errno = EINVAL;
        return FAIL;
    }
    else {
        PLIC->IER |= 0x1U << (pin+10);
    }
    return OK;
}

/*---------------------------------------------------------------------------------------------------*/

int GPIO_IT_Disable(uint16_t pin) 
{
    if (pin > 11) {
        errno = EINVAL;
        return FAIL;
    }
    else {
        PLIC->IER &= ~(0x1U << (pin+10));
    }
    return OK;
}
/*---------------------------------------------------------------------------------------------------*/

__attribute__((weak)) void GPIO_EXTICallback(uint16_t pin)
{
    return;
}

void GPIO0_IRQHandler(void)
{
    GPIO_EXTICallback(0);
}

void GPIO1_IRQHandler(void)
{
    GPIO_EXTICallback(1);
}

void GPIO2_IRQHandler(void)
{
    GPIO_EXTICallback(2);
}

void GPIO3_IRQHandler(void)
{
    GPIO_EXTICallback(3);
}

void GPIO4_IRQHandler(void)
{
    GPIO_EXTICallback(4);
}

void GPIO5_IRQHandler(void)
{
    GPIO_EXTICallback(5);
}

void GPIO6_IRQHandler(void)
{
    GPIO_EXTICallback(6);
}

void GPIO7_IRQHandler(void)
{
    GPIO_EXTICallback(7);
}

void GPIO8_IRQHandler(void)
{
    GPIO_EXTICallback(8);
}

void GPIO9_IRQHandler(void)
{
    GPIO_EXTICallback(9);
}

void GPIO10_IRQHandler(void)
{
    GPIO_EXTICallback(10);
}

void GPIO11_IRQHandler(void)
{
    GPIO_EXTICallback(11);
}

