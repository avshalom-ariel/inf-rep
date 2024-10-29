
#include <stdio.h> 	/*printf*/
#include <stddef.h>	/*size_t*/

static void swap(int *a, int *b);
static int MinKValue(int *array, size_t size, int k);

int main(void)
{
	int arr[10] = {1, 9, 3, 7, 5, 6, 4, 8, 2, 10};
	
	printf("the %d minimum element is: %d\n", 1, MinKValue(arr, 10, 1));
	printf("the %d minimum element is: %d\n", 2, MinKValue(arr, 10, 2));
	printf("the %d minimum element is: %d\n", 3, MinKValue(arr, 10, 3));
	printf("the %d minimum element is: %d\n", 4, MinKValue(arr, 10, 4));
	printf("the %d minimum element is: %d\n", 5, MinKValue(arr, 10, 5));
	printf("the %d minimum element is: %d\n", 6, MinKValue(arr, 10, 6));
	printf("the %d minimum element is: %d\n", 7, MinKValue(arr, 10, 7));
	printf("the %d minimum element is: %d\n", 8, MinKValue(arr, 10, 8));
	printf("the %d minimum element is: %d\n", 9, MinKValue(arr, 10, 9));
	printf("the %d minimum element is: %d\n", 10, MinKValue	(arr, 10, 10));
	
	return 0;
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}


int MinKValue(int *array, size_t size, int k)
{
    size_t i = 0; 
    size_t j = size - 1;
    
    for (i = 0; i < k; ++i)
    {
        for (j = size - 1; 0 < j; --j)
        {
            if (array[j] < array[j - 1])
            {
                swap(&array[j], &array[j - 1]);
            }
        }
    }
    return array[k - 1];
}


