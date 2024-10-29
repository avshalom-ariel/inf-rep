#include<stdio.h>


int IsSum(int* arr, int sum, int size);


int main(void)
{
	int arr[12];
	int sum;
	int size;
	int i;
	
	for (i = 0; i < 12; ++i)
	{
		arr[i] = i;
	}
	sum = 10;
	size = 12;
	
	printf("the sum is %d \n", IsSum(arr, sum, size));
	
	return 0;
}



int IsSum(int* arr, int sum, int size)
{
	int right;
	int left;
	int temp;
	
	left = 0;
	right = size - 1;
	
	while(left < right)
	{
		temp = arr[right] + arr[left];
		
		if(temp == sum)
		{
			printf("the indexes of sum are %d and %d \n", right, left);
			return 1;
		}
		else if (temp < sum)
		{
			++left;
		}
		else
		{
			--right;
		}
	}
	return 0;
}




