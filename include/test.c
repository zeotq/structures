#include "Deque.h"
#include <stdlib.h>
#include <stdio.h>

Z_DEQ(int)

inline static void int_deque_values(int_deq * deq, FILE * stream) {\
    int_deq_item * item = deq->back;                                                  
    while (item != NULL) {                                                                
        int_deq_item * next_item = item->next;                                        
        fprintf(stream, "%d\n", item->data);
        item = next_item;                                                                 
    }                                                                                     
}

int main() {
    int_deq * deq = create();
    int value;
    int_deque_status(deq, stdout);
    int_deque_push_front(deq, 1488);
    int_deque_pop_back(deq);

    int_deque_push_front(deq, 5);
    int_deque_push_back(deq, 1);
    int_deque_push_front(deq, 6);
    int_deque_push_front(deq, 7);
    int_deque_pop_back(deq);
    int_deque_push_back(deq, 2);
    int_deque_pop_front(deq);

    int_deque_status(deq, stdout);
    int_deque_values(deq, stdout);
    int_deque_destroy(deq);
}

