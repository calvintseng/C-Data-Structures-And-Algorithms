#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct entry {
    char *key;
    char *value;
    struct entry *next;
} entry;

typedef struct hash_map {
    entry **buckets;
    unsigned int size;
    float load_factor;
} hash_map;

hash_map *hash_map_init(unsigned int size, float load_factor) {
    hash_map *my_map = malloc(sizeof(hash_map));
    my_map->buckets = malloc(sizeof(entry*) * size);
    my_map->size = size;
    my_map->load_factor = load_factor;
    for (int i = 0; i < size; ++i) {
        my_map->buckets[i] = NULL;
    }

    return my_map;
}

unsigned long int hash(const char *key) {
    unsigned long int value = 0;
    unsigned int key_len = strlen(key);
    for (unsigned int i = 0; i < key_len; ++i) {
        value = value * 37 + key[i];
    }

    return value;
}

entry *hash_map_pair(const char *key, const char *value) {
    entry *node = malloc(sizeof(*node));
    node->key = malloc(strlen(key) + 1);
    node->value = malloc(strlen(value) + 1);

    strcpy(node->key, key);
    strcpy(node->value, value);

    node->next = NULL;
    return node;
}

void hash_map_insert(hash_map *map, const char *key, char *value) {
    unsigned int slot = hash(key) % map->size;
    entry *head = map->buckets[slot];

    if (head == NULL) {
        map->buckets[slot] = hash_map_pair(key, value);
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

    prev->next = hash_map_pair(key, value);
}

char *hash_map_get(hash_map *map, const char *key) {
    unsigned int slot = hash(key) % map->size;
    entry *head = map->buckets[slot];

    while (head != NULL) {
        if (strcmp(head->key, key) == 0) {
            return head->value;
        }
        head = head->next;
    }
    
    return NULL;
}

void hash_map_erase(hash_map *map, const char *key) {
    unsigned int slot = hash(key) % map->size;
    entry *head = map->buckets[slot];
    entry *prev = NULL;

    if (head == NULL) return;

    while (head != NULL) {
        if (strcmp(head->key, key) == 0) {
            if (prev == NULL) {
                map->buckets[slot] = head->next;
            } else {
                prev->next = head->next;
            }

            free(head->key);
            free(head->value);

            free(head);
            return;
        }
        prev = head;
        head = head->next;
    }    
}

void hash_map_free(hash_map *map) {
    for (int i = 0; i < map->size; ++i) {
        entry *head = map->buckets[i];
        while (head) {
            free(head->key);
            free(head->value);
            entry *next = head->next;
            free(head);
            head = next;
        }
    }

    free(map->buckets);
    free(map);
}

int main() {
    hash_map *mymap = hash_map_init(10, .75);

    hash_map_insert(mymap, "first", "hello");
    hash_map_insert(mymap, "second", "goodbye");
    if (strcmp(hash_map_get(mymap, "first"), "hello") == 0) {
        printf("Insertion successful\n");
    } else {
        printf("Insertion failed\n");
    }

    hash_map_insert(mymap, "first", "replaced");
    if (strcmp(hash_map_get(mymap, "first"), "replaced") == 0) {
        printf("Replaced key value successful\n");
    } else {
        printf("Replaced key value failed\n");
    }

    if (hash_map_get(mymap, "invalid") == NULL) {
        printf("Lookup invalid key value successful\n");
    } else {
        printf("Lookup invalid key value failed\n");
    }

    hash_map_erase(mymap, "first");
    if (hash_map_get(mymap, "first") == NULL) {
        printf("Deletion successful\n");
    } else {
        printf("Deletion Failed\n");
    }

    hash_map_free(mymap);
}

