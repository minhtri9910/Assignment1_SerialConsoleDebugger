#ifndef __MASTER__
#define __MASTER__

#include <stddef.h>
#include <stdint.h>
#include "../../include/kernel/uart.h"

typedef union I2C_control {
    struct
    {
        uint8_t READ_read_transfer : 1; // 0 = Write Packet Transfer. 1 = Read packet Transfer
        uint8_t padding1 : 3;
        uint8_t CLEAR_FIFO_clear : 2; /* x1 = Clear FIFO. One shot operationn; 1x = CLear FIFO. One shot operation. 
        if CLEAR and ST are both set in the same operation, the FIFO is cleared before the new frame is started. 
        Read back as 0. */
        uint8_t padding2 : 1;
        uint8_t ST_start_transfer : 1;      // if 1, start a new transfer. One shot operation. Read back as 0
        uint8_t INTD_interrupt_on_DONE : 1; // if 1, generate interrupt while DONE = 1
        uint8_t INTT_interrupt_on_TX : 1;   // if 1, generate interrupt while TXW = 1
        uint8_t INTR_interrupt_on_RX : 1;   // if 1, generate interrupt while RXR = 1
        uint8_t padding3 : 4;               // Reserver
        uint8_t I2CEN_I2C_enable : 1;       // if 1, BSC is enabled
        uint32_t padding4 : 16;              // Reserver
    };
    uint32_t as_int;
} I2C_control_t;

typedef union I2C_status {
    struct
    {
        uint8_t TA_transfer_active : 1;          // 0 = Transfer not active. 1 = Transfer active.
        uint8_t DONE_transfer_done : 1;          // 0 = Transfer not completed. 1 = Transfer complete. Cleared by writing 1.
        uint8_t TXW_FIFO_needs_Writing_full : 1; // 0 = FIFO is at least full and a write is underway (or sufficient data to send). 1 = FIFO is less then full and a write is underway. CLeared by writing sufficient data to the FIFO
        uint8_t RXR_FIFO_needs_Reading_full : 1; // 0 = FIFO is less than full and a read is underway. 1 = FIFO is or more full and read is underway. CLeared by reading sufficient data from the FIFO.
        uint8_t TXD_FIFO_can_accept_Data : 1;    // 0 = FIFO is full. the FIFO cannot accept more data. 1 = FIFO has space for at least 1 byte.
        uint8_t RXD_FIFO_contains_Data : 1;      // 0 = FIFO is empty. 1 = FIFO contains at least 1 byte. CLeared by reading sufficient data from FIFO.
        uint8_t TXE_FIFO_empty : 1;              // 0 = FIFO is not empty. 1 = FIFO is empty. If a write is underway, no further serial data can be transmitted untill data is written to the FIFO.
        uint8_t RXF_FIFO_full : 1;               // 0 = FIFO is not full. 1 = FIFO is full. if a read is underway, no further serial data will be received untill data is read from FIFO.
        uint8_t ERR_ACK_error : 1;                   // 0 = No errors detected. 1 = Slave has not acknowledged its address. Cleared by writing 1 to the field
        uint8_t CLKT_clock_stretch_timeout : 1;       /* 1 = Slave has held the SCL signal low (clock stretching) 
        for longer and that specified in the I2CCLKT register Cleared by writing 1 to the field */
        uint32_t padding : 22;                    // Reserver
    };
    uint32_t as_int;
} I2C_status_t;

enum
{
    //Use BSC1 to use Pin 3 and Pin 5 to connect to line SDA1 and SCL1
    BSC1_BASE = 0x3F804000,
    BSC1_C = (BSC1_BASE + 0x00),    // Control
    BSC1_S = (BSC1_BASE + 0x04),    // Status
    BSC1_DLEN = (BSC1_BASE + 0x08), // Data Length
    BSC1_A = (BSC1_BASE + 0xC),     // Slave Address
    BSC1_FIFO = (BSC1_BASE + 0x10), //  Data FIFO
    BSC1_DIV = (BSC1_BASE + 0x14),  // Clock Divider
    BSC1_DEL = (BSC1_BASE + 0x18),  // Data Delay
    BSC1_CLKT = (BSC1_BASE + 0x1C), // Clock Stretch Timeout
};

void i2c_master_init();

I2C_status_t read_status(void);

void clear_FIFO();

void start_tx(uint8_t read);

void stop_tx();

#endif
