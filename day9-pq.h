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
} D9History;

typedef struct {
    int priority;
    int id;
    D9History visited;
} D9ItemPriority;

// Define PriorityQueue structure
typedef struct {
    D9ItemPriority items[MAX];
    int size;
    bool inverse;
} D9PriorityQueue;

void d9enqueue(D9PriorityQueue *pq, D9ItemPriority value);

D9ItemPriority d9dequeue(D9PriorityQueue *pq);

D9ItemPriority d9peek(const D9PriorityQueue *pq);

#endif //AOC_2015_DAY9_PQ_H
