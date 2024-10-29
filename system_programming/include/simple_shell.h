#ifndef __AVSHI_SHELL_H__
#define __AVSHI_SHELL_H__

#include <unistd.h>			/*pid_t*/

#define COMMAND_SIZE 50
#define MAX_WORDS_IN_COMMAND 40
#define ERROR -1
#define TRUE 1

/*void CommandToArg(char *argv[MAX_WORDS_IN_COMMAND], char *command);*/

int Fork(void);
int System(void);




#endif /*__AVSHI_SHELL_H__*/
