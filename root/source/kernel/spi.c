
#include "../../include/kernel/spi.h"


void spi_start_tx()
{
    spi_control_t spi_ctrl;
    spi_ctrl.as_int = mmio_read(SPI0_CS);
    spi_ctrl.CS = 0;
    spi_ctrl.CPHA = 0;
    spi_ctrl.CPOL = 0;
    spi_ctrl.CLEAR = 1;
    spi_ctrl.CSPOL = 0;
    spi_ctrl.TA = 1;
    spi_ctrl.CSPOL0 = 0;
    spi_ctrl.CSPOL1 = 0;
    spi_ctrl.CSPOL2 = 0;

    mmio_write(SPI0_CS, spi_ctrl.as_int);
}

void poll()
{
    spi_control_t spi_ctrl;
    do
    {
        spi_ctrl.as_int = mmio_read(SPI0_CS);

    } while (!spi_ctrl.DONE);

    bzero(&spi_ctrl, 4);
    spi_ctrl.TA = 0;
    mmio_write(SPI0_CS, spi_ctrl.as_int); //Set TA back to 0
}


