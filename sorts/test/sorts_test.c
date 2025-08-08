
/*
    Developer: Ofri Rozner
    Reviwer: 
    Date: 12/11/23
    sorts - test file
*/

#include <stdio.h>  /* printf */
#include <time.h>	/* time */
#include <stdlib.h>	/* malloc, rand, qsort */



#include "sorts.h" /* sorts API */

#define ARRAY_SIZE 5000

/***********************Tests decleration*************************/
int compareInt(const void *a, const void *b);
static void TestMergeSort(void);
static void TestQuickSort(void);
static void BinarySearch(void);
static void TestNonFunctional(void);


/***************************Main****************************/    

int main()
{
    TestMergeSort();
    BinarySearch();
    TestQuickSort();
    TestNonFunctional();

    return 0;
}
    
    


/***************************Tests impl****************************/    
static void BinarySearch()
{
    int arr[] = {3, 7, 11, 21, 9, 2, 21, 6, 10};
    size_t arr_size = sizeof(arr) / sizeof(arr[0]);
    size_t i = 0;
    int target = 9;

    printf("TEST: BINARY SEARCH\n");
    printf("---------------------\n");

    printf("Array: \n");
    for (i = 0; i < arr_size; ++i) 
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    if (BinarySearchIter(arr, arr_size, target) == target)
    {
        printf("Binary Search (iterator) found target 9 SUCCESFFULY\n");
    }
    else
    {
        printf("BINARY SEARCH(iterator) FAILED");
    }
    
    target = 21;

    if (BinarySearchRec(arr, arr[0], arr[arr_size - 1], target) == target)
    {
        printf("Binary Search (recurrsion) found target 21 SUCCESFFULY\n");
    }
    else
    {
        printf("BINARY SEARCH(recurrsion) FAILED");
    }

    printf("\n\n");
}

static void TestMergeSort()
{
    int arr[] = {4, 1, 3, 5, 2, 8};
    size_t arr_size = sizeof(arr) / sizeof(arr[0]);
    size_t i = 0;

    printf("TEST: MERGESORT\n");
    printf("---------------------\n");

    printf("Before MergeSort: \n");
    for (i = 0; i < arr_size; ++i) 
    {
        printf("%d ", arr[i]);
    }

    MergeSort(arr, arr_size);

    printf("\nAfter MergeSort: \n");
    for (i = 0; i < arr_size; ++i) 
    {
        printf("%d ", arr[i]);
    }

    printf("\n\n");
}

static void TestQuickSort()
{
    int arr[] = {5, 2, 9, 1, 7, 6};
    size_t arr_size = sizeof(arr) / sizeof(arr[0]);
    size_t i = 0;

    printf("TEST: QUICKSORT\n");
    printf("---------------------\n");

    printf("Before QuickSort: \n");
    for (i = 0; i < arr_size; ++i) 
    {
        printf("%d ", arr[i]);
    }

    QSort(arr, arr_size, sizeof(arr[0]), compareInt);

    printf("\nAfter QuickSort: \n");
    for (i = 0; i < arr_size; ++i) 
    {
        printf("%d ", arr[i]);
    }

    printf("\n\n");
}
    
static void TestNonFunctional()
{
    clock_t start = 0;
	clock_t end = 0;
    double cpu_time_used  = 0;
	size_t arr_size = ARRAY_SIZE;
    size_t i = 0;
    int arr[ARRAY_SIZE] = {0};
	
    for (i = 0; i < arr_size; ++i)
    {
        arr[i] = rand() % 100;
    }

    printf("TEST: QUICKSORT vs qsort run time\n");
    printf("---------------------\n");

	start = clock();
    QSort(arr, arr_size, sizeof(arr[0]), compareInt);
	end = clock();
    cpu_time_used = ((double)(end - start)) / 60;    
	printf("QSort Run time(sec): %f\n", cpu_time_used);

	for (i = 0; i < arr_size; ++i)
    {
        arr[i] = rand() % 100;
    }

	start = clock();
    qsort(arr, arr_size, sizeof(arr[0]), compareInt);
	end = clock();
    cpu_time_used = ((double)(end - start)) / 60;    
	printf("qsort Run time(sec): %f\n", cpu_time_used);
}


int compareInt(const void *a, const void *b) 
{
    return (*(int *)a - *(int *)b);
}

    