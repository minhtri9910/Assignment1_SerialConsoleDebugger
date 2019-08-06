#ifndef __GPIO__
#define __GPIO__

#include <stddef.h>
#include <stdint.h>
#include "uart.h" 

enum
{
    GPIO_BASE = 0x3F200000,
    GPFSEL0 = GPIO_BASE, //GPIO function select
    GPPUD = (GPIO_BASE + 0x94),
    GPPUDCLK0 = (GPIO_BASE + 0x98),
};

void gpio_init();

#endif