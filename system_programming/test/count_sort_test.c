
#include <stddef.h>		/*size_t*/
#include <stdio.h>		/*printf, file functions*/
#include <time.h>		/*clock_t, clock*/
#include <stdlib.h>		/*rand*/
#include <string.h>     /*strcat*/

#include "count_sort.h"

#define ARRAY_SIZE 5000
#define MAX_VAL 5000
#define NUM_OF_DICTIONARIES 3

/*static int CountingSortTest(void);*/
static void DictionaryTest(void);

static void InitializeUnderHundredArr(int *arr, size_t arr_size);
static int SortingCheck(unsigned char *arr, size_t arr_size);
static void PrintArr(int *arr);

int main(void)
{
	DictionaryTest();
	
	return 0;
}


/*****************************************/
/*			Test Functions				 */
/*****************************************/


void DictionaryTest(void)
{
	unsigned char *ditionary_holder1 = NULL;
	unsigned char *ditionary_holder2 = NULL;
	unsigned char *ditionary_holder3 = NULL;
	unsigned char *all_ditionaries_holder = NULL;
    size_t dictionary_size = 0;
    FILE *dictionary = NULL;
	size_t bytes_read = 0;

	dictionary = fopen("/usr/share/dict/words", "r");
    if (dictionary == NULL) 
    {
        printf("file loading failed!\n");
		return;
    }

    fseek(dictionary, 0, SEEK_END);
    
	dictionary_size = ftell(dictionary);
    if (0 > dictionary_size)
	{
		perror("Error finding file size\n");
	}

    printf("dictionary_size = %ld\n", dictionary_size);

	fseek(dictionary, 0, SEEK_SET);


    ditionary_holder1 = (char *)calloc(dictionary_size + 1 ,sizeof(char));
	if (!ditionary_holder1)
	{
		perror("Failed to allocate memmory 1");

        fclose(dictionary);

	}

	ditionary_holder2 = (char *)calloc(dictionary_size + 1, sizeof(char));
	if (!ditionary_holder2)
	{
		perror("Failed to allocate memmory 2");

        fclose(dictionary);

	}

	ditionary_holder3 = (char *)calloc(dictionary_size + 1, sizeof(char));
	if (!ditionary_holder3)
	{
		perror("Failed to allocate memmory 3");

        fclose(dictionary);

	}

	all_ditionaries_holder = (char *)calloc((dictionary_size * NUM_OF_DICTIONARIES) + 1, sizeof(char));
	if (!all_ditionaries_holder)
	{
		perror("Failed to allocate memmory all");

        fclose(dictionary);

	}

    bytes_read = fread(ditionary_holder1, 1, dictionary_size, dictionary);
	if (bytes_read != dictionary_size) 
	{
        printf("%ld bytes read out of %ld", bytes_read, dictionary_size);
		perror("Failed reading reading dictionary1");
    }

	fseek(dictionary, 0, SEEK_SET);

    bytes_read = fread(ditionary_holder2, 1, dictionary_size, dictionary);
	if (bytes_read != dictionary_size) 
	{
        printf("%ld bytes read out of %ld", bytes_read, dictionary_size);
		perror("Failed reading reading dictionary2");
    }

	fseek(dictionary, 0, SEEK_SET);

    bytes_read = fread(ditionary_holder3, 1, dictionary_size, dictionary);
	if (bytes_read != dictionary_size) 
	{
        printf("%ld bytes read out of %ld", bytes_read, dictionary_size);
		perror("Failed reading reading dictionary3");
    }

	strcat(all_ditionaries_holder, ditionary_holder1);
	strcat(all_ditionaries_holder, ditionary_holder2);
	strcat(all_ditionaries_holder, ditionary_holder3);

    SortingCheck(all_ditionaries_holder, dictionary_size * NUM_OF_DICTIONARIES);

    free(ditionary_holder1);
    free(ditionary_holder2);
    free(ditionary_holder3);
    free(all_ditionaries_holder);

	fclose(dictionary);
}

/*
int CountingSortTest(void)
{
	clock_t start = {0}, end = {0};
	int arr[ARRAY_SIZE] = {0};
	int  status = 0;
	size_t  i = 0;

	InitializeUnderHundredArr(arr, ARRAY_SIZE);

	start = clock();
	CountingSort(arr, ARRAY_SIZE, MAX_VAL);
	end = clock();
	
	printf("CountingSort time difference is: %f\n", (double)(end - start));
	
	i = 0;
	
	while (arr[i] <= arr[i + 1] && i < ARRAY_SIZE - 2)
	{
		++i;
		break;
	}
	
	if (ARRAY_SIZE - 2 != i)
	{
		printf("CountingSortTest Failed!\n");	

		printf("index of fault: %ld\nvalue of fault: %d\n", i, arr[i]);
		++status;
	}
	
	return status;	
}
*/

/*****************************************/
/*			Help Functions				 */
/*****************************************/


void InitializeUnderHundredArr(int *arr, size_t arr_size)
{
	int num = 0;
	size_t i = 0;
	
	srand(time(NULL));
	
	while (i < arr_size)
	{
        num = (rand() % MAX_VAL)/* - (rand() % MAX_VAL)*/;
        arr[i] = num;
         ++i;
    }
}

void PrintArr(int *arr)
{
	size_t i = 0;

	for (; i < ARRAY_SIZE; ++i)
	{
		printf("%d, ", arr[i]);
	}
}


int SortingCheck(unsigned char *arr, size_t arr_size)
{
	clock_t start = {0}, end = {0};
	size_t  status = 0;
	size_t  i = 0;

	start = clock();
	CountingSort(arr, arr_size, 254);
	end = clock();

	printf("CountingSort time difference is: %f\n", (double)(end - start));
	
	i = 0;
	
	while (i < arr_size - 2)
	{
		++i;
		if (arr[i] > arr[i + 1])
		{
		/*printf("we have a problem!\n");*/
		/*printf("%d > %d \n\n",arr[i], arr[i + 1]);*/
		++status;
		}
	}
	
	printf("Failed in %ld out of %ld\n", status, arr_size);
	
	return status;	
}
