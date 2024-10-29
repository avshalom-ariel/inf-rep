
#include <string.h>			/*memcmp, strlen*/
#include <stdio.h>			/*printf, fgets*/

#include "simple_shell.h"	/*function declarations*/

int main(int argc, char **argv)
{
	int status = 0;

	(void)argc;
		
	printf("Running Avshi's Shell...\n");

	if (0 == memcmp("fork", argv[1], strlen("fork")))
	{
		status = Fork();
	}
	else if (0 == memcmp("system", argv[1], strlen("system")))
	{
		status = System();
	}
	else
	{
		printf("Invalid command, please enter 'fork' or 'system'\n");
	}
	
	if (0 == status)
	{		
		printf ("Leaving Avshi's Shell...\n");
	
		return 0;
	}
	else if (ERROR == status)
	{
		return -1;
	}
	else
	{
		return 0;
	}
	
	return 0;
}


