#ifndef __MYSTDLIB__
#define __MYSTDLIB__

void bzero(void * dest, int bytes);

char* itoa(int i);

int atoi(char *str);

char* dectohex(int i);

void delay(uint32_t count);

#endif
