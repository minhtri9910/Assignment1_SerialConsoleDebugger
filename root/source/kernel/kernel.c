#include "../../include/kernel/kernel.h"

struct tm t;
time_t now;

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
    puts("S3426353: Hoang Quoc Dai\n");

    i2c_master_init();

    /* COMMUNICATE WITH TINYRTC */

    /* WRITE DATA PROCESS */
    //Clear FIFO before transaction - about FIFO register: page 33 - BCM2837 Manual
    clear_FIFO();
    //Data length: 8 bytes to transmit - 1st byte for register address of tinyRTC, the remaining bytes for data
    //Referenced: Page 8 - DS1307 Manual - Data Write
    mmio_write(BSC1_DLEN, 0x8);
    //Write data to transmit to FIFO register
    mmio_write(BSC1_FIFO, 0);    //1st byte: Register address OOH of tinyRTC
    mmio_write(BSC1_FIFO, 0x12); //2nd byte: Clear CH bit in the OOH register address to 0 to enable oscillator
    mmio_write(BSC1_FIFO, 0x13);
    mmio_write(BSC1_FIFO, 0x82);
    mmio_write(BSC1_FIFO, 0x03);
    mmio_write(BSC1_FIFO, 0x06);
    mmio_write(BSC1_FIFO, 0x08);
    mmio_write(BSC1_FIFO, 0x00);
    //Start transfers
    start_tx(0);
    //Wait until transfer finished
    stop_tx();

    /*-------------------------------------------------------------------------------------------------------------*/
    int sec_compare = 0;
    char control = 'r';
    while (1)
    {
        /* SET REGISTER POINTER */
        //Clear FIFO before transaction - about FIFO register: page 33 - BCM2837 Manual
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
        //Clear FIFO before transaction - about FIFO register: page 33 - BCM2837 Manual
        clear_FIFO();
        //Data length: 7 bytes to read - seconds, minutes, hours, day, date, month, year
        //Referenced: page 8 - DS1307 Manual - Data Read
        mmio_write(BSC1_DLEN, 0x7);
        //Start transfer
        start_tx(1);
        //Wait until transfer finished
        stop_tx();
        /* Extract data from FIFO and display to console */
        // Store the values read in the tm structure, after masking unimplemented bits.
        t.tm_sec = *(volatile uint32_t *)BSC1_FIFO & 0x7f;
        t.tm_min = *(volatile uint32_t *)BSC1_FIFO & 0x7f;
        t.tm_hour = *(volatile uint32_t *)BSC1_FIFO & 0x3f;
        t.tm_mday = *(volatile uint32_t *)BSC1_FIFO & 0x3f;
        t.tm_wday = *(volatile uint32_t *)BSC1_FIFO & 0x07;
        t.tm_mon = *(volatile uint32_t *)BSC1_FIFO & 0x1f; // 1-12 --> 0-11
        t.tm_year = *(volatile uint32_t *)BSC1_FIFO;

        if (control == 'r')
        {
            if (sec_compare != t.tm_sec)
            {
                sec_compare = t.tm_sec;
                puts(itoa(t.tm_sec));
                putc(' ');
                puts(itoa(t.tm_min));
                putc(' ');
                puts(itoa(t.tm_hour));
                putc(' ');
                puts(itoa(t.tm_mday));
                putc(' ');
                puts(itoa(t.tm_wday));
                putc(' ');
                puts(itoa(t.tm_mon));
                putc(' ');
                puts(itoa(t.tm_year));
                putc('\n');
            }
            control = mmio_read(UART0_DR);
            if (control != 'p')
                control = 'r';
        }
        else if (control == 'p')
        {
            control = mmio_read(UART0_DR);
            if (control != 'r')
                control = 'p';
        }
    }
}
