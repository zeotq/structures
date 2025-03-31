#ifndef Z_DEQ_HPP_
#define Z_DEQ_HPP_

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define Z_DEQ(dtype, dname)                                                                   \
    typedef struct dname##_deq_item_ {                                                        \
        dtype data;                                                                           \
        struct deq_dname##_item_ * next;                                                      \
        struct deq_dname##_item_ * prev;                                                      \
    } dname##_deq_item;                                                                       \
                                                                                              \
    typedef struct {                                                                          \
        dname##_deq_item * front;                                                             \
        dname##_deq_item * back;                                                              \
        size_t size;                                                                          \
    } dname##_deq;                                                                            \
                                                                                              \
                                                                                              \
    inline static dname##_deq * dname##_create() {                                            \
        dname##_deq * deq = (dname##_deq *) malloc(sizeof(dname##_deq));                      \
        deq->front = NULL;                                                                    \
        deq->back = NULL;                                                                     \
        deq->size = 0;                                                                        \
        return deq;                                                                           \
    }                                                                                         \
    inline static void dname##_push_first(dname##_deq * deq, dtype value) {                   \
        dname##_deq_item * new_item = (dname##_deq_item *) malloc(sizeof(dname##_deq_item));  \
        new_item->data = value;                                                               \
        new_item->next = new_item->prev = NULL;                                               \
        deq->front = deq->back = new_item;                                                    \
        deq->size += 1;                                                                       \
    }                                                                                         \
                                                                                              \
    inline static void dname##_push_front(dname##_deq * deq, dtype value) {                   \
        if (deq->size == 0) { dname##_push_first(deq, value); return; }                       \
        dname##_deq_item * new_item = (dname##_deq_item *) malloc(sizeof(dname##_deq_item));  \
        dname##_deq_item * old_item = deq->front;                                             \
        new_item->data = value;                                                               \
        new_item->next = NULL;                                                                \
        new_item->prev = old_item;                                                            \
        old_item->next = new_item;                                                            \
        deq->front = new_item;                                                                \
        deq->size += 1;                                                                       \
    }                                                                                         \
                                                                                              \
    inline static void dname##_push_back(dname##_deq * deq, dtype value) {                    \
        if (deq->size == 0) { dname##_push_first(deq, value); return; }                       \
        dname##_deq_item * new_item = (dname##_deq_item *) malloc(sizeof(dname##_deq_item));  \
        dname##_deq_item * old_item = deq->back;                                              \
        new_item->data = value;                                                               \
        new_item->next = old_item;                                                            \
        new_item->prev = NULL;                                                                \
        old_item->prev = new_item;                                                            \
        deq->back = new_item;                                                                 \
        deq->size += 1;                                                                       \
    }                                                                                         \
                                                                                              \
    inline static void dname##_destroy_item(dname##_deq_item * item) {                        \
        free(item);                                                                           \
    }                                                                                         \
                                                                                              \
    inline static void dname##_destroy(dname##_deq * deq) {                                   \
        dname##_deq_item * item = deq->back;                                                  \
        while (item != NULL) {                                                                \
            dname##_deq_item * next_item = item->next;                                        \
            dname##_destroy_item(item);                                                       \
            item = next_item;                                                                 \
        }                                                                                     \
        free(deq);                                                                            \
    }                                                                                         \
                                                                                              \
    inline static dtype dname##_pop_front(dname##_deq * deq) {                                \
        if (deq->size == 0) exit(1);                                                          \
        dname##_deq_item * old_front_item = deq->front;                                       \
        dtype value = old_front_item->data;                                                   \
        if (deq->size == 1) {                                                                 \
            deq->front = deq->back = NULL;                                                    \
        } else {                                                                              \
            deq->front = old_front_item->prev;                                                \
            deq->front->next = NULL;                                                          \
        }                                                                                     \
        dname##_destroy_item(old_front_item);                                                 \
        deq->size -= 1;                                                                       \
        return value;                                                                         \
    }                                                                                         \
                                                                                              \
    inline static dtype dname##_pop_back(dname##_deq * deq) {                                 \
        if (deq->size == 0) exit(1);                                                          \
        dname##_deq_item * old_back_item = deq->back;                                         \
        dtype value = old_back_item->data;                                                    \
        if (deq->size == 1) {                                                                 \
            deq->front = deq->back = NULL;                                                    \
        } else {                                                                              \
            deq->back = old_back_item->next;                                                  \
            deq->back->prev = NULL;                                                           \
        }                                                                                     \
        dname##_destroy_item(old_back_item);                                                  \
        deq->size -= 1;                                                                       \
        return value;                                                                         \
    }                                                                                         \
                                                                                              \
    inline static bool dname##_empty(dname##_deq * deq) {                                     \
        return (deq->size == 0);                                                              \
    }                                                                                         \
                                                                                              \
    inline static size_t dname##_size(dname##_deq * deq) {                                    \
        return deq->size;                                                                     \
    }                                                                                         \
                                                                                              \
    inline static void dname##_status(dname##_deq * deq, FILE * stream) {                     \
        if (dname##_empty(deq)) { fprintf(stream, "empty\n"); return; }                       \
        fprintf(stream, "BACK: Addres: %p Value: %d Prev: %p Next: %p\n",                     \
            deq->back, (dtype)deq->back->data,                                                \
            deq->back->prev, deq->back->next);                                                \
        fprintf(stream, "FRONT: Addres: %p Value: %d Prev: %p Next: %p\n",                    \
            deq->front, (dtype)deq->front->data,                                              \
            deq->front->prev, deq->front->next);                                              \
    }                                                                                         \

#endif // end of Z_DEQ_HPP
