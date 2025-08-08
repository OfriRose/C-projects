/*
-------------------------------------------------------------------------------
*
*	Filename:		dlist.h
*	Owner:			Ofri Rozner
*	Date:			10/09/23
*	Course:			OL-149
*	reviewer:		Amitai Milshtain
*	Description:	Doubly Linked List data structure
	Notes:			
*	
------------------------------------------------------------------------------
*/

/*DESCRIPTION:
API provides functionality for creating, managing, and manipulating doubly
 linked lists.
 A doubly linked list is a linear data structure where elements are connected
 by refrences to previous and next element.
 policy: sequantial access, data storage by refrence
 */

#ifndef __ILRD_OL149_H_DLIST__
#define __ILRD_OL149_H_DLIST__ 

#include <stddef.h>

/**
*A function pointer used for matching elements in the list.
*should return 1 for match, 0 otherwise.
*/
typedef int (*dlist_is_match_func_t)(const void *data, void *param);

/* document the function pointer and guide the user for correct implementation*/
typedef int (*dlist_action_func_t)(void *data, void *param);


/* ----------- Structs Declerations ------------- */

typedef struct dlist dlist_t; 
typedef struct dlist_node *dlist_iter_t; 


/* ----------- Functions Declerations ------------- */

/**
*Creates a new doubly linked list.
*@Returns a pointer to the created list.
Time complexity O(1), Space complexity O(1)*/
dlist_t *DListCreate(void);

/**
*Destroys a doubly linked list and frees all associated memory.
*@param list: A pointer to the list to be destroyed.
Time complexity O(n), Space complexity O(n)*/
void DListDestroy(dlist_t *list);

/**
*Inserts a new element with the given data before the specified iterator 'where'.
*@param list: The list in which to insert the element.
*@param where: The iterator before which to insert the element.
*@param data: A pointer to the data to be inserted.
*@Returns an iterator pointing to the newly inserted element.
Time complexity O(1), Space complexity O(1)*/
dlist_iter_t DListInsertBefore(dlist_t *list, dlist_iter_t where, void *data);

/**
*insert a new alement to the back of the list
*@param list a doubly linked list
*@param data the element's data to store
Time complexity O(1) */ 
dlist_iter_t DListPushBack(dlist_t *list, void *data);

/**
*insert a new alement to the front of the list
*@param list a doubly linked list
*@param data the element's data to store*/
/* Time complexity O(1) */ 
dlist_iter_t DListPushFront(dlist_t *list, void *data);

/**
*remove an element
*@param iter a refrence to the element
*@Return the element foloowing the one that was removed*/
/* Time complexity O(1), Space complexity O(1)
Note: removing the end iterator in undefiend. */
dlist_iter_t DListRemove(dlist_iter_t iter);                      

/**
*removes an element from the back of the list
*@param list a doubly linked list
Time complexity O(1) 
Note: Use it on empty list is undefiend.*/
void *DListPopBack(dlist_t *list);

/**
*removes an element from the front of the list
*@param list a doubly linked list
Time complexity O(1) 
Note: Use it on empty list is undefiend.*/
void *DListPopFront(dlist_t *list);

/**
* Searches for an element in the list using a matching function and parameter.
* @param from An iterator pointing to the start of the search range.
* @param to An iterator pointing to the end of the search range.
* @param match_func A function pointer used to determine if an element matches.
* @param param A parameter passed to the matching function.
* @return An iterator pointing to the first matching element, or 'to' if not found.
Time complexity O(n), Space complexity O(1)*/   
dlist_iter_t DListFind(dlist_iter_t from, dlist_iter_t to,
                       dlist_is_match_func_t match_func, void *param);
                       
/**
*Searches for multiple elements in the list using a matching function and parameter.
* @param from An iterator pointing to the start of the search range.
* @param to An iterator pointing to the end of the search range.
* @param match_func A function pointer used to determine if an element matches.
* @param param A parameter passed to the matching function.
* @param output_list A pointer to a list where matching elements will be stored.
* @return The number of matching elements found.
* Time complexity: O(n).
Note: using from and to that arent part of same list is undefiend.*/
int DListMultiFind(dlist_iter_t from, dlist_iter_t to, 
           dlist_is_match_func_t match_func, void *param, dlist_t *output_list);

