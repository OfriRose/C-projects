
/*-----------------------------------------------------------/
 *  Developer: Ofri Rozner									*
 *  Reviwer:    								*
 *  Date: 22/10/23											*
 *  cmp_sort - h file					    				*
------------------------------------------------------------*/

#ifndef __ILRD_OL149_H_CMP_SORT__
#define __ILRD_OL149_H_CMP_SORT__

/* ------------------------- Preprocessor Directives ------------------------ */

#include <stddef.h>

/* --------------------------- Function Definition -------------------------- */

/**
 * @brief sorts an interger array in ascending order using bubble sort algorithm
 * @param arr   refrence to the array to be sorted.
 * @param size  size of the array.
 * @complexity Time: O(n^2), Space: O(1)
 *  */
void BubbleSort(int *arr, size_t size);

/**
 * @brief sorts an interger array in ascending order using  insertion algorithm
 * @param arr   refrence to the array to be sorted.
 * @param size  size of the array.
 * @complexity  Time: O(n^2), Space: O(1)
 */
void InsertionSort(int *arr, size_t size);

/**
 * @brief sorts an interger array in ascending order using selection algorithm
 * @param arr   refrence to the array to be sorted.
 * @param size  size of the array.
 * @complexity Time: O(n^2), Space: O(1)
 */
void SelectionSort(int *arr, size_t size);


#endif /* __ILRD_OL149_H_CMP_SORT__ */
