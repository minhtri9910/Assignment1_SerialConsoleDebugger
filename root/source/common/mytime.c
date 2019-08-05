#include "../../include/common/mytime.h"

uint8_t convert_to_RTC (uint8_t data)
{
    return (((data/10) << 4) + (data % 10));
}

//write 0 to hrmode to enable 24 hour, 1 for 12hr am, 2 for 12hr pm
uint8_t convert_to_RTC_hours (uint8_t data, uint8_t hrmode)
{
    if (hrmode == 1) return ((1 << 6) + ((data/10) << 4) + (data % 10));
    else if (hrmode == 2) return ((1 << 6) + (1 << 5) + ((data/10) << 4) + (data % 10));
    else return ((data/10 << 4) + (data % 10));
}

uint8_t convert_from_RTC (uint8_t data)
{
    return (((data & 0x70) >> 4) * 10 + (data & 0x0F));
}

char * convert_DAY_from_RTC (uint8_t data)
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
