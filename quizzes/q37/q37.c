
#include <stdio.h> 	/*printf*/
#include <stddef.h>	/*size_t*/

static size_t NumOfRot(int *arr, size_t arr_size);

int main(void)
{
	int arr[] = {7, 8, 11, 1, 4, 5};
	int arr2[] = {7, 8, 11, 12, 4, 5, 6};

	printf("Number of rotations is: %lu\n", NumOfRot(arr, sizeof(arr) / sizeof(int)));
	printf("Number of rotations is: %lu\n", NumOfRot(arr2, sizeof(arr2) / sizeof(int)));


	return 0;
}


size_t NumOfRot(int *arr, size_t arr_size)
{
	size_t start = 0;
	size_t end = arr_size - 1;
	size_t mid = (start + end) / 2;

	while (start < end - 1)
	{
		if (arr[start] > arr[mid])
		{
			end = mid;
			mid = (start + end) / 2;
		}
		else if (arr[end] < arr[mid])
		{
			start = mid;
			mid = (start + end) / 2;
		}
	}

	return end;
}


