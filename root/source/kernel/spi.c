
#include "../../include/kernel/spi.h"

void spi_start_tx()
{
    spi_control_t spi_ctrl;
    bzero(&spi_ctrl, 4);
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

// void spi_stop_tx()
// {
//     bzero(&spi_ctrl, 4);

//     spi_ctrl.TA = 0;
//     mmio_write(SPI0_CS, spi_ctrl.as_int); //Set TA back to 0
// }

// spi_control_t read_status(void)
// {
//     spi_control_t control;
//     status.as_int = mmio_read(SPI_CS);
//     return control;
// }

// clear_FIFO()
// {
//     spi_control_t control; // create spi control
//     bzero(&control, 4);
//     mmio_write(SPI_CS, control.as_int); // set all to 0
//     // clear FIFO before transaction - about FIFO register
//     control.CLEAR = 1;
//     // Apply clear FIFO to control register
//     mmio_write(SPI_CS, control.as_int);
// }

// start_tx(uint8_t read)
// {
//     spi_control_t control; // Create spi control
//     // Zero out control again
//     bzero(&control, 4);
//     control.TA = 1;

// }

// stop_tx()
// {
//     // Wait untill transfer finished
//     spi_control_t control; // create spi control
//     do
//     {
//         control = read_status();
//     } while (!(control.DONE));

//     // CLear DONE
//     mmio_write(SPI_CS, (1 << 16));
// }
