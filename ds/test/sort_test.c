
#include <stdio.h> 		   /*printf*/
#include <stddef.h> 	   /*size_t*/
#include <stdlib.h> 	   /*rand*/
#include <time.h>		   /*time_t, time, clock_t, clock */

#include "sort.h" 	   /*sort functions*/
#include "test_utility.h"  /*Test Functions*/

#define ARRAY_SIZE 5000

static int BubbleSortTest(void);
static int SelectionSortTest(void);
static int InsertionSortTest(void);
static int QSortTest(void);
static int CountingSortTest(void);
static int RadixSortTest(void);

static int IntCmp(const void *data1, const void *data2);
static void InitializeRandArr(int *arr);
static void InitializeUnderHundredArr(int *arr, size_t arr_size);
static void InitializeSevenDigitsArr(int *arr, size_t arr_size);

static void IterativeBinarySearchTest(void);
static void RecursiveBinarySearchTest(void);

static int MergeSortTest(void);
static int QuickSortTest(void);

static int HeapSortTest(void);

static int CompFunc(const void *data1, const void *data2);

int main(void)
{
	int status = 0;
	
	status += BubbleSortTest();
	status += SelectionSortTest();
	status += InsertionSortTest();
	status += QSortTest();
	status += CountingSortTest();
	status += RadixSortTest();
	status += MergeSortTest();
	status += QuickSortTest();

	status += HeapSortTest();

	IterativeBinarySearchTest();
	RecursiveBinarySearchTest();

	if (0 != status)
	{
		printf("failed!\n");
	}

	
	
	
	Test();
	
	return 0;	
}


/**************************************************/
/*		Sorting Functions - Comparison Sort		  */
/**************************************************/


int BubbleSortTest(void)
{
	int arr[ARRAY_SIZE] = {0};
	size_t  i = 0;
	clock_t start = {0}, end = {0};
	
	InitializeRandArr(arr);
	
	start = clock();
	BubbleSort(arr, ARRAY_SIZE);
	end = clock();
	
	printf("BuobleSort time difference is: %f\n", (double)(end - start));
	
	while (arr[i] <= arr [i + 1] && i < ARRAY_SIZE - 2)
	{
		++i;
	}

	if (ARRAY_SIZE - 2 != i)
	{
		printf("BuobleSort Failed!\n");
		printf("%ld\n", i);
		return 1;
	}
	
	return 0;	
}

int SelectionSortTest(void)
{
	int arr[ARRAY_SIZE] = {0};
	size_t  i = 0;
	clock_t start = {0}, end = {0};
	
	InitializeRandArr(arr);

	start = clock();
	SelectionSort(arr, ARRAY_SIZE);
	end = clock();

	printf("SelectionSort time difference is: %f\n", (double)(end - start));
	
	while (arr[i] <= arr [i + 1] && i < ARRAY_SIZE - 2)
	{
		++i;
	}

	if (ARRAY_SIZE - 2 != i)
	{
		printf("SelectionSort Failed!\n");
		
		printf("index of fault: %ld\n",i);
		
		return 1;
	}
	
	return 0;	
}

int InsertionSortTest(void)
{
	int arr[ARRAY_SIZE] = {0};
	size_t  i = 0;
	clock_t start = {0}, end = {0};
	
	InitializeRandArr(arr);
	
	start = clock();
	InsertionSort(arr, ARRAY_SIZE);
	end = clock();
	
	printf("InsertionSort time difference is: %f\n", (double)(end - start));
	
	while (arr[i] <= arr [i + 1] && i < ARRAY_SIZE - 2)
	{
		++i;
	}

	if (ARRAY_SIZE - 2 != i)
	{
		printf("InsertionSort Failed!\n");
		
		printf("index of fault: %ld\n",i);
		
		return 1;
	}
	
	return 0;
}

