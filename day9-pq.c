//
// Created by Samuel Barnes on 4/12/26.
//
#include <stdio.h>
#include "day9-pq.h"

// Define swap function to swap two integers
void swap(ItemPriority *a, ItemPriority *b) {
    ItemPriority temp = *a;
    *a = *b;
    *b = temp;
}

// Define heapifyUp function to maintain heap property
// during insertion
void heapifyUp(PriorityQueue *pq, const int index) {
    if (index
        && pq->items[(index - 1) / 2].priority > pq->items[index].priority) {
        swap(&pq->items[(index - 1) / 2],
             &pq->items[index]);
        heapifyUp(pq, (index - 1) / 2);
    }
}

// Define enqueue function to add an item to the queue
void enqueue(PriorityQueue *pq, const ItemPriority value) {
    if (pq->size == MAX) {
        printf("Priority queue is full\n");
        return;
    }

    pq->items[pq->size++] = value;
    heapifyUp(pq, pq->size - 1);
}

// Define heapifyDown function to maintain heap property
// during deletion
void heapifyDown(PriorityQueue *pq, const int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < pq->size
        && pq->items[left].priority < pq->items[smallest].priority)
        smallest = left;

    if (right < pq->size
        && pq->items[right].priority < pq->items[smallest].priority)
        smallest = right;

    if (smallest != index) {
        swap(&pq->items[index], &pq->items[smallest]);
        heapifyDown(pq, smallest);
    }
}

// Define dequeue function to remove an item from the queue
ItemPriority dequeue(PriorityQueue *pq) {
    if (!pq->size) {
        printf("Priority queue is empty\n");
        return (ItemPriority){-1, -1};
    }

    ItemPriority item = pq->items[0];
    pq->items[0] = pq->items[--pq->size];
    heapifyDown(pq, 0);
    return item;
}

// Define peek function to get the top item from the queue
ItemPriority peek(const PriorityQueue *pq) {
    if (!pq->size) {
        printf("Priority queue is empty\n");
        return (ItemPriority){-1, -1};
    }
    return pq->items[0];
}
