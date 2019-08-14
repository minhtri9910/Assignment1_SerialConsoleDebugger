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
    puts("Trial 3\n");

    /* COMMUNICATE WITH TINYRTC */
    i2c_master_init();
    my_time now;
    now.tm_sec = 30;  //Set second
    now.tm_min = 45;  //Set minute
    now.tm_hour = 11; //Set hour - in 24 hr mode
    now.tm_mday = 7;  //Set date
    now.tm_wday = 4;  //Set day
    now.tm_mon = 8;   //Set month
    now.tm_year = 0;  //start from 2019

    /* WRITE DATA PROCESS */
    //Clear FIFO before transaction
    clear_FIFO();
    //Data length: 8 bytes to transmit - 1st byte for register address of tinyRTC, the remaining bytes for data
    mmio_write(BSC1_DLEN, 0x8);
    //Write data to transmit to FIFO register
    mmio_write(BSC1_FIFO, 0); //1st byte: Register address OOH of tinyRTC
    int hrmode = 2;
    write_I2C_time(now, hrmode);
    // mmio_write(BSC1_FIFO, convert_to_RTC(now.tm_sec)); //Seconds + Clearing CH bit
    // mmio_write(BSC1_FIFO, convert_to_RTC(now.tm_min)); //Minutes
    // mmio_write(BSC1_FIFO, convert_to_RTC_hours(now.tm_hour, hrmode)); //Hours - 24h mode
    // mmio_write(BSC1_FIFO, convert_to_RTC(now.tm_wday));               //Day
    // mmio_write(BSC1_FIFO, convert_to_RTC(now.tm_mday));               //Date
    // mmio_write(BSC1_FIFO, convert_to_RTC(now.tm_mon));                //Month
    // mmio_write(BSC1_FIFO, convert_to_RTC(now.tm_year));               //Year
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
            // t.tm_sec = *(volatile uint32_t *)BSC1_FIFO & 0x7f;
            // t.tm_min = *(volatile uint32_t *)BSC1_FIFO & 0x7f;
            // t.tm_hour = *(volatile uint32_t *)BSC1_FIFO & 0x7f;
            // t.tm_wday = *(volatile uint32_t *)BSC1_FIFO & 0x07;
            // t.tm_mday = *(volatile uint32_t *)BSC1_FIFO & 0x3f;
            // t.tm_mon = *(volatile uint32_t *)BSC1_FIFO & 0x1f; // 1-12 --> 0-11
            // t.tm_year = *(volatile uint32_t *)BSC1_FIFO;

            /* SPI SECTION */
            //Start transfer
            spi_start_tx();
            //Send data to TX FIFO
            write_SPI_time(t);
            // mmio_write(SPI0_FIFO, t.tm_sec);
            // mmio_write(SPI0_FIFO, t.tm_min);
            // mmio_write(SPI0_FIFO, t.tm_hour);
            // mmio_write(SPI0_FIFO, t.tm_wday);
            // mmio_write(SPI0_FIFO, t.tm_mday);
            // mmio_write(SPI0_FIFO, t.tm_mon);
            // mmio_write(SPI0_FIFO, t.tm_year);
            //Poll
            poll();
            //Read RX FIFO
            t = read_SPI_time();
            // t.tm_sec = *(volatile uint32_t *)SPI0_FIFO;
            // t.tm_min = *(volatile uint32_t *)SPI0_FIFO;
            // t.tm_hour = *(volatile uint32_t *)SPI0_FIFO;
            // t.tm_wday = *(volatile uint32_t *)SPI0_FIFO;
            // t.tm_mday = *(volatile uint32_t *)SPI0_FIFO;
            // t.tm_mon = *(volatile uint32_t *)SPI0_FIFO;
            // t.tm_year = *(volatile uint32_t *)SPI0_FIFO;

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
