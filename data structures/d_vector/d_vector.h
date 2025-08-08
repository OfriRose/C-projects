#ifndef __ILRD_OL149_D_VECTOR_H__
#define __ILRD_OL149_D_VECTOR_H__

/*******************************************************************************
*				NAME: OFRI ROZNER				  *
*				REVIWER: ISRAEL WEISS				  *
*				DATE: 20.8.2023				  *
*				WS: VECTOR				          *									  
*******************************************************************************/

#include <stddef.h>/*size_t*/

typedef struct d_vector d_vector_t;

/*******************************************************************************
*Dynamic Vector API for managing a resizable data structure as an array of elements
*
* A dynamic vector is a data structure that allows you to store and manage a
* collection of elements stord by value that can dynamically grow or shrink in
* size. the dynamic vector is Random Access memory, meaning element can be
* accessed by index
* It provides methods for adding, removing, and accessing elements.
*******************************************************************************/


/*
param capacity: The initial capacity of the dynamic vector.
param elem_size: The size (in bytes) of each element.

return A refrence to a new dynamic vector, or NULL on failure.
 
creates a new dynamic vector with the specified initial

notes: undefined behaviour if element size is 0;

Time Complexity- O(1), Space Complexity- O(n)
*/
d_vector_t* VectorCreate(size_t capacity, size_t elem_size);

/*
param vec A pointer to the dynamic vector to be destroyed.

destroy the handle.

Time Complexity- O(1), Space Complexity- O(1) 
*/
void VectorDestroy(d_vector_t *vec);

/*
param vec A refrence to the dynamic vector.
param value A refrence to the data to be added.
return 0 on success, a non zero number on failure.

push new data into the handle, exapand vector when capacity equals size. .

notes: undefined behaviour if value is NULL or pushed over capacity

Amortized Time Complexity- O(1), Worst Case Time Complexity- O(n),
Space Complexity- O(n) 

*/
int VectorPushBack(d_vector_t *vec, const void *value);

/*
param vec:  A refrence to the dynamic vector.
removes the last element from the dynamic vector. If the
vector is empty, no action is taken.

Notes: undefined behavior if vector is empty. 

Time Complexity- O(1), Space Complexity- O(1)
*/
void VectorPopBack(d_vector_t *vec);

/*
param vec: A refrence to the dynamic vector.
param index: The index of the element to access.

return the data stored at the vector's last element


Time Complexity- O(1), Space Complexity- O(1)

Notes: undefined behavior if index is out of range. 
elements acceseed will ne invalid after push, reserve, and shrink
*/
void *VectorGetElem(const d_vector_t *vec, size_t index);

/*
param vec: a refrence to the vector.

return the vector's current size.

Time Complexity- O(1), Space Complexity- O(1) 
*/
size_t VectorSize(const d_vector_t *vec);

/*
param vec: a refrence to the vector.

return the vector's capacity (maximun number of elemnts supported
without resizing)

Time Complexity- O(1), Space Complexity- O(1)
*/
size_t VectorCapacity(const d_vector_t *vec);

/*
param vec: A refrence to the dynamic vector.
param new_capacity: The desired capacity.

return 0 on success, a non zero number on failure.

Time Complexity- O(n), Space Complexity- O(n) 
*/
int VectorReserve(d_vector_t *vec, size_t new_capacity);

/*
param vec: A refrence to the dynamic vector.
return 0 on success, a non zero number on failure.

Shrink the vector by factor of 2, will cause a data loss if shrinked below size.

Time Complexity- O(n), Space Complexity- O(n)
*/
int VectorShrink(d_vector_t *vec);


#endif /* __ILRD_OL149_D_VECTOR_H__ */
