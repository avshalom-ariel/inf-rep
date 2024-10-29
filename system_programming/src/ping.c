
#define _POSIX_C_SOURCE 199309L
#include <stdio.h>			/*printf*/
#include <signal.h>			/*signal*/
#include <sys/types.h>		/*pid_t*/
#include <unistd.h>			/*pause, kill*/

static void PingHandler(int signal, siginfo_t *info, void *somthing);

int main(void)
{
	struct sigaction act;
	
	act.sa_sigaction = PingHandler;
    act.sa_flags = SA_SIGINFO;
    sigemptyset(&act.sa_mask);
	
	if (sigaction(SIGUSR1, &act, NULL) == -1)
	{
		perror("sigaction");
	}

	while (1)
	{	
		pause();
	}

	return 0;
}

void PingHandler(int signal, siginfo_t *info, void *somthing)
{
	(void)signal;
	(void)somthing;
	printf("ping\n");
	sleep(1);

	kill(info->si_pid, SIGUSR2);
}


