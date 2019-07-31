#include "../../include/kernel/kernel.h"

void kernel_main(uint32_t r0, uint32_t r1, uint32_t atags)
{
    char buf[256];
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
    mmio_write(BSC1_A, 0x68); // Slave address = 110 1000

    //Write data to transmit to FIFO register
    mmio_write(BSC1_FIFO, 0x00); //2nd byte: Register address OOH of tinyRTC
    mmio_write(BSC1_FIFO, 0x00); //3rd byte: Clear CH bit in the OOH register address to 0 to enable oscillator

    //Data length: 3 bytes to transmit - first byte for slave address, 2nd byte for register address of tinyRTC, 3rd byte for data 
    //Referenced: Page 36 - BCM2837 Manual; Page 8 - DS1307 Manual
    mmio_write(BSC1_DLEN, 0x3);

    //Create master controller
    I2C_control_t control;
    bzero (&control, 4);

    //Clear FIFO before transaction - about FIFO register: page 33 - BCM2837 Manual
    control.CLEAR_FIFO_clear = 1; //!!! Unsure 1 or 2 or both?? - need to look back

    //Apply CLEAR FIFO to control register
    mmio_write(BSC1_C, control.as_int); 

    //Zero out control again
    bzero (&control, 4);

    //Specify Write method
    control.READ_read_transfer = 0;
    control.ST_start_transfer = 1;

    //Apply control to control register -- transfer should start after this line of code (to clear CH bit of tinyRTC)
    mmio_write(BSC1_C, control.as_int); 
    
    //Zero out control again
    //bzero (&control, 4);


    


    // while (1) {
    //     gets(buf,256);
    // }
}
