#include "spi.h"

void spi_init()
{

}

spi_control_t read_status(void)
{
    spi_control_t status;
    status.as_int = mmio_read(SPI_CS);
    return status;
}

clear_FIFO()
{
    spi_control_t control; // create spi control
    bzero(&control, 4);
    mmio_write(SPI_CS, control.as_int); // set all to 0
    // clear FIFO before transaction - about FIFO register
    control.CLEAR = 1;
    // Apply clear FIFO to control register
    mmio_write(SPI_CS, control.as_int);
}

start_tx(uint8_t read)
{
    spi_control_t control; // Create spi control
    // Zero out control again
    bzero(&control, 4);
    control.TA = 1;

}

stop_tx()
{
    spi_control_t control; // create spi control

}
