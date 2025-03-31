#ifndef Z_DEQ_HPP_
#define Z_DEQ_HPP_

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define Z_DEQ(dtype, dname)                                                                   \
    typedef struct dname##_item_ {                                                            \
        dtype data;                                                                           \
        struct deq_dname##_item_ * next;                                                      \
        struct deq_dname##_item_ * prev;                                                      \
    } dname##_item;                                                                           \
                                                                                              \
    typedef struct dname##_ {                                                                 \
        dname##_item * front;                                                                 \
        dname##_item * back;                                                                  \
        size_t size;                                                                          \
    } dname;                                                                                  \
                                                                                              \
                                                                                              \
    inline static dname * dname##_create() {                                                  \
        dname * deq = (dname *) malloc(sizeof(dname));                                        \
        deq->front = NULL;                                                                    \
        deq->back = NULL;                                                                     \
        deq->size = 0;                                                                        \
        return deq;                                                                           \
    }                                                                                         \
    inline static void dname##_push_first(dname * deq, dtype value) {                         \
        dname##_item * new_item = (dname##_item *) malloc(sizeof(dname##_item));              \
        new_item->data = value;                                                               \
        new_item->next = new_item->prev = NULL;                                               \
        deq->front = deq->back = new_item;                                                    \
        deq->size += 1;                                                                       \
    }                                                                                         \
                                                                                              \
    inline static void dname##_push_front(dname * deq, dtype value) {                         \
        if (deq->size == 0) { dname##_push_first(deq, value); return; }                       \
        dname##_item * new_item = (dname##_item *) malloc(sizeof(dname##_item));              \
        dname##_item * old_item = deq->front;                                                 \
        new_item->data = value;                                                               \
        new_item->next = NULL;                                                                \
        new_item->prev = old_item;                                                            \
        old_item->next = new_item;                                                            \
        deq->front = new_item;                                                                \
        deq->size += 1;                                                                       \
    }                                                                                         \
                                                                                              \
    inline static void dname##_push_back(dname * deq, dtype value) {                          \
        if (deq->size == 0) { dname##_push_first(deq, value); return; }                       \
        dname##_item * new_item = (dname##_item *) malloc(sizeof(dname##_item));              \
        dname##_item * old_item = deq->back;                                                  \
        new_item->data = value;                                                               \
        new_item->next = old_item;                                                            \
        new_item->prev = NULL;                                                                \
        old_item->prev = new_item;                                                            \
        deq->back = new_item;                                                                 \
        deq->size += 1;                                                                       \
    }                                                                                         \
                                                                                              \
    inline static void dname##_destroy_item(dname##_item * item) {                            \
        free(item);                                                                           \
    }                                                                                         \
                                                                                              \
    inline static void dname##_destroy(dname * deq) {                                         \
        dname##_item * item = deq->back;                                                      \
        while (item != NULL) {                                                                \
            dname##_item * next_item = item->next;                                            \
            dname##_destroy_item(item);                                                       \
            item = next_item;                                                                 \
        }                                                                                     \
        free(deq);                                                                            \
    }                                                                                         \
                                                                                              \
    inline static dtype dname##_pop_front(dname * deq) {                                      \
        if (deq->size == 0) exit(1);                                                          \
        dname##_item * old_front_item = deq->front;                                           \
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
    inline static dtype dname##_pop_back(dname * deq) {                                       \
        if (deq->size == 0) exit(1);                                                          \
        dname##_item * old_back_item = deq->back;                                             \
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
    inline static bool dname##_empty(dname * deq) {                                           \
        return (deq->size == 0);                                                              \
    }                                                                                         \
                                                                                              \
    inline static size_t dname##_size(dname * deq) {                                          \
        return deq->size;                                                                     \
    }                                                                                         \
                                                                                              \
    inline static void dname##_status(dname * deq, FILE * stream) {                           \
        if (dname##_empty(deq)) { fprintf(stream, "empty\n"); return; }                       \
        fprintf(stream, "BACK: Addres: %p Value: %d Prev: %p Next: %p\n",                     \
            deq->back, (dtype)deq->back->data,                                                \
            deq->back->prev, deq->back->next);                                                \
        fprintf(stream, "FRONT: Addres: %p Value: %d Prev: %p Next: %p\n",                    \
            deq->front, (dtype)deq->front->data,                                              \
            deq->front->prev, deq->front->next);                                              \
    }                                                                                         \

#endif // end of Z_DEQ_HPP
