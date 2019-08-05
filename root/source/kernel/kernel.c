#include "../../include/kernel/kernel.h"

struct tm t;
time_t now;

void kernel_main(uint32_t r0, uint32_t r1, uint32_t atags)
{
    // Declare as unused
    (void)r0;
    (void)r1;
    (void)atags;

    uart_init();
    puts("EEET2490: Embedded Systems - Operating Systems & Interfacing\n");
    puts("------------------------------------------------------------\n");
    puts("Assessment Group: 9\n");
    puts("S3726096: Nguyen Minh Tri\n");
    puts("S3715125: Duong Minh Nhat\n");
    puts("S3426353: Hoang Quoc Dai\n");

    //Deliverable 3
    I2C_master_init();

    for (int i = 0; i < 10; i++)
    {

        // /* COMMUNICATE WITH TINYRTC */
        // /* WRITE DATA PROCESS */
        // //Specify slave address of tinyRTC
        // mmio_write(BSC1_A, 0x68); // Slave address = 110 1000

        // //Data length: 8 bytes to transmit - 1st byte for register address of tinyRTC, the remaining bytes for data
        // //Referenced: Page 8 - DS1307 Manual - Data Write
        // mmio_write(BSC1_DLEN, 0x8);

        // //Create master controller
        // I2C_control_t control;
        // bzero(&control, 4);
        // mmio_write(BSC1_C, control.as_int); //Set all to 0

        // //Clear FIFO before transaction - about FIFO register: page 33 - BCM2837 Manual
        // control.CLEAR_FIFO_clear = 1;
        // //Apply CLEAR FIFO to control register
        // mmio_write(BSC1_C, control.as_int);

        // //Write data to transmit to FIFO register
        // mmio_write(BSC1_FIFO, 0x00); //1st byte: Register address OOH of tinyRTC

        // mmio_write(BSC1_FIFO, 0x00); //2nd byte: Clear CH bit in the OOH register address to 0 to enable oscillator
        // mmio_write(BSC1_FIFO, 0x00);
        // mmio_write(BSC1_FIFO, 0x00);
        // mmio_write(BSC1_FIFO, 0x00);
        // mmio_write(BSC1_FIFO, 0x00);
        // mmio_write(BSC1_FIFO, 0x00);
        // mmio_write(BSC1_FIFO, 0x00);

        // //Zero out control again
        // bzero(&control, 4);
        // //Enable I2C
        // control.I2CEN_I2C_enable = 1;
        // //Specify Write method
        // control.READ_read_transfer = 0;
        // //Start transfer
        // control.ST_start_transfer = 1;
        // //Apply control to control register -- transfer should start after this line of code (to clear CH bit of tinyRTC)
        // mmio_write(BSC1_C, control.as_int);

        // //Wait until transfer finished
        // I2C_status_t status;
        // do
        // {
        //     status = read_status();
        // } while (!(status.DONE_transfer_done));

        // //Clear DONE
        // mmio_write(BSC1_S, (1 << 1));

        // /* SET REGISTER POINTER */
        // //Specify slave address of tinyRTC
        // mmio_write(BSC1_A, 0x68); // Slave address = 110 1000

        // //Data length: 2 bytes to transmit - 1st byte for register address of tinyRTC, 2nd byte for data
        // //Referenced: Page 8 - DS1307 Manual - Data Write
        // mmio_write(BSC1_DLEN, 0x1);

        // //Create master controller
        // bzero(&control, 4);
        // mmio_write(BSC1_C, control.as_int); //Set all to 0

        // //Clear FIFO before transaction - about FIFO register: page 33 - BCM2837 Manual
        // control.CLEAR_FIFO_clear = 1;
        // //Apply CLEAR FIFO to control register
        // mmio_write(BSC1_C, control.as_int);

        // //Write data to transmit to FIFO register
        // mmio_write(BSC1_FIFO, 0x00); //1st byte: Register address OOH of tinyRTC

        // //Zero out control again
        // bzero(&control, 4);
        // //Enable I2C
        // control.I2CEN_I2C_enable = 1;
        // //Specify Write method
        // control.READ_read_transfer = 0;
        // //Start transfer
        // control.ST_start_transfer = 1;
        // //Apply control to control register -- transfer should start after this line of code (to clear CH bit of tinyRTC)
        // mmio_write(BSC1_C, control.as_int);

        // //Wait until transfer finished
        // do
        // {
        //     status = read_status();
        //     if (status.TA_transfer_active)
        //         puts("Pointed to OOH\n");
        // } while (!(status.DONE_transfer_done));

        // //Clear DONE
        // mmio_write(BSC1_S, (1 << 1));

        // /* READ DATA FROM TINYRTC */
        // //Slave address - (already defined above - may be possible to comment out!!)
        // mmio_write(BSC1_A, 0x68); // Slave address = 110 1000

        // //Data length: 7 bytes to read - seconds, minutes, hours, day, date, month, year
        // //Referenced: page 8 - DS1307 Manual - Data Read
        // mmio_write(BSC1_DLEN, 0x7);

        // //Zero out control again
        // bzero(&control, 4);
        // mmio_write(BSC1_C, control.as_int); //Set all to 0

        // //Clear FIFO before transaction - about FIFO register: page 33 - BCM2837 Manual
        // control.CLEAR_FIFO_clear = 1;
        // //Enable I2C
        // control.I2CEN_I2C_enable = 1;
        // //Specify Read method
        // control.READ_read_transfer = 1;
        // //Start transfer
        // control.ST_start_transfer = 1;
        // //Apply control to control register -- transfer should start after this line of code (to read data from tinyRTC)
        // mmio_write(BSC1_C, control.as_int);

        // //Wait until transfer finished
        // do
        // {
        //     status = read_status();
        // } while (status.TA_transfer_active && !(status.DONE_transfer_done)); //At this point - the Receiver FIFO contains data from tinyRTC

        // //Clear DONE
        // mmio_write(BSC1_S, (1 << 1));

        /* Extract data from FIFO and display to console */
        // puts((char*) mmio_read(BSC1_FIFO));
        // Store the values read in the tm structure, after masking unimplemented bits.
        t.tm_sec = *(volatile uint32_t *)BSC1_FIFO & 0x7f;
        t.tm_min = *(volatile uint32_t *)BSC1_FIFO & 0x7f;
        t.tm_hour = *(volatile uint32_t *)BSC1_FIFO & 0x3f;
        t.tm_mday = *(volatile uint32_t *)BSC1_FIFO & 0x3f;
        t.tm_wday = *(volatile uint32_t *)BSC1_FIFO & 0x07;
        t.tm_mon = *(volatile uint32_t *)BSC1_FIFO & 0x1f; // 1-12 --> 0-11
        t.tm_year = *(volatile uint32_t *)BSC1_FIFO;

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

        // //Clear FIFO before transaction - about FIFO register: page 33 - BCM2837 Manual
        // control.CLEAR_FIFO_clear = 1;
        // //Apply CLEAR FIFO to control register
        // mmio_write(BSC1_C, control.as_int);
    }
    //char buf[256];
    // while (1) {
    //     gets(buf,256);
    // }
}
