#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>
#include <stdio.h>

typedef struct queue queue;
typedef struct node node;

const int ERR_INVALID_QUEUE = -1;
const int ERR_EMPTY_QUEUE = -2;

queue *queue_init();

void queue_push(queue* myqueue, int val, int *error_code);

void queue_pop(queue* myqueue, int *error_code);

int queue_peek(queue* myqueue, int *error_code);

void queue_free(queue* myqueue, int *error_code);

#endif 