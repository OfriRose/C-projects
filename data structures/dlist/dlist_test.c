/*******************************************************************************
*    Developer: Ofri Rozner
*    Reviwer: Amitai Milshtain
*    Date: 10/09/23
*    dlist - test file
*******************************************************************************/
#include <stdio.h>  /* printf */

#include "dlist.h" /* dlist API */

/****************************defines******************************/

enum test_res
{
    FAIL = 0,
    SUCCESS = 1
};

/***********************Tests decleration*************************/

static int TestDListCreateAndDestroy(void);
static int TestDListInsertBefore(void);
static int TestDListRemove(void);
static int TestDListCount(void);
static int TestDListIsEmpty(void);
static int TestDListGetData(void);
static int TestDListSetData(void);
static int TestDListForEach(void);
static int TestSplice(void);
static int TestDListMultiFind(void);
static int MatchInt(const void *data, void *param);
static int IntAction(void *data, void *param);

/*****************************main*******************************/

int main(void)
{
	int count = 0;
	int num_of_tests = 10;
	printf("\n");
	
	count += TestDListCreateAndDestroy();
	count += TestDListInsertBefore();
	count += TestDListRemove();
	count += TestDListCount();
	count += TestDListIsEmpty();
	count += TestDListGetData();
	count += TestDListSetData();
	count += TestDListForEach();
	count += TestSplice();
	count += TestDListMultiFind();
	
	if (count == num_of_tests)
	{
		printf("\n\n\t\tALL TESTS PASSED!\n");
	}
	
	return 0;
}

/***************************Tests impl****************************/    

static int TestDListCreateAndDestroy(void)
{
	dlist_t *list = DListCreate();
	if (NULL == list)
	{
		printf("CREATE FAILED\n");
		DListDestroy(list);
		return FAIL;
	}

	DListDestroy(list);
	
	printf("CREATE -\t\tPASSED!\n");
	printf("DESTROY -\t\tPASSED!\n");

	return SUCCESS;
}


static int TestDListInsertBefore(void)
{
	int status = SUCCESS;
	int int_data = 10;
	char *char_data = "test";
	float float_data = 3.3;

	dlist_t *list = DListCreate();
	if (NULL == list)
	{
		printf("failed to create at InserBefore\n");
		return FAIL;
	}
	
	status = 
(DListInsertBefore(list, DListEnd(list), &int_data) == DListPrev(DListEnd(list)));
	if (FAIL == status)
	{
		printf("FAILED to to insert int\n");
		DListDestroy(list);
		return FAIL;
	}
	
	printf("INSERT INT -\t\tPASSED!\n");

	status = 
(DListInsertBefore(list, DListEnd(list), &char_data) == DListPrev(DListEnd(list)));
	if (FAIL == status)
	{
		printf("FAILED to to insert string\n");
		DListDestroy(list);
		return FAIL;
	}
	
	printf("INSERT CHAR -\t\tPASSED!\n");
	
	status = 
(DListInsertBefore(list, DListEnd(list), &float_data) == DListPrev(DListEnd(list)));
	if (FAIL == status)
	{
		printf("FAILED to to insert float\n");
		DListDestroy(list);
		return FAIL;
	}
	
	printf("INSERT FLOAT -\t\tPASSED!\n");
	
	DListDestroy(list);
	
	return status;
}


static int TestDListRemove(void)
{
	int status = SUCCESS;
	int data1 = 10;
	
	dlist_iter_t inserted1 = NULL;

	dlist_t *list = DListCreate();
	if (NULL == list)
	{
		printf("FAILED to create at ListRemove\n");
		DListDestroy(list);
		return FAIL;
	}
	
	inserted1 = DListInsertBefore(list, DListEnd(list), &data1);
	if(NULL == inserted1)
	{
		printf("FAILED to insert at ListRemove\n");
		DListDestroy(list);
		return FAIL;
	}	
	
	DListRemove(inserted1);
	printf("REMOVE -\t\tPASSED!\n");
		
	DListDestroy(list);

	return status;
}


static int TestDListCount(void)
{
	int data1 = 10;
	int data2 = 20;
	int data3 = 30;
	int status = SUCCESS;

	dlist_t *list = DListCreate();
	if (NULL == list)
	{
		printf("FAILED to create at ListCount\n");
		DListDestroy(list);
		return FAIL;
	}
	
	DListInsertBefore(list, DListEnd(list), &data1);
	DListInsertBefore(list, DListEnd(list), &data2);
	DListInsertBefore(list, DListEnd(list), &data3);
	
	status = (3 == DListCount(list));
	
	if(SUCCESS == status)
	{
		printf("COUNT -\t\t\tPASSED!\n");
	}

	DListDestroy(list);

	return SUCCESS;
}


