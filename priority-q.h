//
// Created by sb17057 on 5/12/2026.
//

#ifndef PRIORITY_Q_H
#define PRIORITY_Q_H


/// @brief Represents an item with a priority
typedef struct {
    /// Pointer to the prioritized item
    void *value;
    /// The priority used to sort the item in the queue
    int priority;
} PriorityItem;


/// @brief Represents a priority sorted queue
typedef struct {
    /// Current size of the queue
    int size;
    /// If true, the largest value is prioritized, if false, the smallest value is prioritized
    bool inverse;
    int max_size;
    /// Items contained in the queue
    PriorityItem *items;
} PriorityQueue;

/// @param pq
/// @param value
/// @remark
/// Enqueue item with a priority
void enqueue(PriorityQueue *pq, PriorityItem value);

/// @param pq
/// @remark
/// Dequeue item with most important priority
void *dequeue(PriorityQueue *pq);

/// @param pq
/// @remark
/// Peek item with most important priority without removing from queue
void *peek(const PriorityQueue *pq);

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

/// @param size
/// Max item size in queue
/// @param inverse
///  If true, the smallest value is prioritized, else the largest value is prioritized
/// @remark
/// Create the priority queue
PriorityQueue create_priority_queue(int size, bool inverse);

/// @param priority
/// The priority used to sort the item in the queue
/// @param value
/// The pointer to the object being prioritized
/// @remark
/// Create a new PriorityItem
PriorityItem new_pq_item(int priority, void *value);

#endif //PRIORITY_Q_H
