#ifndef __SLAVE__
#define __SLAVE__

#include <stddef.h>
#include <stdint.h>
#include "../../common/mystdlib.h"
#include "../../include/kernel/uart.h"

typedef union slave_control {
    struct
    {
        uint8_t EN_enable_device : 1;                    // 0 = Disbale I2C SPI slave; 1 = Enable SPI slave
        uint8_t SPI_mode : 1;                            // 0 = Disbaled SPI mode; 1 = Enabled SPI mode
        uint8_t I2C_mode : 1;                            // 0 = Disabled I2C mode; 1 = Enabled I2C mode
        uint8_t CPHA_clock_phase : 1;                    // 1 = SPI Related
        uint8_t CPOL_clock_polarity : 1;                 // 1 = SPI Related
        uint8_t ENSTAT_enable_status_8bit_register : 1;  // 0 = Status register disable; 1 = Status register enable
        uint8_t ENCTRL_enable_control_8bit_register : 1; // 0 = Control register disabled; 1 = Control register enabled
        uint8_t BRK_break_current_operation : 1;         // 1 = Stop operation and clear FIFOs
        uint8_t TXE_transmit_enable : 1;                 // 0 = Transmit mode disabled; 1 = Transmit mode enabled
        uint8_t RXE_receive_enable : 1;                  // 0 = Receive mode disabled; 1 = Receive mode enabled
        uint8_t INV_RXF_inverse_RX_status_flags : 1;     // 0 = Default status flags; 1 = inverted status flags
        uint8_t TESTFIFO_test_fifo : 1;                  // 0 = TESTT FIFO disabled; 1 = TESTT FIFO enabled
        uint8_t HOSTCTRLEN_enable_control_for_host : 1;  // 0 = Host Control disabled; 1 = Host Control Enabled
        uint8_t INV_TXF_inverse_TX_status_flags : 1;     // 0 = default status flags; 1 = inverted status flags
        uint8_t padding : 18;                            // Reserver
    };
    uint32_t as_int;
} slave_control_t;

typedef union slave_flag {
    struct
    {
        uint8_t TXBUSY_transmit_busy : 1;   // 0 = Transmit operation inactive; 1 = Transmit operation in operation
        uint8_t RXFE_RX_FIFO_empty : 1;     // 0 = FX FIFO is not empty; 1 = when FX FIFO is empty
        uint8_t TXFF_TX_FIFO_full : 1;      // 0 = TX FIFO is not full; 1 = when TX FIFO is full
        uint8_t RXFF_RX_FIFO_full : 1;      // 0 = FX FIFO is not full; 1 = when FX FIFO is full
        uint8_t TXFE_TX_FIFO_empty : 1;     // 0 = TX FIFO is not empty; 1 = when TX FIFO is empty
        uint8_t RXBUSY_reveive_busy : 1;    // 0 = Receive oepration inactive; 1 = Receive operation in operation
        uint8_t TXFLEVEL_TX_FIFO_level : 5; // Returns the current level of the TX FIFO use
        uint8_t RXFLEVEL_RX_FIFO_level : 5; // Returns the current level of the RX FIFO use
        uint8_t padding : 16;               // Reserved
    };
    uint32_t as_int;
} slave_flag_t;

enum
{
    BSC_SLAVE_BASE = 0x3F214000,                 // Base address
    BSC_SLAVE_DR = (BSC_SLAVE_BASE + 0x0),       // Data Register
    BSC_SLAVE_RSR = (BSC_SLAVE_BASE + 0x4),      // The operation status register and error clear register
    BSC_SLAVE_SLV = (BSC_SLAVE_BASE + 0x8),      // the I2C SPI Address Register holds the I2C slave address value
    BSC_SLAVE_CR = (BSC_SLAVE_BASE + 0xC),       // The Control register is used to configure the I2C or SPI operation
    BSC_SLAVE_FR = (BSC_SLAVE_BASE + 0x10),      // Flag register
    BSC_SLAVE_IFLS = (BSC_SLAVE_BASE + 0x14),    // Interrupt fifo level select register
    BSC_SLAVE_IMSC = (BSC_SLAVE_BASE + 0x18),    // Interrupt Mask Set Clear Register
    BSC_SLAVE_RIS = (BSC_SLAVE_BASE + 0x1C),     // RAW Interrupt Status Register
    BSC_SLAVE_MIS = (BSC_SLAVE_BASE + 0x20),     // Masked Interrupt Status Register
    BSC_SLAVE_ICR = (BSC_SLAVE_BASE + 0x24),     // Interrupt Clear Register
    BSC_SLAVE_DMACR = (BSC_SLAVE_BASE + 0x28),   // DMA Control Register
    BSC_SLAVE_TDR = (BSC_SLAVE_BASE + 0x2C),     // FIFO Test Data
    BSC_SLAVE_GPUSTAT = (BSC_SLAVE_BASE + 0x30), // GPU Status Register
    BSC_SLAVE_HCTRL = (BSC_SLAVE_BASE + 0x34),   // Host Control Register
    BSC_SLAVE_DEBUG1 = (BSC_SLAVE_BASE + 0x38),  // I2C Debug Register
    BSC_SLAVE_DEBUG2 = (BSC_SLAVE_BASE + 0x3C),  // SPI Debug Register
}

#endif
