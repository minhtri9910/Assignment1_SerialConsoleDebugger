#include "../../include/common/mytime.h"
#include "../../include/common/stdio.h"

uint8_t convert_to_RTC(uint8_t data)
{
    return (((data / 10) << 4) + (data % 10));
}

//write 0 to hrmode to enable 24 hour, 1 for 12hr am, 2 for 12hr pm
uint8_t convert_to_RTC_hours(uint8_t data, uint8_t hrmode)
{
    if (hrmode == 1)
        return ((1 << 6) + ((data / 10) << 4) + (data % 10));
    else if (hrmode == 2)
        return ((1 << 6) + (1 << 5) + ((data / 10) << 4) + (data % 10));
    else
        return ((data / 10 << 4) + (data % 10));
}

uint8_t convert_from_RTC(uint8_t data)
{
    return (((data & 0x70) >> 4) * 10 + (data & 0x0F)); //Limit year*10 to 3-bit
}

char *convert_wday(uint8_t data)
{
    switch (data)
    {
    case 1:
        return "Monday";
        break;
    case 2:
        return "Tuesday";
        break;
    case 3:
        return "Wednesday";
        break;
    case 4:
        return "Thursday";
        break;
    case 5:
        return "Friday";
        break;
    case 6:
        return "Saturday";
        break;
    case 7:
        return "Sunday";
        break;
    default:
        break;
    }
    return "Undefined";
}

void display_time(my_time t)
{
    int hrmode, am_pm;

    t.tm_sec = convert_from_RTC(t.tm_sec);
    t.tm_min = convert_from_RTC(t.tm_min);

    // if ((t.tm_hour & (1 << 6)) == 0)
    //     t.tm_hour = convert_from_RTC(t.tm_hour);

    t.tm_wday = convert_from_RTC(t.tm_wday);
    t.tm_mday = convert_from_RTC(t.tm_mday);
    t.tm_mon = convert_from_RTC(t.tm_mon); // 1-12 --> 0-11
    t.tm_year = convert_from_RTC(t.tm_year);

    puts(convert_wday(t.tm_wday));
    putc(' ');
    if (t.tm_mday < 10)
        putc('0');
    puts(itoa(t.tm_mday));
    putc('/');
    if (t.tm_mon < 10)
        putc('0');
    puts(itoa(t.tm_mon));
    putc('/');
    puts(itoa(t.tm_year + 19));
    putc(' ');

    // if (t.tm_hour < 10) putc('0');
    // puts(itoa(t.tm_hour));
    // putc(':');

    hrmode = t.tm_hour & (1 << 6);

    if (hrmode == 0)
    {
        t.tm_hour = convert_from_RTC(t.tm_hour);
        if (t.tm_hour < 10)
            putc('0');
        puts(itoa(t.tm_hour));
        putc(':');
    }
    else
    {
        //Borrow t.tm_mday to be 12hrmode flag
        am_pm = ((t.tm_hour & (1 << 5)) == 0);

        t.tm_hour = (((t.tm_hour & 0x10) >> 4) * 10 + (t.tm_hour & 0x0F));
        if (t.tm_hour < 10)
            putc('0');
        puts(itoa(t.tm_hour));
        putc(':');
    }

    if (t.tm_min < 10)
        putc('0');
    puts(itoa(t.tm_min));
    putc(':');
    if (t.tm_sec < 10)
        putc('0');
    puts(itoa(t.tm_sec));
    // putc('\n');

    if (hrmode != 0)
    {
        if (am_pm == 0)
            puts(" PM");
        else
            (puts(" AM"));
    }

    putc('\n');
}

void toggle_time(int *hrmode, uint8_t hour)
{
    if (*hrmode == 0)
    {
        hour = convert_from_RTC(hour);
        if (hour >= 12)
        {
            *hrmode = 2;
            hour -= 12;
        }
        else
            *hrmode = 1;
    }
    else
    {
        *hrmode = 0;
        int am_pm = (hour & (1 << 5));
        hour = (((hour & 0x10) >> 4) * 10 + (hour & 0x0F));
        if (am_pm != 0)
            hour += 12;
    }

    //WRITE HOUR TO RTC
    //Clear FIFO before transaction
    clear_FIFO();
    //Data length: 1 byte to transmit - register address of tinyRTC
    mmio_write(BSC1_DLEN, 0x2);
    //Write data to transmit to FIFO register
    mmio_write(BSC1_FIFO, 0x2);                                 //1st byte: Register address OOH of tinyRTC
    mmio_write(BSC1_FIFO, convert_to_RTC_hours(hour, *hrmode)); //Hours
    //Start transfer
    start_tx(0);
    //Wait until transfer finished
    stop_tx();
}

void write_I2C_time(my_time now, int hrmode)
{
    mmio_write(BSC1_FIFO, convert_to_RTC(now.tm_sec)); //Seconds + Clearing CH bit
    mmio_write(BSC1_FIFO, convert_to_RTC(now.tm_min)); //Minutes
    mmio_write(BSC1_FIFO, convert_to_RTC_hours(now.tm_hour, hrmode)); //Hours - 24h mode
    mmio_write(BSC1_FIFO, convert_to_RTC(now.tm_wday));               //Day
    mmio_write(BSC1_FIFO, convert_to_RTC(now.tm_mday));               //Date
    mmio_write(BSC1_FIFO, convert_to_RTC(now.tm_mon));                //Month
    mmio_write(BSC1_FIFO, convert_to_RTC(now.tm_year));
}

my_time read_I2C_time()
{
    my_time t;
    t.tm_sec = *(volatile uint32_t *)BSC1_FIFO & 0x7f;
    t.tm_min = *(volatile uint32_t *)BSC1_FIFO & 0x7f;
    t.tm_hour = *(volatile uint32_t *)BSC1_FIFO & 0x7f;
    t.tm_wday = *(volatile uint32_t *)BSC1_FIFO & 0x07;
    t.tm_mday = *(volatile uint32_t *)BSC1_FIFO & 0x3f;
    t.tm_mon = *(volatile uint32_t *)BSC1_FIFO & 0x1f; // 1-12 --> 0-11
    t.tm_year = *(volatile uint32_t *)BSC1_FIFO;

    return t;
}

void write_SPI_time(my_time t)
{
    mmio_write(SPI0_FIFO, t.tm_sec);
    mmio_write(SPI0_FIFO, t.tm_min);
    mmio_write(SPI0_FIFO, t.tm_hour);
    mmio_write(SPI0_FIFO, t.tm_wday);
    mmio_write(SPI0_FIFO, t.tm_mday);
    mmio_write(SPI0_FIFO, t.tm_mon);
    mmio_write(SPI0_FIFO, t.tm_year);
}

my_time read_SPI_time()
{
    my_time t;
    t.tm_sec = *(volatile uint32_t *)SPI0_FIFO;
    t.tm_min = *(volatile uint32_t *)SPI0_FIFO;
    t.tm_hour = *(volatile uint32_t *)SPI0_FIFO;
    t.tm_wday = *(volatile uint32_t *)SPI0_FIFO;
    t.tm_mday = *(volatile uint32_t *)SPI0_FIFO;
    t.tm_mon = *(volatile uint32_t *)SPI0_FIFO;
    t.tm_year = *(volatile uint32_t *)SPI0_FIFO;

    return t;
}