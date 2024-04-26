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
    my_stack->sz = size;
    for (int i = 0; i < size; ++i) {
        my_stack->arr[i] = -1;
    }
    return my_stack;
}

void stack_push(stack *my_stack, int val) {
    if (my_stack->top_ind == my_stack->sz-1) {
        int new_size = my_stack->sz * 2;
        int *new_arr = realloc(my_stack->arr, new_size * sizeof(int));
        if (new_arr == NULL) {
            printf("Error allocating memory\n");
            return;
        }
        my_stack->arr = new_arr;
        my_stack->sz = new_size;
    }
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

void stack_free(stack *my_stack) {
    if (my_stack != NULL) {
        free(my_stack->arr);
        free(my_stack);
    }
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
    stack_free(my_stack);
}