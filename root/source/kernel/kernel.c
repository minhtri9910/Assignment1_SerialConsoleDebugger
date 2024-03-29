#include "../../include/kernel/kernel.h"

void kernel_main(uint32_t r0, uint32_t r1, uint32_t atags)
{
    // Declare as unused
    (void)r0;
    (void)r1;
    (void)atags;

    gpio_init();
    uart_init();

    puts("EEET2490: Embedded Systems - Operating Systems & Interfacing\n");
    puts("------------------------------------------------------------\n");
    puts("Assessment Group: 9\n");
    puts("S3726096: Nguyen Minh Tri\n");
    puts("S3715125: Duong Minh Nhat\n");
    puts("S3426353: Hoang Quoc Dai\n\n");

    puts("DS1307 Real Time Clock Data\n");
    puts("----------------------------\n");

    /* COMMUNICATE WITH TINYRTC */
    i2c_master_init();
    my_time now;
    now.tm_sec = 0;  //Set second
    now.tm_min = 44;  //Set minute
    now.tm_hour = 22; //Set hour - in 24 hr mode
    now.tm_mday = 15;  //Set date
    now.tm_wday = 4;  //Set day
    now.tm_mon = 8;   //Set month
    now.tm_year = 19;  //start from 2000

    /* WRITE DATA PROCESS */
    //Clear FIFO before transaction
    clear_FIFO();
    //Data length: 8 bytes to transmit - 1st byte for register address of tinyRTC, the remaining bytes for data
    mmio_write(BSC1_DLEN, 0x8);
    //Write data to transmit to FIFO register
    mmio_write(BSC1_FIFO, 0); //1st byte: Register address OOH of tinyRTC
    int hrmode = 0;
    write_I2C_time(now, hrmode);
    //Start transfers
    start_tx(0);
    //Wait until transfer finished
    stop_tx();

    /*-------------------------------------------------------------------------------------------------------------*/
    int sec_compare = 0;
    char control = 'r';
    while (1)
    {
        if (control == 'r' || control == 'R')
        {
            /* SET REGISTER POINTER */
            //Clear FIFO before transaction
            clear_FIFO();
            //Data length: 1 byte to transmit - register address of tinyRTC
            mmio_write(BSC1_DLEN, 0x1);
            //Write data to transmit to FIFO register
            mmio_write(BSC1_FIFO, 0); //1st byte: Register address OOH of tinyRTC
            //Start transfer
            start_tx(0);
            //Wait until transfer finished
            stop_tx();

            /*-------------------------------------------------------------------------------------------------------------*/

            /* READ DATA FROM TINYRTC */
            //Clear FIFO before transaction
            clear_FIFO();
            //Data length: 7 bytes to read - seconds, minutes, hours, day, date, month, year
            mmio_write(BSC1_DLEN, 0x7);
            //Start transfer
            start_tx(1);
            //Wait until transfer finished
            stop_tx();
            /* Extract data from FIFO */
            // Store the values read in the tm structure, after masking unimplemented bits.
            my_time t = read_I2C_time(t);

            /* SPI SECTION */
            //Start transfer
            spi_start_tx();
            //Send data to TX FIFO
            write_SPI_time(t);
            //Poll
            poll();
            //Read RX FIFO
            t = read_SPI_time();

            if (sec_compare != t.tm_sec){
                sec_compare = t.tm_sec;
                display_time(t);
            }

            control = mmio_read(UART0_DR);
            if (control == 't' || control == 'T') toggle_time(&hrmode,t.tm_hour);
            if (control != 'p' && control != 'P')
                control = 'r';
        }
        else if (control == 'p' || control == 'P')
        {
            control = mmio_read(UART0_DR);
            if (control != 'r' && control != 'R')
                control = 'p';
        }
    }
}
