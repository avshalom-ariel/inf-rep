
#include <stdio.h> /*printf*/
#include <stddef.h> /*size_t*/

static size_t Search(int *arr, size_t size, int loot);
static size_t BinaryCircularSearch(int *arr, size_t start, size_t end, int loot);

int main(void)
{
	int arr1[7] = {7, 8, 11, 1, 4, 5, 6};
	int arr2[20] = {10, 11, 15, 16, 30, 50, 60, 70, 100, 120, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	
	if (2 == Search(arr1, 7, 11) && 13 == Search(arr2, 20, 3))
	{
		printf("All Tests succeed!\n");
	}
	else
	{
		printf("Test failed!\n");
	}
	
	
	return 0;
}

size_t Search(int *arr, size_t size, int loot)
{
	size_t result = BinaryCircularSearch(arr, 0, size-1, loot);
	
	return result;
}

size_t BinaryCircularSearch(int *arr, size_t start, size_t end, int loot)
{
	size_t mid = (start + end) / 2;
	
	if (arr[mid] == loot)
	{
		return mid;
	}
	
	if (loot > arr[mid])
	{
		if (loot > arr[end])
		{
			return BinaryCircularSearch(arr, start, mid - 1, loot);
		}
		else
		{
			return BinaryCircularSearch(arr, mid + 1, end, loot);
		}
	}
	else
	{
		if (loot < arr[start])
		{
			return BinaryCircularSearch(arr, mid + 1, end, loot);
		}
		else
		{
			return BinaryCircularSearch(arr, start, mid - 1, loot);
		}
	}
}


