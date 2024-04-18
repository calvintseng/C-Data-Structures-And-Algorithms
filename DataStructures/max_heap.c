#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

//priority queue is a heap 

typedef struct node {
    int val;
    struct node* left;
    struct node* right;
    struct node* parent;
} node;

typedef struct max_heap {
    node* head;
    unsigned int size;

} max_heap;

typedef max_heap priority_queue_max;

node *node_init(int val) {
    node *my_node = malloc(sizeof(node));
    my_node->left = NULL;
    my_node->right = NULL;
    my_node->parent = NULL;
    my_node->val = val;

    return my_node;
}

max_heap *max_heap_init() {
    max_heap *heap = malloc(sizeof(max_heap));
    heap->size = 0;
    heap->head = NULL;
    return heap;
}

void swap_val(node *a, node *b) {
    int temp = a->val;
    a->val = b->val;
    b->val = temp;
}

void bubble_up(node *cur) {
    while (cur->parent && cur->parent->val < cur->val) {
        swap_val(cur, cur->parent);
        cur = cur->parent;
    }
}

void bubble_down(node* cur) {
    while (1) {
        int left_val = cur->left ? cur->left->val : INT_MIN;
        int right_val = cur->right ? cur->right->val : INT_MIN;
        int largest_val = cur->val;

        node *largest_node = cur;

        if (left_val > largest_val) {
            largest_node = cur->left;
            largest_val = left_val;   
        }
        if (right_val > largest_val) {
            largest_node = cur->right;
            largest_val = right_val;
        }

        if (largest_node != cur) {
            swap_val(cur, largest_node);
            cur = largest_node;
        } else {
            break;
        }
    }
}

node* get_last_node(max_heap *heap) {
    node* temp = heap->head;
    int path = heap->size - 1;
    int level = 0;

    while ((1 << (level + 1)) <= heap->size) {
        level++;
    }

    for (int i = level - 1; i >= 0; --i) {
        if ((path >> i) & 1) {
            temp = temp->right;
        } else {
            temp = temp->left;
        }
    }

    return temp;
}

void max_heap_insert(max_heap* heap, int val) {
    node *temp = heap->head;
    node *insert_node = node_init(val);
    heap->size++;

    if (heap->head == NULL) {
        heap->head = insert_node;
        return;
    }

    int level_nodes = 1;
    while (heap->size >= (1 << level_nodes)) {
        level_nodes++;
    }

    int path = (heap->size - (1 << (level_nodes-1)));

    for (int i = level_nodes - 2; i > 0; --i) {
        if (path & (1 << i)) {
            temp = temp->right;
        }
        else {
            temp = temp->left;
        }
    }

    insert_node->parent = temp;
    if (path & 1) {
        temp->right = insert_node;
    }
    else {
        temp->left = insert_node;
    }

    bubble_up(insert_node);
}

void max_heap_pop(max_heap* heap) {
    if (heap->head == NULL) {
        return;
    }
    if (heap->size == 1) {
        free(heap->head);
        heap->head = NULL;
        heap->size = 0;
        return;
    }

    int max_val = heap->head->val;

    node *last_node = get_last_node(heap);
    heap->head->val = last_node->val;

    if (last_node->parent) {
        if (last_node->parent->left == last_node) {
            last_node->parent->left = NULL;
        } else {
            last_node->parent->right = NULL;
        }
    }
    free(last_node);
    heap->size--;

    bubble_down(heap->head);
}

int max_heap_peek(max_heap* heap) {
    if (heap->head == NULL) {
        return -1;
    }

    return heap->head->val;
}

unsigned int max_heap_size(max_heap* heap) {
    return heap->size;
}

int main() {
    max_heap *heap = max_heap_init();
    max_heap_insert(heap, 5);
    max_heap_insert(heap, 3);
    max_heap_insert(heap, 8);
    if (max_heap_peek(heap) == 8) {
        printf("Insert Successful\n");
    }
    else {
        printf("Insert Failed\n");
    }

    max_heap_pop(heap);
    if (max_heap_peek(heap) == 5) {
        printf("Pop Successful\n");
    }
    else {
        printf("Pop Failed\n");
    }

    if (max_heap_size(heap) == 2) {
        printf("Size Successful\n");
    }
    else {
        printf("Size Failed\n");
    }
}