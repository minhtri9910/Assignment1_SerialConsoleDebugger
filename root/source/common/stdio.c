#include "../../include/common/stdio.h"

//get a single character from the standard i/o (UART device in Raspberry Pi 3)
char getc(void) {
    return uart_getc();
}

//place a single character from the standard i/o
void putc(char c) {
    uart_putc(c);
}

void puts(const char * str) {
    int i;
    for (i = 0; str[i] != '\0'; i ++)
        putc(str[i]);
}

//get a C string from the standard i/o
void gets(char * buf, int buflen) {
    int i;
    char c;
    // Leave a spot for null char in buffer
    for (i = 0; (c = getc()) != '\r' && buflen > 1; i++, buflen--) {
        //i increments and buflen decreases until a return carriage has been received
        //or the buffer length in reached
        putc(c);
        buf[i] = c;
    }

    putc('\n');
    if (c == '\r') {//the current 'c' may not reach the '\r'
        buf[i] = '\0';
    }
    else
        buf[buflen-1] = '\0';
}
