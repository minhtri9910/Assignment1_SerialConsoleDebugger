#ifndef __UART__
#define __UART__

#include <stddef.h>
#include <stdint.h>
#include "../../include/common/mystdlib.h"

//in union the struct and variable as_int share the same memory
typedef union uart_flags {
    struct
    {
        //complement of UART clear to send input, the bit is 1 when input is LOW
        uint8_t clear_to_send : 1;
        uint8_t data_set_ready : 1;
        uint8_t data_carrier_detected : 1;
        uint8_t busy : 1;// if 1, UART is busy transmitting
        uint8_t recieve_queue_empty : 1;// if 1, the receive queue is empty
        uint8_t transmit_queue_full : 1;// if 1, the transmit queue is full
        uint8_t recieve_queue_full : 1;// if 1, the receive queue is full
        uint8_t transmit_queue_empty : 1;// if 1, the transmit queue is empty
        uint8_t ring_indicator : 1;
        uint32_t padding : 23;
    };
    uint32_t as_int;
} uart_flags_t;

typedef union uart_control {
    struct
    {
        uint8_t uart_enabled : 1; //0 - disable UART, 1 - enable UART
        uint8_t sir_enabled : 1; 
        uint8_t sir_low_power_mode : 1;
        uint8_t reserved : 4;
        uint8_t loop_back_enabled : 1;
        uint8_t transmit_enabled : 1;
        uint8_t receive_enabled : 1;
        uint8_t data_transmit_ready : 1;
        uint8_t request_to_send : 1;
        uint8_t out1 : 1;
        uint8_t out2 : 1;
        uint8_t rts_hardware_flow_control_enabled : 1;
        uint8_t cts_hardware_flow_control_enabled : 1;
        uint16_t padding;
    };
    uint32_t as_int;
} uart_control_t;

enum
{
    UART0_BASE = 0x3F201000,  // UART Base address
    UART0_DR = (UART0_BASE + 0x00),     // Data Register
    UART0_RSRECR = (UART0_BASE + 0x04), // Receive Status Register / Error Clear Register
    UART0_FR = (UART0_BASE + 0x18),     // Flag Register
    UART0_ILPR = (UART0_BASE + 0x20),   // Disable IrDA Register
    UART0_IBRD = (UART0_BASE + 0x24),   // Integer Baud Rate Division Register
    UART0_FBRD = (UART0_BASE + 0x28),   // Fractional Baud Rate Division Register
    UART0_LCRH = (UART0_BASE + 0x2C),   // Line Control Register
    UART0_CR = (UART0_BASE + 0x30),     // Control Register
    UART0_IFLS = (UART0_BASE + 0x34),   // Interrupt FIFO Level Select Register
    UART0_IMSC = (UART0_BASE + 0x38),   // Interrupt Mask Set / Clear Register
    UART0_RIS = (UART0_BASE + 0x3C),    // Raw Interrupt Status Register
    UART0_MIS = (UART0_BASE + 0x40),    // Masked Interrupt Status Register
    UART0_ICR = (UART0_BASE + 0x44),    // Interrupt Clear Register
    UART0_DMACR = (UART0_BASE + 0x48),  // Disable DMA Control Register
    UART0_ITCR = (UART0_BASE + 0x80),   // Test Control Register
    UART0_ITIP = (UART0_BASE + 0x84),   // Test Control Register
    UART0_ITOP = (UART0_BASE + 0x88),   // Test Control Register
    UART0_TDR = (UART0_BASE + 0x8C),    // Test Data Register
};

void mmio_write(uint32_t reg, uint32_t data);

uint32_t mmio_read(uint32_t reg);

void uart_init();

uart_flags_t read_flags(void);

void uart_putc(unsigned char c);

unsigned char uart_getc();

void uart_puts(const char *str);
#endif
