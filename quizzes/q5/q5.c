#include<stdio.h> /*printf*/

void Bursa(int arr[], int size);

int main(void)
{
	int arr[8] = {6, 12, 3, 5, 1, 4, 9, 2};
	int size = 8;
	
	Bursa(arr, size);
	
	return 0;
}


void Bursa(int *arr, int size)
{
	int sell = 0;
	int buy = 0;
	int profit = 0;
	int i = 0; 
	int min = 0;
	
	while (i < size)
	{
		if (arr[i] < arr[buy])
		{
			buy = i;
		}
		else if (arr[sell] < arr[i] || profit < (arr[sell] - arr[buy]))
		{
		    sell = i;
		    profit = arr[sell] - arr[buy];
		}
		if (buy < sell)
		{
			min = buy;
		}
		++i;
	}
	
	
	printf("min is %d, sell is %d and profit %d\n", min, sell, profit);
}


