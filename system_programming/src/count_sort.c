
#include <pthread.h>	/*pthread typedef and functions*/
#include <stddef.h>		/*size_t*/
#include <stdio.h>		/*printf*/
#include <stdlib.h>		/*calloc free*/
#define NUM_OF_THREADS 2

typedef struct thread_data
{
    unsigned char *arr;
    size_t *count_arr;
    size_t start;
    size_t end;
    unsigned char max_value;
} thread_data_t;

static void *CountRoutine(void *arg);

void CountingSort(unsigned char *arr, size_t arr_size, unsigned char max_value)
{
	size_t chunk_size = arr_size / NUM_OF_THREADS;
	thread_data_t thread_data[NUM_OF_THREADS] = {0};
	pthread_t threads[NUM_OF_THREADS] = {0};
	size_t *count_arr = NULL;
	size_t i = 0;
	size_t j = 0;

	count_arr = (size_t *)calloc(max_value + 1, sizeof(size_t));
    if (!count_arr)
	{
		perror ("Failed in memory allocation\n");
		exit(EXIT_FAILURE);
	}
    for (; i < NUM_OF_THREADS; ++i)
    {
        thread_data[i].arr = arr;
        thread_data[i].count_arr = count_arr;
        thread_data[i].start = i * chunk_size;
        thread_data[i].end = (i == NUM_OF_THREADS - 1) ? arr_size : (i + 1) * chunk_size;
		thread_data[i].max_value = max_value;

        pthread_create(&threads[i], NULL, CountRoutine, &thread_data[i]);
    }

	for (i = 0; i < NUM_OF_THREADS; ++i)
	{
		pthread_join(threads[i], NULL);
	}

	for (i = 0; i <= (size_t)max_value; ++i)
	{
        while (count_arr[i] > 0)
		{
            arr[j] = i;

			--count_arr[i];
			++j;
        }
    }
    
	free(count_arr);
}


void *CountRoutine(void *arg)
{
	thread_data_t *thread_data = (thread_data_t *)arg;
	size_t i = 0;

	printf("start = %ld\n", thread_data->start);
    printf("end = %ld\n", thread_data->end);

	for (i = thread_data->start; i < thread_data->end; ++i)
	{

        ++thread_data->count_arr[(int)(thread_data->arr[i])];
    }

	return NULL;	
}


