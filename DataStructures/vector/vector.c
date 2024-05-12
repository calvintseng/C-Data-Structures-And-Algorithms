#include "vector.h"

const int STARTING_CAPACITY = 10;

typedef struct vector {
    void **data;
    size_t sz;
    size_t capacity;
} vector;

vector* vector_init() {
    vector* myvec = malloc(sizeof(vector));
    if (myvec == NULL) {
        return NULL;
    }
    
    myvec->data = malloc(STARTING_CAPACITY * sizeof(void*));
    if (myvec->data == NULL) {
        free(myvec);
        return NULL;
    }

    myvec->sz = 0;
    myvec->capacity = STARTING_CAPACITY;
    return myvec;
}

void vector_push_back(vector *myvec, void *val) {
    if (myvec == NULL) return;

    if (myvec->capacity == myvec->sz) {
        myvec->capacity = myvec->capacity * 2;
        realloc(myvec->data, myvec->capacity * sizeof(void *));
    }

    myvec->data[myvec->sz++] = val;
}

void vector_pop_back(vector *myvec) {
    if (myvec == NULL) return;
    myvec->sz--;
}

void *vector_at(vector* myvec, size_t index) {
    if (myvec == NULL || index >= myvec->sz) return NULL;
    return myvec->data[index];
}

void vector_free(vector *myvec) {
    if (myvec == NULL) return;
    for (size_t i = 0; i < myvec->sz; ++i) {
        free(myvec->data[i]);
    }
    
    free(myvec->data);
    free(myvec);
}


