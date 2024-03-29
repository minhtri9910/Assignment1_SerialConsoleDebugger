#include "../../include/kernel/gpio.h"

void gpio_init()
{
    //Set gpio for UART
    // Setup the GPIO pin 14 && 15.
    // Disable pull up/down for all GPIO pins & delay for 150 cycles.
    mmio_write(GPPUD, 0x00000000);
    delay(150);

    // Disable pull up/down for pin 14,15 & delay for 150 cycles.
    mmio_write(GPPUDCLK0, (1 << 14) | (1 << 15));
    delay(150);

    // Write 0 to GPPUDCLK0 to make it take effect.
    mmio_write(GPPUDCLK0, 0x00000000);

    //Set gpio for Master I2C
    //Set up for GPIO2 and GPIO3 - SDA1 and SCL1
    mmio_write(GPPUD, 0x00000000);
    delay(150);

    mmio_write(GPPUDCLK0, (1 << 2) | (1 << 3));
    delay(150);

    mmio_write(GPPUDCLK0, 0x00000000);

    //Disable Pull up/down register pins 7,8,9,10,11
    mmio_write(GPPUD, 0x00000000);
    delay(150);

    mmio_write(GPPUDCLK0, (1 << 7) | (1 << 8) | (1 << 9) | (1 << 10) | (1 << 11));
    delay(150);

    mmio_write(GPPUDCLK0, 0x00000000);

    // Set ALT0 for GPIO2,3,7,8,9,10,11 and GPIO14,15 (UART)
    mmio_write(GPFSEL0, (4 << 6) | (4 << 9) | (4 << 21) | (4 << 24) | (4 << 27));
    mmio_write(GPFSEL1, (4 << 0) | (4 << 3) | (4 << 12) | (4 << 15));
}