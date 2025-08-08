/*******************************************************************************
*			NAME: OFRI ROZNER					  *
*			REVIWER: Roiy Mastor
*			DATE: 28.8					 	  *
*			WS: DATA_STRUCTERS					  *
*******************************************************************************/

/*
DESCRIPTION: An API for a BIT_ARRAY data structe. aloows user to create store
data in the form of binary bits in an array. the following functions can be used
to edit the value of specific bit or al the array and access values by index.
*/

#ifndef __ILRD_OL149_BIT_ARRAY_H__
#define __ILRD_OL149_BIT_ARRAY_H__

#include <stddef.h> /* size_t */

typedef size_t bitarr_t;


/*
gets the value of a bit

param: bit_arr - The bit array to operate on.
param: index - the index of the bit.
Returns: value of a bit (0 or 1)

notes: undefined behaviour if bit_arr is NULL or if index is out of bound

time complex: O(1), space complex: O(1)*/
int BitArrGetBit(bitarr_t bit_arr, size_t index);

/*
sets the value of a bit to 1. Regardless of its initial value.

param: bit_arr - The bit array to operate on.
param: index - the index of the bit.
Returns: the bit array after the operation.

notes: undefined behaviour if bit_arr is NULL or if index is out of bound

time complex: O(1), space complex: O(1)*/
bitarr_t BitArrSetBitOn(bitarr_t bit_arr, size_t index);

 
/*
sets the value of a bit to 0. Regardless of its initial value.

param: bit_arr - The bit array to operate on.
param: index - the index of the bit.
Returns: the bit array after the operation.

notes: undefined behaviour if bit_arr is NULL or if index is out of bound

time complex: O(1), space complex: O(1)*/
bitarr_t BitArrSetBitOff(bitarr_t bit_arr, size_t index);

/*
sets the value of a bit to a user detarmined value (0 or 1).

param: bit_arr - The bit array to operate on.
param: index - the index of the bit.
param: value - value to set the bit to (1 or 0).
Returns: the bit array after the operation.

notes: undefined behaviour if bit_arr is NULL, if index is out of bound and if 
value is not 0 or 1

time complex: O(1), space complex: O(1)*/
bitarr_t BitArrSetBit(bitarr_t bit_arr, size_t index, int value);

/*
Set all bits in the bit array to 1.

param: bit_arr - The bit array to operate on.
Returns: The bit array with all bits set to 1.


 time complex: O(1), space complex: O(1)*/
bitarr_t BitArrSetAll(bitarr_t bit_arr);

/*
Set all bits in the bit array to 0.

param: bit_arr - The bit array to operate on.
Returns: The bit array with all bits set to 1.


time complex: O(1), space complex: O(1)*/
bitarr_t BitArrReSetAll(bitarr_t bit_arr);

/*
flip the value of a bit, turn 1 into 0 and 0 into 1.

param: bit_arr - The bit array to operate on.
param: index - the index of a bit to operate on.
Returns: the bit array after the operation.

notes: undefined behaviour if bit_arr is NULL or index is out of bound

time complex: O(1), space complex: O(1)*/
bitarr_t BitArrFlipBit(bitarr_t bit_arr, size_t index);

/*

Check if a specific bit at the given index is set to 1.

param: bit_arr - The bit array to operate on.
param: index - The index of the bit to check.

Returns: 1 if the specified bit is set to 1, 0 otherwise.

notes: undefined behaviour if bit_arr is NULL or index is out of bound

time complex: O(1), space complex: O(1)*/
int BitArrIsBitOn(bitarr_t bit_arr, size_t index);

/*
Check if a specific bit at the given index is set to 0.

param: bit_arr - The bit array to operate on.
param: index - The index of the bit to check.

Returns: 1 if the specified bit is set to 0, 0 otherwise.

notes: undefined behaviour if index is out of bound

time complex: O(1), space complex: O(1)*/
int BitArrIsBitOff(bitarr_t bit_arr, size_t index);

/*
Rotate the bit array to the left by a specified number of positions.

param: bit_arr - The bit array to operate on.
param: n - The number of positions to rotate to the left.

Returns: The bit array rotated to the left by n positions.

notes: undefined behaviour if index is out of bound

time complex: O(1), space complex: O(1)*/
bitarr_t BitArrRotateLeft(bitarr_t bit_arr, size_t n);

/*
Rotate the bit array to the right by a specified number of positions.

param: bit_arr - The bit array to operate on.
param: n - The number of positions to rotate to the right.

Returns: The bit array rotated to the right by n positions.

time complex: O(1), space complex: O(1)*/
bitarr_t BitArrRotateRight(bitarr_t bit_arr, size_t n);

/*
Count the number of bits set to 1 in the bit array.

param: bit_arr - The bit array to operate on.

Returns: The number of bits set to 1 in the bit array.

time complex: O(1), space complex: O(1)*/
size_t BitArrCountSetBits(bitarr_t bit_arr);

/*
Count the number of bits set to 1 in the bit array using a LUT.

param: bit_arr - The bit array to operate on.

Returns: The number of bits set to 1 in the bit array.

time complex: O(1), space complex: O(1)*/
size_t BitArrCountSetBitsLUT(bitarr_t bit_arr);

/* 
Count the number of bits set to 0 in the bit array.

param: bit_arr - The bit array to operate on.

Returns: The number of bits set to 0 in the bit array.

time complex: O(1), space complex: O(1)*/
size_t BitArrCountOffBits(bitarr_t bit_arr);

/*
Mirrors the order of the bit in the array

param: bitt_arr - The bit array.

Returns: The mirrored array.

time complex: O(1), space complex: O(1)*/
bitarr_t BitArrMirror(bitarr_t bit_arr);

/*
Mirrors the order of the bit in the array using a LUT.

param: bitt_arr - The bit array.

Returns: The mirrored array.

time complex: O(1), space complex: O(1)*/
bitarr_t BitArrMirrorLUT(bitarr_t bit_arr);

/* 
Convert a bit array into a string format.

param: dest - The destination character array where the string will be stored.
param: bit_arr - The bit array to convert.

Returns: A string representing the array.

notes: undefined behaviour if bit_arr is NULL or *dest is smaller then bit array
 size + 1.

time complex: O(1), space complex: O(1)*/
char *BitArrToString(char *dest, bitarr_t bit_arr);



#endif /* __ILRD_OL149_BIT_ARRAY_H__ */






