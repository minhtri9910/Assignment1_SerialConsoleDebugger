#ifndef __MYTIME__
#define __MYTIME__

#include <stddef.h>
#include <stdint.h>

uint8_t convert_to_RTC (uint8_t data);

uint8_t convert_to_RTC_minutes (uint8_t data, uint8_t hrmode);

typedef struct time_structure
    {
        uint8_t tm_sec;
        uint8_t tm_min;
        uint8_t tm_hour;
        uint8_t tm_wday;
        uint8_t tm_mday;
        uint8_t tm_mon;
        uint8_t tm_year;
    } my_time;

uint8_t convert_from_RTC (uint8_t data);

char * convert_DAY_from_RTC (uint8_t data);

void display_time();
#endif