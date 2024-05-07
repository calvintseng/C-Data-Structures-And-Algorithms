#include "queue.h"

const int starting_size = 10;

typedef struct node {
    void *data;
    struct node *next;
} node;

typedef struct queue {
    node *head;
    node *tail;
    int size;
} queue;

node *node_init(void *val) {
    node *n = malloc(sizeof(node));
    if (n) {
        n->next = NULL;
        n->data = val;
    }
    return n;
}

queue *queue_init() {
    queue *q = malloc(sizeof(queue));
    if (q) {
        q->head = NULL;
        q->tail = NULL;
        q->size = 0;
    }
    return q;
}

void queue_push(queue* myqueue, void *val, int *error_code) {
    if (myqueue == NULL) {
        *error_code = ERR_INVALID_QUEUE;
        return;
    }
    node *new_node = node_init(val);

    if (myqueue->tail) {
        myqueue->tail->next = new_node;
    }
    
    myqueue->tail = new_node;
    
    if (myqueue->head == NULL) {
        myqueue->head = new_node;
    }

    myqueue->size++;
}

void queue_pop(queue* myqueue, int *error_code) {
    if (myqueue == NULL) {
        *error_code = ERR_INVALID_QUEUE;
        return;
    }
    if (myqueue->size == 0) {
        *error_code = ERR_EMPTY_QUEUE;
        return;
    }

    node *temp = myqueue->head;
    myqueue->head = myqueue->head->next;
    if (myqueue->head == NULL) {
        myqueue->tail = NULL;
    }
    free(temp);

    myqueue->size--;
}

void *queue_peek(queue* myqueue, int *error_code) {
    if (myqueue == NULL) {
        *error_code = ERR_INVALID_QUEUE;
    }
    if (myqueue->size == 0) {
        *error_code = ERR_EMPTY_QUEUE;
    }

    if (myqueue->head) {
        return myqueue->head->data;
    }
    return NULL;
}

void queue_free(queue* myqueue, int *error_code) {
    if (myqueue == NULL) {
        *error_code = ERR_INVALID_QUEUE;
        return;
    }

    while (myqueue->head) {
        queue_pop(myqueue, 0);
    }
    free(myqueue);
}