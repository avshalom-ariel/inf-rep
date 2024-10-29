
#include <stdio.h> /*printf*/

static void ZeroOneSort(int *arr, size_t arr_size);
static void Swap(int *num1, int *num2);


int main(void)
{
	int arr[10] = {0, 1, 0, 1, 0, 1, 0, 1, 0, 1};
	size_t i = 0;
	
	ZeroOneSort(arr, 10);
	
	for (; i < 10; ++i)
	{
		printf("%d", arr[i]);
	}
	
	printf("\n");
	
	return 0;
}


void ZeroOneSort(int *arr, size_t arr_size)
{
	size_t i = 0, curr = 0;
	
	while(i < arr_size)
	{
		if (0 == arr[curr])
		{
			++curr;
		}
		else if (arr[curr] > arr[i])
		{
			Swap(arr + curr, arr + i);
			++i;
			++curr;
		}
		else
		{
			++i;
		}
		
		if (curr > i)
		{
			++i;
		}
	}
}


void Swap(int *num1, int *num2)
{
	int temp = *num1;
	*num1 = *num2;
	*num2 = temp;
}


