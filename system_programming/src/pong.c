#define _POSIX_C_SOURCE 199309L
#include <stdio.h>			/*printf*/
#include <signal.h>			/*signal*/
#include <sys/types.h>		/*pid_t*/
#include <unistd.h>			/*pause, kill*/
#include <stdlib.h>			/*atoi*/
	
static pid_t pid;

static void PongHandler(int signal);

static volatile unsigned int sig_flag = 0;

int main(int argc, char **argv)
{
	struct sigaction act;

	(void)argc;
	
	act.sa_handler = PongHandler;
    act.sa_flags = SA_SIGINFO;
	sigemptyset(&act.sa_mask);
	
	if (sigaction(SIGUSR2, &act, NULL) == -1)
	{
		perror("sigaction");
	}
	
	pid = atoi(argv[1]);

	kill(pid, SIGUSR1);

	while (1)
	{
        if(1 == sig_flag)
		{
			sig_flag = 0;
			printf("       pong\n");
			sleep(1);
			kill(pid, SIGUSR1);
		}
		
		pause();
	}

	return 0;
}

void PongHandler(int signal)
{
	(void)signal;
	
	sig_flag = 1;
}


