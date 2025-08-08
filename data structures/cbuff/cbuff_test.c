/*
    Developer: Ofri Rozner
    Reviwer: Shahar Molina    
    Date: 06/09/23
    cbuff - test file
*/


#include <stdio.h>  /* printf */

#include "cbuff.h" /* cbuff API */

/***********************Tests decleration*************************/
 void TestCreateDestroy(void);
void TestReadandWrite(void);
void TestSizeFreeSpace(void);

/***************************Tests impl****************************/    

int main(void)
{
	TestCreateDestroy();
	TestReadandWrite();
	TestSizeFreeSpace();
	
	return 0;
}


void TestCreateDestroy(void)
{
	size_t cap = 10;
	c_buff_t *buff = NULL;
 	
	buff = CBuffCreate(cap);
 	
	if (buff != NULL)
	{
		printf("CREATE -\t\t SUCCESS!\n");
	}
	else
 	{
		printf("CREATE -\t\t FAILURE!\n");
	}
	
	CBuffDestroy(buff);
}


void TestReadandWrite(void)
{	
	ssize_t error_statues = 0;
	size_t cap = 15;
	size_t to_write = 5;
	c_buff_t *buff = NULL;
	char source[] = "ABCDEFGHIJKLMNOPQRST";
	char dest[20];
	buff = CBuffCreate(cap);
	
	error_statues = CBuffWrite(buff, (const void *)source,  to_write);
	if (5 == error_statues)
	{
		printf("WRITE -\t\t\t SUCCESS!\n");
	}
	else
	{
		printf("WRITE -\t\t\t FAILURE!\n");
		printf("WRITE OUTPUT: %lu", error_statues);
	}
	
	error_statues = CBuffRead((void *)dest, buff, 3);
	
	if (3 == error_statues)
	{
		printf("READ -\t\t\t SUCCESS!\n");
	}
	else
	{
		printf("READ -\t\t\t FAILURE!\n");
		printf("READ OUTPUT: %lu", error_statues);
	}
	
	CBuffDestroy(buff);
}


void TestSizeFreeSpace(void)
{
	size_t buff_size = 0;
	size_t to_write = 5;
	size_t cap = 15;
	c_buff_t *buff = NULL;
	char source[] = "ABCDEFGHIJKLMNOPQRST";
	char dest[20];
	buff = CBuffCreate(cap);
	CBuffWrite(buff, (const void *)source,  to_write);
	buff_size = CBuffSize(buff);
	
	if (buff_size == to_write)
	{
		printf("SIZE -\t\t\t SUCCESS!\n");
	}
	
	else
	{
		printf("SIZE -\t\t\t FAILURE!\n");
		printf("SIZE OUTPUT: %ld", buff_size);
	}
	
	if (CBuffFreeSpace(buff) == (cap - buff_size))
	{
		printf("FreeSpace -\t\t SUCCESS!\n");
	}
	
	else
	{
		printf("FreeSpace -\t\t FAILURE!\n");
	}
	
	if (0 == CBuffIsEmpty(buff))
	{
		printf("IS EMPTY(not empty) -\t SUCCESS!\n");
	}
	else
	{
		printf("IS EMPTY(not empty) -\t FAILURE!\n");
	}
	
	CBuffRead((void *)dest, buff, (cap - to_write));
	
	if (1 == CBuffIsEmpty(buff))
	{
		printf("IS EMPTY(empty) -\t SUCCESS!\n");
	}
	else
	{
		printf("IS EMPTY(empty) -\t FAILURE!\n");
	}
	
	to_write = cap;
	CBuffWrite(buff, (const void *)source,  to_write);
	if (0 == CBuffIsEmpty(buff))
	{
		printf("IS EMPTY(full) -\t SUCCESS!\n");
	}
	else
	{
		printf("IS EMPTY(full) -\t FAILURE!\n");
	}
	
	CBuffDestroy(buff);
}
	
