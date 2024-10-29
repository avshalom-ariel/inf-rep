#define _POSIX_C_SOURCE 200112L

#include <pthread.h>	/*pthread Functions*/
#include <stdlib.h>		/*malloc free*/
#include <stdio.h>		/*printf*/
#include <stdatomic.h> 	/*atomic_int*/
#include <unistd.h>		/*sleep*/
#include <semaphore.h> /* semaphore Functions */

#include "sllist.h"
#include "cbuffer.h"
#include "fsq.h"

#define NUM_OF_RESOURCE 15
#define NUM_OF_PRODUCERS 5
#define NUM_OF_CONSUMERS 5
#define NUM_OF_MESSAGES 5
#define CAPACITY 40

static void *Producer1(void *arg);
static void *Consumer1(void *arg);
static void *Producer2(void *arg);
static void *Consumer2(void *arg);
static void *Producer3(void *arg);
static void *Consumer3(void *arg);
static void *Producer4(void *arg);
static void *Consumer4(void *arg);
static void *Producer5(void *arg);
static void *Consumer5(void *arg);
static void *Producer6(void *arg);
static void *Consumer6(void *arg);

static volatile int stop;

/********************************************/
/*			   		Ex1						*/
/********************************************/


pthread_spinlock_t p_lock = {0};
pthread_spinlock_t c_lock = {0};

static char g_resource1[NUM_OF_RESOURCE] = {0};
static size_t index = 0;

static char g_consumer_arr[NUM_OF_RESOURCE] = {0};
static char g_producer_arr[NUM_OF_RESOURCE] = {'A', 'v', 's', 'h', 'i', ' ', 't', 'h',
											   			'e', ' ', 'm', 'a', 'n', '\n'};

void Ex1(void)
{
	pthread_t producer = {0};
	pthread_t consumer = {0};
	size_t i = 0;

	if (0 != pthread_spin_init(&p_lock, PTHREAD_PROCESS_PRIVATE))
	{
		printf("error creating lock\n");
		return;
	}
	
	if (0 != pthread_spin_init(&c_lock, PTHREAD_PROCESS_PRIVATE))
	{
		printf("error creating lock\n");
		return;
	}
	
	pthread_spin_lock(&c_lock);

	pthread_create(&producer, NULL, Producer1, NULL);
	pthread_create(&consumer, NULL, Consumer1, NULL);
	
	pthread_join(producer, NULL);
	pthread_join(consumer, NULL);
	
	for(i = 0; i < NUM_OF_RESOURCE; ++i)
	{	
		printf("%c", g_consumer_arr[i]);
	}
	
	pthread_spin_destroy(&p_lock);
	pthread_spin_destroy(&c_lock);
}

void *Consumer1(void *arg)
{
	size_t i = 0;
	
	(void)arg;
	
	for(i = 0; i < NUM_OF_RESOURCE; ++i)
	{
		pthread_spin_lock(&c_lock);
		
		printf("consumer: %ld\n", index);
		g_consumer_arr[index] = g_resource1[index];
		
		pthread_spin_unlock(&p_lock);
		
		++index;
	}	
	
	return NULL;
}

void *Producer1(void *arg)
{
	size_t i = 0;

	(void)arg;

	for(i = 0; i < NUM_OF_RESOURCE; ++i)
	{
		pthread_spin_lock(&p_lock);
		
		printf("producer: %ld\n", index);
		g_resource1[index] = g_producer_arr[index];
		
		pthread_spin_unlock(&c_lock);
	}	
	
	return NULL;
}


/********************************************/
/*			   		Ex2						*/
/********************************************/


static linked_list_t *g_resource2 = NULL;
static pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;

