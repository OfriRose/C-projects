/*
*    Developer: Ofri Rozner
*    Reviwer: 
*    Date: 12/09/23
*    sorted_list - src file
*******************************************************************************/

/*
*DESCRIPTION:
*An API for a sorted list data structure. 
*sorted list stores data elements in a sorted order according to  a user-defined 
*function so every element is linked to the next and previous one.
*core features: insert, merge, foreach, find, findif.
*behaviour: sequential access, stable sorting.
*/

#ifndef __ILRD_OL149_H_SORTED_LIST__
#define __ILRD_OL149_H_SORTED_LIST__ 

#include "../dlist/dlist.h"

typedef int (*sorted_list_compare_func_t)(const void *base_val, const void *cmp_to);
typedef int (*sorted_list_is_match_func_t)(const void *data, void *param);
typedef int (*sorted_list_action_func_t)(void *data, void *param);

/* ----------- Structs Declerations ------------- */
typedef struct sorted_list sorted_list_t;
typedef struct sorted_list_iter
{
#ifndef NDEBUG
	sorted_list_t *list;
#endif
	dlist_iter_t iter; 
} sorted_list_iter_t;

/* ----------- Functions Declerations ------------- */

/**
*Creates a new sorted list.
*
* @param cmp_func The comparison function for sorting elements in the list.
* @return A refrence to the created list, or NULL if allocation fails.
*
 *@note: use SortedListDestroy() to clean the list from memory after use
*Time complexity O(1), Space Complexity O(1)
*/

sorted_list_t *SortedListCreate(sorted_list_compare_func_t cmp_func);

/**
* Destroys a sorted list and frees its resources.
* @param list a handle to the list to be destroyed.
*
*Time Complexity O(n), Space Complexity O(n)
*/
void SortedListDestroy(sorted_list_t *list);

/**
*nserts a new element into the sorted list.
*
*@param list a handle to the sorted list to insert into.
*@param data A pointer to the element to be inserted.
*@return A refrence pointing to the newly inserted element in the sorted list,
*or the list's tail if the function fails.
*Time Complexity O(n), Space Complexity O(1)
*/
sorted_list_iter_t SortedListInsert(sorted_list_t *list, void *data);

/**
* Removes an element from the sorted list.
*
* @param iter An iterator pointing to the element to be removed.
* @return An iterator pointing to the next element after the removed one.
*
*@note undefined behavior: remove from empty list. 
*
*Time Compliexity O(1), Space complexity O(1)
*/
sorted_list_iter_t SortedListRemove(sorted_list_iter_t iter);

/**
*Finds an element
*
* @param list a handle to the sorted list to search in.
* @param from An iterator pointing to the beginning of the search range.
* @param to An iterator pointing to the end of the search range.
* @param data A pointer to the data to be searched.
* @return A refrence to the found element, or 'to' if nothing found.
*
* @note undefined behavior if from and to are not in the same list
* @note undefined behavior if from is before to.
* Time Complexity O(n), Space Complexity O(1)
*/
sorted_list_iter_t SortedListFind(sorted_list_t *list, sorted_list_iter_t from, 
sorted_list_iter_t to, void *data);

/**
*Searches and returns an element in the sorted list based on a custom matching function.
*
* @param list a handle to the sorted list to search in.
* @param from An iterator pointing to the beginning of the search range.
* @param to An iterator pointing to the end of the search range.
* @param match_func The custom matching function to apply.
* @param param A parameter to pass to the matching function.
* @return An iterator pointing to the found element, or 'to' if not found.
*
* @note undefined behavior if from and to are not in the same list
* @note undefined behavior if from is before to.
*Time complexity O(n), Space comeplexity O(1)
*/
sorted_list_iter_t SortedListFindIf(sorted_list_iter_t from, 
sorted_list_iter_t to, sorted_list_is_match_func_t match_func, void *param);

