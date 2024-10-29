#define _POSIX_C_SOURCE 199309L
#include <stdio.h>		/*perror*/
#include <stdlib.h>		/*exit*/
#include <time.h>		/*time_t*/
#include <sys/types.h>	/*pid_t*/
#include <unistd.h>		/*pause*/
#include <sys/stat.h>  	/*For mode constants in sem_open (SEM_NAME,)*/
#include <fcntl.h>      /* For O_* constants in fopen (O_CREAT)*/
#include <signal.h>		/*signaction, ginal functions, signal typedef*/
#include <pthread.h>	/*pthread typedef and functions*/
#include <semaphore.h>	/*sem_t, semaphore functions*/
#include <stdatomic.h> 	/*atomic typedef and functions*/

#include "watch_dog.h"

#define SNAME "/mysem"


static void WatchDog(size_t interval_in_seconds, size_t repitition, char **argv);
static void *WDThreadCheckRoutine(void *data);
static void WDRevive(char **argv)
static void Handler(int signal);

static volatile unsigned int sig_flag = 0;
atomic_int g_count = ATOMIC_VAR_INIT(0);
static sem_t client_sem;
static sem_t wd_sem;
static sem_t wd_check_sem;


int MMI(size_t interval_in_seconds, size_t repitition, char **argv)
{
	pthread_t wd_check_thread = {0};
	struct sigaction act = {0};
	pid_t pid = 0;
	int status = 0;
	sem_t *sem = NULL;
	
	act.sa_handler = Handler;
	act.sa_flags = 0;
	
	if (-1 == sigaction(SIGUSR1, &act, NULL))
	{
		perror("fork failed!\n");
		exit(EXIT_FAILURE);
	}

	sem = sem_open(SNAME, O_CREAT, 0644, 0);

	sem_init(&wd_check_sem, 0, 0);
	sem_init(&client_sem, 0, 0);
	sem_init(&wd_sem, 0, 0);

	pid = fork();
	if (0 > pid)		/*ERROR*/
	{
		perror("fork failed!\n");
		exit(EXIT_FAILURE);
	}
	else if (0 == pid)	/*CHILD*/
	{
		WatchDog(interval_in_seconds, repitition, argv);
	}
	else				/*PARENT*/
	{	
		if(-1 == sigaction(SIGUSR1, &act, NULL))
		{
			perror("sigaction failure");
			exit(EXIT_FAILURE);
		}
		
		pthread_create(&wd_check_thread, NULL, WDThreadCheckRoutine, NULL);
		
		sem_wait(/*client_*/sem);
		pthread_join(wd_check_thread, NULL);

		wait(NULL);
	}
}

void Handler(int signal)
{	
	(void)signal;
	sig_flag = 1;
}

void WDRevive(char **argv)
{
	while(1)
	{
		if(sig_flag)
		{
			sig_flag = 0;

			sleep(1);

			kill(pid,sig);
		}
		else
		{
			pause(); /* Avoid busy waiting */
		}
	}
}

void WatchDog(size_t interval_in_seconds, size_t repitition, char **argv)
{
	pid_t pid = {0};
	sem_t *sem = sem_open(SNAME, 0);

	if (SEM_FAILED == sem)
	{
		printf("failed!\n");
	}
	
	pid = getppid();
	
	kill(pid, SIGUSR1);
	
	sem_post(&wd_check_sem);
/*	sem_wait(&wd_sem);*/
	sem_post(/*client_*/sem);
}

void *WDThreadCheckRoutine(void *data)
{
	if (sig_flag)
	{
		printf("signal received!\n");
	}
	
	sem_post(&wd_sem);
/*	sem_wait(&wd_check_sem);*/
	sem_post(&client_sem);
}

