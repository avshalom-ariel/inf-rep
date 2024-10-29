/*
Author: Avshalom Ariel
Review by: 
Review date:
Status:
*/

#include <stddef.h> 	/*size_t*/
#include <stdlib.h> 	/*malloc free*/
#include <assert.h> 	/*assert*/
#include <sys/types.h> 	/*ssize_t*/

#include "sort.h" 		/*typedefs, function declarations*/

#define LEFT(index) 2 * index + 1
#define RIGHT(index) 2 * index + 2
#define PARENT(index) (index - 1) / 2

static void Swap(int *a, int *b);
static void QuickSortSwap(void *data1, void *data2, size_t size);
static int GetMax(int *arr, size_t arr_size);
static int GetMin(int *arr, size_t arr_size);
static void CountSortForRadix(int *arr, size_t arr_size, size_t exp);
static int GetMaxDigit(int *arr, int arr_size, int exp);

static void MergeSortRecursion(int arr[], size_t start, size_t end);
static void Merge(int *arr, size_t start, size_t mid, size_t end);

static void QuickSortRecursive(char *start, char *end, size_t size, int (*compar)(const void *, const void *));
static char *Partition(char *start, char *end, size_t size, int (*compar)(const void *, const void *));

static void HeapifyUp(int *arr, size_t index);
static void HeapifyDown(int *arr, long arr_size, long index);

void Print(int *arr);

/**************************************************/
/*		Sorting Functions - Comparison Sort		  */
/**************************************************/


void BubbleSort(int arr[], size_t arr_size)
{
	size_t i = 0, j = 0;
	
	for (; i < arr_size - 1; ++i)
	{
		for(j = 0; j < arr_size - 1 - i; ++j)
		{
			if (arr[j] > arr[j + 1])
			{
				Swap(arr + j, arr + j + 1);
			}
		}
	}
}

void SelectionSort(int *arr, size_t arr_size)
{
    size_t MinIndex = 0;
    size_t i = 0, j = 0;

    for (; i < arr_size -1; i++) 
    {
        MinIndex = i;
        
        for (j = i + 1; j < arr_size; ++j)
        {
            if (arr[j] < arr[MinIndex])
            {
                MinIndex = j;
            }
        }

        Swap(arr + MinIndex, arr + i);
    }
}

void InsertionSort(int *arr, size_t arr_size)
{
    size_t i = 0, j = 0; 
    int key = 0;
    
    for (i = 1; i < arr_size; ++i)
    {
        key = arr[i];
        j = i - 1;

        while (arr[j] > key/* && 0 <= j*/) 
        {
            arr[j + 1] = arr[j];
            j -= 1;
        }
        
        arr[j + 1] = key;
    }
}


/***************************************************/
/*		  Sorting Functions - Linear Sort 		   */
/***************************************************/


void CountingSort(int *arr, size_t arr_size)
{
	int *auxilary_arr = NULL;
	size_t count = 0;
	size_t i = 0;
	int max_val = 0;
	int min_val = 0;
	
	assert(arr);
	
	min_val = GetMin(arr, arr_size);
	max_val = GetMax(arr, arr_size);
	
	auxilary_arr = (int *)calloc((max_val - min_val + 1), sizeof(int));
	
	for (i = 0; i < arr_size; ++i)
	{
		auxilary_arr[arr[i] - min_val] += 1;
	}
	
	for (i = 0; i < arr_size; ++i)
	{
		if (0 != auxilary_arr[count])
		{
			arr[i] = count + min_val;
			auxilary_arr[count] -= 1;
		}
		else
		{
			++count;
			--i;
		}
	}
	
	free(auxilary_arr);
}


void RadixSort(int *arr, size_t arr_size)
{
	int exp = 1;
	int max = GetMax(arr, arr_size/*, exp*/);

    for (exp = 1; max / exp > 0; exp *= 10)
    {
        CountSortForRadix(arr, arr_size, exp);
	}
}


/***************************************************/
/*		      Divide And Conquer Search			   */
/***************************************************/


