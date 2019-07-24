#ifndef __STDIO__
#define __STDIO__

#include "../../include/kernel/uart.h"
#include "../../include/common/mystdlib.h"

char getc(void);
void putc(char c);

void puts(const char * s);

// This version of gets copies until newline, 
//replacing newline with null char, or until buflen.
void gets(char * buf, int buflen);

#endif

