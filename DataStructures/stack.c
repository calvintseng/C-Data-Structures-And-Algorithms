#include <stdio.h>
#include <stdlib.h>

typedef struct stack {
    int *arr;
    unsigned int sz;
    unsigned int top_ind;
} stack;

stack *stack_init(int size) {
    stack *my_stack = malloc(sizeof(stack));
    my_stack->top_ind = -1;
    my_stack->arr = malloc(sizeof(int) * size);
    for (int i = 0; i < size; ++i) {
        my_stack->arr[i] = -1;
    }
    return my_stack;
}

void stack_push(stack *my_stack, int val) {
    my_stack->arr[++my_stack->top_ind] = val;
}

void stack_pop(stack *my_stack) {
    if (my_stack->top_ind == -1) {
        return;
    }
    my_stack->top_ind--;
}

int stack_peek(stack *my_stack) {
    if (my_stack->top_ind == -1) return -1;
    return my_stack->arr[my_stack->top_ind];
}

int main() {
    stack *my_stack = stack_init(100);
    stack_push(my_stack, 10);
    stack_push(my_stack, 15);
    stack_push(my_stack, 20);
    stack_push(my_stack, 25);
    printf("%d\n", stack_peek(my_stack));
    stack_pop(my_stack);
    printf("%d\n", stack_peek(my_stack));
}