
#include <pthread.h>		/*pthread_create */
#include <unistd.h>			/*sleep*/

#include <stdio.h>			/*printf*/

#define ARRAY_SIZE 100000
#define THREADS_UNTIL_DETACH 30000
#define SLEEP_TIME 10
#define BASE_NUMBER 100
#define NUMBER 1000000000
#define AVSHALOM 0
/*		yarden: LAALALALALALALLALALALALALALALALALALAL LALALALALALALALALLALALALALALAL*/
/*		uriah: return AVSHALOM */

static void *InsertIndex(void *vargp);
static void *MainThread(void *vargp);
static void PrintArray(void);
static void Detach(void);

pthread_t pthread_arr[THREADS_UNTIL_DETACH];
int g_array[ARRAY_SIZE];
size_t sun_of_div;
time_t g_start_time;
time_t g_end_time;

void Threads(void)
{
	pthread_t thread_id = {0};

	pthread_create(&thread_id, NULL, MainThread, NULL);
	
	sleep(SLEEP_TIME);

	PrintArray();
	
	printf("performence: %ld\n", g_end_time - g_start_time);
	
	printf("sum of divisor: %ld\n", sun_of_div);
}

void *MainThread(void *vargp)
{
	pthread_t thread_id = {0};
	size_t j = 0;
	int i = 0;
	
	(void)vargp;

	g_start_time = time(NULL);

	for (i = 0; i < ARRAY_SIZE; ++i)
	{
		while (0 != pthread_create(&thread_id, NULL, InsertIndex, g_array + i))
		{
			pthread_create(&thread_id, NULL, InsertIndex, g_array + i);
		}
		
		pthread_arr[j] = thread_id;
		++j;
		
		if (!(j % THREADS_UNTIL_DETACH))
		{
			j = 0;
			Detach();
		}
	}
	
	g_end_time = time(NULL);
	
	return NULL;
}     

void *InsertIndex(void *vargp)
{
	int index = (int)((size_t)vargp - (size_t)g_array) / sizeof(int);
	int i = index * (NUMBER / ARRAY_SIZE) + 1;
	
	for (; i < (index + 1) * (NUMBER / ARRAY_SIZE) + 1; ++i)
	{
		if (0 == NUMBER % i)
		{
			sun_of_div += i;
		}
	}

	*(int *)vargp = index;	
	
	return NULL;
}

void Detach(void)
{
	size_t i = 0;
	
	for (; i < THREADS_UNTIL_DETACH; ++i)
	{
		pthread_detach(pthread_arr[i]);
	}
}

void PrintArray(void)
{
	int i = 0;
	
	for (i = 0; i < ARRAY_SIZE; ++i)
	{
		if (g_array[i] == i)
		{
			printf("g_array[%d] = %d\n", i, g_array[i]);
		}
	}
}

