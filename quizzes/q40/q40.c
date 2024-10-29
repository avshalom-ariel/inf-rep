
#include <stdio.h>	/*printf*/

static size_t ConsecutiveBitCount(int num);

int main()
{
	int num1 = 157;	/*3*/
	int num2 = 341;	/*1*/
	int num3 = 1279; /*8*/
	
	printf("%d has: %ld bits turned on.\n", num1, ConsecutiveBitCount(num1));
	printf("%d has: %ld bits turned on.\n", num2, ConsecutiveBitCount(num2));
	printf("%d has: %ld bits turned on.\n", num3, ConsecutiveBitCount(num3));

	return 0;
}

size_t ConsecutiveBitCount(int num)
{
	size_t count = 0;
	size_t result = 0;
	
	while (num)
	{
		++count;
		count *= (num & 1);
		num >>= 1;
		
		if (result < count)
		{
			result = count;
		}
	}

	return result;
}


