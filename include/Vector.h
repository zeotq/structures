#ifndef Z_VECTOR_HPP_
#define Z_VECTOR_HPP_

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define VECTOR_INIT_CAPACITY 8

#define Z_VECTOR(dtype, dname)                                                                  \
    typedef struct dname##_ {                                                                   \
        size_t size;                                                                            \
        size_t capacity;                                                                        \
        dtype * data;                                                                           \
    } dname;                                                                                    \
                                                                                                \
    inline static dname * dname##_create() {                                                    \
        dname * vec = (dname *) malloc(sizeof(dname));                                          \
        vec->size = 0;                                                                          \
        vec->capacity = VECTOR_INIT_CAPACITY;                                                   \
        vec->data = malloc(sizeof(dtype) * VECTOR_INIT_CAPACITY);                               \
        return vec;                                                                             \
    }                                                                                           \
                                                                                                \
    inline static void dname##_destroy(dname * vec) {                                           \
        free(vec->data);                                                                        \
        free(vec);                                                                              \
    }                                                                                           \
                                                                                                \
    inline static void dname##_resize(dname * vec, size_t new_capacity) {                       \
        vec->data = (dtype *) realloc(vec->data, sizeof(dtype) * new_capacity);                 \
        vec->capacity = new_capacity;                                                           \
    }                                                                                           \
                                                                                                \
    inline static void dname##_shift_left(dname * vec, size_t start_index) {                    \
        for (size_t index = start_index; index < vec->size - 1; ++index) {                      \
            vec->data[index] = vec->data[index + 1];                                            \
        }                                                                                       \
        --vec->size;                                                                            \
    }                                                                                           \
                                                                                                \
    inline static dtype * dname##_at(dname * vec, size_t vec_index) {                           \
        assert(("Index out of range!\n", vec_index > vec->size));                               \
        return &vec->data[vec_index];                                                           \
    }                                                                                           \
                                                                                                \
    inline static void dname##_push_back(dname * vec, dtype value) {                            \
        if (vec->size >= vec->capacity) {                                                       \
            dname##_resize(vec, vec->capacity * 2);                                             \
        }                                                                                       \
        vec->data[vec->size++] = value;                                                         \
    }                                                                                           \
                                                                                                \
    inline static dtype dname##_pop_back(dname * vec) {                                         \
        assert(("Error in front of monitor!\n", !vec->size));                                   \
        return vec->data[--vec->size];                                                          \
    }                                                                                           \
                                                                                                \
    inline static dtype dname##_pop(dname * vec, size_t index) {                                \
        assert(("Vector index out of range!\n", index < vec->size));                            \
        dtype value = vec->data[index];                                                         \
        dname##_shift_left(vec, index);                                                         \
        return value;                                                                           \
    }                                                                                           \
                                                                                                \
    inline static size_t dname##_size(dname * vec) {                                            \
        return vec->size;                                                                       \
    }                                                                                           \
                                                                                                \
    typedef struct dname##_iterator_ {                                                          \
        dtype * start;                                                                          \
        dtype * current;                                                                        \
        dtype * end;                                                                            \
    } dname##_iterator;                                                                         \
                                                                                                \
    /* Iterator */                                                                              \
                                                                                                \
    inline static dname##_iterator dname##_iterator_begin(dname * vec) {                        \
        dname##_iterator iter;                                                                  \
        iter.start = iter.current = vec->data;                                                  \
        iter.end = vec->data + vec->size;                                                       \
        return iter;                                                                            \
    }                                                                                           \
                                                                                                \
    inline static bool dname##_iterator_has_next(dname##_iterator * iter) {                     \
        return iter->current < iter->end;                                                       \
    }                                                                                           \
                                                                                                \
    inline static bool dname##_iterator_has_prev(dname##_iterator * iter) {                     \
        return iter->current >= iter->start;                                                    \
    }                                                                                           \
                                                                                                \
    inline static dtype * dname##_iterator_current(dname##_iterator * iter) {                   \
        return iter->current;                                                                   \
    }                                                                                           \
                                                                                                \
    inline static dtype * dname##_iterator_next(dname##_iterator * iter) {                      \
        return iter->current++;                                                                 \
    }                                                                                           \
                                                                                                \
    inline static dtype * dname##_iterator_prev(dname##_iterator * iter) {                      \
        return iter->current--;                                                                 \
    }                                                                                           \
    inline static void dname##_iterator_to_start(dname##_iterator * iter) {                     \
        iter->current = iter->start;                                                            \
    }                                                                                           \
                                                                                                \
    inline static void dname##_iterator_to_end(dname##_iterator * iter) {                       \
        iter->current = iter->end - 1;                                                          \
    }                                                                                           \


#endif // end of Z_VECTOR_HPP