/**
*Applies an action function to elements in a range of the sorted list.
*
* @param from An iterator pointing to the beginning of the range.
* @param to An iterator pointing to the end of the range.
* @param action_func The action function to apply.
* @param param A parameter to pass to the action function.
* @return 0 if the action function succeeds for all elements, non-zero otherwise.
*
* @note undefined behavior if from and to are not in the same list
* @note undefined behavior if from is before to.
*
* @complexity Time: O(n), Space: O(1)

 */
int SortedListForEach(sorted_list_iter_t from, sorted_list_iter_t to,
                 sorted_list_action_func_t action_func, void *param);

/**
* Removes and returns the first element from the sorted list.
*
* @param list The sorted list.
* @return A pointer to the removed data element.
*
*@note undefine behavior if pop from empty list
*Time Compleixty O(1) , Space Complexity O(1) 
 */
void *SortedListPopFront(sorted_list_t *list);

/**
* Removes and returns the last element from the sorted list.
*
* @param list The sorted list.
* @return A pointer to the removed data element.
*
*@note undefine behavior if pop from empty list
*Time Compleixty O(1) , Space Complexity O(1) 
 */
void *SortedListPopBack(sorted_list_t *list);

/**
*Merges two sorted lists into one.
*
*@param dest The destination sorted list.
*@param src The source sorted list to merge.
*
*@note function empties src after use.
*
*Time Compleixty O(n) , Space Complexity O(1)
*/

void SortedListMerge(sorted_list_t *dest, sorted_list_t *src);

/**
*Returns the number of elements in the sorted list.
*
*@param list The sorted list to count elements in.
*@return The number of elements in the sorted list.
*
*Time complexity O(n), Space complexity O(1)
*/
size_t SortedListCount(const sorted_list_t *list);        

/**
* @brief Checks if the sorted list is empty.
*
* @param list The sorted list to check.
* @return 1 if the list is empty, 0 otherwise.
*
* @complexity Time: O(1), Space: O(1)
*/
int SortedListIsEmpty(const sorted_list_t *list);   
 
/**
 * @brief Retrieves the data element at the current iterator position.
 *
 * @param iter The iterator to get data from.
 * @return A reference to the data element.
 *
 * @note undefined behaviour if recives the list's tail as argument
 *
 * @complexity Time: O(1), Space: O(1)
 */
void *SortedListGetData(sorted_list_iter_t iter);

/**
 * @brief Returns an iterator pointing to the end of the sorted list.
 *
 * @param list The sorted list.
 * @return An iterator pointing to the end of the list.
 *
 * @complexity Time: O(1), Space: O(1)
 */
sorted_list_iter_t SortedListEnd(const sorted_list_t *list);

/**
 * @brief Returns an iterator pointing to the start of the sorted list.
 *
 * @param list The sorted list.
 * @return An iterator pointing to the start of the list.
 *
 * @complexity Time: O(1), Space: O(1)
 */
sorted_list_iter_t SortedListBegin(const sorted_list_t *list);

/**
 * @brief Returns an iterator pointing to the next element in the sorted list.
 *
 * @param iter The current iterator.
 * @return An iterator pointing to the next element.
 *
 * @note undefined behaviour if recives the list's tail as argument
 *
 * @complexity Time: O(1), Space: O(1)
 */
sorted_list_iter_t SortedListNext(sorted_list_iter_t iter);

/**
 * @brief Returns an iterator pointing to the previous element in the sorted list.
 *
 * @param iter The current iterator.
 * @return An iterator pointing to the previous element.
 *
 * @note undefined behaviour if recives the list's head as argument
 *
 * @complexity Time: O(1), Space: O(1)
 */

sorted_list_iter_t SortedListPrev(sorted_list_iter_t iter);

/**
 * @brief Checks if two iterators are equal.
 *
 * @param iter1 The first iterator.
 * @param iter2 The second iterator.
 * @return 1 if the iterators are equal, 0 otherwise.
 * @complexity Time: O(1), Space: O(1)
 */
int SortedListIsIterEqual(sorted_list_iter_t iter1, sorted_list_iter_t iter2); 


#endif /* __ILRD_OL149_SORTED_LIST__ */
