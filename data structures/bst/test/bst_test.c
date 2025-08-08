/*
    Developer: Ofri Rozner
    Reviwer: Mentor
    Date: 24/10/23
    bst - test file
*/

#include <stdio.h>
#include "bst.h"

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define RESET "\x1b[0m"

#define PRINTRESULT(test_fails, test_name) \
    if (0 == test_fails) { \
        printf(GREEN"%s passed!\n" RESET, test_name); \
    } else { \
        printf(RED "%s failed.\n" RESET, test_name); \
    }

/* Function declarations */
void TestCreateDestroy();
void TestInsert();
void TestNextPrev();
void TestFindForEach();
void TestRemove();

/* Comparison function for BST */
static int compare_int(const void *a, void *b);

/* Operation for BSTForEach */
int Operation(void *data, void *param);

int main() 
{
    printf("TEST FILE: BST\n");
    printf("-----------------------\n\n");

    printf("CRAETE AND DESTROY:\n");
    TestCreateDestroy();
    printf("INSERTS:\n");
    TestInsert();
    printf("ITERATION OPERATIONS:\n");
    TestNextPrev();
    printf("FOREACH:\n");
    TestFindForEach();
    printf("REMOVE:\n");
    TestRemove();

    return 0;
}

static int compare_int(const void *a, void *b) 
{
    int int_a = *(int *)a;
    int int_b = *(int *)b;
    
    return (int_a - int_b);
}

void TestCreateDestroy() 
{
    size_t test = 0;
    char *test_name = "TestCreate";

    bst_t *tree = BSTCreate(compare_int);
    test = BSTSize(tree);
    PRINTRESULT(test, test_name);
    BSTDestroy(tree);
    test_name = "TestDestroy";
    PRINTRESULT(test, test_name);
}

void TestInsert() 
{
    size_t test = 0;
    int i = 0;
    int array[30] = {15, 14, 20, 4, 7, 9, 26, 17, 12, 2, 3, 22, 30, 28, 13, 1, 11, 8, 24, 16, 10, 27, 5, 25, 29, 23, 21, 19, 18, 6};
    int *array_idx = array;
    bst_t *tree = BSTCreate(compare_int);
    char *test_name = "TestInsert - ints";

    test = 0;
    for (i = 0; i < 5; ++i) 
    {
        BSTInsert(tree, array_idx);
        array_idx++;

        test += BSTSize(tree) - i - 1;
        test += BSTIsEmpty(tree);
    }

    test += *(int *)BSTIterGetData(BSTBegin(tree)) - 4;
    test += *(int *)BSTIterGetData(BSTNext(BSTBegin(tree))) - 7;
    test_name = "TestInsert - retrive data";
    PRINTRESULT(test, test_name);

    for (i = 5; i < 10; ++i) 
    {
        BSTInsert(tree, array_idx);
        ++array_idx;

        test += BSTSize(tree) - i - 1;
        test += BSTIsEmpty(tree);
    }
    test += *(int *)BSTIterGetData(BSTBegin(tree)) - 2;
    test += *(int *)BSTIterGetData(BSTNext(BSTBegin(tree))) - 4;
    test_name = "TestInsert - add inserts";
    PRINTRESULT(test, test_name);

    BSTDestroy(tree);
}

void TestNextPrev() 
{
    size_t test = 0;
    int i = 0;
    int array[30] = {15, 14, 20, 4, 7, 9, 26, 17, 12, 2, 3, 22, 30, 28, 13, 1, 11, 8, 24, 16, 10, 27, 5, 25, 29, 23, 21, 19, 18, 6};
    int *array_idx = array;
    bst_iter_t iter = NULL;
    bst_t *tree = BSTCreate(compare_int);
    char *test_name = "TestNext";


    test = 0;
    for (i = 0; i < 30; ++i) 
    {
        BSTInsert(tree, array_idx);
        ++array_idx;

        test += BSTSize(tree) - i - 1;
        test += BSTIsEmpty(tree);
    }

    test = 0;
    iter = BSTBegin(tree);
    for (i = 1; i <= 30; ++i) {
        test += *(int *)BSTIterGetData(iter) - i;
        iter = BSTNext(iter);
    }
    test_name = "TestBegin";
    PRINTRESULT(test, test_name);

    test = 0;
    iter = BSTEnd(tree);
    for (i = 30; i >= 1; --i) 
    {
        iter = BSTPrev(iter);
        test += *(int *)BSTIterGetData(iter) - i;
    }
    test_name = "TestEnd";
    PRINTRESULT(test, test_name);

    BSTDestroy(tree);
}

void TestFindForEach() 
{
    size_t test = 0;
    int i = 0;
    int array[30] = {15, 14, 20, 4, 7, 9, 26, 17, 12, 2, 3, 22, 30, 28, 13, 1, 11, 8, 24, 16, 10, 27, 5, 25, 29, 23, 21, 19, 18, 6};
    int *array_idx = array;
    bst_iter_t iter = NULL;
    bst_t *tree = BSTCreate(compare_int);
    char *test_name = "TestFind";

    test = 0;
    for (i = 0; i < 30; ++i) 
    {
        BSTInsert(tree, array_idx);
        array_idx++;
    }

    test = 0;
    for (i = 1; i <= 30; ++i) 
    {
        test += *(int *)BSTIterGetData(BSTFind(tree, &i)) - i;
    }
    PRINTRESULT(test, test_name);

    i = 0;
    iter = BSTFind(tree, &i);
    test = BSTIterIsEqual(BSTEnd(tree), iter) - 1;
    test_name = "TestFind - node doesn't exist";
    PRINTRESULT(test, test_name);

    i = 1;
    test = 0;
    iter = BSTBegin(tree);
    BSTForEach(BSTBegin(tree), BSTEnd(tree), Operation, &i);

    for (i = 1; i <= 30; ++i)
    {
        test += *(int *)BSTIterGetData(iter) - i * i;
        iter = BSTNext(iter);
    }
    test_name = "TestForEach";
    PRINTRESULT(test, test_name);

    BSTDestroy(tree);
}

void TestRemove() 
{
    size_t test = 0;
    int i = 0;
    int array[30] = {15, 14, 20, 4, 7, 9, 26, 17, 12, 2, 3, 22, 30, 28, 13, 1, 11, 8, 24, 16, 10, 27, 5, 25, 29, 23, 21, 19, 18, 6};
    int *array_idx = array;
    bst_iter_t iter = NULL;
    bst_t *tree = BSTCreate(compare_int);
    char *test_name = "TestRemove";


    test = 0;
    for (i = 0; i < 30; ++i) 
    {
        BSTInsert(tree, array_idx);
        ++array_idx;
    }

    iter = BSTBegin(tree);
    for (i = 1; i < 4; ++i) 
    {
        iter = BSTNext(iter);
    }
    test =  *(int *)BSTIterGetData(iter) - 4;
    BSTRemove(iter);

    iter = BSTBegin(tree);
    for (i = 1; i < 4; ++i) 
    {
        iter = BSTNext(iter);
    }
    test =  *(int *)BSTIterGetData(iter) - 5;
    PRINTRESULT(test, test_name);

    iter = BSTBegin(tree);

    test =  *(int *)BSTIterGetData(iter) - 1;
    test_name = "TestRemove2";

    PRINTRESULT(test, test_name);
    BSTDestroy(tree);
}

int Operation(void *data, void *param) 
{
    *(int *)data *= (*(int *)param * *(int *)data);
    return 0;
}
