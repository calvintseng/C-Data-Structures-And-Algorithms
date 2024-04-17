#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int hash(const char *key) {
    unsigned int length = strlen(key);
    unsigned long int value = 0;

    if (length == 0) {
        return value;
    }

    for (int i = 0; i < length; ++i) {
        value = value * 37 + key[i];
    }

    return value;
}

typedef struct linked_list {
    char* key;
    struct linked_list *next;
} linked_list;

typedef struct linked_list entry;

typedef struct unordered_set {
    unsigned int size;
    entry **buckets;
} unordered_set;

unordered_set *init_unordered_set(const unsigned int set_size) {
    unordered_set *myset = malloc(sizeof(unordered_set));
    myset->size = set_size;
    myset->buckets = malloc(sizeof(linked_list*) * set_size);

    for (int i = 0; i < set_size; ++i) {
        myset->buckets[i] = NULL;
    }

    return myset;
}

entry *init_entry(const char *key) {
    entry *entry = malloc(sizeof(entry));
    entry->key = malloc(strlen(key)+1);
    
    strcpy(entry->key, key);
    entry->next = NULL;
    return entry;
}

void unordered_set_insert(unordered_set *myset, const char *key) {
    if (myset->size == 0) {
        return;
    }

    unsigned int slot = hash(key) % myset->size;
    entry *head = myset->buckets[slot];

    if (head == NULL) {
        myset->buckets[slot] = init_entry(key);
        return;
    }

    entry *prev = NULL;
    while (head != NULL) {
        if (strcmp(head->key, key) == 0) {
            return;
        }
        prev = head;
        head = head->next;
    }

    prev->next = init_entry(key);
}

int unordered_set_lookup(unordered_set *myset, const char *key) {
    unsigned int slot = hash(key) % myset->size;
    entry *head = myset->buckets[slot];

    while (head != NULL) {
        if (strcmp(head->key, key) == 0) {
            return 1;
        }
        head = head->next;
    }
    return 0;
}

void unordered_set_erase(unordered_set *myset, const char *key) {
    unsigned int slot = hash(key) % myset->size;
    entry *head = myset->buckets[slot];
    entry *prev = NULL;

    while (head != NULL) {
        if (strcmp(head->key, key) == 0) {
            if (prev == NULL) {
                myset->buckets[slot] = NULL;
            }
            else {
                prev->next = head->next;
            }
            free(head->key);
            free(head);
            return;
        }

        prev = head;
        head = head->next;
    }
}

void unordered_set_free(unordered_set *myset) {
    for (int i = 0; i < myset->size; ++i) {
        entry *head = myset->buckets[i];
        while (head) {
            free(head->key);
            entry *next = head->next;
            free(head);
            head = next;
        }
        free(myset->buckets[i]);
    }
    free(myset->buckets);
    free(myset);
}

int main() {
    unordered_set *myset = init_unordered_set(10);
    unordered_set_insert(myset, "hello");
    if (unordered_set_lookup(myset, "hello") == 1) {
        printf("Insert and Lookup Successful\n");
    }
    else {
        printf("Insert and Lookup Failed\n");
    }

    if (unordered_set_lookup(myset, "nonexistent") == 0) {
        printf("Insert and Lookup Successful\n");
    }
    else {
        printf("Insert and Lookup Failed\n");
    }

    unordered_set_erase(myset, "hello");
    if (unordered_set_lookup(myset, "hello") == 0) {
        printf("Erase Successful\n");
    }
    else {
        printf("Erase Failed\n");
    }    

    unordered_set_free(myset);

    return 0;
}