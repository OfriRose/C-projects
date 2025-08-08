/*******************************************************************************
*				NAME: OFRI ROZNER				  *
*				REVIWER: ISRAEL WEISS				  *
*				DATE: 20.8.2023				  *
*				WS: VECTOR					  *
*******************************************************************************/

/**********************includes**********************/
#include <stdlib.h>/*malloc*/
#include <assert.h>/*assert*/

#include "d_vector.h"

#define GROWTH_FACTOR 2
#define SHRINK_FACTOR 0.5


struct d_vector
{
	char *elements;
	size_t capacity;
	size_t size;
	size_t elem_size;
};

/**********************functions*******************/

d_vector_t* VectorCreate(size_t capacity, size_t elem_size)
{
	d_vector_t *vec = (d_vector_t *)malloc(sizeof(d_vector_t));
	assert(0 < capacity && 0 < elem_size);
	
	if(NULL == vec)
	{
		return NULL;
	}
	
	vec->elements = malloc(capacity * elem_size);
	
	if(NULL == vec->elements)
	{
		return NULL;
	}
	
	vec->capacity = capacity;
	vec->size = 0;
	vec->elem_size = elem_size;
	
	return vec;
}

size_t VectorSize(const d_vector_t *vec)
{
	return vec->size;
}

size_t VectorCapacity(const d_vector_t *vec)
{
	return vec->capacity;
}

void VectorDestroy(d_vector_t *vec)
{	
	assert(vec);
	
	free(vec->elements);
	vec->elements = NULL;
	free (vec);
	vec = NULL;
}

int VectorPushBack(d_vector_t *vec, const void *value)
{
	size_t new_capacity = 0;
	char *target = (char*)vec -> elements + (vec->size * vec->elem_size);
	size_t i = 0;

	assert(vec);
	assert(value);

	if(VectorCapacity(vec) == VectorSize(vec) +1 )
	{	
		new_capacity = vec->capacity * GROWTH_FACTOR;
		return VectorReserve(vec, new_capacity);
		
	}

	for (i = 0; i < vec -> elem_size; ++i)
	{
		*target = *((char*)value + i);
		++target;
	}
	
	++vec->size;
	
	return 1;
}

void VectorPopBack(d_vector_t *vec)
{
	assert(vec);
	if (0 < (vec->size)) 
	{
		free(VectorGetElem(vec, vec->size)); 
		--vec->size;
	}
}


void *VectorGetElem(const d_vector_t *vec, size_t index)
{
	assert(vec);
	assert (index <= vec->size);
	
	if (index >= vec->size)
	{
		return NULL;
	}
    
	return vec->elements + (index * vec->elem_size);
}


int VectorReserve(d_vector_t *vec, size_t new_capacity)
{
	char *new_elements = realloc(vec->elements, new_capacity * vec->elem_size);
	assert(vec);

	if (NULL == new_elements)
	{
		return 0; 
	}
	
	if(vec->size <  new_capacity)
	{
		vec->size =  new_capacity;
	}

	vec->elements = new_elements;
	vec->capacity = new_capacity;

	return 1;
}

int VectorShrink(d_vector_t *vec)
{
	size_t new_capacity = 0;
	new_capacity = (size_t)(vec->capacity * SHRINK_FACTOR + 1);
	VectorReserve(vec, new_capacity);

	return 1;
}
