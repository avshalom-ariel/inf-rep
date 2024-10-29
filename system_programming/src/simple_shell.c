/*
Name: Avshalom Ariel
Reveiwer: Ido
date: 	09/07/2024
status: 
*/

#include <string.h>			/*memcpy*/
#include <unistd.h>			/*fork*/
#include <stdio.h>			/*printf, gets*/
#include <stdlib.h>			/*system*/
#include <sys/types.h>		/*pid_t*/
#include <sys/wait.h> 		/*wait WEXITSTATUS*/
#include <signal.h>			/*kill, signals*/

#include "simple_shell.h"	/*function declarations*/


/********************************************/
/*			    Shell Functions    		    */
/********************************************/


int Fork(void)
{
	pid_t pid = 0;
	int status = 0;
	char command[COMMAND_SIZE] = {0};
	char *argv[MAX_WORDS_IN_COMMAND] = {0};
	char **runner = argv;
	char *token = NULL;
	char space[2] = " ";
	
	while (0 != memcmp("exit", command, strlen("exit")))
	{
		if (!fgets(command, COMMAND_SIZE, stdin))
		{
			printf("Command reading failed!\n");
			return -1;
		}
		
		runner = argv;
		
		command[strlen(command) - 1] = '\0';
		
		token = strtok(command, " ");
		
		while (NULL != token)
		{
			*runner = token;
			++runner;
			
			token = strtok(NULL, space);
		}
		
		*runner = NULL;
		
		pid = fork();
		
		if (0 > pid)
		{
			printf("fork child process creation failed!\n");
			
			return -1;
		}
		else if (0 == pid)
		{
			status = execvp(command, argv);
			if (ERROR == status)
			{
				return status;
			}
		}
		else
		{
			waitpid(pid, &status, 0);
		}
	}
	
	return 0;
}

int System(void)
{
	char command[COMMAND_SIZE] = {0};
	int status = 0;
	
	while (0 != memcmp("exit", command, strlen("exit")))
	{	
		if (!fgets(command, COMMAND_SIZE, stdin))
		{
			printf("Command reading failed!\n");
			return -1;
		}
		
		command[strlen(command) - 1] = '\0';
					
		status = system(command);
		if (-1 == status)
		{
			printf("system execute failed\n");
		}
	}
	
	return 0;
}


