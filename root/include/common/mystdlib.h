#ifndef __MYSTDLIB__
#define __MYSTDLIB__

void memcpy(void * dest, void * src, int bytes);

void bzero(void * dest, int bytes);

char* itoa(int i);

int atoi(char *str);

char* dectohex(int i);

#endif
