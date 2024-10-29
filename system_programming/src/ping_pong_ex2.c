/*
Name: Avshalom Ariel
Reveiwer: Yarden
Date: 14/07/2024
status: Approved
*/

#define _POSIX_C_SOURCE 1
#include <stdio.h>			/*printf*/
#include <stdlib.h>			/*exit*/
#include <signal.h>			/*sigaction*/
#include <unistd.h>			/*fork pause*/
#include <sys/types.h>		/*pid_t*/
#include <sys/wait.h>		/*wait*/

#include "ping_pong_ex2.h"

#define ERROR -1
#define MAX_WORDS_IN_COMMAND 30

static volatile unsigned int sig_flag = 1;

static void Handler(int signal);


/********************************************/
/*			   Second Exercise				*/
/********************************************/


void PingProgram(void)
{
 	char *argv[MAX_WORDS_IN_COMMAND] = {0};
	int status = 0;
 	
 	struct sigaction act = {0};
	pid_t pid = 0;
	
	act.sa_handler = Handler;
	
	act.sa_flags = 0;
	
	if (-1 == sigaction(SIGUSR2, &act, NULL))
	{
		perror("fork failed!\n");
		exit(EXIT_FAILURE);
	}

 	argv[0] = "./pong_program";
 	
	pid = fork();

	if (-1 == pid)
	{
		return;
	}
	else if (0 == pid)
	{
		status = execvp(argv[0], argv);
		if (ERROR == status)
		{
			perror("error");
		}
	}
	else
	{	
		printf("pid=:%d\n", pid);

		while(1)
		{
			if(sig_flag)
			{
				sig_flag = 0;

				printf("ping\n");
				sleep(1);

				if (-1 == kill(pid, SIGUSR1))
				{
					perror("kill failed!\n");
					exit(EXIT_FAILURE);
				}
			}
			else
			{
				pause(); /* Avoid busy waiting */
			}
			
			wait(&status);
		}
	}
}


/********************************************/
/*			   	  Handler					*/
/********************************************/


void Handler(int signal)
{	
	(void)signal;
	sig_flag = 1;
}


