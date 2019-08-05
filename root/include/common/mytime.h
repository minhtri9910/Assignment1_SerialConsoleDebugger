#ifndef __MYTIME__
#define __MYTIME__

#include <stddef.h>
#include <stdint.h>

uint8_t convert_to_RTC (uint8_t data);

uint8_t convert_to_RTC_minutes (uint8_t data, uint8_t hrmode);

typedef struct times 
    {
        uint8_t tm_min;
        uint8_t tm_hour;
        uint8_t tm_mday;
        uint8_t tm_wday;
        uint8_t tm_mon;
        uint8_t tm_year;
    } time;

uint8_t convert_from_RTC (uint8_t data);

char * convert_DAY_from_RTC (uint8_t data);
#endif