#include "../../include/kernel/kernel.h"

void kernel_main(uint32_t r0, uint32_t r1, uint32_t atags)
{
    //char buf[256];
    // Declare as unused
    (void) r0;
    (void) r1;
    (void) atags;

    uart_init();
    puts("EEET2490: Embedded Systems - Operating Systems & Interfacing\n");
    puts("------------------------------------------------------------\n");
    puts("Assessment Group: 9\n");
    puts("S3726096: Nguyen Minh Tri\n");
    puts("S3715125: Duong Minh Nhat\n");
    puts("S3426353: Hoang Quoc Dai\n");

    //Deliverable 3
    I2C_master_init();

    /* Communicate with tinyRTC - enable CH bit */
    //Specify slave address of tinyRTC
    // mmio_write(BSC1_A, 0x68); // Slave address = 110 1000
    mmio_write(BSC1_A, (1 << 3) | (1 << 5) | (1 << 6));

    //Data length: 2 bytes to transmit - 1st byte for register address of tinyRTC, 2nd byte for data 
    //Referenced: Page 8 - DS1307 Manual - Data Write
    // mmio_write(BSC1_DLEN, 0x2);
    mmio_write(BSC1_A, (1 << 1));

    //Create master controller
    I2C_control_t control;
    bzero (&control, 4);
    mmio_write(BSC1_C, control.as_int); //Set all to 0

    //Clear FIFO before transaction - about FIFO register: page 33 - BCM2837 Manual
    control.CLEAR_FIFO_clear = 1; //!!! Unsure 1 or 2 or both?? - need to look back
    //Apply CLEAR FIFO to control register
    mmio_write(BSC1_C, control.as_int); 

    //Write data to transmit to FIFO register
    // mmio_write(BSC1_FIFO, 0x00); //1st byte: Register address OOH of tinyRTC
    // mmio_write(BSC1_FIFO, 0x12); //2nd byte: Clear CH bit in the OOH register address to 0 to enable oscillator
    mmio_write(BSC1_FIFO, 0x00000000);
    mmio_write(BSC1_FIFO, 0x00000000);


    //Zero out control again
    bzero (&control, 4);

    //Enable I2C
    control.I2CEN_I2C_enable = 1;
    //Specify Write method
    control.READ_read_transfer = 0;
    //Start transfer
    control.ST_start_transfer = 1;

    //Apply control to control register -- transfer should start after this line of code (to clear CH bit of tinyRTC)
    mmio_write(BSC1_C, control.as_int); 
    
    //Wait until transfer finished
    I2C_status_t status;
    do {
        status = read_status();
    }
    while (status.TA_transfer_active && !(status.DONE_transfer_done));

    /* Read data from tinyRTC */

    //Slave address - (already defined above - may be possible to comment out!!)
    // mmio_write(BSC1_A, 0x68); // Slave address = 110 1000
    mmio_write(BSC1_A, (1 << 3) | (1 << 5) | (1 << 6));

    //Data length: 7 bytes to read - seconds, minutes, hours, day, date, month, year
    //Referenced: page 8 - DS1307 Manual - Data Read
    // mmio_write(BSC1_DLEN, 0x7);
    mmio_write(BSC1_A, (1 << 1));

    //Zero out control again
    bzero (&control, 4);
    mmio_write(BSC1_C, control.as_int); //Set all to 0  

    //Clear FIFO before transaction - about FIFO register: page 33 - BCM2837 Manual
    control.CLEAR_FIFO_clear = 1;
    //Enable I2C
    control.I2CEN_I2C_enable = 1;
    //Specify Read method
    control.READ_read_transfer = 1;
    //Start transfer
    control.ST_start_transfer = 1;
    //Apply control to control register -- transfer should start after this line of code (to read data from tinyRTC)
    mmio_write(BSC1_C, control.as_int); 

    //Clear DONE
    mmio_write(BSC1_S, (1 << 1));
    
    //Wait until transfer finished
    do {
        status = read_status();
    }
    while (status.TA_transfer_active && !(status.DONE_transfer_done)); //At this point - the Receiver FIFO contains data from tinyRTC

    //Clear DONE
    mmio_write(BSC1_S, (1 << 1));

    /* Extract data from FIFO and display to console */
    puts((char*) mmio_read(BSC1_FIFO));



    // while (1) {
    //     gets(buf,256);
    // }
}


/*
    //Nhat's working part - do not delete without my permission
    //Note: !! Unsure about whether Slave address counts as 1 transfer in DLEN  - page 37 - BCM2837 Manual indicates it does not 
    
    //Write data to transmit to FIFO register
    mmio_write(BSC1_FIFO, 0x00); //2nd byte: Register address OOH of tinyRTC
    mmio_write(BSC1_FIFO, 0x00); //3rd byte: Clear CH bit in the OOH register address to 0 to enable oscillator

    //Data length: 3 bytes to transmit - first byte for slave address, 2nd byte for register address of tinyRTC, 3rd byte for data 
    //Referenced: Page 36 - BCM2837 Manual; Page 8 - DS1307 Manual - Data Write
    mmio_write(BSC1_DLEN, 0x3);
 */

/*
    How to access data from receiver FIFO
    -- Read one by one after each transfer?
    or
    -- Wait until transfer finishes then read all?
 */