#include <stdio.h> /*printf*/



int CountBitCouple(char byte)
{
	int i = 0;
	int count = 0;
	
	for(; i < 8; ++i)
	{
		if((byte & 1) && (byte >> 1) & 1)
		{
			++count;
		}
		
		byte >>= 1;
	}
	
	return count;
}


void Swap1(int *num1, int *num2)
{
	*num1 = *num1 + *num2;
	*num2 = *num1 - *num2;
	*num1 = *num1 - *num2;
}



void Swap2(int *num1, int *num2)
{
	int temp = *num1;
	*num1 = *num2;
	*num2 = temp;
}



void Swap3(int *num1, int *num2)
{
	*num1 = *num1 ^ *num2;
	*num2 = *num1 ^ *num2;
	*num1 = *num1 ^ *num2;
}


int BitCount(long num)
{
	int count = 0;
	
	while(num)
	{
		if(num & 1)
		{
			++count;
		}
		
		num >>= 1;
	}
	
	return count;	
}


int main(void)
{
	int num1 = 1;
	int num2 = 2;
	char byte = 27; /*00011011*/
	long num_to_count_bits = 299289957; /*00010001110101101100110101100101 which have 16 bits on*/
	
	printf("expected value: 2, result value: %d\n", CountBitCouple(byte));
	
	Swap1(&num1, &num2);
	
	printf("Before swap: num1 = 1, num2 = 2, after swap: num1 =  %d\n, num2 = %d\n", num1,num2);
	
	Swap2(&num1, &num2);
	
	printf("Before swap: num1 = 2, num2 = 1, after swap: num1 =  %d\n, num2 = %d\n", num1,num2);
	
	Swap3(&num1, &num2);
	
	printf("Before swap: num1 = 1, num2 = 2, after swap: num1 =  %d\n, num2 = %d\n", num1,num2);
	
	printf("expected value: 16, result value:%d\n", BitCount(num_to_count_bits));
	
	
	return 0;
}












