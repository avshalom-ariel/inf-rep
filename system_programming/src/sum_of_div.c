
#include <stddef.h>		/*size_t*/
#include <pthread.h>	/*pthread_create */
#include <unistd.h>		/*sleep*/
#include <omp.h>		/*OpenMP*/

#include "sum_of_div.h"

#define THREAD_NUMBER 10

static void *InsertIndex(void *vargp);

size_t g_sum_of_div;

size_t SumOfDiv(int number)
{
	size_t sum_of_div = 0;
	int i = 1;
	
	#pragma omp parallel for reduction(+:sum_of_div)

	for (i = 1; i <= number; ++i)
	{
		if (0 == number % i)
		{
			sum_of_div += i;
		}
	}


	return sum_of_div;
}


size_t SumOfDivThreads(int number)
{
	pthread_t thread_id = {0};
	int i = 0;
	
	(void)number;
	
	for (; i < THREAD_NUMBER; ++i)
	{
		pthread_create(&thread_id, NULL, InsertIndex, &g_sum_of_div + i);
	}

	sleep(1);

	return g_sum_of_div;
}

void *InsertIndex(void *vargp)
{
	int index = ((size_t)vargp - (size_t)&g_sum_of_div) / sizeof(size_t);
	int i = index * (NUMBER / THREAD_NUMBER) + 1;
	
	for (; i <= (index + 1) * (NUMBER / THREAD_NUMBER) + 1; ++i)
	{
		if (0 == NUMBER % i)
		{
			g_sum_of_div += i;
		}
	}
	
	return NULL;
}


