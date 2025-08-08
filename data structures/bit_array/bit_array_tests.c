/*******************************************************************************
*			NAME: OFRI ROZNER					  *
*			REVIWER: Roiy Mastor					  *
*			DATE: 28.8					 	  *
*			WS: DATA_STRUCTERS					  *
*******************************************************************************/

#include <stdio.h>/*printf*/
#include <limits.h>/*char_bit*/

#include "bit_array.h"/*bit_array custom library*/

#define ARRAY_SIZE (sizeof(size_t)) * (CHAR_BIT)

static void PrintBits(bitarr_t bitarr);
static void TestSetAll(bitarr_t bitarr);
static void TestReSetAll(bitarr_t bitarr);
static void TestSetBitOn(bitarr_t bitarr);
static void TestSetBitOff(bitarr_t bitarr);
static void TestSetBit(bitarr_t bitarr);
static void TestBitArrGetBit(bitarr_t bitarr);
static void TestBitArrIsBitOn(bitarr_t bitarr);
static void TestBitArrIsBitOff(bitarr_t bitarr);
static void TestBitArrFlipBit(bitarr_t bitarr);
static void TestRotate(bitarr_t bitarr);
static void TestBitArrCountSetBits(bitarr_t bitarr);
static void TestBitArrCountSetBitsLUT(bitarr_t bitarr);
static void TestBitArrCountOffBits(bitarr_t bitarr);
static void TestBitArrToString(bitarr_t bitarr);
static void TestMirror(bitarr_t bitarr);
static void TestMirrorLUT(bitarr_t bitarr);

int main()
{
	bitarr_t bitarr = 3;
	printf("Original bit array:\n");
	PrintBits(bitarr);
	printf("\n\n");  
	TestSetAll(bitarr);
	TestReSetAll(bitarr);
	TestSetBitOff(bitarr);
	TestSetBitOn(bitarr);
	TestSetBit(bitarr);
	TestBitArrGetBit(bitarr);
	TestBitArrIsBitOn(bitarr);
	TestBitArrIsBitOff(bitarr);
	TestBitArrFlipBit(bitarr);
	TestRotate(bitarr);
	TestBitArrCountSetBits(bitarr);
	TestBitArrCountSetBitsLUT(bitarr);
	TestBitArrCountOffBits(bitarr);
	TestBitArrToString(bitarr);
	TestMirror(bitarr);
	TestMirrorLUT(bitarr);
 
	return 0;
}

static void PrintBits(bitarr_t bitarr)
{
	char bit_arr_string[ARRAY_SIZE + 1];
	BitArrToString(bit_arr_string, bitarr);
	printf("%s\n", bit_arr_string);
}

static void TestSetAll(bitarr_t bitarr)
{
	printf("Set All Test:\n");
	bitarr = BitArrSetAll(bitarr);
	PrintBits(bitarr);
	printf("\n\n");
}

static void TestReSetAll(bitarr_t bitarr)
{
	printf("ReSet All Test:\n");
	bitarr = BitArrReSetAll(bitarr);
	PrintBits(bitarr);
	printf("\n\n");
}

static void TestSetBitOn(bitarr_t bitarr)
{
	printf("Set 5th bit on test:\n");
	bitarr = BitArrSetBitOn(bitarr, 5);
	PrintBits(bitarr);
	printf("\n\n");
}

static void TestSetBitOff(bitarr_t bitarr)
{
	printf("Set 5th bit off test:\n");
	bitarr = BitArrSetBitOff(bitarr, 5);
	PrintBits(bitarr);
	printf("\n\n");
}

static void TestSetBit(bitarr_t bitarr)
{
	printf("Set 10th bit on test:\n");
	bitarr = BitArrSetBit(bitarr, 10, 1);
	PrintBits(bitarr);
	printf("\n\n");  
	printf("Set 10th bit off test:\n");
	bitarr = BitArrSetBit(bitarr, 10, 0);
	PrintBits(bitarr);
	printf("\n\n");
}

static void TestBitArrGetBit(bitarr_t bitarr)
{
	int bit;
	printf("Get 5th bit test:\n");
	bit = BitArrGetBit(bitarr, 5);
	printf("%d\n\n", bit);
}

static void TestBitArrIsBitOn(bitarr_t bitarr)
{
	int is_on;
	printf("Is 5th bit on test:\n");
	is_on = BitArrIsBitOn(bitarr, 5);
	printf("%d\n\n", is_on);
}

static void TestBitArrIsBitOff(bitarr_t bitarr)
{
	int is_off;
	printf("Is 5th bit off test:\n");
	is_off = BitArrIsBitOff(bitarr, 5);
	printf("%d\n\n", is_off);
}

static void TestBitArrFlipBit(bitarr_t bitarr)
{
	printf("Flip 5th bit test:\n");
	bitarr = BitArrFlipBit(bitarr, 5);
	PrintBits(bitarr);
	printf("\n\n");
}

static void TestRotate(bitarr_t bitarr)
{
	printf("Before rotate right:\n");
	bitarr = 15;
	PrintBits(bitarr);
	printf("\n\n");

	printf("After rotate right (n=3):\n");
	bitarr = BitArrRotateRight(bitarr, 3);
	PrintBits(bitarr);
	printf("\n\n");

	printf("After rotate left (n=2):\n");
	bitarr = BitArrRotateLeft(bitarr, 2);
	PrintBits(bitarr);
	printf("\n\n");
}

static void TestBitArrCountSetBits(bitarr_t bitarr)
{
	size_t count = 0;
	bitarr = 3;
	printf("Set bit count:\n");
	count = BitArrCountSetBits(bitarr);
	printf("%lu\n\n", count);
}

static void TestBitArrCountSetBitsLUT(bitarr_t bitarr)
{
	size_t count = 0;
	bitarr = 3;
	printf("Set bit count (LUT):\n");
	count = BitArrCountSetBitsLUT(bitarr);
	printf("%lu\n\n", count);
}

static void TestBitArrCountOffBits(bitarr_t bitarr)
{
	size_t count = 0;
	printf("Off bit count:\n");
	count = BitArrCountOffBits(bitarr);
	printf("%lu\n\n", count);
}

static void TestBitArrToString(bitarr_t bitarr)
{
	char bit_arr_string[ARRAY_SIZE + 1];
	printf("BitArrToString:\n");
	BitArrToString(bit_arr_string, bitarr);
	printf("%s\n\n", bit_arr_string);
}

static void TestMirror(bitarr_t bitarr)
{
	printf("Test mirror:\n");
	bitarr = 11;
	printf("before mirror:\n");
	PrintBits(bitarr);
	bitarr = BitArrMirror(bitarr);
	printf("after mirror:\n");
	PrintBits(bitarr);
	printf("\n\n");
}

static void TestMirrorLUT(bitarr_t bitarr)
{
	printf("Test mirror (LUT):\n");
	printf("before mirrorLUT:\n");
	PrintBits(bitarr);
	bitarr = BitArrMirrorLUT(bitarr);
	printf("after mirrorLUT:\n");
	PrintBits(bitarr);
	printf("\n\n");
}