int QSortTest(void)
{
	int arr[ARRAY_SIZE] = {0};
	size_t  i = 0;
	clock_t start = {0}, end = {0};

	InitializeRandArr(arr);
	
	start = clock();
	qsort(arr, ARRAY_SIZE, sizeof(int), IntCmp);
	end = clock();
	
	printf("qsort time difference is: %f\n", (double)(end - start));
	
	while (arr[i] <= arr [i + 1] && i < ARRAY_SIZE - 2)
	{
		++i;
	}
	
	if (ARRAY_SIZE - 2 != i)
	{
		printf("qsort Failed!\n");
		return 1;
	}
	
	return 0;
}


/***************************************************/
/*		  Sorting Functions - Linear Sort 		   */
/***************************************************/


int CountingSortTest(void)
{
	int arr[ARRAY_SIZE] = {0};
	size_t  i = 0;
	clock_t start = {0}, end = {0};

	InitializeUnderHundredArr(arr, ARRAY_SIZE);
	
	start = clock();
	CountingSort(arr, ARRAY_SIZE);
	end = clock();
	
	printf("CountingSort time difference is: %f\n", (double)(end - start));
	
	i = 0;
	
	while (arr[i] <= arr [i + 1] && i < ARRAY_SIZE - 2)
	{
		++i;
	}
	
	if (ARRAY_SIZE - 2 != i)
	{
		printf("CountingSortTest Failed!\n");	

		printf("index of fault: %ld\n", i);
		return 1;
	}
	
	return 0;	
}


int RadixSortTest(void)
{
	int arr[ARRAY_SIZE] = {0};
	size_t  i = 0;
	clock_t start = {0}, end = {0};

	InitializeSevenDigitsArr(arr, ARRAY_SIZE);

	start = clock();
	RadixSort(arr, ARRAY_SIZE);
	end = clock();

	printf("RadixSortTest time difference is: %f\n", (double)(end - start));
	
	i = 0;
	
	while (arr[i] <= arr [i + 1] && i < ARRAY_SIZE - 2)
	{
		++i;
	}
	
	if (ARRAY_SIZE - 2 != i)
	{
		printf("RadixSortTest Failed!\n");

		printf("index of fault: %ld\n", i);
		return 1;
	}
	
	return 0;	
}


/***************************************************/
/*		      Divide And Conquer Search			   */
/***************************************************/


void IterativeBinarySearchTest(void)
{
	int arr1[] = {1,5,9,12,15,17,18,26,29,34,35,38,39,40,42,44,48,49,51,56,58,67,78,80,91,92,93,99,100};
	size_t arr_size1 = sizeof(arr1) / sizeof(int);
	
	int arr2[] = {-256,-254,-241,-125, 45,-2,10,11,12,13,15,16,18,19,25,64,67,76,85,95,101,123,253,563};
	size_t arr_size2 = sizeof(arr2) / sizeof(int);
	
	TestSizeT("IterativeBinarySearchTest", __FILE__, __LINE__, 10, 
														IterativeBinarySearch(arr1, arr_size1, 35));
	TestSizeT("IterativeBinarySearchTest", __FILE__, __LINE__, 14, 
														IterativeBinarySearch(arr2, arr_size2, 25));

	TestSizeT("IterativeBinarySearchTest", __FILE__, __LINE__, arr_size1 - 1, 
														IterativeBinarySearch(arr1, arr_size1, 100));
	TestSizeT("IterativeBinarySearchTest", __FILE__, __LINE__, 0, 
														IterativeBinarySearch(arr2, arr_size2, -256));
}