/**
*Applies an action function to elements in the list within the specified range.
*@param from An iterator pointing to the start of the range.
*@param to An iterator pointing to the end of the range.
*@param action_func A function pointer that performs an action on each element.
*@param param A parameter passed to the action function.
*@return The result of the last action function call, or 0 if all actions were successful.
Time complexity O(n), Space complexity O(n)
Note: Upon first failure of the action_func, ForEach is instantly terminated.*/
int DListForEach(dlist_iter_t from, dlist_iter_t to,
            dlist_action_func_t action_func, void *param); 


/**
*Moves elements from one range in the list to another position specified by 'where'.
*
*@param from An iterator pointing to the start of the source range.
*@param to An iterator pointing to the end of the source range.
*@param where An iterator pointing to the destination position.
*@return An iterator pointing to 'where' after the elements have been moved.
*Time complexity O(1) 
Note: using from and to that arent part of same list is undefiend.
	  where that located in the same list and between from and to us undefiend*/ 
dlist_iter_t DListSplice(dlist_iter_t from, dlist_iter_t to, dlist_iter_t where);       

/**
* Returns the number of elements in the list.
*@param list A pointer to the doubly linked list.
*@return The number of elements in the list.
*Time complexity O(n), Space complexity O(1)*/
size_t DListCount(const dlist_t *list);        

/**
* Checks if the list is empty.
* @param list A pointer to the doubly linked list.
* @return 1 if the list is empty, 0 if it is not.
*Time complexity O(1), Space complexity O(1)*/    
int DListIsEmpty(const dlist_t *list);    


/**
*Retrieves the data stored at the specified iterator.
*@param iter An iterator pointing to the desired element.
*@return A pointer to the data stored at the iterator.
Time complexity: O(1) 
Note: Use it on end iterator is undefiend.*/
void *DListGetData(dlist_iter_t iter);
    
/**
*Sets the data stored at the specified iterator.
*@param iter An iterator pointing to the element to be modified.
*@param data A pointer to the new data to be set.
*@return An iterator pointing to the modified element.    
*Time complexity O(1)
Note: Use it on end iterator is undefiend.*/ 
dlist_iter_t DListSetData(dlist_iter_t iter, void *data);

/**
*Returns an iterator pointing to the end of the list.
*@param list A pointer to the doubly linked list
*@return An iterator pointing to the end of the list.
Time complexity O(1) */ 
dlist_iter_t DListEnd(const dlist_t *list);

/**
*Returns an iterator pointing to the beginning of the list.
*@param list A pointer to the doubly linked list.
*@return An iterator pointing to the beginning of the list.
*Time complexity O(1) */ 
dlist_iter_t DListBegin(const dlist_t *list);

/**
*Returns an iterator pointing to the next element in the list.
*@param iter An iterator pointing to the current element.
*@return An iterator pointing to the next element in the list.
Time complexity: O(1) 
Note: Use it on end iterator is undefiend. */
dlist_iter_t DListNext(dlist_iter_t iter);
   
/**
*Returns an iterator pointing to the previous element in the list.
*@param iter An iterator pointing to the current element.
*@return An iterator pointing to the previous element in the list.
*@note Time complexity: O(1).   
Time complexity: O(1) 
Note: Use it on begin iterator is undefiend. */
dlist_iter_t DListPrev(dlist_iter_t iter);

/**
*Checks if two iterators point to the same element in the list.
*@param iter1 An iterator.
*@param iter2 An iterator.
*@return 1 if the iterators point to the same element, 0 otherwise.Time complexity O(1) */ 
int DListIsIterEqual(dlist_iter_t iter1, dlist_iter_t iter2); 

#endif /* __ILRD_OL149_DLIST__ */
