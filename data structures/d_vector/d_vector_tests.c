/*******************************************************************************
*				NAME: OFRI ROZNER				  *
*				REVIWER:					  *
*				DATE: 20.8.2023				  *
*				WS: VECTOR					  *
*******************************************************************************/

#include <stdio.h>/*printf*/
#include <assert.h>/*assert*/

#include "d_vector.h"

static void test_vector();

int main()
{
    test_vector();
    return 0;
}

static void test_vector()
{
	d_vector_t *vec = VectorCreate(10, sizeof(int));
	size_t size = 0;
	int values[] = {10, 20, 30, 40, 50};
	int *elem = NULL;
	size_t i = 0;

	assert(vec);
			
	printf("Vector size: %lu\n", (unsigned long)size);

	for (i = 0; i < 5; ++i)
	{
		VectorPushBack(vec, &values[i]);
		size = VectorSize(vec);
		printf("Vector size: %lu\n", (unsigned long)size);
	}

	printf("Vector capacity: %lu\n", (unsigned long)VectorCapacity(vec));
			
	VectorPopBack(vec);
	size = VectorSize(vec);
	printf("Vector size after pop: %lu\n", (unsigned long)size);
			
	VectorPushBack(vec, &values[4]);
	elem = (int *)VectorGetElem(vec, 4);

	if (elem)
	{
		printf("Element at index 4: %d\n", *elem);
	}

	else
	{
		printf("Invalid index\n");
	}

	VectorReserve(vec, 20);
	printf("Vector capacity after reserve: %lu\n", (unsigned long)VectorCapacity(vec));

	VectorShrink(vec);
	printf("Vector capacity after shrink: %lu\n", (unsigned long)VectorCapacity(vec));

	VectorDestroy(vec);
}
