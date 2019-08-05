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

    //Set alternative function 0 (ALT0) for GPIO2 and GPIO3 - page 102,92 - BCM2837 Manual
    // //GPIO2 - bit 6:8 - 0b111 = 7, 0b100 = 4: set to ALT0
    // //GPIO3 - bit 9:11 
    mmio_write(GPFSEL0, 0x00000900);
}