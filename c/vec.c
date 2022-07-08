#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#define T int
#define INITIAL_CAPACITY 4

typedef struct {
    int capacity;
    int length;
    T* buffer;
} Vec;

void panic(char message[]) {
    fprintf(stderr, "%s\n", message);
    exit(1);
}

void vec_print(Vec vec) {
    printf("[");
    if (vec.length > 0) {
        printf("%d", vec.buffer[0]);
        for (int i = 1; i < vec.length; i += 1) {
            printf(", %d", vec.buffer[i]);
        }
    }
    printf("]\n");
}

Vec vec_new() {
    Vec v = {
        .length = 0,
        .capacity = INITIAL_CAPACITY,
        .buffer = malloc(sizeof(T[INITIAL_CAPACITY])),
    };
    if (v.buffer == NULL) {
        panic("Malloc failed");
    }
    return v;
}

void vec_grow_capacity(Vec* vec) {
    if (vec->length >= vec->capacity) {
        vec->capacity <<= 1;
        vec->buffer = realloc(vec->buffer, sizeof(T[vec->capacity]));
    }
}

void vec_push(Vec* vec, int value) {
    vec_grow_capacity(vec);
    vec->buffer[vec->length++] = value;
}

void vec_insert(Vec* vec, int position, int value) {
    vec_grow_capacity(vec);
    for (int i = vec->length; i > position; --i) {
        vec->buffer[i] = vec->buffer[i - 1];
    }
    vec->buffer[position] = value;
    vec->length++;
}

void vec_remove(Vec* vec, int index) {
    if (!(0 <= index && index < vec->length)) {
        panic("Out of bounds");
    }
    for (int i = index; i < vec->length - 1; ++i) {
        vec->buffer[i] = vec->buffer[i + 1];
    }
    vec->length--;
}

T vec_get(Vec vec, int index) {
    if (!(0 <= index && index < vec.length)) {
        panic("Out of bounds");
    }
    return vec.buffer[index];
}

T vec_pop(Vec* vec) {
    if (vec->length <= 0) {
        panic("Out of bounds");
    }
    return vec->buffer[vec->length--];
}

void vec_free(Vec vec) {
    free(vec.buffer);
}

int main() {
    Vec vec = vec_new();
    vec_print(vec);
    for (int i = 0; i < 10; ++i) {
        vec_push(&vec, i);
    }
    vec_print(vec);
    vec_insert(&vec, 5, 42);
    printf("vec[5] = %d\n", vec_get(vec, 5));
    vec_print(vec);
    vec_remove(&vec, 5);
    vec_print(vec);
    vec_free(vec);
}
