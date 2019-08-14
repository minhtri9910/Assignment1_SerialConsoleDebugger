#ifndef __MYTIME__
#define __MYTIME__

#include <stddef.h>
#include <stdint.h>
#include "../kernel/master.h"
#include "../kernel/spi.h"

typedef struct RTC_struct
{
    uint8_t tm_sec;
    uint8_t tm_min;
    uint8_t tm_hour;
    uint8_t tm_wday;
    uint8_t tm_mday;
    uint8_t tm_mon;
    uint8_t tm_year;
} my_time;

uint8_t convert_to_RTC(uint8_t data);

uint8_t convert_to_RTC_hours(uint8_t data, uint8_t hrmode);

uint8_t convert_from_RTC(uint8_t data);

char *convert_DAY_from_RTC(uint8_t data);

void display_time(my_time t);

void toggle_time(int *hrmode, uint8_t hour);

void write_I2C_time(my_time now, int hrmode);

my_time read_I2C_time();

void write_SPI_time(my_time t);

my_time read_SPI_time();

#endif