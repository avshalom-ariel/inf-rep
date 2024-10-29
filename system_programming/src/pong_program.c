#define _POSIX_C_SOURCE 1
#include <stdio.h>			/*printf*/
#include <stdlib.h>			/*exit*/
#include <stddef.h>			/*size_t*/
#include <signal.h>			/*signal*/
#include <sys/types.h>		/*pid_t*/
#include <unistd.h>			/*fork pause*/

static void Handler(int signal);

static volatile unsigned int sig_flag = 1;

int main(void)
{	
 	struct sigaction act = {0};
	
	act.sa_handler = Handler;
	
	act.sa_flags = 0;
	
	if (-1 == sigaction(SIGUSR1, &act, NULL))
	{
		perror("fork failed!\n");
		exit(EXIT_FAILURE);
	}
	
	while (1)
	{
		if(sig_flag)
		{
			sig_flag = 0;

			printf("         pong\n");
			sleep(1);

			if (-1 == kill(getppid(), SIGUSR2))
			{
				perror("kill failed!\n");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			pause(); /* Avoid busy waiting */
		}
		
		pause();
	}
}

void Handler(int signal)
{	
	(void)signal;
	sig_flag = 1;
}