void RecursiveBinarySearchTest(void)
{
	int arr1[] = {1,5,9,12,15,17,18,26,29,34,35,38,39,40,42,44,48,49,51,56,58,67,78,80,91,92,93,99,100};
	size_t arr_size1 = sizeof(arr1) / sizeof(int);
	
	int arr2[] = {-256,-254,-241,-125, 45,-2,10,11,12,13,15,16,18,19,25,64,67,76,85,95,101,123,253,563};
	size_t arr_size2 = sizeof(arr2) / sizeof(int);
	
	TestSizeT("RecursiveBinarySearchTest", __FILE__, __LINE__, 10, 
														RecursiveBinarySearch(arr1, 0, arr_size1 - 1, 35));
	TestSizeT("RecursiveBinarySearchTest", __FILE__, __LINE__, 14, 
														RecursiveBinarySearch(arr2, 0, arr_size2 - 1, 25));

	TestSizeT("RecursiveBinarySearchTest", __FILE__, __LINE__, arr_size1 - 1, 
														RecursiveBinarySearch(arr1, 0, arr_size1 - 1, 100));
	TestSizeT("RecursiveBinarySearchTest", __FILE__, __LINE__, 0, 
														RecursiveBinarySearch(arr2, 0, arr_size2 - 1, -256));
}


int MergeSortTest(void)
{
	int arr[ARRAY_SIZE] = {0};
	size_t  i = 0;
	clock_t start = {0}, end = {0};
	
	InitializeRandArr(arr);
	
	start = clock();
	MergeSort(arr, ARRAY_SIZE);
	end = clock();
	
	printf("MergeSort time difference is: %f\n", (double)(end - start));
	
	while (arr[i] <= arr [i + 1] && i < ARRAY_SIZE - 2)
	{
		++i;
	}

	if (ARRAY_SIZE - 2 != i)
	{
		printf("MergeSort Failed!\n");
		
		printf("index of fault: %ld\n",i);
		
		return 1;
	}
	
	return 0;
}


int QuickSortTest(void)
{
	int arr[ARRAY_SIZE] = {0};
	size_t  i = 0;
	clock_t start = {0}, end = {0};

	InitializeRandArr(arr);
	
	start = clock();
	QuickSort(arr, ARRAY_SIZE, sizeof(int), CompFunc);
	end = clock();
	
	printf("QuickSort time difference is: %f\n", (double)(end - start));
	
	while (arr[i] <= arr [i + 1] && i < ARRAY_SIZE - 2)
	{
		++i;
	}
	
	if (ARRAY_SIZE - 2 != i)
	{
		printf("QuickSort Failed!\n");
		printf("index of false: %ld\n", i);
		return 1;
	}
	
	return 0;
}
 

int HeapSortTest(void)
{
	int arr[ARRAY_SIZE] = {0};
	size_t  i = 0;
	clock_t start = {0}, end = {0};

	InitializeRandArr(arr);
	
	start = clock();
	HeapSort(arr, ARRAY_SIZE);
	end = clock();
	
	printf("HeapSortTest time difference is: %f\n", (double)(end - start));
	
	while (arr[i] <= arr [i + 1] && i < ARRAY_SIZE - 2)
	{
		++i;
	}
	
	if (ARRAY_SIZE - 2 != i)
	{
		printf("HeapSortTest Failed!\n");
		printf("index of false: %ld\n", i);
		return 1;
	}
	
	return 0;
}


/***************************************************/
/*			       Help Functions				   */
/***************************************************/


void InitializeRandArr(int *arr)
{
	int num = 0;
	size_t i = 0;
	
	srand(time(NULL));
	
	while (i < ARRAY_SIZE)
	{
        num = rand() % 5000;

        arr[i] = num;
         ++i;
    }
}

int IntCmp(const void *data1, const void *data2)
{
	return *(int *)data1 - *(int *)data2;
}


void InitializeUnderHundredArr(int *arr, size_t arr_size)
{
	int num = 0;
	size_t i = 0;
	
	srand(time(NULL));
	
	while (i < arr_size)
	{
        num = (rand() % 5000) - (rand() % 5000);
        arr[i] = num;
         ++i;
    }
}

void InitializeSevenDigitsArr(int *arr, size_t arr_size)
{
	int num = 0;
	size_t i = 0;
	
	srand(time(NULL));
	
	while (i < arr_size)
	{
        num = (rand() % 1000000);
        arr[i] = num;
         ++i;
    }
}

int CompFunc(const void *data1, const void *data2)
{
	return *(int *)data1 - *(int *)data2;
}

