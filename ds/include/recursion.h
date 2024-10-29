#ifndef __RECURSION_H__
#define __RECURSION_H__

#include "stack.h" /*stack_t*/

typedef struct node node_t;

int Fibonacci(int element_index);
node_t *FlipList(node_t *head);


void SetNode(node_t *node, node_t *next, void *data);
void *GetData(node_t *node);
void StackSort(stack_t *stack);
void StackSortInsert(stack_t *stack, int *peek);

node_t *Next(node_t *node);

size_t Strlen(char *str);
int Strcmp(char *str1, char *str2);
char *Strcpy(char *dest, char *src);
char *Strcat(char *dest, char *src);
char *Strstr(char *haystack, char *needle);

void StackOverflow(void);

#endif /*__RECURSION_H__*/
