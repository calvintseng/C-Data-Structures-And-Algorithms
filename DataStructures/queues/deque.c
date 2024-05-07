#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    struct node* next;
    struct node* prev;
    int val;
} node;

typedef struct deque {
    struct node* head;
    struct node* tail;
    int sz;
} deque;


node *node_init(int val) {
    node *newnode = malloc(sizeof(node));
    newnode->next = NULL;
    newnode->prev = NULL;
    newnode->val = val;
    return newnode;
}

deque *deque_init() {
    deque *mydeque = malloc(sizeof(deque));
    mydeque->sz = 0;
    mydeque->head = node_init(-1);
    mydeque->tail = node_init(-1);
    mydeque->head->next = mydeque->tail;
    mydeque->tail->prev = mydeque->head;
    return mydeque;
}

void deque_push_front(deque *mydeque, int val) {
    node *insert = node_init(val);
    if (mydeque->sz == 0) {
        mydeque->tail->prev = insert;
        insert->next = mydeque->tail;
    }
    node *front = mydeque->head->next;
    front->prev = insert;
    insert->next = front;
    insert->prev = mydeque->head;
    mydeque->head->next = insert;
    mydeque->sz++;
}

void deque_push_back(deque *mydeque, int val) {
    node *insert = node_init(val);
    if (mydeque->sz == 0) {
        mydeque->head->next = insert;
        insert->prev = mydeque->head;
    }
    node* back = mydeque->tail->prev;
    back->next = insert;
    insert->prev = back;
    insert->next = mydeque->tail->prev;
    mydeque->tail->prev = insert;
    mydeque->sz++;
}

void deque_pop_front(deque *mydeque) {
    if (mydeque->sz == 0) {
        return;
    }
    node *front = mydeque->head->next;
    front->next->prev = front->prev;
    mydeque->head->next = front->next;
    free(front);
    mydeque->sz--;
}

void deque_pop_back(deque *mydeque) {
    if (mydeque->sz == 0) {
        return;
    }
    node *back = mydeque->tail->prev;
    back->prev->next = mydeque->tail;
    mydeque->tail->prev = back->prev;
    free(back);
    mydeque->sz--;
}

int deque_peek_front(deque *mydeque) {
    if (mydeque->sz == 0) {
        return -1;
    }

    return mydeque->head->next->val;
}

int deque_peek_back(deque *mydeque) {
    if (mydeque->sz == 0) {
        return -1;
    }
    return mydeque->tail->prev->val;
}

void deque_free(deque *mydeque) {
    node *root = mydeque->head;
    while (root) {
        node *next = root->next;
        free(root);
        root = next;
    }
    free(mydeque);
}

int main() {
    deque *mydeque = deque_init();
    deque_push_back(mydeque, 3);
    printf("%d\n", deque_peek_front(mydeque));
    deque_push_back(mydeque, 5);
    printf("%d\n", deque_peek_back(mydeque));
    deque_push_front(mydeque, 22);
    printf("%d\n", deque_peek_back(mydeque));
    deque_pop_back(mydeque);

    deque_free(mydeque);

    return -1;
}

