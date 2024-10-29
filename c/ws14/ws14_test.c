#include <stdio.h> /*printf*/
#include <string.h> /*memcpy*/

#include "ws14.h"


int main(void)
{
	
	char arr1[5] = {'a', '5', 'T', 'y', 'T'};
	char arr2[5] = {'a', '5', 'T', 'y', 'T'};
	char arr3[6] = {'a', '5', '3', 'k', 's', 'q'};
	
	char atoi1[64] = {0};
	int base1 = 0; 

	char itoa1[64] = {0};
	int result1= 0; 
	
	char atoi2[64] = {0};
	int base2= 0; 

	char itoa2[64] = {0};
	int result2= 0; 
	
	base1 = 13;
	base2 = 16;
	
	
	memcpy(atoi1, "1A8B", 5);
	
	MyItoa(itoa1, 4002, base1);
	
	printf("Itoa result %s\n", itoa1);
	
	result1 = MyAtoi(atoi1, base1);
	
	printf("Atoi result %d\n", result1);
	
	
	
	memcpy(atoi2, "CE10",5);
	
	MyItoa(itoa2, 52752, base2);
	
	printf("Itoa result %s\n", itoa2);
	
	result2 = MyAtoi(atoi2, base2);
	
	printf("Atoi result %d\n", result2);
	
	
	AtoiTest("1020");
	
	AtoiExamples();
	
	
	DoubleParallelArray(arr1, arr2, arr3, 4, 4, 5);
	
	EndianCheck();
	ENDIAN_CHECK2	
	
	return 0;
}


