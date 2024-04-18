#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define HEAP_SIZE 1024 * 1024

typedef struct linked_list {
    unsigned int size;
    bool free;
    struct linked_list *next;
} linked_list;

typedef linked_list memory_block;

static char heap[HEAP_SIZE];
static memory_block *free_list = (void*)heap;

void init_memory_block() {
    free_list->size = HEAP_SIZE - sizeof(memory_block);
    free_list->free = true;
    free_list->next = NULL;
}

void *my_malloc(int size) {
    memory_block *head = free_list;
    while (head) {
        if (head->free && head->size >= size) {
            if (head->size  > size + sizeof(memory_block)) {
                memory_block *new_block = (void*)((char*)head + sizeof(memory_block) + size);
                new_block->size = head->size - (sizeof(memory_block) + size);
                new_block->free = true;
                new_block->next = head->next;

                head->size = size;
                head->next = new_block;
            }

            head->free = false;
            return (void*)((char*)head + sizeof(memory_block));
        }
        head = head->next;
    }
    return NULL;
}

void my_free(void* ptr) {
    if (!ptr) return;

    memory_block *cur = (memory_block*)((char*)ptr - sizeof(memory_block));
    cur->free = true;

    cur = free_list;
    while (cur != NULL && cur->next != NULL) {
        if (cur->free && cur->next->free) {
            cur->size += cur->next->size + sizeof(memory_block);
            cur->next = cur->next->next;
        }
        cur = cur->next;
    }
}

int main() {
    init_memory_block();

    void *a = my_malloc(100);
    void *b = my_malloc(200);
    my_free(a);
    void *c = my_malloc(50);
    my_free(c);

    return 0;
}