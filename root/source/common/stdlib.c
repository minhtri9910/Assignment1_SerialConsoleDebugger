#include "../../include/common/stdlib.h"

void memcpy(void * dest, void * src, int bytes) {
    char * d = dest, * s = src;
    while (bytes--) {
        *d++ = *s++;
    }
}

void bzero(void * dest, int bytes) {
    char * d = dest;
    while (bytes--) {
        *d++ = 0;
    }
}

int power(int num, int pow){
    if (pow==1) return num;
    if (pow==0) return 1;

    int base = num;
    for (int i=1; i < pow; i++){
        num = num*base;
    }
    return num;
}

char *itoa(int i){
    static char intbuf[12];
    int j = 0, isneg = 0;

    if (i==0){
        intbuf[0] = '0';
        intbuf[1] = '\0';
        return intbuf;
    }

    if (i<0){
        isneg = 1;
        i = -i;
    }

    while (i != 0){
        intbuf[j++] = '0' + (i%10);
        i /= 10;
    }

    if (isneg){
        intbuf[j++] = '-';
    }

    intbuf[j] = '\0';
    j--;
    i=0;

    while (i<j){
        isneg = intbuf[i];
        intbuf[i] = intbuf[j];
        intbuf[j] = isneg;
        i++;
        j--;
    }

    return intbuf;

}

int atoi(char *str){
    int i=0, len=0;
    int n=0;

    //Measure string length
    for (int l=0; str[l]!='\0'; l++){
        len++;
    }

    for (;len != 0; len--){
        i = i + (str[len-1] - '0')*power(10,n);
        n++;
    }

    return i;
}

char toHex(int i){
    if ((i>=0) && (i<=9)) return '0' + i;
    else if (i == 10) return 'a';
    else if (i == 11) return 'b';
    else if (i == 12) return 'c';
    else if (i == 13) return 'd';
    else if (i == 14) return 'e';
    else if (i == 15) return 'f';
    else return '0';
}

char* hextodec(int i){
    static char intbuf[12];
    int j = 0, isneg = 0;

    if (i==0){
        intbuf[0] = '0';
        intbuf[1] = 'x';
        intbuf[2] = '0';
        intbuf[3] = '\0';
        return intbuf;
    }

    if (i<0){
        isneg = 1;
        i = -i;
    }

    while (i != 0){
        intbuf[j++] = toHex(i%16);
        i /= 16;
    }

    intbuf[j++] = 'x';
    intbuf[j++] = '0';

    if (isneg){
        intbuf[j++] = '-';
    }

    intbuf[j] = '\0';
    j--;
    i=0;

    while (i<j){
        isneg = intbuf[i];
        intbuf[i] = intbuf[j];
        intbuf[j] = isneg;
        i++;
        j--;
    }

    return intbuf;
}

