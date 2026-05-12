//
// Created by sb17057 on 5/12/2026.
//

#ifndef PRIORITY_Q_H
#define PRIORITY_Q_H

#define MAX 10000

typedef struct {
    void *value;
    int priority;
} PriorityItem;

typedef struct {
    PriorityItem items[MAX];
    int size;
    bool inverse;
} PriorityQueue;

void enqueue(PriorityQueue *pq, PriorityItem value);

PriorityItem dequeue(PriorityQueue *pq);

PriorityItem peek(const PriorityQueue *pq);

void free_content(PriorityQueue *pq);

#endif //PRIORITY_Q_H
