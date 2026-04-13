//
// Created by Samuel Barnes on 4/12/26.
//

#ifndef AOC_2015_DAY9_PQ_H
#define AOC_2015_DAY9_PQ_H

// Define maximum size of the priority queue
#define MAX 1000

typedef struct {
    int visited_ids[8];
    int visited_count;
} History;

typedef struct {
    int priority;
    int id;
    History visited;
} ItemPriority;

// Define PriorityQueue structure
typedef struct {
    ItemPriority items[MAX];
    int size;
    bool inverse;
} PriorityQueue;

void enqueue(PriorityQueue *pq, ItemPriority value);

ItemPriority dequeue(PriorityQueue *pq);

ItemPriority peek(const PriorityQueue *pq);

#endif //AOC_2015_DAY9_PQ_H
