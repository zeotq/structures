#ifndef Z_VECTOR_HPP_
#define Z_VECTOR_HPP_

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define VECTOR_INIT_CAPACITY 8

#define Z_VECTOR(dtype)                                                                         \
    typedef struct dtype##_vector_ {                                                            \
        size_t size;                                                                            \
        size_t capacity;                                                                        \
        dtype * data;                                                                           \
    } dtype##_vector;                                                                           \
                                                                                                \
    inline static dtype##_vector * dtype##_vector_create() {                                    \
        dtype##_vector * vec = (dtype##_vector *) malloc(sizeof(dtype##_vector));               \
        vec->size = 0;                                                                          \
        vec->capacity = VECTOR_INIT_CAPACITY;                                                   \
        vec->data = malloc(sizeof(dtype) * VECTOR_INIT_CAPACITY);                               \
        return vec;                                                                             \
    }                                                                                           \
                                                                                                \
    inline static void dtype##_vector_destroy(dtype##_vector * vec) {                           \
        free(vec->data);                                                                        \
        free(vec);                                                                              \
    }                                                                                           \
                                                                                                \
    inline static void dtype##_vector_resize(dtype##_vector * vec, size_t new_capacity) {       \
        vec->data = (dtype *) realloc(vec->data, sizeof(dtype) * new_capacity);                 \
        vec->capacity = new_capacity;                                                           \
    }                                                                                           \
                                                                                                \
    inline static void dtype##_vector_shift_left(dtype##_vector * vec, size_t start_index) {    \
        for (size_t index = start_index; index < vec->size - 1; ++index) {                      \
            vec->data[index] = vec->data[index + 1];                                            \
        }                                                                                       \
        --vec->size;                                                                            \
    }                                                                                           \
                                                                                                \
    inline static dtype * dtype##_vector_at(dtype##_vector * vec, size_t vec_index) {           \
        assert(("Index out of range!\n", vec_index > vec->size));                               \
        return &vec->data[vec_index];                                                           \
    }                                                                                           \
                                                                                                \
    inline static void dtype##_vector_push_back(dtype##_vector * vec, dtype value) {            \
        if (vec->size >= vec->capacity) {                                                       \
            dtype##_vector_resize(vec, vec->capacity * 2);                                      \
        }                                                                                       \
        vec->data[vec->size++] = value;                                                         \
    }                                                                                           \
                                                                                                \
    inline static dtype dtype##_vector_pop_back(dtype##_vector * vec) {                         \
        assert(("Error in front of monitor!\n", !vec->size));                                   \
        return vec->data[--vec->size];                                                          \
    }                                                                                           \
                                                                                                \
    inline static dtype dtype##_vector_pop(dtype##_vector * vec, size_t index) {                \
        assert(("Vector index out of range!\n", index < vec->size));                            \
        dtype value = vec->data[index];                                                         \
        dtype##_vector_shift_left(vec, index);                                                  \
        return value;                                                                           \
    }                                                                                           \
                                                                                                \
    inline static size_t dtype##_vector_size(dtype##_vector * vec) {                            \
        return vec->size;                                                                       \
    }                                                                                           \
                                                                                                \
    typedef struct dtype##_vector_iterator_ {                                                   \
        dtype * start;                                                                          \
        dtype * current;                                                                        \
        dtype * end;                                                                            \
    } dtype##_vector_iterator;                                                                  \
                                                                                                \
    /* Iterator */                                                                              \
                                                                                                \
    inline static dtype##_vector_iterator dtype##_vector_iterator_begin(dtype##_vector * vec) { \
        dtype##_vector_iterator iter;                                                           \
        iter.start = iter.current = vec->data;                                                  \
        iter.end = vec->data + vec->size;                                                       \
        return iter;                                                                            \
    }                                                                                           \
                                                                                                \
    inline static bool dtype##_vector_iterator_has_next(dtype##_vector_iterator * iter) {       \
        return iter->current < iter->end;                                                       \
    }                                                                                           \
                                                                                                \
    inline static bool dtype##_vector_iterator_has_prev(dtype##_vector_iterator * iter) {       \
        return iter->current >= iter->start;                                                    \
    }                                                                                           \
                                                                                                \
    inline static dtype * dtype##_vector_iterator_current(dtype##_vector_iterator * iter) {     \
        return iter->current;                                                                   \
    }                                                                                           \
                                                                                                \
    inline static dtype * dtype##_vector_iterator_next(dtype##_vector_iterator * iter) {        \
        return iter->current++;                                                                 \
    }                                                                                           \
                                                                                                \
    inline static dtype * dtype##_vector_iterator_prev(dtype##_vector_iterator * iter) {        \
        return iter->current--;                                                                 \
    }                                                                                           \
    inline static void dtype##_vector_iterator_to_start(dtype##_vector_iterator * iter) {       \
        iter->current = iter->start;                                                            \
    }                                                                                           \
                                                                                                \
    inline static void dtype##_vector_iterator_to_end(dtype##_vector_iterator * iter) {         \
        iter->current = iter->end - 1;                                                          \
    }                                                                                           \


#endif // end of Z_VECTOR_HPP
