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

    puts("Trial 31\n");
    puts(dectohex(GPFSEL1));
    putc('\n');

    //Step 1: Set config.text: dtparam=spi=on - DONE

    // //Disable Pull up/down register pins
    // mmio_write(GPPUD, 0x00000000);
    // delay(150);

    // mmio_write(GPPUDCLK0, (1 << 7) | (1 << 8) | (1 << 9) | (1 << 10) | (1 << 11));
    // delay(150);

    // mmio_write(GPPUDCLK0, 0x00000000);

    //Set alternatives for GPIO7,8,9,10,11: ALT0 - page 102 BCM2837 Manual
    //on GPIO.c file - DONE

    /* SPI communication */
    /*
    CS Register:
    Bits may need: RXF, RXR, TXD, RXD, CSPOL(to active low?), CS?, DMAEN?
    Bits must use: DONE, TA, CLEAR, CPOL, CPHASE

    FIFO Register - (need DMA?)

    DLEN Register - only valid for DMA mode - hence not used!

    CLK Register!
     */

    //Chip Select Lines - LOW; Clock Polar: 0; Clock Phase: 0; Chip Select: 0; Clear FIFO + Start Transfer
    // //Clear
    spi_control_t spi_ctrl;
    // bzero(&spi_ctrl, 4);

    spi_ctrl.as_int = mmio_read(SPI0_CS);
    spi_ctrl.CLEAR = 1;
    mmio_write(SPI0_CS, spi_ctrl.as_int);

    // //Send data to TX FIFO
    // mmio_write(SPI0_FIFO, 'a');
    // mmio_write(SPI0_FIFO, 'b');
    // mmio_write(SPI0_FIFO, 'a');
    // mmio_write(SPI0_FIFO, 'b');


    //Start transfer
    // bzero(&spi_ctrl, 4);
    spi_ctrl.as_int = mmio_read(SPI0_CS);
    spi_ctrl.CS = 0;
    spi_ctrl.CPHA = 0;
    spi_ctrl.CPOL = 0;
    // spi_ctrl.CLEAR = 1;
    spi_ctrl.CSPOL = 0;
    spi_ctrl.TA = 1;
    // spi_ctrl.DMAEN = 0;
    // spi_ctrl.INTD = 0;
    // spi_ctrl.INTR = 0;
    // spi_ctrl.ADCS = 0;
    // spi_ctrl.REN = 1;
    // spi_ctrl.LEN = 0;
    // spi_ctrl.LMONO = 0;
    // spi_ctrl.TE_EN = 0;
    spi_ctrl.CSPOL0 = 0;
    spi_ctrl.CSPOL1 = 0;
    spi_ctrl.CSPOL2 = 0;
    // spi_ctrl.DMA_LEN = 0;
    // spi_ctrl.LEN_LONG = 0;
    mmio_write(SPI0_CS, spi_ctrl.as_int);

    //Send data to TX FIFO
    // mmio_write(SPI0_FIFO, 'a');
    // mmio_write(SPI0_FIFO, 'b');
    mmio_write(SPI0_FIFO, 'a');
    mmio_write(SPI0_FIFO, 'b');
    mmio_write(SPI0_FIFO, 'a');
    mmio_write(SPI0_FIFO, 'b');

    //Poll
    do {
        spi_ctrl.as_int = mmio_read(SPI0_CS);
        // mmio_write(SPI0_FIFO, 'a');
        puts("Inside the loop\n");
    }
    while (!spi_ctrl.DONE);

    puts("Outside the loop!\n");

    // bzero(&spi_ctrl, 4);
    spi_ctrl.as_int = mmio_read(SPI0_CS);
    // spi_ctrl.REN = 1;
    spi_ctrl.TA = 0;
    mmio_write(SPI0_CS, spi_ctrl.as_int);  //Set TA back to 0
    //Read RX FIFO
    // uint8_t read = *(volatile uint32_t*)SPI0_FIFO & 0xff;
    // uint8_t read2 = *(volatile uint32_t*)SPI0_FIFO & 0xff;

    // //Display to console
    // puts(itoa(read));
    // putc('\n');
    // puts(itoa(read2));
    // putc('\n');
    puts(itoa(*(volatile uint32_t*)SPI0_FIFO));
    putc('\n');



























    // /* COMMUNICATE WITH TINYRTC */
    // i2c_master_init();
    // my_time now;
    // now.tm_sec = 0;   //Set second
    // now.tm_min = 10;  //Set minute
    // now.tm_hour = 2;  //Set hour - in 24 hr mode
    // now.tm_mday = 13; //Set date
    // now.tm_wday = 2;  //Set day
    // now.tm_mon = 8;   //Set month
    // now.tm_year = 0;  //start from 2019

    // /* WRITE DATA PROCESS */
    // //Clear FIFO before transaction
    // clear_FIFO();

    // //Data length: 8 bytes to transmit - 1st byte for register address of tinyRTC, the remaining bytes for data
    // mmio_write(BSC1_DLEN, 0x8);

    // //Write data to transmit to FIFO register
    // mmio_write(BSC1_FIFO, 0); //1st byte: Register address OOH of tinyRTC

    // int hrmode = 2;
    // mmio_write(BSC1_FIFO, convert_to_RTC(now.tm_sec));                //Seconds + Clearing CH bit
    // mmio_write(BSC1_FIFO, convert_to_RTC(now.tm_min));                //Minutes
    // mmio_write(BSC1_FIFO, convert_to_RTC_hours(now.tm_hour, hrmode)); //Hours - 24h mode
    // mmio_write(BSC1_FIFO, convert_to_RTC(now.tm_wday));               //Day
    // mmio_write(BSC1_FIFO, convert_to_RTC(now.tm_mday));               //Date
    // mmio_write(BSC1_FIFO, convert_to_RTC(now.tm_mon));                //Month
    // mmio_write(BSC1_FIFO, convert_to_RTC(now.tm_year));               //Year

    // //Start transfers
    // start_tx(0);
    // //Wait until transfer finished
    // stop_tx();

    // /*-------------------------------------------------------------------------------------------------------------*/
    // int sec_compare = 0;
    // char control = 'r';
    // while (1)
    // {
    //     if (control == 'r' || control == 'R')
    //     {
    //         /* SET REGISTER POINTER */
    //         //Clear FIFO before transaction
    //         clear_FIFO();
    //         //Data length: 1 byte to transmit - register address of tinyRTC
    //         mmio_write(BSC1_DLEN, 0x1);
    //         //Write data to transmit to FIFO register
    //         mmio_write(BSC1_FIFO, 0); //1st byte: Register address OOH of tinyRTC
    //         //Start transfer
    //         start_tx(0);
    //         //Wait until transfer finished
    //         stop_tx();

    //         /*-------------------------------------------------------------------------------------------------------------*/

    //         /* READ DATA FROM TINYRTC */
    //         //Clear FIFO before transaction
    //         clear_FIFO();

    //         //Data length: 7 bytes to read - seconds, minutes, hours, day, date, month, year
    //         mmio_write(BSC1_DLEN, 0x7);
    //         //Start transfer
    //         start_tx(1);
    //         //Wait until transfer finished
    //         stop_tx();
    //         /* Extract data from FIFO and display to console */
    //         // Store the values read in the tm structure, after masking unimplemented bits.

    //         // my_time t;
    //         // t.tm_sec = convert_from_RTC(*(volatile uint32_t *)BSC1_FIFO & 0x7f);
    //         // t.tm_min = convert_from_RTC(*(volatile uint32_t *)BSC1_FIFO & 0x7f);
    //         // t.tm_hour = convert_from_RTC(*(volatile uint32_t *)BSC1_FIFO & 0x3f);
    //         // t.tm_wday = convert_from_RTC(*(volatile uint32_t *)BSC1_FIFO & 0x07);
    //         // t.tm_mday = convert_from_RTC(*(volatile uint32_t *)BSC1_FIFO & 0x3f);
    //         // t.tm_mon = convert_from_RTC(*(volatile uint32_t *)BSC1_FIFO & 0x1f); // 1-12 --> 0-11
    //         // t.tm_year = convert_from_RTC(*(volatile uint32_t *)BSC1_FIFO);

    //         my_time t;
    //         t.tm_sec = *(volatile uint32_t *)BSC1_FIFO & 0x7f;
    //         t.tm_min = *(volatile uint32_t *)BSC1_FIFO & 0x7f;
    //         t.tm_hour = *(volatile uint32_t *)BSC1_FIFO & 0x7f;
    //         t.tm_wday = *(volatile uint32_t *)BSC1_FIFO & 0x07;
    //         t.tm_mday = *(volatile uint32_t *)BSC1_FIFO & 0x3f;
    //         t.tm_mon = *(volatile uint32_t *)BSC1_FIFO & 0x1f; // 1-12 --> 0-11
    //         t.tm_year = *(volatile uint32_t *)BSC1_FIFO;

    //         if (sec_compare != t.tm_sec)
    //         {
    //             sec_compare = t.tm_sec;
    //             display_time(t);
    //         }
    //         control = mmio_read(UART0_DR);
    //         if (control == 't' || control == 'T')
    //         {
    //             if (hrmode == 0)
    //             {
    //                 if (convert_from_RTC(t.tm_hour) > 12)
    //                     hrmode = 2;
    //                 else
    //                     hrmode = 1;
    //             }
    //             else
    //                 hrmode = 0;

    //             /* SET REGISTER POINTER */
    //             //Clear FIFO before transaction
    //             clear_FIFO();
    //             //Data length: 1 byte to transmit - register address of tinyRTC
    //             mmio_write(BSC1_DLEN, 0x1);
    //             //Write data to transmit to FIFO register
    //             mmio_write(BSC1_FIFO, 0x2); //1st byte: Register address OOH of tinyRTC
    //             //Start transfer
    //             start_tx(0);
    //             //Wait until transfer finished
    //             stop_tx();

    //             /*-------------------------------------------------------------------------------------------------------------*/

    //             if (hrmode == 0)
    //             {
    //                 am_pm = ((t.tm_hour & (1 << 5)) == 0);

    //                 t.tm_hour = (((t.tm_hour & 0x10) >> 4) * 10 + (t.tm_hour & 0x0F));
    //             }
    //         }
    //         if (control != 'p' && control != 'P')
    //             control = 'r';
    //     }
    //     else if (control == 'p' || control == 'P')
    //     {
    //         control = mmio_read(UART0_DR);
    //         if (control == 't' || control == 'T')
    //             puts("t\n");
    //         if (control != 'r' && control != 'R')
    //             control = 'p';
    //     }
    // }
}
