#ifndef STRING_FUNCTIONS_H
#define STRING_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>

int my_strcmp(const char* string1, const char* string2);

size_t my_strlen(const char* string);

char *my_strcpy(char *destination, const char *src);

char *my_strcat(char *destination, const char *src);

#endif
