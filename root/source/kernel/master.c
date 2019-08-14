#include "../../include/kernel/master.h"

void i2c_master_init()
{
    //Specify slave address of tinyRTC
    mmio_write(BSC1_A, 0x68); // Slave address = 110 1000
}

I2C_status_t read_status(void)
{
    I2C_status_t status;
    status.as_int = mmio_read(BSC1_S);
    return status;
}

void clear_FIFO()
{
    I2C_control_t control; //Create master controller
    bzero(&control, 4);
    mmio_write(BSC1_C, control.as_int); //Set all to 0
    //Clear FIFO before transaction - about FIFO register: page 33 - BCM2837 Manual
    control.CLEAR_FIFO_clear = 1;
    //Apply CLEAR FIFO to control register
    mmio_write(BSC1_C, control.as_int);
}

void start_tx(uint8_t read)
{
    I2C_control_t control; //Create master controller
    //Zero out control again
    bzero(&control, 4);
    //Enable I2C
    control.I2CEN_I2C_enable = 1;
    //Specify Write method
    control.READ_read_transfer = read;
    //Start transfer
    control.ST_start_transfer = 1;
    //Apply control to control register -- transfer should start after this line of code (to clear CH bit of tinyRTC)
    mmio_write(BSC1_C, control.as_int);
}

void stop_tx()
{
    //Wait until transfer finished
    I2C_status_t status;
    do
    {
        status = read_status();
    } while (!(status.DONE_transfer_done));

    //Clear DONE
    mmio_write(BSC1_S, (1 << 1));
}

