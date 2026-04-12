//
// Created by Samuel Barnes on 4/12/26.
//

#ifndef AOC_2015_DAY9_PQ_H
#define AOC_2015_DAY9_PQ_H

// Define maximum size of the priority queue
#define MAX 100

// Define PriorityQueue structure
typedef struct {
    int items[MAX];
    int size;
} PriorityQueue;

void enqueue(PriorityQueue* pq, int value);
int dequeue(PriorityQueue* pq);
int peek(const PriorityQueue* pq);

#endif //AOC_2015_DAY9_PQ_H
