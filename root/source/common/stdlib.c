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

char *itoa(int i){
    static char cstring[12];
    int j = 0, isneg = 0;

    if (i==0){
        cstring[0] = '0';
        cstring[1] = '\0';
        return cstring;
    }

    if (i<0){
        isneg = 1;
        i = -i;
    }

    while (i != 0){
        cstring[j++] = '0' + (i%10);
        i /= 10;
    }

    if (isneg){
        cstring[j++] = '-';
    }

    cstring[j] = '\0';
    j--;
    i=0;

    while (i<j){
        isneg = cstring[i];
        cstring[i] = cstring[j];
        cstring[j] = isneg;
        i++;
        j--;
    }

    return cstring;

}

int atoi(char *cstring){
    int res = 0;
    for (int i = 0; cstring[i] != '\0'; i++){ //?
        res = res*10+ (cstring[i] - '0');
    }
    return res;
}

char* dectohex(int i){
    static char cstring[12];
    int j = 0, isneg = 0;

    if (i==0){
        cstring[0] = '0';
        cstring[1] = 'x';
        cstring[2] = '0';
        cstring[3] = '\0';
        return cstring;
    }

    if (i<0){
        isneg = 1;
        i = -i;
    }

    while (i != 0){
        //?
        if ((i%16) < 10)
            cstring[j++] = '0' + (i%16);
        else
            cstring[j++] = 55 + (i%16);

        i /= 16;
    }

    cstring[j++] = 'x';
    cstring[j++] = '0';

    if (isneg){
        cstring[j++] = '-';
    }

    cstring[j] = '\0';
    j--;
    i=0;

    while (i<j){
        isneg = cstring[i];
        cstring[i] = cstring[j];
        cstring[j] = isneg;
        i++;
        j--;
    }

    return cstring;
}

