#include "string_functions.h"

int my_strcmp(const char* string1, const char* string2) {
    while (*string1 && (*string1 == *string2)) {
        string1++;
        string2++;
    }

    return *(unsigned char *)string1 - *(unsigned char *)string2;
}

size_t my_strlen(const char* string) {
    const char *p = string;
    while (*p) {
        p++;
    }

    return p - string;
}

char *my_strcpy(char *destination, const char *src) {
    char *result = destination;
    while (*src) {
        *destination++ = *src++;
    }

    *destination = '\0';
    return result;
}

char *my_strcat(char *destination, const char *src) {
    char *result = destination;
    while (*destination) {
        destination++;
        }

    while (*src) {
        *destination++ = *src++;
        }

    *destination = '\0';

    return result;
}