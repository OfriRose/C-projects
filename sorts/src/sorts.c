
/*
    Developer: Ofri Rozner
    Reviwer: Yael Hava
    Date: 12/11/23
    sorts - src file
*/
    
#include <assert.h>  /* assert */
#include <stdlib.h> /* malloc */
#include <string.h> /*memcpy*/
#include <stdio.h>

#include "sorts.h"


/******************Service function decleration*************************/
static void Swap(void* ptra, void* ptrb, int size);
static int MergeSortHelper(int *arr, int left, int right);
static int Merge(int *arr, int left, int mid, int right);

/****************************Implementation*****************************/
int BinarySearchIter(int *arr, int size, int target)
{
    size_t arr_length = size;
    int *runner = arr + size / 2;

    while (arr <= runner && (arr + arr_length) >= runner)
    {
        if (*runner == target)
        {
            return *runner;
        }
        if (*runner < target)
        {
            ++runner;
        }
        if (*runner > target)
        {
            --runner;
        }
    }

    return -1;
}

int BinarySearchRec(int arr[], int min, int max, int target)
{
    int mid = min + (max - min) / 2;

    if (arr[mid] == target)
    {
        return target;
    }
    if (arr[mid] > target)
    {
        return BinarySearchRec(arr, min, mid - 1, target);
    }
    if (arr[mid] < target)
    {
        return BinarySearchRec(arr, mid + 1, max, target);
    }

    return -1;
}

int MergeSort(int *arr_to_sort, size_t num_elements) 
{
    return MergeSortHelper(arr_to_sort, 0, num_elements - 1);
}

static int MergeSortHelper(int *arr, int left, int right) 
{
    int mid = 0;

    if (left >= right) 
    {
        return 0;
    }

    mid = (left + right) / 2;

    MergeSortHelper(arr, left, mid);
    MergeSortHelper(arr, mid + 1, right);

    return Merge(arr, left, mid, right);
}

static int Merge(int *arr, int left, int mid, int right) 
{
    int arr1_index = 0;
    int arr2_index = 0;

    int i = 0;

    int arr_ptr = left;

    int arr1_size = mid - left + 1;
    int arr2_size = right - mid;

    int *arr1 = NULL;
    int *arr2 = NULL;

    arr1 = (int *)malloc(sizeof(int) * arr1_size);
    if (NULL == arr1) 
    {
        return 1;
    }

    arr2 = (int *)malloc(sizeof(int) * arr2_size);
    if (NULL == arr2) 
    {
        free(arr1);
        return 1;
    }

    for (i = 0; i < arr1_size; ++i) 
    {
        arr1[i] = arr[i + left];
    }

    for (i = 0; i < arr2_size; ++i) 
    {
        arr2[i] = arr[i + mid + 1];
    }

    while (arr1_index < arr1_size && arr2_index < arr2_size) 
    {
        if (arr1[arr1_index] < arr2[arr2_index]) 
        {
            arr[arr_ptr] = arr1[arr1_index];
            ++arr1_index;
        } 
        else 
        {
            arr[arr_ptr] = arr2[arr2_index];
            ++arr2_index;
        }

        ++arr_ptr;
    }

    while (arr1_index < arr1_size) 
    {
        arr[arr_ptr] = arr1[arr1_index];
        ++arr1_index;
        ++arr_ptr;
    }

    while (arr2_index < arr2_size) 
    {
        arr[arr_ptr] = arr2[arr2_index];
        ++arr2_index;
        ++arr_ptr;
    }

    free(arr1);
    free(arr2);

    return 0;
}


static void Swap(void* ptra, void* ptrb, int size)
{
    char temp;
    int i = 0;
    char *pa = (char *)ptra;
    char *pb = (char *)ptrb;

    for (i = 0 ; i < size ; ++i) 
    {
        temp = pa[i];
        pa[i] = pb[i];
        pb[i] = temp;
    }
}

static int Partition(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void*)) 
{
    size_t index = 0;
    size_t j = 0;
    char *pivot = (char *)base + (nmemb - 1) * size;

    while (j < (nmemb - 1)) 
    {
        if (compar((char *)base + j * size, pivot) <= 0) 
        {
            Swap((char *)base + index * size, (char *)base + j * size, (int)size);
            ++index;
        }
        ++j;
    }

    Swap((char *)base + index * size, pivot, (int)size);

    return index;
}

void QSort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void*)) 
{
    int pivot_index = 0;

    if (1 >= nmemb)
    {
        return;
    }

    pivot_index = Partition(base, nmemb, size, compar);

    QSort(base, pivot_index, size, compar);
    QSort((char *)base + (pivot_index + 1) * size, nmemb - pivot_index - 1, size, compar);
    

}

