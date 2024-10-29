

#include <stdio.h> /*printf*/

#include "ws9.h"





int main(void)
{
	
	unsigned int arr[3] = {0};
	int size = 3; 
	unsigned int x = 0;
	unsigned int y = 0;
	float a = 0, b = 0;

	float f = 0;
	
	
	printf("%ld", Pow2(2,3));
	
	printf("%d", Pow2CheckWithLoop(4096));
	
	printf("%d", Pow2CheckWithoutLoop(4096));
	
	printf("%d", add1(410));
	
	
	
	arr[0] = 7;
	arr[1] = 11;
	arr[2] = 13;
	
	ThreeBytePrint(arr, size);   
	
	printf("%d\n", ByteMirror(1));
	
	printf("%d\n", ByteMirrorLoop(64));
	
	printf("%d\n", True1(34)); 
	
	printf("%d\n", True2(3));

	printf("%d\n", Swap3_5(4));
	
	printf("%d\n", CloseDiv16(64));
	

	x = 2;
	y = 4;
	
	printf("before:x = %d and y = %d\n", x, y);
	Swap(&x, &y);
	printf("after:x = %d and y = %d\n", x, y);
	
	
	printf("%d\n", BitCountLoop(31));
	
	printf("%d\n", BitCount(16));
	
	BitPrint(1.1);
	
	
	a = 1.1;
	b = 2.2;
	
	printf("before:x = %f and y = %f\n", a, b);
	Swap(&x, &y);
	printf("after:x = %f and y = %f\n", a, b);
	
	x = 5;
	
	printf("%u %u %u ", x, x << 2, x >> 2 );
	
	
	printf("%d", -8 << 1);
	
	
	f = 1.111;
	
	BitPrint(f);
	
	
	DoubleBitCount(1.111);
	
	FloateBitCount(1.11);
	
	
	return 0;	
}






