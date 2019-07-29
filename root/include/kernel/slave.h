#ifndef __SLAVE__
#define __SLAVE__

#include <stddef.h>
#include <stdint.h>
#include "../../common/mystdlib.h"
#include "../../include/kernel/uart.h"

enum
{
    BSC_SLAVE_BASE = 0x7E214000, // Base address
    BSC_SLAVE_DR = (BSC_SLAVE_BASE + 0x0), // Data Register
    BSC_SLAVE_RSR = (BSC_SLAVE_BASE + 0x4), // The operation status register and error clear register
    BSC_SLAVE_SLV = (BSC_SLAVE_BASE + 0x8), // the I2C SPI Address Register holds the I2C slave address value
    BSC_SLAVE_CR = (BSC_SLAVE_BASE + 0xC), // The Control register is used to configure the I2C or SPI operation
    BSC_SLAVE_FR = (BSC_SLAVE_BASE + 0x10), // Flag register
    BSC_SLAVE_IFLS = (BSC_SLAVE_BASE + 0x14), // Interrupt fifo level select register
    BSC_SLAVE_IMSC = (BSC_SLAVE_BASE + 0x18), // Interrupt Mask Set Clear Register
    BSC_SLAVE_RIS = (BSC_SLAVE_BASE + 0x1C), // RAW Interrupt Status Register
    BSC_SLAVE_MIS = (BSC_SLAVE_BASE + 0x20), // Masked Interrupt Status Register
    BSC_SLAVE_ICR = (BSC_SLAVE_BASE + 0x24), // Interrupt Clear Register
    BSC_SLAVE_DMACR = (BSC_SLAVE_BASE + 0x28), // DMA Control Register
    BSC_SLAVE_TDR = (BSC_SLAVE_BASE + 0x2C), // FIFO Test Data
    BSC_SLAVE_GPUSTAT = (BSC_SLAVE_BASE + 0x30), // GPU Status Register
    BSC_SLAVE_HCTRL = (BSC_SLAVE_BASE + 0x34), // Host Control Register
    BSC_SLAVE_DEBUG1 = (BSC_SLAVE_BASE + 0x38), // I2C Debug Register
    BSC_SLAVE_DEBUG2 = (BSC_SLAVE_BASE + 0x3C), // SPI Debug Register
}



#endif
