#ifndef __ILRD_OL149_H_HEAP__
#define __ILRD_OL149_H_HEAP__

#include <stddef.h>

typedef struct heap heap_t;

typedef int(*heap_cmp_func_t)(const void *data, const void *base_data);
typedef int(* heap_match_func_t)(void *data, const void *base_data)

/**
 * @complexity Time: O(1), Space: O(1)
 */
heap_t *HeapCreate(heap_cmp_func_t cmp_func);

/**
 * @complexity Time: O(1), Space: O(1)
 */
void HeapDestroy(heap_t *heap);

/**
 * @return 0 on success, -1 on failure.
 * @complexity Time: O(log n) - average, O(n) - worst, Space: O(1)
 */
int HeapPush(heap_t *heap, void *element);

/**
 * @return The root element on success, -1 on failure.
 * @complexity Time: O(log n) - average, O(n) - worst, Space: O(1)
 */
void HeapPop(heap_t *heap);

/**
 * @complexity Time: O(1), Space: O(1)
 */
void *HeapPeek(const heap_t *heap);

/**
 *@note Remove the first element the function finds.
 * @complexity Time: O(log n) - average, O(n) - worst, Space: O(1)
 */
void *HeapRemove(heap_t *heap, heap_match_func_t match_func, void *data, const void *base_data);

/**
 * @complexity Time: O(1), Space: O(1)
 */
int HeapIsEmpty(heap_t *heap);

/**
 * @complexity Time: O(n), Space: O(1)
 */
size_t HeapSize(heap_t *heap);

#endif /* __ILRD_OL149_H_HEAP__ */
