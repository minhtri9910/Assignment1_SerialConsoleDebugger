#ifndef __MYSTDLIB__
#define __MYSTDLIB__

#include <stddef.h>
#include <stdint.h>

void bzero(void * dest, int bytes);

char* itoa(int i);

char* itob(int i);

int atoi(char *str);

char* dectohex(int i);

void delay(uint32_t count);

#endif
