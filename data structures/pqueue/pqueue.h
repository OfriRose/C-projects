/*
    Developer: Ofri Rozner
    Reviwer: Romi Kamin
    Date: 26/09/23
    pqueue - h file
*/
    
/*
*DESCRIPTION:
*An API for a priority list data structure. 
*priority list stores data elements in a sorted order according to  a user-defined 
*priority function so every element is linked to the next and previous one.
*core features: Enqueue, Dequeue, Peek.
*behaviour: sequential access, stable sorting.
*/

#ifndef __ILRD_OL149_PQUEUE_H__
#define __ILRD_OL149_PQUEUE_H__

#include <stddef.h> /* size_t */
#include "../sorted_list/sorted_list.h"

typedef struct pqueue pqueue_t;

/**
 * @brief a user defined function to determine an element's priority in queue.
 * @return An integer representing the comparison result:
 *         - Negative value if target is less than source.
 *         - Zero if target is equal to source.
 *         - Positive value if target is greater than source.
 * @complexity Time Complexity: O(1), Space Complexity: O(1)
 */
typedef int (*cmp_func_t)(const void *target, const void *source);

/**
 * @brief a user defined function to check if 2 element match.
 * @complexity Time Complexity: O(1), Space Complexity: O(1)
 */
typedef int (*match_func_t)(const void *data, void *param);

/**
 * @brief Creates a new priority queue.
 *
 * This function creates a new priority queue and returns a refrence to it. 
 *
 * @param cmp_func A comparison function used to determine the priority of
 * elements in the queue.
 * @return A pointer to the newly created priority queue.
 *
 * @note: The queue is initialized as empty.
 * @note: use PQDestroy to clen the queue from memory after use
 *
 * @complexity Time: O(1), Space: O(1)
 */
pqueue_t *PQCreate(cmp_func_t cmp_func);

/**
 * @brief Destroys the priority queue and clean it from memory.
 *
 * This function deallocates all the memory associated with the priority queue 
 * and its elements. After calling this function, the priority queue becomes invalid.
 *
 * @param pq A refrence to the priority queue to be destroyed.
 * @complexity Time: O(n), Space: O(1)
 */
void PQDestroy(pqueue_t *pq);

/**
 * @brief Inserts an element into the priority queue.
 *
 * @param pq A refrence to the priority queue.
 * @param data A refrence to the data to be inserted.
 * @return 0 on success, -1 on failure.
 * @note If the comparison function returns zero, the element to be inserted 
 * will take the position after the existing element, ensuring stable insertion.
 * @note Data that does not agree with cmp_func_t will result in an undefined 
 * behavior.
 * @note a Null Prio. queue or data will result in an undefined behavior.
 * @complexity Time: O(1), Space: O(1)
 */
int PQEnqueue(pqueue_t *pq, void *data);

/**
 * @brief Removes and returns the highest-priority element from the priority queue.
 *
 * @param pq A refrence to the priority queue.
 * @return A refrence to the removed element.
 * @note Undefined behavior if the priority queue is empty.
 * @complexity Time: O(1), Space: O(1)
 */
void *PQDequeue(pqueue_t *pq);

/**
 * @brief Returns the data of the highest-priority element int priority queue.
 *
 * @param pq A refrence to the priority queue.
 * @return A refrence to the highest-priority element's data.
 * @note Undefined behavior if the queue is empty.
 * @complexity Time: O(1), Space: O(1)
 */
void *PQPeek(const pqueue_t *pq);

/**
 * @brief Returns the number of elements in the priority queue.
 *
 * @param pq A refrence to the priority queue.
 * @return The number of elements in the priority queue.
 * @return Size of the priority queue.
 * @complexity Time: O(n), Space: O(1)
 */
size_t PQSize(const pqueue_t *pq);

/**
 * @brief Checks if the priority queue is empty.
 *
 * @param pq A refrence to the priority queue.
 * @return 1 if the priority queue is empty, 0 otherwise.
 * @complexity Time: O(1), Space: O(1)
 */
int PQIsEmpty(const pqueue_t *pq);

/**
 * @brief Clears all elements from the priority queue, while not destroying it
 *
 * @param pq A refrence to the priority queue.
 * @complexity Time: O(n), Space: O(1)
 */
void PQClear(pqueue_t *pq);

/**
 * @brief Removes the first element that matches the given criteria.
 *
 * @param pq A pointer to the priority queue.
 * @param match_func A function used to determine if an element matches the criteria.
 * @param param A parameter to be passed to the match function.
 * @return A refrence to the removed element if found, otherwise NULL.
 * @return the removed element's data if found. Otherwise, returns NULL.
 * @note Undefined behavior undefined if the priority queue is empty.
 * @complexity Time: O(n), Space: O(1)
 */
void *PQErase(pqueue_t *pq, match_func_t match_func, void *param);

#endif /* __ILRD_OL149_PQUEUE_H__ */
