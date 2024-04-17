#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TRIE_SIZE 26

typedef struct trie {
    int validword;
    struct trie *children[TRIE_SIZE];
} trie;

trie* trie_init_node(void) {
    trie *node = malloc(sizeof(trie));
    for (size_t i = 0; i < TRIE_SIZE; ++i) {
        node->children[i] = NULL;
    }

    return node;
} 

void trie_insert(trie* node, char* key) {
    unsigned int length = strlen(key);

    for (unsigned int i = 0; i < length; ++i) {
        int index = key[i] - 'a';
        if (node->children[index] == NULL) {
            node->children[index] = trie_init_node();
        }
        node = node->children[index];
    }
    node->validword = true;
}

bool trie_lookup(trie* node, char* key) {
    unsigned int length = strlen(key);

    for (unsigned int i = 0; i < length; ++i) {
        int index = key[i] - 'a';
        if (node->children[index] == NULL) {
            return false;
        }
        node = node->children[index];
    }

    return node != NULL && node->validword;
}

void trie_delete_word(trie* node, char* key) {
    unsigned int length = strlen(key);

    for (unsigned int i = 0; i < length; ++i) {
        int index = key[i] - 'a';
        if (node->children[index] == NULL) {
            return;
        }
        node = node->children[index];
    }
    node->validword = false;
}

void trie_free_memory(trie* node) {
    for (unsigned int i = 0; i < TRIE_SIZE; ++i) {
        if (node->children[i] != NULL) {
            trie_free_memory(node->children[i]);
        }
    }
    free(node);
}

int main() {
    trie *my_trie = trie_init_node();
    trie_insert(my_trie, "hello world");
    
    if (trie_lookup(my_trie, "hello world")) {
        printf("Lookup for existing word successful\n");
    }
    else {
        printf("Lookup for existing word failed\n");
    }

    if (!trie_lookup(my_trie, "asdf")) {
        printf("Lookup for non-existing word successful\n");
    }
    else {
        printf("Lookup for non-existing word failed\n");
    }

    trie_delete_word(my_trie, "hello world"); 
        if (!trie_lookup(my_trie, "hello world")) {
        printf("Delete for existing word successful\n");
    }
    else {
        printf("Delete for existing word failed\n");
    }
    
    trie_free_memory(my_trie);
}