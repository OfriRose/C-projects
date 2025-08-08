
/*
    Developer: Ofri Rozner
    Reviwer: 
    Date: 26/09/23
    pqueue - test file
*/

#include <stdio.h>  /* printf */
#include <stddef.h> /* size_t */
#include <stdlib.h> /* malloc, free */

#include "pqueue.h" /* Include your pqueue API */

int TestPQCreateAndDestroy(void);
int TestPQPushReturn(void);
int TestPQPushPeekPop(void);
int TestPQSizeAfterPush(void);
int TestPQSizeAfterPop(void);
int TestPQIsEmpty(void);
int TestPQClear(void);
int TestPQEraseFound(void);
int TestPQEraseNotFound(void);

size_t failures = 0;

int main()
{
	puts("Testing Priority Queue...");
	TestPQCreateAndDestroy();
	TestPQPushReturn();
	TestPQPushPeekPop();
	TestPQSizeAfterPush();
	TestPQSizeAfterPop();
	TestPQIsEmpty();
	TestPQClear();
	TestPQEraseFound();
	TestPQEraseNotFound();

	if (0 == failures)
	{
		printf("All tests passed!\n");
	}
	else
	{
		printf("%lu tests failed.\n", failures);
	}
	
	return (int)failures;
}

int compare(const void *data1, const void *data2)
{

	if (*(int *)data1 > *(int *)data2)
	{
		return (1);
	}
		else if (*(int *)data1 == *(int *)data2)
	{
		return (0);
	}
	else
	{
		return (-1);
	}
}

int TestPQCreateAndDestroy()
{
	pqueue_t *pq = PQCreate(compare);

	if (NULL == pq)
	{
		puts("\tMalloc failed");
		++failures;
	}

	PQDestroy(pq);

	return (int)failures;
}

int TestPQPushReturn()
{
	size_t i = 0;
	int data_arr[] = {4, 1, 0, -1, 4, -1, 300};
	int exp_return[] = {0, 0, 0, 0, 0, 0, 0};
	int actual_return[7] = {0};

	pqueue_t *pq = PQCreate(compare);

	for (i = 0; i < sizeof(data_arr) / sizeof(data_arr[0]); ++i)
	{
		actual_return[i] = PQEnqueue(pq, &data_arr[i]);
	}

	for (i = 0; i < sizeof(data_arr) / sizeof(data_arr[0]); ++i)
	{
		if (actual_return[i] != exp_return[i])
		{
			printf("\tFAILED at index %lu on line %d\n", i, __LINE__);
			printf("\t\tExpected: %d\n", exp_return[i]);
			printf("\t\tReturned: %d\n", actual_return[i]);
			++failures;
		}
	}

	PQDestroy(pq);

	return (int)failures;
}

int TestPQPushPeekPop()
{
	size_t i = 0;
	int data_arr[] = {4, 1, 0, -1, 4, -1, 300};
	int exp_data[] = {-1, -1, 0, 1, 4, 4, 300};
	int peek_return[7] = {0};
	int pop_return[7] = {0};

	pqueue_t *pq = PQCreate(compare);

	for (i = 0; i < sizeof(data_arr) / sizeof(data_arr[0]); ++i)
	{
		PQEnqueue(pq, &data_arr[i]);
	}

	for (i = 0; i < sizeof(data_arr) / sizeof(data_arr[0]); ++i)
	{
		peek_return[i] = *(int *)PQPeek(pq);
		pop_return[i] = *(int *)PQDequeue(pq);
	}

	for (i = 0; i < sizeof(data_arr) / sizeof(data_arr[0]); ++i)
	{
		if (peek_return[i] != exp_data[i])
		{
			printf("\tFAILED at index %lu on line %d\n", i, __LINE__);
			printf("\t\tExpected Peek: %d\n", exp_data[i]);
			printf("\t\tReturned: %d\n", peek_return[i]);
			++failures;
		}
	}

	for (i = 0; i < sizeof(data_arr) / sizeof(data_arr[0]); ++i)
	{
		if (pop_return[i] != exp_data[i])
		{
			printf("\tFAILED at index %lu on line %d\n", i, __LINE__);
			printf("\t\tExpected Pop: %d\n", exp_data[i]);
			printf("\t\tReturned: %d\n", pop_return[i]);
			++failures;
		}
	}

	PQDestroy(pq);

	return (int)failures;
}