void Ex2(void)
{
	pthread_t producer_threads[NUM_OF_PRODUCERS] = {0};
	pthread_t consumer_threads[NUM_OF_CONSUMERS] = {0};
	size_t i = 0;
	
	g_resource2 = SLListCreate();
	if (NULL == g_resource2)
	{
		printf("error creating slist\n");
		return;
	}
	
	stop = 0;
	
	pthread_mutex_init(&mutex2, NULL);

	for (i = 0; i < NUM_OF_PRODUCERS; ++i) 
	{
		pthread_create(&producer_threads[i], NULL, Producer2, NULL);
		pthread_create(&consumer_threads[i], NULL, Consumer2, NULL);
	}

	for (i = 0; i < NUM_OF_PRODUCERS; ++i) 
	{
		pthread_join(producer_threads[i], NULL);
	}
	
	stop = 1;

	for (i = 0; i < NUM_OF_CONSUMERS; ++i) 
	{
		pthread_join(consumer_threads[i], NULL);
	}

	SLListDestroy(g_resource2);
	pthread_mutex_destroy(&mutex2);
}

void *Producer2(void *arg) 
{
	size_t i = 0;

	(void)arg;

	srand(time(NULL));

	for (i = 0; i < NUM_OF_RESOURCE; ++i) 
	{
		int *data = (int *)malloc(sizeof(int));
		
		*data = rand() % 1000;

		pthread_mutex_lock(&mutex2);

		SLListInsert(g_resource2, data, SLListGetEnd(g_resource2));
		
		printf("Produced: %d\n", *data);

		pthread_mutex_unlock(&mutex2);
	}
	
	return NULL;
}

void *Consumer2(void *arg) 
{
	int *data = NULL;
	
	while (!SLListIsEmpty(g_resource2) || !stop)
	{
		iterator_t iter = {0};

		pthread_mutex_lock(&mutex2);

		if (!SLListIsEmpty(g_resource2)) 
		{
			iter = SLListGetBegin(g_resource2);
			
			data = (int *)SLListGetData(iter);
			
			SLListRemove(iter);
			
			printf("Consumed: %d\n", *data);
			
			free(data);
		}

		pthread_mutex_unlock(&mutex2);
	}
	
	(void)arg;
	return NULL;
}


/********************************************/
/*			   		Ex3						*/
/********************************************/


static linked_list_t *g_resource3 = NULL;
static pthread_mutex_t mutex3 = PTHREAD_MUTEX_INITIALIZER;
static sem_t sem3;

void Ex3(void)
{
	pthread_t producer_threads[NUM_OF_PRODUCERS] = {0};
	pthread_t consumer_threads[NUM_OF_CONSUMERS] = {0};
	size_t i = 0;
	
	g_resource3 = SLListCreate();
	if (NULL == g_resource3)
	{
		printf("error creating slist\n");
		return;
	}
	
	stop = 0;
	pthread_mutex_init(&mutex3, NULL);
	sem_init(&sem3, 0, 1);

	for (i = 0; i < NUM_OF_PRODUCERS; ++i) 
	{
		pthread_create(&producer_threads[i], NULL, Producer3, NULL);
		pthread_create(&consumer_threads[i], NULL, Consumer3, NULL);
	}

	for (i = 0; i < NUM_OF_PRODUCERS; ++i) 
	{
		pthread_join(producer_threads[i], NULL);
	}
	
	stop = 1;
	
	for (i = 0; i < NUM_OF_CONSUMERS; ++i) 
	{
		pthread_join(consumer_threads[i], NULL);
	}

	SLListDestroy(g_resource3);
	pthread_mutex_destroy(&mutex3);
}

void *Producer3(void *arg) 
{
	size_t i = 0;

	(void)arg;

	srand(time(NULL));

	for (i = 0; i < NUM_OF_RESOURCE; ++i) 
	{
		int *item = (int *)malloc(sizeof(int));
		*item = rand() % 1000;

		pthread_mutex_lock(&mutex3);

		SLListInsert(g_resource3, item, SLListGetEnd(g_resource3));
		printf("Produced: %d\n", *item);

		pthread_mutex_unlock(&mutex3);

		sem_post(&sem3);
	}
	
	return NULL;
}

