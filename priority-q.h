//
// Created by sb17057 on 5/12/2026.
//

#ifndef PRIORITY_Q_H
#define PRIORITY_Q_H

#define MAX 10000

/// @brief Represents an item with a priority
typedef struct {
    /// Pointer to the prioritized item
    void *value;
    /// The priority used to sort the item in the queue
    int priority;
} PriorityItem;


/// @brief Represents a priority sorted queue
typedef struct PriorityQueue PriorityQueue;

/// @param pq
/// @param value
/// @remark
/// Enqueue item with a priority
void enqueue(PriorityQueue *pq, PriorityItem value);

/// @param pq
/// @remark
/// Dequeue item with most important priority
PriorityItem dequeue(PriorityQueue *pq);

/// @param pq
/// @remark
/// Peek item with most important priority without removing from queue
PriorityItem peek(const PriorityQueue *pq);

/// @param pq
/// @remark
/// Free the memory of all contained pointers
void free_content(PriorityQueue *pq);

#endif //PRIORITY_Q_H
