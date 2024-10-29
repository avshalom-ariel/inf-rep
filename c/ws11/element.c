#include "programer.h" /*element_t*/

void PrintAll(element_t *arr, int size)
{
	int i;
	
	for (i = 0; i < size; i++)
	{
		arr[i].print(arr[i].element);
	}
}

void AddAll(element_t *arr, int size, int num)
{
	int i;
	
	for (i = 0; i < size; i++)
	{
		arr[i].add(arr[i].element, num);
	}
}

void CleanAll(element_t *arr, int size)
{
	int i;
	
	for (i = 0; i < size; i++)
	{
		arr[i].clean(arr[i].element);
	}
}









