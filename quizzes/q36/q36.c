
#include <stdio.h>	/*printf*/
#include <stddef.h>	/*size_t*/

static void Swap(int *num1, int *num2);
static size_t Min(int *arr, size_t arr_size);
static size_t MinMaxValue(int *arr, size_t arr_size, int min_value_to_write);

static void BubbleSort(int *arr, size_t arr_size);
static void SelectionSort(int *arr, size_t arr_size);
static void InsertionSort(int *arr, size_t arr_size);

int main(void)
{
	int result[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	int arr1[] = {2, 4, 5, 6, 8, 1, 3, 10, 7, 9};
	int arr2[] = {2, 4, 5, 6, 8, 1, 3, 10, 7, 9};
	int arr3[] = {2, 4, 5, 6, 8, 1, 3, 10, 7, 9};
	int failiure_status = 0;
	size_t i = 0;
	
	BubbleSort(arr1, sizeof(arr1) / sizeof(arr1[0]));
	SelectionSort(arr2, sizeof(arr2) / sizeof(arr2[0]));
	InsertionSort(arr3, sizeof(arr3) / sizeof(arr3[0]));
	
	for (i = 0; i < sizeof(arr1) / sizeof(arr1[0]); ++i)
	{
		if (arr1[i] != result[i])
		{
			printf("arr1 sort failed!\n");
			printf("expected %d, received: %d\n", result[i], arr1[i]);
			printf("i = %ld\n", i);
			++failiure_status;
		}
	}
	
	for (i = 0; i < sizeof(arr2) / sizeof(arr2[0]); ++i)
	{
		if (arr2[i] != result[i])
		{
			printf("arr2 sort failed!\n");
			printf("expected %d, received: %d\n", result[i], arr2[i]);
			printf("i = %ld\n", i);
			++failiure_status;
		}
	}
	
	for (i = 0; i < sizeof(arr3) / sizeof(arr3[0]); ++i)
	{
		if (arr3[i] != result[i])
		{
			printf("arr3 sort failed!\n");
			printf("expected %d, received: %d\n", result[i], arr3[i]);
			printf("i = %ld\n", i);
			++failiure_status;
		}
	}
	
	
	if (failiure_status)
	{
		printf("failed in %d many results!\n", failiure_status);
	}
	else
	{
		printf("All tests are passed!\n");
	}
	
	return 0;
}


/***********************************/
/*			Sort Functions		   */
/***********************************/


void BubbleSort(int *arr, size_t arr_size)
{
	size_t i = 0;
	size_t j = 0;
	size_t decreasing_size = arr_size;
	
	for (; i < arr_size; ++i)
	{
		for (j = 0; j < decreasing_size - 1; ++j)
		{
			if (arr[j] > arr[j + 1])
			{
				Swap(arr + j, arr + j + 1);
			}
		}
		
		--decreasing_size;
	}
}

void SelectionSort(int *arr, size_t arr_size)
{
	int index_to_swap = arr[0];
	size_t i = 0;
	
	Swap(arr, arr + Min(arr, arr_size));
	
	for (i = 1; i < arr_size; ++i)
	{
		index_to_swap = MinMaxValue(arr + i, arr_size - i, arr[i - 1]);

		Swap(arr + i, arr + index_to_swap + i);
	}
}


void InsertionSort(int *arr, size_t arr_size)
{
    size_t i = 0;
    size_t j = 0; 
    
    for (i = 1; i < arr_size; ++i)
    {
        j = i;

        while (arr[j - 1] > arr[j] && 0 < j) 
        {
			Swap(arr + j, arr + j - 1);
            j -= 1;
        }
    }
}


/***********************************/
/*			Help Functions		   */
/***********************************/


size_t Min(int *arr, size_t arr_size)
{
	size_t min_index = 0;
	size_t i = 0;
	
	for(; i < arr_size; ++i)
	{
		if (arr[i] < arr[min_index])
		{
			min_index = i;
		}
	}
	
	return min_index;
}

size_t MinMaxValue(int *arr, size_t arr_size, int min_value_to_write)
{
	size_t nominator_index = 0;
	size_t i = 0;
	
	for(; i < arr_size; ++i)
	{
		if (arr[i] < arr[nominator_index] && min_value_to_write <= arr[i])
		{
			nominator_index = i;
		}
	}
	
	return nominator_index;
}


void Swap(int *num1, int *num2)
{
	int temp = *num1;
	*num1 = *num2;
	*num2 = temp;
}