void *Consumer3(void *arg) 
{
	(void)arg;

	while (!SLListIsEmpty(g_resource3) || !stop)
	{
		iterator_t iter = {0};
		int *data = NULL;

		sem_wait(&sem3);

		pthread_mutex_lock(&mutex3);

		if (!SLListIsEmpty(g_resource3)) 
		{		
			iter = SLListGetBegin(g_resource3);
			
			data = (int *)SLListGetData(iter);
			
			SLListRemove(iter);

			printf("Consumed: %d\n", *data);
			
			free(data);
		}

		pthread_mutex_unlock(&mutex3);
	}
	
	return NULL;
}


/********************************************/
/*			   		Ex4						*/
/********************************************/


static cbuffer_t *g_resource4 = NULL;
static pthread_mutex_t mutex4 = PTHREAD_MUTEX_INITIALIZER;
static sem_t empty;
static sem_t full;

void Ex4(void)
{
	pthread_t producer_threads[NUM_OF_PRODUCERS] = {0};
	pthread_t consumer_threads[NUM_OF_CONSUMERS] = {0};
	size_t i = 0;
	
	g_resource4 = CBufferCreate(CAPACITY);
	if (NULL == g_resource4)
	{
		printf("error creating cbuffer\n");
		return;
	}
	
	pthread_mutex_init(&mutex4, NULL);
	sem_init(&empty, 0, CAPACITY);
	sem_init(&full, 0, 0);

	for (i = 0; i < NUM_OF_PRODUCERS; ++i) 
	{
		pthread_create(&producer_threads[i], NULL, Producer4, NULL);
		pthread_create(&consumer_threads[i], NULL, Consumer4, NULL);
	}

	for (i = 0; i < NUM_OF_PRODUCERS; ++i) 
	{
		pthread_join(producer_threads[i], NULL);
	}

	for (i = 0; i < NUM_OF_CONSUMERS; ++i) 
	{
		pthread_join(consumer_threads[i], NULL);
	}

	CBufferDestroy(g_resource4);
	pthread_mutex_destroy(&mutex4);
	sem_destroy(&empty);
	sem_destroy(&full);
}

void *Producer4(void *arg)
{
	size_t i = 0;
	int data = 0;
	
	(void)arg;
	
	srand(time(NULL));
	
	for (i = 0; i < NUM_OF_RESOURCE; ++i)
	{
		data = rand() % 1000;
		
		sem_wait(&empty);		

		pthread_mutex_lock(&mutex4);
		
		CBufferWrite(g_resource4, &data, sizeof(int));
		
		printf("Produced: %d\n", data);
		
		pthread_mutex_unlock(&mutex4);		

		sem_post(&full);
		
		sleep(1);
	}
	
	return NULL;
}

void *Consumer4(void *arg)
{
	size_t i = 0;
	int data = 0;
	
	(void)arg;

	for (i = 0; i < NUM_OF_RESOURCE; i++)
	{		
		sem_wait(&full);

		pthread_mutex_lock(&mutex4);
		
		CBufferRead(g_resource4, &data, sizeof(int));
		
		printf("Consumed: %d\n", data);
		
		pthread_mutex_unlock(&mutex4);

		sem_post(&empty);		
		
		sleep(1);
	}
	
	return NULL;
}


/********************************************/
/*			   		Ex5						*/
/********************************************/


static fsq_t *g_resource5 = NULL;

void Ex5(void)
{
	pthread_t producer_threads[NUM_OF_PRODUCERS] = {0};
	pthread_t consumer_threads[NUM_OF_CONSUMERS] = {0};
	size_t i = 0;
	
	g_resource5 = FSQCreate(CAPACITY);
	if (NULL == g_resource5)
	{
		printf("error creating fsq\n");
		return;
	}

	for (i = 0; i < NUM_OF_PRODUCERS; ++i) 
	{
		pthread_create(&producer_threads[i], NULL, Producer5, NULL);
		pthread_create(&consumer_threads[i], NULL, Consumer5, NULL);
	}

	for (i = 0; i < NUM_OF_PRODUCERS; ++i) 
	{
		pthread_join(producer_threads[i], NULL);
	}

	for (i = 0; i < NUM_OF_CONSUMERS; ++i) 
	{
		pthread_join(consumer_threads[i], NULL);
	}

	FSQDestroy(g_resource5);
}

