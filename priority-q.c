//
// Created by sb17057 on 5/12/2026.
//

#include "priority-q.h"

#include <stdio.h>
#include <stdlib.h>


PriorityQueue create_priority_queue(const int size, const bool inverse) {
    PriorityQueue pq;
    pq.items = malloc(sizeof(PriorityItem) * size);
    pq.size = 0;
    pq.max_size = size;
    pq.inverse = inverse;
    return pq;
}

PriorityItem new_pq_item(const int priority, void *value) {
    PriorityItem item;
    item.value = value;
    item.priority = priority;
    return item;
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

bool is_empty(const PriorityQueue *pq) {
    return pq->size == 0;
}

void enqueue(PriorityQueue *pq, const PriorityItem value) {
    if (pq->size == pq->max_size) {
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

void *dequeue(PriorityQueue *pq) {
    if (!pq->size) {
        printf("Priority queue is empty\n");
        return NULL;
    }

    PriorityItem item = pq->items[0];
    pq->items[0] = pq->items[--pq->size];
    heapifyDown(pq, 0);
    return item.value;
}

void *peek(const PriorityQueue *pq) {
    if (!pq->size) {
        printf("Priority queue is empty\n");
        return NULL;
    }
    return pq->items[0].value;
}

void free_item(PriorityItem *item) {
    free(item->value);
}

void free_content(PriorityQueue *pq) {
    if (pq->size > 0) {
        for (int i = 0; i < pq->size; i++) {
            free_item(&pq->items[i]);
        }
    }
    free(pq->items);
}

