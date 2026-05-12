//
// Created by Samuel Barnes on 4/12/26.
//
#include <stdio.h>
#include "day9-pq.h"

// Define swap function to swap two integers
void d9swap(D9ItemPriority *a, D9ItemPriority *b) {
    D9ItemPriority temp = *a;
    *a = *b;
    *b = temp;
}

// Define heapifyUp function to maintain heap property
// during insertion
void d9heapifyUp(D9PriorityQueue *pq, const int index) {
    if (index
        && ((!pq->inverse && pq->items[(index - 1) / 2].priority > pq->items[index].priority) || (
                pq->inverse && pq->items[(index - 1) / 2].priority < pq->items[index].priority))) {
        d9swap(&pq->items[(index - 1) / 2],
             &pq->items[index]);
        d9heapifyUp(pq, (index - 1) / 2);
    }
}

// Define enqueue function to add an item to the queue
void d9enqueue(D9PriorityQueue *pq, const D9ItemPriority value) {
    if (pq->size == MAX) {
        printf("Priority queue is full\n");
        return;
    }

    pq->items[pq->size++] = value;
    d9heapifyUp(pq, pq->size - 1);
}

// Define heapifyDown function to maintain heap property
// during deletion
void d9heapifyDown(D9PriorityQueue *pq, const int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < pq->size
        && ((!pq->inverse && pq->items[left].priority < pq->items[smallest].priority) || (
                pq->inverse && pq->items[left].priority > pq->items[smallest].priority)))
        smallest = left;

    if (right < pq->size
        && ((!pq->inverse && pq->items[right].priority < pq->items[smallest].priority) || (
                pq->inverse && pq->items[right].priority > pq->items[smallest].priority)))
        smallest = right;

    if (smallest != index) {
        d9swap(&pq->items[index], &pq->items[smallest]);
        d9heapifyDown(pq, smallest);
    }
}

// Define dequeue function to remove an item from the queue
D9ItemPriority d9dequeue(D9PriorityQueue *pq) {
    if (!pq->size) {
        printf("Priority queue is empty\n");
        return (D9ItemPriority){-1, -1};
    }

    D9ItemPriority item = pq->items[0];
    pq->items[0] = pq->items[--pq->size];
    d9heapifyDown(pq, 0);
    return item;
}

// Define peek function to get the top item from the queue
D9ItemPriority d9peek(const D9PriorityQueue *pq) {
    if (!pq->size) {
        printf("Priority queue is empty\n");
        return (D9ItemPriority){-1, -1};
    }
    return pq->items[0];
}
