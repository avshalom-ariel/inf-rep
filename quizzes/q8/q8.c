#include <stddef.h> /*NULL*/
#include <stdio.h> /*printf*/
#include <stdlib.h> /*malloc*/

int *MaxSubarray(int *arr, int arr_size);

int main(void)
{
	int array[10] = {-2, 1, -3, 7, -8, -1, 2, 3, -5, 4};
	int *result = MaxSubarray(array, 10);
	printf ("the max is: %d\nths start is: %d\nthe end is: %d\n", result[0], result[1], result[2]);
	
	return 0;
}


int *MaxSubarray(int *arr, int arr_size)
{
	int i;
	int cur_start = 0;
	int cur_end = 0;
	int cur_sum = 0;
	int max_start = 0;
	int max_end = 0;
	int max_sum = 0;
	
	int *result = (int *)malloc(sizeof(int) * 3);
	
	if (NULL == result)
	{
		perror("memory allocation failed");
	}
	
	for (i = 0; i < arr_size; ++i)
	{
		if (cur_sum + arr[i] >= 0)
		{
			cur_sum += arr[i];
			cur_end = i;
			
		}
		else
		{
			cur_start = i + 1;
			cur_sum = 0;
			
		}
		if (cur_sum > max_sum)
		{
			max_sum = cur_sum;
			max_start = cur_start;
			max_end = cur_end;
		}
	
	}
	
	result[0] = max_sum;
	result[1] = max_start;
	result[2] = max_end;
	
	return (result);
	
	free (result);
}