size_t IterativeBinarySearch(int *arr, size_t arr_size, int loot)
{
	size_t start = 0;
	size_t end = arr_size - 1;
	size_t mid = (start + end) / 2;
	
	assert(arr);
	
	while (start <= end)
	{
		if (loot < arr[mid])
		{
			end = mid;
			mid = (start + end) / 2;
		}
		else if (loot > arr[mid])
		{
			start = mid;
			mid = (start + end) / 2 + 1;
		}
		else
		{
			return mid;
		}
	}
	
	return -1;
}

size_t RecursiveBinarySearch(int *arr, size_t start, size_t end, int loot)
{
	size_t mid = (start + end) / 2;
	
	if (arr[mid] == loot)
	{
		return mid;
	}
	
	if (loot < arr[mid])
	{
		return RecursiveBinarySearch(arr, start, mid, loot);
	}
	else
	{
		return RecursiveBinarySearch(arr, mid + 1, end, loot);
	}
}


/***************************************************/
/*		      Divide And Conquer Search			   */
/***************************************************/


/* Function to merge two subarrays arr[l..m] and arr[m+1..r]*/
void Merge(int *arr, size_t start, size_t mid, size_t end) 
{
    size_t left_index = 0;
    size_t right_index = 0;
    size_t merged_index = 0;
    size_t size1 = mid - start + 1;
    size_t size2 = end - mid;
    int *LeftArray = (int *)malloc((size1 + 1) * sizeof(int));
    int *RightArray = (int *)malloc((size2 + 1) * sizeof(int));

/*  Copy data to temporary arrays*/
    for (left_index = 0; left_index < size1; ++left_index)
    {
        LeftArray[left_index] = arr[start + left_index];
    }
    for (right_index = 0; right_index < size1; ++right_index)
    {
        RightArray[right_index] = arr[mid + 1 + right_index];
	}

/*  Merge the temporary arrays back into arr[l..r]*/
    left_index = 0; 
    right_index = 0; 
    merged_index = start; 
    
    while (left_index < size1 && right_index < size2) 
    {
        if (LeftArray[left_index] <= RightArray[right_index])
         {
            arr[merged_index] = LeftArray[left_index];
            ++left_index;
        } 
        else 
        {
            arr[merged_index] = RightArray[right_index];
            ++right_index;
        }
        
        ++merged_index;
    }

/*  Copy the remaining elements of LeftArray, if there are any*/
    while (left_index < size1) 
    {
        arr[merged_index] = LeftArray[left_index];
        ++left_index;
        ++merged_index;
    }

/*    Copy the remaining elements of RightArray, if there are any*/
    while (right_index < size2) 
    {
        arr[merged_index] = RightArray[right_index];
        ++right_index;
        ++merged_index;
    }

    free(LeftArray);
    free(RightArray);
}

void MergeSort(int arr[], size_t arr_size)
{
	MergeSortRecursion(arr, 0, arr_size - 1);
}

void MergeSortRecursion(int *arr, size_t start, size_t end)
{
    size_t mid = 0;
    
    if (start < end) 
    {
        mid = start + (end - start) / 2;

        MergeSortRecursion(arr, start, mid);
        MergeSortRecursion(arr, mid + 1, end);
        
/*        Merge the sorted halves*/
        Merge(arr, start, mid, end);
    }
}

void QuickSort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *))
{
	char *start = (char *)base;
	char *end = start + ((nmemb - 1) * size);
	
	QuickSortRecursive(start, end, size, compar);
}

void QuickSortRecursive(char *start, char *end, size_t size, int (*compar)(const void *, const void *))
{
	char *pivot = NULL;
	
	if(start < end)
	{
		pivot = Partition(start, end, size, compar);
	
		QuickSortRecursive(start, pivot - size, size, compar);
		QuickSortRecursive(pivot + size, end, size, compar);
	}
}

char *Partition(char *start, char *end, size_t size, int (*compar)(const void *, const void *))
{
	char *pivot = end; /*pivot chosing at end (optional)*/
    char *fast_runner = start;
	char *slow_runner = fast_runner;
	
	while (fast_runner < end) 
	{
		if (0 > compar(fast_runner, pivot)) 
		{
			QuickSortSwap(fast_runner, slow_runner, size);
			slow_runner += size;
		}
		
		fast_runner += size;
	}
	
	QuickSortSwap(pivot, slow_runner, size);
	
	return slow_runner;
}


