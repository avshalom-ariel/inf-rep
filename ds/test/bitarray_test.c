
#include "bitarray.h" /*all the func declarations*/
#include <stdio.h> /*printf*/
#include <assert.h> /*assert*/




int main(void)
{
	char buffer[65] = {0};
	
	/*SetAll test*/
	assert(-1 == (int)SetAll(220));
	
	/*ResetAll test*/
	assert(0 == ResetAll(220));
	
	/*SetBitOn test*/
	assert(4 == SetBitOn(0, 2));
	
	/*SetBitOff test*/
	assert(14 == SetBitOff(15, 0));
	
	/*SetBit test*/
	assert(36 == SetBit(32, 2, 1));
	
	/*GetVal test*/
	assert(1 == GetVal(32, 5));
	
	assert(32 == FlipBit(48, 4));
	
	/*FlipAll test*/
	assert(-33 == FlipAll(32));
	
	/*Mirror test*/
	assert(128 == Mirror(72057594037927936));
	
	/*RotateRight test*/
	assert(2 == RotateRight(4, 1));
	
	/*RotateLeft test*/
	assert(16 == RotateLeft(4, 2));
	
	/*CountOn test*/
	assert(5 == CountOn(31));
	
	/*CountOff test*/
	assert(59 == CountOff(31));
	
	/*ToString test*/
	printf("Should be five ones at beginig (repressenting 31):\n%s", ToString(31, buffer));
	
	/*CountOnLUT test*/
	assert(5 == CountOnLUT(31));
	
	/*MirrorLUT test*/
	assert(128 == MirrorLUT(72057594037927936));
	printf("\n");
	
	printf("\nAll tests passed!\n\n");
	return 0;
}





