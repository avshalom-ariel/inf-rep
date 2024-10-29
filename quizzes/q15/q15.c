

#include <stddef.h>
#include <stdio.h>



int FindNumArr(int *arr, int num, size_t size);




int main(void)
{
	int arr1[5] = {1, 2, 3, 4, 5};
	int arr2[6] = {6, 7, 8, 9, 10, 11};
	
	int num = 3;
	
	if(FindNumArr(arr1, num, 5) == 1)
	{
		printf("Test1 Passed!\n");
	}
	
	if(FindNumArr(arr2, num, 6) == 0)
	{
		printf("Test2 Passed!\n");
	}
	
	
	
	return 0;
}


int FindNumArr(int *arr, int num, size_t size)
{
	int check = 1;
	size_t i = 0;
	
	for(; i < size; ++i)
	{
		check *= arr[i] - num;
	}
		
	return (0 == check);
}