/***************************************************/
/*		      		Heap Sort					   */
/***************************************************/


void HeapSort(int *arr, size_t arr_size)
{
	size_t i = 0;

	for (; i < arr_size; ++i)
	{
		HeapifyUp(arr, i);
	}

	for (; 0 < arr_size; --arr_size)
	{	
		Swap(arr, arr + arr_size - 1);
		
		HeapifyDown(arr, arr_size - 1, 0);
	}
}


/***************************************************/
/*			       Help Functions				   */
/***************************************************/


void Swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void QuickSortSwap(void *data1, void *data2, size_t size)
{
	size_t i = 0;
	char temp = 0;
	char *runner1 = (char *)data1;
	char *runner2 = (char *)data2;
	
	for(; i < size; ++i)
	{
		temp = *runner1;
		*runner1 = *runner2;
		*runner2 = temp;
		
		++runner1;
		++runner2;
	}
}

int GetMax(int *arr, size_t arr_size)
{
	int max = 0;
	size_t i = 0;
	
	max = arr[0];
	
    for (; i < arr_size; ++i)
    {
    	if (arr[i] > max)
        {
        	max = arr[i];
        }
    }
    
	return max;
}

int GetMin(int *arr, size_t arr_size)
{
	int min = 0;
	size_t i = 0;
	
	min = arr[0];
	
    for (; i < arr_size; ++i)
    {
    	if (arr[i] < min)
        {
        	min = arr[i];
        }
    }
    
	return min;
}

void CountSortForRadix(int *arr, size_t arr_size, size_t exp)
{
	int *output = calloc(arr_size + 1, sizeof(int));
	int max_element = GetMaxDigit(arr, arr_size, exp);
	int *count_arr = calloc(max_element + 1, sizeof(int));
	int i = 0;

	for (i = 0; (size_t)i < arr_size; ++i)
	{
		++count_arr[(arr[i] / exp) % 10];
	}

	
	for (i = 1; i < 10; ++i)
	{
		count_arr[i] += count_arr[i - 1];
	}

	for (i = arr_size - 1; i >= 0; --i)
	{
		output[count_arr[(arr[i] / exp) % 10] - 1] = arr[i];
		--count_arr[(arr[i] / exp) % 10];
	}

	for (i = 0; (size_t)i < arr_size; ++i)
	{
		arr[i] = output[i];
	}
	
	free(output);
	free(count_arr);
}

int GetMaxDigit(int *arr, int arr_size, int exp)
{
	int max_element = (arr[0] / exp) % 10;
	int i = 1;
	
	for (i = 1; i < arr_size; i++)
	{
		if (((arr[i] / exp) % 10) > max_element)
		max_element = arr[i];
	}

	return max_element;
}

void HeapifyUp(int *arr, size_t index)
{
	long parent = PARENT(index);

	if (0 >= index)
	{
		return;
	}
	
	/*if parent is larger, swap, then repeat recursively */
	if(arr[index] > arr[parent])
	{
		Swap(arr + index, arr + parent);

		HeapifyUp(arr, parent);
	}
}

void HeapifyDown(int *arr, long arr_size, long index)
{
	long left = LEFT(index);
	long right = RIGHT(index);
	long largest = index;

	/*check if left child is larger*/
	if (left <=  arr_size - 1 && arr[largest] < arr[left])
	{
		largest = left;
	}

	/*check if right child is larger*/	/*check if left child is larger*/
	if (right <=  arr_size - 1 && arr[largest] < arr[right])
	{
		largest = right;
	}

	/*swap the larger child (if exist) the repeat recursively*/
	if (index <= ((arr_size / 2) - 1) && largest != index)
	{
		Swap(arr + index, arr + largest);
		
		HeapifyDown(arr, arr_size - 1, largest);
	}
}


void Print(int *arr)
{
	size_t i = 0;
	
	for (; i < 10; ++i)
	{
		printf("%d, ", arr[i]);
	}
	
	printf("\n");
}
