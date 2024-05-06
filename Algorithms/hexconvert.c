#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *convert_to_hex(int num) {
    unsigned int val = num;
    char convert[17] = "0123456789abcdef";
    char rem[100];
    char *res;
    int i = 0;
    int j = 0;

    if (val == 0) return "0";
    while (val) {
        rem[i++] = convert[val%16];
        val /= 16;
    }

    res = malloc(sizeof(char)*(i+1));
    for (j = 0; j < i; ++j) {
        res[j] = rem[i-j-1];
    }
    res[j] = '\0';

    return res;
}