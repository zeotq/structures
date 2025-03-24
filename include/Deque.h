#ifndef Z_DEQ_HPP_
#define Z_DEQ_HPP_

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define Z_DEQ(dtype)                                                                          \
    typedef struct deq_dtype##_item_ {                                                        \
        dtype data;                                                                           \
        struct deq_dtype##_item_ * next;                                                      \
        struct deq_dtype##_item_ * prev;                                                      \
    } dtype##_deq_item;                                                                       \
                                                                                              \
    typedef struct {                                                                          \
        dtype##_deq_item * front;                                                             \
        dtype##_deq_item * back;                                                              \
        size_t size;                                                                          \
    } dtype##_deq;                                                                            \
                                                                                              \
                                                                                              \
    inline static dtype##_deq * create() {                                                    \
        dtype##_deq * deq = (dtype##_deq *) malloc(sizeof(dtype##_deq));                      \
        deq->front = NULL;                                                                    \
        deq->back = NULL;                                                                     \
        deq->size = 0;                                                                        \
        return deq;                                                                           \
    }                                                                                         \
    inline static void dtype##_deque_push_first(dtype##_deq * deq, dtype value) {             \
        dtype##_deq_item * new_item = (dtype##_deq_item *) malloc(sizeof(dtype##_deq_item));  \
        new_item->data = value;                                                               \
        new_item->next = new_item->prev = NULL;                                               \
        deq->front = deq->back = new_item;                                                    \
        deq->size += 1;                                                                       \
    }                                                                                         \
                                                                                              \
    inline static void dtype##_deque_push_front(dtype##_deq * deq, dtype value) {             \
        if (deq->size == 0) { dtype##_deque_push_first(deq, value); return; }                 \
        dtype##_deq_item * new_item = (dtype##_deq_item *) malloc(sizeof(dtype##_deq_item));  \
        dtype##_deq_item * old_item = deq->front;                                             \
        new_item->data = value;                                                               \
        new_item->next = NULL;                                                                \
        new_item->prev = old_item;                                                            \
        old_item->next = new_item;                                                            \
        deq->front = new_item;                                                                \
        deq->size += 1;                                                                       \
    }                                                                                         \
                                                                                              \
    inline static void dtype##_deque_push_back(dtype##_deq * deq, dtype value) {              \
        if (deq->size == 0) { dtype##_deque_push_first(deq, value); return; }                 \
        dtype##_deq_item * new_item = (dtype##_deq_item *) malloc(sizeof(dtype##_deq_item));  \
        dtype##_deq_item * old_item = deq->back;                                              \
        new_item->data = value;                                                               \
        new_item->next = old_item;                                                            \
        new_item->prev = NULL;                                                                \
        old_item->prev = new_item;                                                            \
        deq->back = new_item;                                                                 \
        deq->size += 1;                                                                       \
    }                                                                                         \
                                                                                              \
    inline static void dtype##_deque_destroy_item(dtype##_deq_item * item) {                  \
        free(item);                                                                           \
    }                                                                                         \
                                                                                              \
    inline static void dtype##_deque_destroy(dtype##_deq * deq) {                             \
        dtype##_deq_item * item = deq->back;                                                  \
        while (item != NULL) {                                                                \
            dtype##_deq_item * next_item = item->next;                                        \
            dtype##_deque_destroy_item(item);                                                 \
            item = next_item;                                                                 \
        }                                                                                     \
        free(deq);                                                                            \
    }                                                                                         \
                                                                                              \
    inline static dtype dtype##_deque_pop_front(dtype##_deq * deq) {                          \
        if (deq->size == 0) exit(1);                                                          \
        dtype##_deq_item * old_front_item = deq->front;                                       \
        dtype value = old_front_item->data;                                                   \
        if (deq->size == 1) {                                                                 \
            deq->front = deq->back = NULL;                                                    \
        } else {                                                                              \
            deq->front = old_front_item->prev;                                                \
            deq->front->next = NULL;                                                          \
        }                                                                                     \
        dtype##_deque_destroy_item(old_front_item);                                           \
        deq->size -= 1;                                                                       \
        return value;                                                                         \
    }                                                                                         \
                                                                                              \
    inline static dtype dtype##_deque_pop_back(dtype##_deq * deq) {                           \
        if (deq->size == 0) exit(1);                                                          \
        dtype##_deq_item * old_back_item = deq->back;                                         \
        dtype value = old_back_item->data;                                                    \
        if (deq->size == 1) {                                                                 \
            deq->front = deq->back = NULL;                                                    \
        } else {                                                                              \
            deq->back = old_back_item->next;                                                  \
            deq->back->prev = NULL;                                                           \
        }                                                                                     \
        dtype##_deque_destroy_item(old_back_item);                                            \
        deq->size -= 1;                                                                       \
        return value;                                                                         \
    }                                                                                         \
                                                                                              \
    inline static bool dtype##_deque_empty(dtype##_deq * deq) {                               \
        return (deq->size == 0);                                                              \
    }                                                                                         \
                                                                                              \
    inline static size_t dtype##_deque_size(dtype##_deq * deq) {                              \
        return deq->size;                                                                     \
    }                                                                                         \
                                                                                              \
    inline static void dtype##_deque_status(dtype##_deq * deq, FILE * stream) {               \
        if (dtype##_deque_empty(deq)) { fprintf(stream, "empty\n"); return; }                 \
        fprintf(stream, "BACK: Addres: %p Value: %d Prev: %p Next: %p\n",                     \
            deq->back, (dtype)deq->back->data,                                                \
            deq->back->prev, deq->back->next);                                                \
        fprintf(stream, "FRONT: Addres: %p Value: %d Prev: %p Next: %p\n",                    \
            deq->front, (dtype)deq->front->data,                                              \
            deq->front->prev, deq->front->next);                                              \
    }                                                                                         \

#endif // end of Z_DEQ_HPP
