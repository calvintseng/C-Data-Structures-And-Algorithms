#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *convert_to_hex(int num) {
    unsigned int val = num;
    char* vals = "0123456789abcdef";
    char* res = malloc(sizeof(int) * 8);
    for (int i = 0; i < 8; ++i) {
        res[i] = '0';
    }
    int ind = 7;
    while (val) {
        int temp = val % 16;
        res[ind--] = vals[temp];
        temp /= 16;
    }

    return res;
}