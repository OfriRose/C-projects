/*******************************************************************************
*			NAME: OFRI ROZNER					  *
*			REVIWER: Roiy Mastor					  *
*			DATE: 28.8					 	  *
*			WS: DATA_STRUCTERS					  *
*******************************************************************************/
#include <assert.h>/*assert*/
#include <stdlib.h>/*malloc*/
#include <string.h>/*mamcpy,strcpy*/
#include <limits.h>/*CHAR_BIT*/

#include "bit_array.h"/*bit_array custom library*/

/*********utility functions*********/
static void MirrorLutInit(unsigned char miror_lut[]);
static void CountLutInit(unsigned char count_lut[]);
static unsigned char ByteMirror(unsigned char ch);

/*********defines*********/
#define ARRAY_SIZE (sizeof(size_t)) * (CHAR_BIT)
#define LUT_SIZE 256
#define SHIFT_BIT_LEFT(num, n) ((num) <<= ((n) - 1))

/*******************************************************************************
				FUNCTIONS
*******************************************************************************/
bitarr_t BitArrSetAll(bitarr_t bit_arr)
{
	size_t mask = ~0;
	
	assert(bit_arr);
	
	return bit_arr | mask;
}

bitarr_t BitArrReSetAll(bitarr_t bit_arr)
{
	(void)bit_arr;
	
	return (bitarr_t)0;
}

bitarr_t BitArrSetBitOn(bitarr_t bit_arr, size_t index)
{
	size_t mask = 1;
	SHIFT_BIT_LEFT(mask, index);
	
	assert (ARRAY_SIZE >= index);
	
	return (bit_arr | mask);
}

bitarr_t BitArrSetBitOff(bitarr_t bit_arr, size_t index)
{
	size_t mask = ~(1 << (index - 1));
	
	assert (ARRAY_SIZE >= index);
	
	return (bit_arr & mask);
}

bitarr_t BitArrSetBit(bitarr_t bit_arr, size_t index, int value)
{
	size_t mask = 1;

	assert ((0 == value) || (1 == value));
	assert (index <= ARRAY_SIZE);
	
	SHIFT_BIT_LEFT(mask, index);

	return (value == 1) ? (bit_arr | mask) : (bit_arr & ~mask);
}

int BitArrGetBit(bitarr_t bit_arr, size_t index)
{
	assert (ARRAY_SIZE >= index);
	
	return (bit_arr >> index) & 1;
}

int BitArrIsBitOn(bitarr_t bit_arr, size_t index)
{
	size_t mask = 1;

	assert (ARRAY_SIZE >= index);
	
	bit_arr >>= (index - 1);

	return (int) mask & bit_arr;
}

int BitArrIsBitOff(bitarr_t bit_arr, size_t index)
{	
	size_t mask = 1;
	
	assert (ARRAY_SIZE >= index);
	
	bit_arr >>= (index - 1);

	return (int) mask ^ bit_arr;
}

bitarr_t BitArrFlipBit(bitarr_t bit_arr, size_t index)
{
	size_t mask = 1;	
	SHIFT_BIT_LEFT(mask, 1);
	
	assert (ARRAY_SIZE >= index);
	
	return bit_arr ^ mask;
}

bitarr_t BitArrMirror(bitarr_t bit_arr)
{
	bitarr_t mirror = 0;
	unsigned int buffer = 0;
	size_t i = 0;
	
	assert(bit_arr);
	
	for (i = 0; i < ARRAY_SIZE; ++i)
	{
		buffer = bit_arr & 1;
		bit_arr = bit_arr >> 1;
		mirror = (mirror << 1) | buffer;
	}
	
	return mirror;
}

bitarr_t BitArrMirrorLUT(bitarr_t bit_arr)
{
	static unsigned char mirror_lut[LUT_SIZE] = { 0 };
	bitarr_t mirror = 0;
	unsigned char byte_mirror = 0;
	unsigned char mask = 0xFF;
	int i = 0;
	static int  is_miror_lut = 0;
	
	assert(bit_arr);
	
	if (0 == is_miror_lut)
	{
		MirrorLutInit(mirror_lut);
		is_miror_lut = 1;
	}
	
	for (i = 0; i < CHAR_BIT; ++i)
	{
		byte_mirror = (bit_arr & mask);
		byte_mirror = mirror_lut[byte_mirror];
		mirror |= (bitarr_t)byte_mirror << (CHAR_BIT * (CHAR_BIT - i - 1));
		bit_arr >>= CHAR_BIT;
	}

	return mirror;
}

bitarr_t BitArrRotateRight(bitarr_t bit_arr, size_t n)
{
	assert(bit_arr);
	
	return (bit_arr >> n) | (bit_arr << (ARRAY_SIZE - n));;
}

bitarr_t BitArrRotateLeft(bitarr_t bit_arr, size_t n)
{	
	assert(bit_arr);
	
	return (bit_arr << n) | (bit_arr >> (ARRAY_SIZE - n));
}

size_t BitArrCountSetBits(bitarr_t bit_arr)
{
	size_t count = 0;
	
	while (bit_arr)
	{
		bit_arr &= (bit_arr - 1);
		++count;
	}
	
	return count;
}

size_t BitArrCountOffBits(bitarr_t bit_arr)
{
	size_t on_bits_count = 0;
	
	on_bits_count = BitArrCountSetBits(bit_arr);
	
	return (ARRAY_SIZE - on_bits_count);
}

size_t BitArrCountSetBitsLUT(bitarr_t bit_arr)
{
	static unsigned char count_lut[LUT_SIZE] = { 0 };
	size_t i = 0;
	unsigned char byte_count = 0;
	unsigned char mask = ~(0);
	size_t count_set = 0;
	static int is_bit_count_lut = 0;
	
	assert(bit_arr);
	
	if(0 == is_bit_count_lut)
	{
		CountLutInit(count_lut);
		is_bit_count_lut = 1;
	}
	
	for (i = 0; i < CHAR_BIT; ++i)
	{
		byte_count = (bit_arr & mask);
		byte_count = count_lut[byte_count];
		count_set += byte_count;
		bit_arr >>= CHAR_BIT;
	}
	
	return count_set;
}

char *BitArrToString(char *dest, bitarr_t bit_arr)
{
	size_t i = 0;
	size_t mask = 0;
	
	assert(NULL != dest);
	
	for (i = 0; i < ARRAY_SIZE; ++i) 
	{
		mask = bit_arr & 1;
		dest[ARRAY_SIZE - i - 1] = mask + '0';
		bit_arr >>= 1;
	}
    
    dest[ARRAY_SIZE] = '\0';
    
    return dest;
}
	
/*********utility functions*********/

static void MirrorLutInit(unsigned char mirror_lut[])
{
	int i = 0;
	
	for (i = 0; i < LUT_SIZE; ++i)
	{
		*mirror_lut = ByteMirror(i);
		++mirror_lut;
	}
}

static unsigned char ByteMirror(unsigned char ch)
{
	unsigned char mirror = 0;
	unsigned char i = 0;
    
	for (i = 0; i < CHAR_BIT; ++i)
	{
		mirror |= (ch & 1);  
		if (i < CHAR_BIT - 1) 
		{
			mirror <<= 1; 
		}

		ch >>= 1;
	}

	return mirror;
}

static void CountLutInit(unsigned char count_lut[])
{
	int i = 0;
	
	for (i = 0; i < LUT_SIZE; ++i)
	{
		*count_lut = BitArrCountSetBits(i);
		++count_lut;
	}
}
