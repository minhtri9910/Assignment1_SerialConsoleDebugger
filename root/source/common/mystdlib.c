#include <stddef.h>
#include <stdint.h>
#include "../../include/common/mystdlib.h"

//zero out segment of "bytes" in memory counted from "dest" address
void bzero(void * dest, int bytes) {
    char * d = dest;
    while (bytes--) {
        *d++ = 0; //assign value 0 to the address 'd', then increment d by one byte
    }
}

//convert integer into C string
char *itoa(int i){
    //sign + 10 digits + '/0' = 12 elements
    static char cstring[12];
    int j = 0, isneg = 0;

    if (i==0){
        cstring[0] = '0';
        cstring[1] = '\0';
        return cstring;
    }

    //check sign
    if (i<0){
        isneg = 1;
        i = -i;
    }

    while (i != 0){
        cstring[j++] = '0' + (i%10); //ASCII value of 'i'
        i /= 10;
    }

    //insert sign if negative
    if (isneg){
        cstring[j++] = '-';
    }

    cstring[j] = '\0';
    j--; //because j is now '\0'
    i=0;

    //invert
    while (i<j){ //to swap elements
        isneg = cstring[i];
        cstring[i] = cstring[j];
        cstring[j] = isneg;
        i++;
        j--;
    }

    return cstring;
}

//convert C string to integer
int atoi(char *cstring){
    int res = 0;
    for (int i = 0; cstring[i] != '\0'; i++){ 
        //to get the decimal value of the digit characters
        //in particular, '0' = 48
        res = res*10+ (cstring[i] - '0');
    }
    return res;
}

//convert an integer to C string in hexadecimal form
char* dectohex(int i){ 
    //2,147,483,647 = 0x7FFFFFFF
    //sign + '0x' + 8 hex digits + '\0' = 12 elements
    static char hexvalue[12];
    int j = 0, isneg = 0;

    if (i==0){ //i is an input integer
        hexvalue[0] = '0';
        hexvalue[1] = 'x';
        hexvalue[2] = '0';
        hexvalue[3] = '\0';
        return hexvalue;
    }

    if (i<0){
        isneg = 1;
        i = -i;
    }

    while (i != 0){
        if ((i%16) < 10) //to get 0-9 digit characters
            hexvalue[j++] = '0' + (i%16);
        else
            hexvalue[j++] = 55 + (i%16); //to get A-F characters

        i /= 16;
    }

    hexvalue[j++] = 'x';
    hexvalue[j++] = '0';

    if (isneg){
        hexvalue[j++] = '-';
    }

    hexvalue[j] = '\0';
    j--;
    i=0;

    while (i<j){
        isneg = hexvalue[i];
        hexvalue[i] = hexvalue[j];
        hexvalue[j] = isneg;
        i++;
        j--;
    }

    return hexvalue;
}

// Loop <delay> times in a way that the compiler won't optimize away
//To create a short pause after executing some actions
void delay(uint32_t count){
    asm volatile("__delay_%=: subs %[count], %[count], #1; bne __delay_%=\n"
              : "=r"(count) : [count] "0" (count) : "cc");
}