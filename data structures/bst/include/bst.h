
/*
    Developer: Ofri Rozner
    Reviwer: Mentor
    Date: 24/10/23
    bst - header file
*/


/* 	DESCRIPTION:
	An API for a Binary Search Tree (BST) data structure.
	BST arranges element as a binary tree graph, so that the smaller value
	is always located to left of it's parent node and the larger value to the
	right. this allows for search and find operations to have a time complexity
	of O(log n). This API also allows for in-order iteration of the tree (O(n)
	sequential access).
	primary operations: insert, find, remove.
*/

#ifndef __ILRD_OL149_H_BST__
#define __ILRD_OL149_H_BST__

#include <stddef.h> /* size_t */

typedef struct bst bst_t;

typedef struct bst_node_t* bst_iter_t;

typedef struct bst_node bst_node_t;

/* User defined function to compare elements for correct implementetion of a binary tree
   Return 0 if data and param are equal, > 0 if param is bigger, < 0 if data is bigger
   - void *data: A reference to the data pointed to by an element in the tree.
   - void *param: A reference to an additional parameter of user's choice.
*/
typedef int (*bst_cmp_func_t)(const void *data, void *param);


/* Define a function that performs an action on data with a given parameter 
   Return type is a status int. returns 0 upon success and non zero upon failure
   - void *data: A reference to the data pointed to by an element in the list.
   - void *param: A reference to an additional parameter of user's choice.
*/
typedef int (*bst_callback_t)(void *data, void *param);

/** 
* @brief Create a binary search tree.
* @param cmp_func Comparison function for the BST.
* @return a newly created BST.
* @note cmp_func NULL will result in undefined behaviour
* @note Use BSTDestroy to clean memory after the bst is not needed
Time complexity O(1), Space Complexity O(1)*/
bst_t *BSTCreate(bst_cmp_func_t cmp_func);

/** 
* @brief Destroys bst, frees all memory allocated to it.
* @param bst bst to destroy.
* @note If bst is NULL, behaviour is undefined.
* Time Complexity O(n), Space O(n) */
void BSTDestroy(bst_t *bst);


/**
* @brief Inserts a new node to bst.
* @param bst bst to insert into.
* @param data data to insert to bst.
* @return the newly inserted element upon success, end upon failure. 
* @note inserting data that already exists leads to undefined behavior
* Average Time Complexity O(log n),
* Worst Case Time Complexity O(n)
* Space Complexity O(n) */
bst_iter_t BSTInsert(bst_t *bst, void *data);


/**
 * @brief Removes iter from it's bst, and frees the memory allocated to it.
 * @param iter iterator to bst node to remove.
 * @note deleting data that does not exist in the tree leads to undefined behavior
 * Average Time Complexity O(log n),
 * Worst Case Time Complexity O(n)
 * Space Complexity O(1) */
void BSTRemove(bst_iter_t iter);


/**
 * @brief Finds the node with value in bst and returns iterator to it.
 * @param bst bst to find value in.
  *@param data value to find.
 * @return iterator to wanted element on success. Root stub on failure.
 * Average Time Complexity O(log n),
 * Worst Case Time Complexity O(n)
 * Space Complexity O(1) 
 **/
bst_iter_t BSTFind(const bst_t *bst, void *data);


/** 
 * @brief Perform an action on data in each one of the nodes.
 * @param from an iterator to the first element in range
 * @param to an iterator to the last element (out of range)
 * @param callback_func user defined function to call
 * @param param parameter for the call back function
 * @return 0 on success, or a non-zero value provided by the action_func on the
 * first failure.
 * @note from and to must be both from same tree otherwise this may lead to undefined behavior 
 * @note from must be prev to 'to' otherwise this may lead to undefined behavior 
 * Time Complexity O(n)
 * Space Complexity O(1) 
*/
int BSTForEach(bst_iter_t from, bst_iter_t to,
               bst_callback_t callback_func, void *param);


/**
 * @brief check if the tree is empty
 * @param bst the tree to check
 * @return 1 upon on empty tree, return 0 if tree is not empty. 
 * Time Complexity O(1)
 * Space Complexity O(1) 
*/
int BSTIsEmpty(bst_t *bst);


/**
* @brief checks the number of elements in the tree
* @param bst the tree to check
* @return the number of elements, not including stub.
* Time O(n), Space O(1) */ 
size_t BSTSize(bst_t* bst);


/**
 * @brief Begin represents the element of smallest value in BST
 * @param bst a binary search tree
 * @return an iterator to the first element 
 * Average Time Complexity O(log n),
 * Worst Case Time Complexity O(n)
 * Space Complexity O(1) 
*/
bst_iter_t BSTBegin(bst_t *bst);


/**
 * @brief End represents the element of largest value in BST
 * @param bst a binary search tree
 * @return an iterator to the last element 
 * Average Time Complexity O(log n),
 * Worst Case Time Complexity O(n)
 * Space Complexity O(1) 
*/
bst_iter_t BSTEnd(bst_t *bst);


/**
 * @brief Returns an iterator to the node with the next bigger key, according to compare function.
 * @param iter an iterator
 * @return an iterator to the next node
 * Average Time Complexity O(log n),
 * Worst Case Time Complexity O(n)
 * Space Complexity O(1) 
*/
bst_iter_t BSTNext(bst_iter_t iter);


/**
 * @brief Returns an iterator to the node with the previous bigger key, according to compare function.
 * @param iter an iterator
 * @return an iterator to the previous node
 * Average Time Complexity O(log n),
 * Worst Case Time Complexity O(n)
 * Space Complexity O(1) 
*/
bst_iter_t BSTPrev(bst_iter_t iter);


/**
 * @brief checks if 2 iterators are of the same node.
 * @param iter1 an iterator
 * @param iter1 a second iterator
 * @return 1 if the iterators are equal, 0 if not.
 * Time Complexity O(1)
 * Space Complexity O(1) 
*/
int BSTIterIsEqual(bst_iter_t iter1, bst_iter_t iter2);


/**
 * @brief retrives data stores in a node
 * @param iter an iterator to a node.
 * @return data stored in the node.
 * @note undefined behaviour if the iterator does not exist.
 * Time Complexity O(1)
 * Space Complexity O(1) 
*/
void *BSTIterGetData(bst_iter_t iter);

#endif /* __ILRD_OL149_H_BST__ */

