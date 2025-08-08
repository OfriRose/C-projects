/*Author: Ofri Rozner
 *Reviwer:
 *Date: 22.10.23
 *File: cmp_sort
 */
 
 #include <assert.h>  /* assert */

 #include "cmp_sort.h" /*function headers*/
 
/*--------------service function declarations---------------*/
static void Swap(int *num1, int *num2);

 
 /*--------------function Imp---------------*/
void BubbleSort(int *arr, size_t size)
{
	size_t i = 0;
	int swapped = 1;

		for (i = 0; i < (size - 1) && swapped; ++i)
		{
			swapped = 0;
			
			if (*(arr + i) > *(arr + i + 1))
			{
				Swap((arr + i), (arr + i + 1));
				swapped = 1;
			}
		}
}


void InsertionSort(int *arr, size_t size)
{
	size_t i = 1;
        int *current = arr + i;
        int *j = current; 

	for (i = 1; i < size; ++i)
	{
		current = arr + i;
		j = current; 

		while (j > arr && *(j - 1) > *current)
		{
			*j = *(j - 1); 
			--j;
		}

		*j = *current;
	}
}


void SelectionSort(int *arr, size_t size)
{	
	size_t i = 0;
	int *min = arr + i;
	int *j = 0;

	for (i = 0; i < size - 1; ++i)
	{
		min = arr + i;
		for (j = arr + i + 1; j < arr + size; ++j)
		{
			if (*j < *min)
			{
				min = j;
			}
		}
	Swap(min, (arr + i));
	}
}

/*--------------service functions---------------*/

static void Swap(int *num1, int *num2)
{
	int temp = *num1;
	*num1 = *num2;
	*num2 = temp;
}
