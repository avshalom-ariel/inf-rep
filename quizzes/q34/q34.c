
#include <stdio.h>		/*printf*/
#include <stddef.h>		/*size_t*/

static int WasCharFound(char *arr, size_t arr_size, char loot);
static void RotateNTimes(char *arr, size_t arr_size, size_t N);
static void Reverse(char *arr, size_t start, size_t end);
static void Swap(char *a, char *b);
static void PrintArr(char *arr, size_t arr_size);

int main(void)
{
	char arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int status = 0;
	size_t i = 0;
	
	for (; 10 > i; ++i)
	{
		status += WasCharFound(arr, 10, i);
/*		printf("status = %d\n", status);*/
	}
	
	printf("array before rotate 3:\n");
	PrintArr(arr, 10);
	
	RotateNTimes(arr, 10, 3);
	
	printf("array after rotate 3:\n");
	PrintArr(arr, 10);
	
	if (0 == status)
	{
		printf("_________________\n");
		printf("All Tests Passed!\n");
	}
	else
	{
		printf("_________________\n");
		printf("Test Failed\n");
	}
	
	return 0;
}

int WasCharFound(char *arr, size_t arr_size, char loot)
{
	size_t i = 0;
	int result = 1;
	
	for (; i < arr_size; ++i)
	{
		result *= (int)(*arr - loot);
		++arr;
	}
	
	return result;
}

void RotateNTimes(char *arr, size_t arr_size, size_t N)
{
	N %= arr_size;
	
	Reverse(arr, 0, arr_size - 1);
	Reverse(arr, 0, N - 1);
	Reverse(arr, N, arr_size - 1);
}

void Reverse(char *arr, size_t start, size_t end)
{
	while(start < end)
	{
		Swap(&arr[start], &arr[end]);
		++start;
		--end;
	}
}

void Swap(char *a, char *b)
{
	char temp = *a;
	*a = *b;
	*b = temp;
}

void PrintArr(char *arr, size_t arr_size)
{
	size_t i = 0;
	
	for (; arr_size > i; ++i)
	{
		printf("%d, ", *arr);
		++arr;
	}
	
	printf("\n");
}