void *Producer5(void *arg) 
{
	size_t i;
	int *data = NULL;
	
	(void)arg;
	
	srand(time(NULL));
	
	for (i = 0; i < NUM_OF_RESOURCE; i++) 
	{
		data = (int *)malloc(sizeof(int));
	
		*data = rand() % 1000;
	
		FSQEnqueue(g_resource5, data);
	
		printf("Produced: %d\n", *data);
	}
	
	return NULL;
}

void *Consumer5(void *arg) 
{
	size_t i;
	int *data = NULL;
	
	(void)arg;

	for (i = 0; i < NUM_OF_RESOURCE; i++) 
	{
		data = (int *)FSQDequeue(g_resource5);
	
		printf("Consumed: %d\n", *data);
	
		free(data);
	}
	
	return NULL;
}


/********************************************/
/*			   		Ex6						*/
/********************************************/


static pthread_mutex_t mutex6 = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
static sem_t sem6;

static int message;
static int consumed_count;
static int massage_count;
static volatile int ready;

void Ex6(void)
{
	pthread_t consumer_threads[NUM_OF_CONSUMERS] = {0};
	pthread_t producer_thread = {0};
	int* data = NULL;
	size_t i = 0;
	
	pthread_mutex_init(&mutex6, NULL);
	pthread_cond_init(&cond, NULL);
	sem_init(&sem6, 0, 1);

	pthread_create(&producer_thread, NULL, Producer6, NULL);

	for (i = 0; i < NUM_OF_CONSUMERS; i++) 
	{
		data = malloc(sizeof(int));
		*data = i + 1;
		pthread_create(&consumer_threads[i], NULL, Consumer6, data);
	}

	pthread_join(producer_thread, NULL);
	
	stop = 1;

	for (i = 0; i < NUM_OF_CONSUMERS; i++) 
	{
		pthread_detach(consumer_threads[i]);
	}

	sem_destroy(&sem6);
	pthread_mutex_destroy(&mutex6);
	pthread_cond_destroy(&cond);
}

void *Producer6(void *arg) 
{
	massage_count = 0;
	
	srand(time(NULL));
	
	while (massage_count < NUM_OF_MESSAGES) 
	{
		sem_wait(&sem6);

		pthread_mutex_lock(&mutex6);
		
		message = rand() % 1000;
		
		printf("Produced: %d\n", message);
		
		consumed_count = 0;
		
		ready = 1;
		
		pthread_cond_broadcast(&cond);
		pthread_mutex_unlock(&mutex6);
		
		++massage_count;
		sleep(1);
	}

	stop = 1;

	return arg;
}

void *Consumer6(void *arg) 
{
	int message_to_read = 0;
	int consumer_number = *(int *)arg;
	
	free(arg);

	while (!stop)
	{
		while (!ready && !stop) 
		{ 
			pthread_cond_wait(&cond, &mutex6);
		}

		message_to_read = message;
		printf("Consumer %d consumed: %d\n", consumer_number, message_to_read);
		++consumed_count;

		if (consumed_count == NUM_OF_CONSUMERS) 
		{
			ready = 0;
			pthread_cond_broadcast(&cond);
			sem_post(&sem6);
		} 
		else 
		{
			while (ready && !stop) 
			{
				pthread_cond_wait(&cond, &mutex6);
			}
		}
		
		if(NUM_OF_MESSAGES == massage_count && consumed_count == NUM_OF_CONSUMERS)
		{
			return NULL;
		}
	}
	
	printf("hry\n");
	
	return NULL;
}


