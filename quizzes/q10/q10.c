
#include <stdio.h> 	/*printf*/
#include <stdlib.h> /* malloc free*/

int *Bursa(int *arr, int size);

int main(void)
{	
	int *result;
	int arr[8] = {6, 12, 1, 14, 2, 4, 1, 13};
	
	result = Bursa(arr, 8);
	
	
	printf("profit is %d sell is %d buy is %d \n", *result, *(result + sizeof(int)), 
													   *(result + 2 * sizeof(int)));
	
	return 0;
}


int *Bursa(int *arr, int size)
{
	int buy_temp = 0;
	int i = 0;
	int buy = 0;
	int profit = 0;
	int sell = 0;
	int *result = (int *)malloc(3 * sizeof(int));
	
	for (; i < size; ++i)
	{	
		if (arr[i] < arr[buy_temp])
		{
			buy_temp = i;
		}
		else if (profit < (arr[sell] - arr[buy_temp]) || arr[sell] < arr[i])
		{
		    sell = i;
		    profit = arr[sell] - arr[buy_temp];
		}
		
		if (buy_temp < sell)
		{
			buy = buy_temp;
		}
	}
	
	*result = profit;
	*(result + sizeof(int)) = buy;
	*(result + 2 * sizeof(int)) = sell;
	
	return result;
}


