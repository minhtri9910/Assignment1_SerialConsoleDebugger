#ifndef __I2C__
#define __I2C__

#include <stddef.h>
#include <stdint.h>

typedef union I2C_control {
    struct
    {
        uint8_t padding : 16; // Reserver
        uint8_t I2C_enable : 1; // if 1, BSC is enabled
        uint8_t padding1 : 4; // Reserver
        uint8_t INTR_interrupt_on_RX : 1; // if 1, generate interrupt while RXR = 1
        uint8_t INTT_interrupt_on_TX : 1; // if 1, generate interrupt while TXW = 1
        uint8_t INTD_interrupt_on_DONE: 1; // if 1, generate interrupt while DONE = 1
        uint8_t ST_Start_Transfer : 1; // if 1, start a new transfer. One shot operation. Read back as 0
        uint8_t padding2 : 1;
        uint8_t CLEAR_FIFO_Clear : 2; /* x1 = Clear FIFO. One shot operationn; 1x = CLear FIFO. One shot operation. 
        if CLEAR and ST are both set in the same operation, the FIFO is cleared before the new frame is started. 
        Read back as 0. */
        uint8_t padding3 : 3; 
        uint8_t READ_Read_Transfer : 1; // 0 = Write Packet Transfer. 1 = Read packet Transfer
    };
    uint32_t as_int;
} I2C_control_t;

typedef union I2C_slave_address {
    struct
    {
        uint8_t padding : 25; // Reserver
        uint8_t ADDR_Slave_Address : 7; 
    };
    uint32_t as_int;
} I2C_slave_address_t;

typedef union I2C_status {
    struct
    {
        uint8_t padding : 22; // Reserver
        uint8_t Clock_Stretch_Timeout : 1; /* 1 = Slave has held the SCL signal low (clock stretching) 
        for longer and that specified in the I2CCLKT register Cleared by writing 1 to the field */
        uint8_t ACK_Error : 1;
        uint8_t RXF_FIFO_Full : 1;
        uint8_t TXE_FIFO_Empty : 1;
        uint8_t RXD_FIFO_contains_Data : 1;
        uint8_t TXD_FIFO_can_accept_Data : 1;
        uint8_t RXR_FIFO_needs_Reading_full : 1;
        uint8_t TXW_FIFO_needs_Writing_full : 1;
        uint8_t DONE_Transfer_Done : 1;
        uint8_t TA_Transfer_Active : 1;

    };
    uint32_t as_int;
} I2C_status_t;

enum
{
    BSC0_BASE = 0x7E205000,
    BSC0_C = (BSC0_BASE + 0x00), // Control
    BSC0_S = (BSC0_BASE + 0x40), // Status
    BSC0_DLEN = (BSC0_BASE + 0x80), // Data Length
    BSC0_A = (BSC0_BASE + 0xC), // Slave Adress
    BSC0_FIFO = (BSC0_BASE + 0x10), //  Data FIFO
    BSC0_DIV = (BSC0_BASE + 0x14), // Clock Divider
    BSC0_DEL = (BSC0_BASE + 0x18), // Data Delay
    BSC0_CLKT = (BSC0_BASE + 0x1c), // Clock Stretch Timeout
}

