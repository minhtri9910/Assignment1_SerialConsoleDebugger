#ifndef __SPI__
#define __SPI__

#include <stddef.h>
#include <stdint.h>
#include "../../include/kernel/uart.h"

typedef union spi_control {
    struct
    {
        uint8_t CS : 2;
        uint8_t CPHA : 1;
        uint8_t CPOL : 1;
        uint8_t CLEAR : 2;
        uint8_t CSPOL : 1;
        uint8_t TA : 1;
        uint8_t DMAEN : 1;
        uint8_t INTD : 1;
        uint8_t INTR : 1;
        uint8_t ADCS : 1;
        uint8_t REN : 1;
        uint8_t LEN : 1;
        uint8_t LMONO : 1; // Unused
        uint8_t TE_EN : 1; // Unused
        uint8_t DONE : 1;
        uint8_t RXD : 1;
        uint8_t TXD : 1;
        uint8_t RXR : 1;
        uint8_t RXF : 1;
        uint8_t CSPOL0 : 1;
        uint8_t CSPOL1 : 1;
        uint8_t DMA_LEN : 1;
        uint8_t CSPOL2 : 1;
        uint8_t LEN_LONG : 1;
        uint8_t padding : 6;
    };
    uint32_t as_int;
} spi_control_t;

enum
{
    SPI_BASE = 0x7E20400,
    SPI_CS = (SPI_BASE + 0x0),
    SPI_FIFO = (SPI_BASE + 0x4),
    SPI_CLK = (SPI_BASE +  0x8),
    SPI_DLEN = (SPI_BASE + 0xC),
    SPI_LTOH = (SPI_BASE + 0x10),
    SPI_DC = (SPI_BASE + 0x14),
}


spi_control_t read_status(void);

void clear_FIFO();

void start_tx(uint8_t read);

void stop_tx();

#endif