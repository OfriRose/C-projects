/*
    Developer: Ofri Rozner
    Reviwer: Shahar Molina
    Date: 06/09/23
    cbuff - src file
*/

#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */
#include <stdio.h>  /*printf*/
#include <string.h> /*memcpy*/

#include "cbuff.h" /* cbuff API */

/***********************************Structs************************************/
struct c_buff
{
	char *read;
	char *write;
	size_t capacity;
	char buffer[1];
};

/***********************************Defines************************************/
#define DUMMY_SIZE 1

/******************************utiliyu functions*******************************/
static size_t Min(size_t param1, size_t param2);

/*******************************Implementation*********************************/

c_buff_t *CBuffCreate(size_t capacity)
{
	c_buff_t *new_buff =
	    (c_buff_t *)malloc(sizeof(c_buff_t) + capacity * sizeof(char));
	if (NULL == new_buff)
	{
		return NULL;
	}

	new_buff->read = new_buff->buffer + 1;
	new_buff->write = new_buff->buffer + 1;
	new_buff->capacity = capacity;
	*new_buff->buffer = 0;

	return new_buff;
}

void CBuffDestroy(c_buff_t *cbuff)
{
	assert(cbuff);

	free(cbuff);

	cbuff = NULL;
}

size_t CBuffSize(const c_buff_t *cbuff)
{
	assert(cbuff);

	if (cbuff->write > cbuff->read)
	{
		return (cbuff->write - cbuff->read);
	}

	else if (cbuff->write < cbuff->read)
	{
		return cbuff->capacity - (cbuff->read - cbuff->write);
	}

	return (*cbuff->buffer) ? (cbuff->capacity) : (0);
}

size_t CBuffFreeSpace(const c_buff_t *cbuff)
{
	size_t size = 0; 
	assert(cbuff);
	size = CBuffSize(cbuff);

	return (cbuff->capacity - size);
}

int CBuffIsEmpty(const c_buff_t *cbuff)
{
	assert(cbuff);
	return (CBuffSize(cbuff) == 0);
}

ssize_t CBuffRead(void *dest, c_buff_t *cbuff, size_t cnt)
{
	size_t to_read = 0;
	char *begin = NULL;
	size_t offset = 0;

	assert(NULL != dest);
	assert(NULL != cbuff);

	begin = cbuff->buffer + DUMMY_SIZE;
	offset = cbuff->read - begin;

	cnt = Min(cnt, CBuffSize(cbuff));
	to_read = Min(cnt, cbuff->capacity - offset);

	memcpy((char *)dest, cbuff->read, to_read);
	memcpy((char *)dest + to_read, begin, cnt - to_read);
	cbuff->read = begin + ((offset + cnt) % cbuff->capacity);

	if (0 != cnt)
	{
		*cbuff->buffer = 0;
	}

	return (ssize_t)cnt;
}

ssize_t CBuffWrite(c_buff_t *cbuff, const void *src, size_t cnt)
{
	size_t to_write = 0;
	char *begin = NULL;
	size_t offset = 0;

	if (NULL == cbuff || NULL == src || 0 == cnt)
	{
		return 0;
	}

	begin = cbuff->buffer + DUMMY_SIZE;
	offset = cbuff->write - begin;

	cnt = Min(cnt, CBuffFreeSpace(cbuff));
	to_write = Min(cnt, cbuff->capacity - offset);

	memcpy(cbuff->write, (const char *)src, to_write);
	memcpy(begin, (const char *)src + to_write, cnt - to_write);
	cbuff->write = begin + ((offset + cnt) % cbuff->capacity);

	if (cbuff->read == cbuff->write)
	{
		*cbuff->buffer = 1;
	}

	return (ssize_t)cnt;
}

/****************************utiliyu functions*****************************/
static size_t Min(size_t param1, size_t param2)
{
	return (param1 > param2) ? (param2) : (param1);
}