int TestPQSizeAfterPush()
{
	size_t i = 0;
	int data_arr[] = {4, 1, 0, -1, 4, -1, 300};

	pqueue_t *pq = PQCreate(compare);

	for (i = 0; i < sizeof(data_arr) / sizeof(data_arr[0]); ++i)
	{

	if (PQSize(pq) != i)
	{
		printf("\tFAILED at index %lu on line %d\n", i, __LINE__);
		printf("\t\tExpected: %lu\n", i);
		printf("\t\tReturned: %lu\n", PQSize(pq));
		++failures;
	}

	PQEnqueue(pq, &data_arr[i]);
	}

	PQDestroy(pq);

	return (int)failures;
}

int TestPQSizeAfterPop()
{
	size_t i = 0;
	int data_arr[] = {4, 1, 0, -1, 4, -1, 300};

	pqueue_t *pq = PQCreate(compare);

	for (i = 0; i < sizeof(data_arr) / sizeof(data_arr[0]); ++i)
	{
		PQEnqueue(pq, &data_arr[i]);
	}

	for (i = 0; i < sizeof(data_arr) / sizeof(data_arr[0]); ++i)
	{

		if (PQSize(pq) != sizeof(data_arr) / sizeof(data_arr[0]) - i)
		{
			printf("\tFAILED at index %lu on line %d\n", i, __LINE__);
			printf("\t\tExpected: %lu\n",
				 sizeof(data_arr) / sizeof(data_arr[0]) - i);
			printf("\t\tReturned: %lu\n", PQSize(pq));
			++failures;
		}

		PQDequeue(pq);
	}

	PQDestroy(pq);

	return (int)failures;
}

int TestPQIsEmpty()
{
	size_t i = 0;
	int data_arr[] = {4, 1, 0, -1, 4, -1, 300};
	int exp_is_empty[] = {1, 0, 0, 0, 0, 0, 0, 0};

	pqueue_t *pq = PQCreate(compare);

	for (i = 0; i < sizeof(data_arr) / sizeof(data_arr[0]); ++i)
	{
		if (PQIsEmpty(pq) != exp_is_empty[i])
		{
			printf("\tFAILED at index %lu on line %d\n", i, __LINE__);
			printf("\t\tExpected: %d\n", exp_is_empty[i]);
			printf("\t\tReturned: %d\n", PQIsEmpty(pq));
			++failures;
		}

		PQEnqueue(pq, &data_arr[i]);
	}

	PQDestroy(pq);

	return (int)failures;
}

int TestPQClear()
{
	size_t i = 0;
	int data_arr[] = {4, 1, 0, -1, 4, -1, 300};

	pqueue_t *pq = PQCreate(compare);

	for (i = 0; i < sizeof(data_arr) / sizeof(data_arr[0]); ++i)
	{
		PQEnqueue(pq, &data_arr[i]);
	}

	PQClear(pq);

	if (PQIsEmpty(pq) != 1)
	{
		printf("\tFAILED on line %d\n", __LINE__);
		printf("\t\tExpected: %d\n", 1);
		printf("\t\tReturned: %d\n", PQIsEmpty(pq));
		++failures;
	}

	PQDestroy(pq);

	return (int)failures;
}

int is_match(const void *data, void *param)
{
	return (*(int *)data + *(int *)param == 301);
}

int TestPQEraseFound()
{
	int param = 1;
	size_t i = 0;
	int data_arr[] = {4, 1, 0, -1, 4, -1, 300};
	void *erase_return = NULL;

	pqueue_t *pq = PQCreate(compare);

	for (i = 0; i < sizeof(data_arr) / sizeof(data_arr[0]); ++i)
	{
		PQEnqueue(pq, &data_arr[i]);
	}

	erase_return = PQErase(pq, is_match, &param);

	if (*(int *)erase_return != data_arr[6])
	{
		printf("\tFAILED on line %d\n", __LINE__);
		printf("\t\tExpected: %d\n", data_arr[6]);
		printf("\t\tReturned: %d\n", *(int *)erase_return);
		++failures;
	}

	PQDestroy(pq);

	return (int)failures;
}

int TestPQEraseNotFound()
{
	int param = 2;
	size_t i = 0;
	int data_arr[] = {4, 1, 0, -1, 4, -1, 300};
	void *erase_return = NULL;

	pqueue_t *pq = PQCreate(compare);

	for (i = 0; i < sizeof(data_arr) / sizeof(data_arr[0]); ++i)
	{
		PQEnqueue(pq, &data_arr[i]);
	}

	erase_return = PQErase(pq, is_match, &param);

	if (erase_return != NULL)
	{
		printf("\tFAILED on line %d\n", __LINE__);
		printf("\t\tExpected: %p\n", NULL);
		printf("\t\tReturned: %p\n", erase_return);
		++failures;
	}

	PQDestroy(pq);

	return (int)failures;
}

