/* --------------------------------------------------*/ 
/* Filename: cbuff.c         			      */
/* Author:  Ofri Rozner       		      */ 
/* Reviewer: Shahar Molina   			      */
/* Date: 06.09.2023     			      */
/* Description:  API for circular buffer            */
/* -------------------------------------------------*/

/*DESCRIPTION:
an API for a circular buffer data structure. Save data in a linear circular manner 
that allows for easy streaming of data using FIFO (first in first out) mechanics
used for a stream of bytes. 
main functions: create, destroy, read, write.
*/


#ifndef __ILRD_OL149_CBUFF_H__
#define __ILRD_OL149_CBUFF_H__

#include <sys/types.h> /* size_t, ssize_t */

typedef struct c_buff c_buff_t;

/**
creates a new circular buffer
@param capacity the buffer's capacity
@return a handle to the cbuff or NULL on error
@note: capacity < 0 is undefined behaviour
@note use CBuffDestroy() after use
Time O(1), space O(1)*/
c_buff_t *CBuffCreate(size_t capacity);

/**
Destorys a buffer
@param cbuff a handler to a buffer to remove
Time O(1), space O(1) */
void CBuffDestroy(c_buff_t *cbuff);

/**
write to a buffer
@param cbuff a handler to a buffer 
@param src a source to write data from 
@param cnt the number of bits to write  from src
@return the number of bits that were written, or negative number on error
@note undefined behaviour if  cnt > dest or cnt < 0
Time O(n), space O(1) */
ssize_t CBuffWrite(c_buff_t *cbuff, const void *src, size_t cnt);

/**
Reads data from a buffer and stores in dest 
@param cbuff a handler to a buffer 
@param dest a destination to read into
@param cnt the number of bits to read  from cbuff
@return the number of bits that were written, or negative number on error
@note undefined behaviour if  cnt > dest or cnt < 0
Time O(n), space O(1) */
ssize_t CBuffRead(void *dest, c_buff_t *cbuff, size_t cnt);

/**
gets a buffer's current size of written bits
@param cbuff a handler to a buffer 
@return the number of written bits in the buffer
Time O(1), space O(1) */
size_t CBuffSize(const c_buff_t *cbuff);

/**
gets the number of bits left to write on cbuff
@param cbuff a handler to a buffer 
@return the buffer's free space
Time O(1), space O(1) */
size_t CBuffFreeSpace(const c_buff_t *cbuff);

/**
check if the buffer is empty
@param cbuff a handler to a buffer 
@return 1 if the buffer is empty or 0 otherwise
Time O(1) Space O(1) */
int CBuffIsEmpty(const c_buff_t *cbuff);

#endif /* __ILRD_OL149_CBUFF_H__ */
