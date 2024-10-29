#ifndef __COMP_SORT_H__
#define __COMP_SORT_H__

#include <stddef.h> 	/*size_t*/
#include <sys/types.h>	/*ssize_t	*/

typedef int (*comp_func_t)(const void *, const void *);

/**************************************************/
/*		Sorting Functions - Comparison Sort		  */
/**************************************************/


void BubbleSort(int *arr, size_t arr_size);
void SelectionSort(int *arr, size_t arr_size);
void InsertionSort(int *arr, size_t arr_size);


/***************************************************/
/*		  Sorting Functions - Linear Sort 		   */
/***************************************************/


void CountingSort(int *arr, size_t arr_size);
void RadixSort(int *arr, size_t arr_size);


/***************************************************/
/*		      Divide And Conquer Sorts			   */
/***************************************************/


size_t IterativeBinarySearch(int *arr, size_t arr_size, int loot);
size_t RecursiveBinarySearch(int *arr, size_t start, size_t end, int loot);


void MergeSort(int arr[], size_t arr_size);
void QuickSort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *));

void HeapSort(int *arr, size_t arr_size);

#endif /*__COMP_SORT_H__*/
