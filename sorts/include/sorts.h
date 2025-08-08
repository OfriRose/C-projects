
/*
    Developer: Ofri Rozner
    Reviwer: Yael Hava
    Date: 12/11/23
    sorts - h file
*/

/*
Description: an API for searching and sorting arrays
*/

#ifndef __ILRD_OL149_H_SORTS__
#define __ILRD_OL149_H_SORTS__


#include <stddef.h>


/**
 *@brief search element in an array using binary search
 *@param arr an array of inergers
 *@size number of elements in the array
 *@target value to find
 *@return the sought value, or -1 on failure
 *@complexity: Time O(log n), Space  O(1)
 */
int BinarySearchIter(int *arr, int size, int target);

/**
 * @brief Performs a recursive binary search on a sorted array.
 * @param arr The sorted array to search.
 * @param min The leftmost index of the search range.
 * @param max The rightmost index of the search range.
 * @param target The target value to search for.
 * @return the sought value, or -1 on failure
 * @complexity: Time O(log n), Space  O(1)
 */

int BinarySearchRec(int *arr, int min, int max, int target);

/**
 * @brief Performs the merge sort algorithm on an array.
 * @param arr_to_sort The array to be sorted.
 * @param num_elements The number of elements in the array.
 * @return 0 on success, non-zero on failure.
 * @complexity: Time O(n*log n), Space  O(n)
 */
int MergeSort(int *arr_to_sort, size_t num_elements); 

/**
 * @brief Performs the quicksort algorithm on an array.
 * @param base The base address of the array.
 * @param nmemb The number of members in the array.
 * @param size The size of each member in the array.
 * @param compar The comparison function to determine the order of elements.
 * @complexity: Time: O(n log n) on average, O(n^2) in the worst case, 
 *              Space O(log n) on average, O(n) in the worst case.
 */
void QSort(void *base, size_t nmemb, size_t size, 
                                    int (*compar)(const void *, const void *));


#endif /* __ILRD_OL149_H_SORTS__ */

