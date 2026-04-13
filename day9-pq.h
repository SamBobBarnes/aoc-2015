//
// Created by Samuel Barnes on 4/12/26.
//

#ifndef AOC_2015_DAY9_PQ_H
#define AOC_2015_DAY9_PQ_H

// Define maximum size of the priority queue
#define MAX 100


typedef struct {
    int priority;
    int id;
} ItemPriority;

// Define PriorityQueue structure
typedef struct {
    ItemPriority items[MAX];
    int size;
} PriorityQueue;

void enqueue(PriorityQueue *pq, ItemPriority value);

ItemPriority dequeue(PriorityQueue *pq);

ItemPriority peek(const PriorityQueue *pq);

#endif //AOC_2015_DAY9_PQ_H
