//
// Created by sb17057 on 5/12/2026.
//

#include "priority-q.h"

#include <stdio.h>
#include <stdlib.h>


struct PriorityItem {
    /// Pointer to the prioritized item
    void *value;
    /// The priority used to sort the item in the queue
    int priority;
};

struct PriorityQueue {
    /// Items contained in the queue
    PriorityItem items[MAX];
    /// Current size of the queue
    int size;
    /// If true, the smallest value is prioritized, if false, the largest value is prioritized
    bool inverse;
};

PriorityQueue *create_priority_queue(const bool inverse) {
    const auto pq = (PriorityQueue *) malloc(sizeof(PriorityQueue));
    pq->inverse = inverse;
    return pq;
}


void swap(PriorityItem *a, PriorityItem *b) {
    const PriorityItem temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUp(PriorityQueue *pq, const int index) {
    if (index
        && ((!pq->inverse && pq->items[(index - 1) / 2].priority > pq->items[index].priority) || (
                pq->inverse && pq->items[(index - 1) / 2].priority < pq->items[index].priority))) {
        swap(&pq->items[(index - 1) / 2],
             &pq->items[index]);
        heapifyUp(pq, (index - 1) / 2);
    }
}

void enqueue(PriorityQueue *pq, const PriorityItem value) {
    if (pq->size == MAX) {
        printf("Priority queue is full\n");
        return;
    }

    pq->items[pq->size++] = value;
    heapifyUp(pq, pq->size - 1);
}

void heapifyDown(PriorityQueue *pq, const int index) {
    int smallest = index;
    const int left = 2 * index + 1;
    const int right = 2 * index + 2;

    if (left < pq->size
        && ((!pq->inverse && pq->items[left].priority < pq->items[smallest].priority) || (
                pq->inverse && pq->items[left].priority > pq->items[smallest].priority)))
        smallest = left;

    if (right < pq->size
        && ((!pq->inverse && pq->items[right].priority < pq->items[smallest].priority) || (
                pq->inverse && pq->items[right].priority > pq->items[smallest].priority)))
        smallest = right;

    if (smallest != index) {
        swap(&pq->items[index], &pq->items[smallest]);
        heapifyDown(pq, smallest);
    }
}

PriorityItem dequeue(PriorityQueue *pq) {
    if (!pq->size) {
        printf("Priority queue is empty\n");
        return (PriorityItem){nullptr, -1};
    }

    PriorityItem item = pq->items[0];
    pq->items[0] = pq->items[--pq->size];
    heapifyDown(pq, 0);
    return item;
}

PriorityItem peek(const PriorityQueue *pq) {
    if (!pq->size) {
        printf("Priority queue is empty\n");
        return (PriorityItem){nullptr, -1};
    }
    return pq->items[0];
}

void free_content(PriorityQueue *pq) {
    if (pq->size > 0) {
        for (int i = 0; i < MAX; i++) {
            free(pq->items[i].value);
        }
    }
    free(pq->items);
    free(pq);
}
