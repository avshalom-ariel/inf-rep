
#include <stdio.h>

long *SumIntPairsToLong(int ints[], size_t numOfElements);


int main(void)
{
	int ints[6] = {1, 6, 256, -3, 8, 12};
	
	long *result = NULL;
	
	result = SumIntPairsToLong(ints, 6);
	
	printf("%ld %ld %ld\n", *result, *(result + 1), *(result + 2));
	
	return 0;
}


long *SumIntPairsToLong(int ints[], size_t numOfElements)
{
	size_t i = 0;
	
	for(; i < numOfElements; i += 2)
	{
		*((long *)ints + i/2) = ints[i] + ints[i + 1];
	}
	
	return (long *)ints;
}

