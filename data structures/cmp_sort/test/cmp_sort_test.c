
/*
    Developer: Ofri Rozner
    Reviwer: 
    Date: 23/10/23
    cmp_sort - test file
*/

#include <stdio.h>  /* printf */
#include <stdlib.h> /* srand, rand */
#include <time.h> /* clock_t, clock */

#include "cmp_sort.h" /* cmp_sort API */

#define ARR_SIZE 5000
/***********************Tests decleration*************************/
static int TestBubble(void);
static int TestInsertion(void);
static int TestSelection(void);
static int TestQsort(void);
static int CompareFunc(const void *a, const void *b);
static void CreateArray(int arr[]);


int main(void)
{
	int num_of_tests = 4;
	int sucesses = 0;
	
	sucesses += TestBubble();
	printf("\n");
	sucesses += TestInsertion();
	printf("\n");
	sucesses += TestSelection();
	printf("\n");
	sucesses += TestQsort();
	printf("\n\n");
	
	if (num_of_tests == sucesses)
	{
		printf("ALL TEST PASSED!");
	}
	

	return 0;
}


/***************************Tests impl****************************/    

static int TestBubble(void)
{
	int arr[ARR_SIZE];
	int i = 0;
	clock_t end_time = 0;
	clock_t start_time = 0;
	double total_time = 0;

	srand(time(NULL));

	CreateArray(arr);
	
	start_time = clock();
	SelectionSort(arr, ARR_SIZE);
	end_time = clock();
	total_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
	
	for (i = 1; i < ARR_SIZE; ++i)
	{
		if (arr[i] < arr[i - 1])
		{
			printf("BUBBLE SORT FAILED");
			return 0;
		}
	}
	
	printf("BUBBLE SORT SUCCESS");
	printf("bubble sort run time: %f seconds\n", total_time);
	
	start_time = clock();
	BubbleSort(arr, ARR_SIZE);
	end_time = clock();
	total_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

	printf("bubble sort run time (sorted): %f seconds\n", total_time);
	
	return 1;
}
	
	
static int TestInsertion(void)
{
	int arr[ARR_SIZE];
	int i = 0;
	clock_t end_time = 0;
	clock_t start_time = 0;
	double total_time = 0;

	srand(time(NULL));

	CreateArray(arr);

	start_time = clock();
	InsertionSort(arr, ARR_SIZE);
	end_time = clock();

	total_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
	
	for (i = 1; i < ARR_SIZE; ++i)
	{
		if (arr[i] < arr[i - 1])
		{
			printf("INSERTION SORT FAILED\n");
			return 0;
		}
	}
	
	printf("INSERTION SORT SUCCESS\n");
	printf("insertion sort run time: %f seconds\n", total_time);

	start_time = clock();
	InsertionSort(arr, ARR_SIZE);
	end_time = clock();

	total_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

	printf("insertion sort run time (sorted): %f seconds\n", total_time);
	
	return 1;
}


static int TestSelection(void)
{
	int arr[ARR_SIZE];
	int i = 0;
	clock_t end_time = 0;
	clock_t start_time = 0;
	double total_time = 0;

	srand(time(NULL));

	CreateArray(arr);

	start_time = clock();
	SelectionSort(arr, ARR_SIZE);
	end_time = clock();

	total_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
	
	for (i = 1; i < ARR_SIZE; ++i)
	{
		if (arr[i] < arr[i - 1])
		{
			printf("INSERTION SORT FAILED\n");
			return 0;
		}
	}
	
	printf("SELECTION SORT SUCCESS\n");
	printf("selection sort run time: %f seconds\n", total_time);

	start_time = clock();
	SelectionSort(arr, ARR_SIZE);
	end_time = clock();

	total_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

	printf("selection sort run time (sorted): %f seconds\n", total_time);
	
	return 1;
}



static int TestQsort(void)
{
	int arr[ARR_SIZE];
	int i = 0;
	clock_t end_time = 0;
	clock_t start_time = 0;
	double total_time = 0;

	srand(time(NULL));

	CreateArray(arr);
	
	start_time = clock();
	qsort(arr, ARR_SIZE, sizeof(int), CompareFunc);
	end_time = clock();

	total_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

	for (i = 1; i < ARR_SIZE; ++i)
	{
		if (arr[i] < arr[i - 1])
		{
			printf("QSORT FAILED\n");
			return 0;
		}
	}
	
	printf("QSORT SUCCESS\n");
	printf("qsort run time: %f seconds\n", total_time);

	start_time = clock();
	qsort(arr, ARR_SIZE, sizeof(int), CompareFunc);
	end_time = clock();

	total_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

	printf("qsort run time (sorted): %f seconds\n", total_time);
	
	return 1;
}


static void CreateArray(int arr[])
{	
	int i = 0;

	for (i = 0; i < ARR_SIZE; ++i)
	{
		arr[i] = 1 + rand() % (ARR_SIZE * 2);
	}
	
}

static int CompareFunc(const void *a, const void *b)
{
	return *((int *)a) - *((int *)b);
}