static int TestDListIsEmpty(void)
{
	int status = SUCCESS;
	int data1 = 10;

	dlist_t *list = DListCreate();
	if (NULL == list)
	{
		printf("failed to create at IsEmpty\n");
		DListDestroy(list);
		return FAIL;
	}

	status = DListIsEmpty(list);
	if (1 == status)
	{
		printf ("ISEMPTY (empty) -\tPASSED!\n");
	}
    
	DListInsertBefore(list, DListEnd(list), &data1);
	status = DListIsEmpty(list);
	if (0 == status)
	{
		printf ("ISEMPTY (not empty) -\tPASSED!\n");
	}
    
	DListDestroy(list);

	return SUCCESS;
}


static int TestDListGetData(void)
{
	int data = 10;
	int status = SUCCESS;
	dlist_iter_t inserted = NULL;

	dlist_t *list = DListCreate();
	if (NULL == list)
	{
		printf("FAILED to create at GetData\n");
		DListDestroy(list);
		return FAIL;
	}
	
	inserted = DListInsertBefore(list, DListEnd(list), &data);
	if(FAIL == inserted)
	{
		printf("FAILED to insert at GetData\n");
		DListDestroy(list);
		return FAIL;
	}	
	status = (data == *((int *)DListGetData(inserted)));
	if(FAIL == status)
	{
		printf("FAIL at GetData\n");
		DListDestroy(list);
		return FAIL;
	}

	printf("GET DATA -\t\tPASSED!\n");

	DListDestroy(list);

	return status;
}


static int TestDListSetData(void)
{
	int data = 10;
	int new_data = 5;
	int status = SUCCESS;
	dlist_iter_t inserted = NULL;

	dlist_t *list = DListCreate();
	if (NULL == list)
	{
		return FAIL;
		DListDestroy(list);
		printf("FAILED to create at SetData\n");
	}
	
	inserted = DListInsertBefore(list, DListEnd(list), &data);
	if(FAIL == inserted)
	{
		printf("FAILED to insert at SetData\n");
		DListDestroy(list);
		return FAIL;
	}
		
	DListSetData(inserted, &new_data);
	
	status = (new_data == *((int *)DListGetData(inserted)));
	if(FAIL == status)
	{
		printf("FAIL at SetData\n");
		DListDestroy(list);
		return FAIL;
	}

	DListDestroy(list);

	printf("SET DATA -\t\tPASSED!\n");

	return status;
}


static int TestDListForEach(void)
{
	dlist_t *list =  DListCreate();
	
	int a = 2;
	int b = 3;
	int c = 4;
	int d = 1;

	dlist_iter_t temp1 = DListInsertBefore(list, DListEnd(list), &a);
	dlist_iter_t temp2 = DListInsertBefore(list, DListEnd(list), &b);
	dlist_iter_t temp3 = DListInsertBefore(list, DListEnd(list), &c);

	DListForEach(DListBegin(list), DListEnd(list), IntAction, &d);

	if (4 == *(int *)DListGetData(temp2))
	{
		printf("FOREACH -\t\tPASSED!\n");
	}
	else
	{
		printf("FOREACH -\t\tFAIL\n");
		DListDestroy(list);
		return FAIL;
	}

	DListDestroy(list);
    
	(void)temp1;
	(void)temp3;
    
	return SUCCESS;
}


static int TestSplice(void)
{
	dlist_t *list =  DListCreate();
	
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	int e = 5;

	dlist_iter_t temp1 = DListPushBack(list, &a);
	dlist_iter_t temp2 = DListPushBack(list, &b);
	dlist_iter_t temp3 = DListPushBack(list, &c);
	dlist_iter_t temp4 = DListPushBack(list, &d);
	dlist_iter_t temp5 = DListPushBack(list, &e);
	
	dlist_iter_t temp6 = DListSplice(temp2, temp4, temp5);
	
	if(DListIsIterEqual(DListNext(temp4), temp2))
	{
		printf("SPLICE -\t\tPASSED!\n");
	}
	else
	{
		printf("SPLICE -\t\tFAILED!\n");
		DListDestroy(list);
		return FAIL;
	}
	
	(void)temp1;
	(void)temp3;
	(void)temp6;

	DListDestroy(list);
	
	return SUCCESS;
}


static int TestDListMultiFind(void)
{
	dlist_t *new_dlist = DListCreate();
	dlist_t *output_list = DListCreate();

	int num2 = 2;
	int num3 = 3;
	int i = 0;
    
	DListPushBack(new_dlist, &num2);
	DListPushBack(new_dlist, &num3);
	DListPushBack(new_dlist, &num3);
    
	i = DListMultiFind(DListBegin(new_dlist), DListEnd(new_dlist), MatchInt, 
	&num3, output_list);
    
	if (2 == i && 2 == DListCount(output_list))
	{
		printf("TestDListMultiFind -\tPASSED!\n");
	}
	else
	{
		printf("TestDListMultiFind -\tFAILED!\n");
		DListDestroy(new_dlist);
		DListDestroy(output_list);
		return FAIL;
	}
	
	DListDestroy(new_dlist);
	DListDestroy(output_list);
	
	return SUCCESS;
}
	
	
/***************************service functions****************************/    
static int MatchInt(const void *data, void *param)
{
	return (*((int *)data) == *((int *)param));
}


static int IntAction(void *data, void *param)
{
	*(int *)data += *(int *)param;

	return 0;
}

