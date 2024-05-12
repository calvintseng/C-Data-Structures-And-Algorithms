#ifndef VECTOR_H
#define VECTOR_H

#include <stdio.h>
#include <stdlib.h>

typedef struct vector vector;

vector *vector_init();

void vector_push_back(vector *myvec, void *val);

void vector_pop_back(vector *myvec);

void *vector_at(vector *myvec, size_t index);

void vector_free(vector *myvec);


#endif