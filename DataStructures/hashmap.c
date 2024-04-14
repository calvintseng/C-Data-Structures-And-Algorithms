#include <stdio.h>

#define TABLE_SIZE 10

typedef struct entry {
    char *key;
    char *value;
    struct entry *next;
} entry;

typedef struct hash_map {
    entry **entries;
} hash_map;

unsigned int hash(const char *key) {
    unsigned long int value = 0;
    unsigned int i = 0;
    unsigned int key_len = strlen(key);

    for (; key_len; ++i) {
        value = value * 37 + key[i];
    }

    value = value % TABLE_SIZE;
    return value;
}

entry *hashmap_pair(const char *key, const char *value) {
    entry *entry = malloc(sizeof(*entry));
    entry->key = malloc(strlen(key) + 1);
    entry->value = malloc(strlen(value) + 1);

    strcpy(entry->key, key);
    strcpy(entry->value, value);

    entry->next = NULL;
    return entry;
}

hash_map *init_hashmap(void) {
    hash_map *hashmap = malloc(sizeof(hashmap));
    hashmap->entries = malloc(sizeof(entry*) * TABLE_SIZE);

    for (int i = 0; i < TABLE_SIZE; ++i) {
        hashmap->entries[i] = NULL;
    }
}

void hashmap_put(hash_map *hashmap, const char *key, const char *value) {
    unsigned int slot = hash(key);
    entry *head = hashmap->entries[slot];

    if (head == NULL) {
        hashmap->entries[slot] = hashmap_pair(key, value);
        return;
    }

    entry *prev = NULL;

    while (head != NULL) {
        if (strcmp(head->key, key) == 0) {
            free(head->value);
            head->value = malloc(strlen(value) + 1);
            strcpy(head->value, value);
            return;
        }

        prev = head;
        head = head->next;
    }

    prev->next = hashmap_pair(key, value);
}

char *hashmap_get(hash_map *hashmap, const char *key) {
    unsigned int slot = hash(key);
    entry *head = hashmap->entries[slot];

    while (head != NULL) {
        if (head->key == key) {
            return head->value;
        }
        head = head->next;
    }

    return NULL;
}

void hashmap_free(hash_map *hashmap) {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        entry *head = hashmap->entries[i];
        while (head) {
            free(head->key);
            free(head->value);
            entry *next = head->next;
            free(head);
            head = next;
        }
    }
    free(hashmap->entries);
    free(hashmap);

}