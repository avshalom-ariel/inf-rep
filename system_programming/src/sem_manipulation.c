
#include <stdlib.h>		/*exit, atoi*/
#include <stdio.h>		/*stdin*/
#include <string.h>		/*strlen*/
#include <fcntl.h>      /*For O_* constants */
#include <sys/stat.h>   /*For mode constants */
#include <semaphore.h>	/*sem_open, sem_unlink, sem_getvalue*/

#define BUFFER_SIZE 50 /*Arbitrary, should hold char and and int*/

static void Decrement(sem_t *my_sem, int number, int undo);
static void Increment(sem_t *my_sem, int number, int undo);
static void Undo(sem_t *my_sem);

int g_lock;
size_t g_undo;


/********************************************/
/*			   Main Functions				*/
/********************************************/


void SemManipulation(const char *name)
{
	int number = 0;
	int sem_val = 0;
	int undo = 0;
	char *buffer = NULL;
	
	sem_t *my_sem = sem_open(name, O_CREAT, S_IWUSR, 0);
	if (SEM_FAILED == my_sem)
	{
		perror("sem_open failed!\n");
    	exit(EXIT_FAILURE);
	}
	
	buffer = (char*)malloc(BUFFER_SIZE * sizeof(char));
	if (!buffer)
	{
		perror("malloc failed!\n");
		sem_unlink(name);
    	exit(EXIT_FAILURE);
	}
	
	printf("Semaphore created, please insert input:\n");
	
	buffer[strlen(buffer) - 1] = '\0';
	
	while ('X' != *buffer)
	{
		number = 0;
		undo = 0;
		
		if (NULL == fgets(buffer, BUFFER_SIZE, stdin)) 
		{
		   perror("command reading failed!\n");
		   sem_unlink(name);
		   exit(EXIT_FAILURE);
		}
	
		buffer[strlen(buffer) - 1] = '\0';
	
		if ('D' == *buffer)
		{
			number = atoi(buffer + 2);
			printf ("Decrement by %d\n", number);
			
			if ('1' == buffer[strlen(buffer) - 1])
			{
				undo = 1;
			}
			
			Decrement(my_sem, number, undo);
		}
		else if ('I' == *buffer)
		{
			number = atoi(buffer + 2);
			printf ("Increment by %d\n", number);
			
			if ('1' == buffer[strlen(buffer) - 1])
			{
				undo = 1;
			}
			
			Increment(my_sem, number, undo);
		}
		else if ('V' == *buffer)
		{
			if (-1 == sem_getvalue(my_sem, &sem_val))
			{
				perror("command reading failed!\n");
				sem_unlink(name);
		   		exit(EXIT_FAILURE);
			}
			
			printf ("Semaphore is: %d\n", sem_val);
		}
		else
		{
			printf("Invalid input, please enter input:\n");
		}
	}
	
	printf("Exit program\n");
	
	Undo(my_sem);
	
	if (-1 == sem_getvalue(my_sem, &sem_val))
	{
		perror("command reading failed!\n");
		sem_unlink(name);
   		exit(EXIT_FAILURE);
	}
	
	if (!sem_val)
	{
		if (-1 == sem_unlink(name))
		{
			printf("closing failed\n");
		}
	}
	
	free(buffer);
}


/********************************************/
/*			   Avction Functions			*/
/********************************************/


void Decrement(sem_t *my_sem, int number, int undo)
{
	while (0 < number && 0 < g_lock)
	{
		sem_wait(my_sem);
		--number;
		--g_lock;
		
		g_undo += undo;
	}
}

void Increment(sem_t *my_sem, int number, int undo)
{
	g_lock += number;
			
	while (number)			
	{
		sem_post(my_sem);
		--number;
		
		g_undo -= undo;
	}
}

void Undo(sem_t *my_sem)
{
	if (0 < g_undo)
	{
		Decrement(my_sem, g_undo, 0);
	}
	else
	{
		Increment(my_sem, g_undo, 0);
	}
}


