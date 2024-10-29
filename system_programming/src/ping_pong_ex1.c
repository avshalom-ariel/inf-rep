/*
Name: Avshalom Ariel
Reveiwer: Yarden
Date: 14/07/2024
status: Approved
*/
#define _POSIX_C_SOURCE 199309L
#include <stdlib.h>		/*exit*/
#include <stdio.h>		/*printf*/
#include <signal.h>		/*sigaction, SIGUSR1, SIGUSR2*/
#include <sys/types.h>	/*pid_t*/
#include <unistd.h>		/*pause, kill, sleep, getppid, dork*/

#include "ping_pong_ex1.h"

static volatile unsigned int sig_flag = 0;

static void SignalLoop(pid_t pid, int sig, char *str);
static void Handler(int signal);

void PingPong(void)
{
	struct sigaction act = {0};
	pid_t pid = 0;
	
	act.sa_handler = Handler;
	
	act.sa_flags = 0;
	
	if (-1 == sigaction(SIGUSR2, &act, NULL))
	{
		perror("fork failed!\n");
		exit(EXIT_FAILURE);
	}

	pid = fork();
	if (0 > pid)		/*ERROR*/
	{
		perror("fork failed!\n");
		exit(EXIT_FAILURE);
	}
	else if (0 == pid)		/*CHILD*/
	{
		SignalLoop(getppid(), SIGUSR2, "ping\n");
	}
	else				/*PARENT*/
	{	
		if(-1 == sigaction(SIGUSR2, &act, NULL))
		{
			perror("sigaction failure");
			exit(EXIT_FAILURE);
		}
		
		kill(pid, SIGUSR1);
		SignalLoop(pid, SIGUSR1, "		pong\n");
	}
}


void Handler(int signal)
{	
	(void)signal;
	sig_flag = 1;
}


void SignalLoop(pid_t pid, int sig, char *str)
{
	while(1)
	{
		if(sig_flag)
		{
			sig_flag = 0;

			printf("%s", str);
			sleep(1);

			kill(pid,sig);
		}
		else
		{
			pause(); /* Avoid busy waiting */
		}
	}
}


