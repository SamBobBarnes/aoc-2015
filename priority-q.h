//
// Created by sb17057 on 5/12/2026.
//

#ifndef PRIORITY_Q_H
#define PRIORITY_Q_H

#define MAX 10000

/// @brief Represents an item with a priority
typedef struct PriorityItem PriorityItem;


/// @brief Represents a priority sorted queue
typedef struct PriorityQueue PriorityQueue;

/// @param pq
/// @param value
/// @remark
/// Enqueue item with a priority
void enqueue(PriorityQueue *pq, const PriorityItem *value);

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
/// Checks if priority queue is empty
bool is_empty(const PriorityQueue *pq);

/// @param item
/// @remark
/// Free the memory of the item and its pointer
void free_item(PriorityItem *item);

/// @param pq
/// @remark
/// Free the memory of all contained pointers
void free_content(PriorityQueue *pq);

/// @param inverse
///  If true, the smallest value is prioritized, else the largest value is prioritized
/// @remark
/// Create the priority queue
PriorityQueue *create_priority_queue(bool inverse);

/// @param priority
/// The priority used to sort the item in the queue
/// @param value
/// The pointer to the object being prioritized
/// @remark
/// Create a new PriorityItem
PriorityItem *new_pq_item(int priority, void *value);

#endif //PRIORITY_Q_H
