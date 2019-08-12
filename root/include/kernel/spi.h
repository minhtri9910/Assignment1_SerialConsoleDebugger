#ifndef __SPI__
#define __SPI__

#include <stddef.h>
#include <stdint.h>
#include "../../include/kernel/uart.h"

typedef union spi_control {
    struct
    {
        uint8_t CS : 2; //Chip select
        uint8_t CPHA : 1; //Clock phase
        uint8_t CPOL : 1; //Clock polarity: rest state: 0 for low, 1 for high
        uint8_t CLEAR : 2;  //Clear FIFO
        uint8_t CSPOL : 1; //Chip select polarity
        uint8_t TA : 1;  //Transfer active
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
    SPI0_BASE = 0x3F204000, 
    SPI0_CS = (SPI0_BASE + 0x00),
    SPI0_FIFO = (SPI0_BASE + 0x04),
    SPI0_CLK = (SPI0_BASE +  0x08),
    SPI0_DLEN = (SPI0_BASE + 0x0C),
    SPI0_LTOH = (SPI0_BASE + 0x10),
    SPI0_DC = (SPI0_BASE + 0x14),
};


// spi_control_t read_status(void);

// void clear_FIFO();

// void start_tx(uint8_t read);

// void stop_tx();

#endif