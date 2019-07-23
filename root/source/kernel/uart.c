#include <stddef.h>
#include <stdint.h>
#include "../../include/kernel/uart.h"
#include "../../include/common/mystdlib.h"

// Memory-Mapped I/O output
//write 'data' to 'reg'
void mmio_write(uint32_t reg, uint32_t data)
{
    //reg is the address of the corresponding register
    //(volatile uint32_t*) is used to cast this to a pointer of type uint32_t
    //assign the value 'data' to reg
    *(volatile uint32_t*)reg = data;
}

// Memory-Mapped I/O input
uint32_t mmio_read(uint32_t reg)
{
    return *(volatile uint32_t*)reg;
}

void uart_init()
{
    uart_control_t control;

    // Disable UART0.
    bzero(&control, 4);
    mmio_write(UART0_CR, control.as_int); //set all the CR register to 0

    // Setup the GPIO pin 14 && 15.
    // Disable pull up/down for all GPIO pins & delay for 150 cycles.
    mmio_write(GPPUD, 0x00000000);
    delay(150);

    // Disable pull up/down for pin 14,15 & delay for 150 cycles.
    mmio_write(GPPUDCLK0, (1 << 14) | (1 << 15));
    delay(150);

    // Write 0 to GPPUDCLK0 to make it take effect.
    mmio_write(GPPUDCLK0, 0x00000000);

    // Clear pending interrupts.
    mmio_write(UART0_ICR, 0x7FF);

    // Enable FIFO & 8 bit data transmissio (1 stop bit, no parity).
    mmio_write(UART0_LCRH, (1 << 4) | (1 << 5) | (1 << 6));

    // Mask all interrupts.
    mmio_write(UART0_IMSC, (1 << 1) | (1 << 4) | (1 << 5) | (1 << 6) |
            (1 << 7) | (1 << 8) | (1 << 9) | (1 << 10));

    // Enable UART0, receive & transfer part of UART.
    control.uart_enabled = 1;
    control.transmit_enabled = 1;
    control.receive_enabled = 1;
    mmio_write(UART0_CR, control.as_int);
}


uart_flags_t read_flags(void) {
    uart_flags_t flags;
    flags.as_int = mmio_read(UART0_FR); //read the whole flag register of 32 bits
    return flags;
}

void uart_putc(unsigned char c)
{
    uart_flags_t flags;
    // Wait for UART to become ready to transmit.

    do {
        flags = read_flags();
    }
    while ( flags.transmit_queue_full );
    mmio_write(UART0_DR, c);
}

unsigned char uart_getc()
{
    // Wait for UART to have received something.
    uart_flags_t flags;
    do {
        flags = read_flags();
    }
    while ( flags.recieve_queue_empty );
    return mmio_read(UART0_DR);
}
