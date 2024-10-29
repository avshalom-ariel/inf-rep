/*
Author: Avshalom Ariel
Review by: 
Review date:
Status:
*/

#include <stdio.h> /*printf*/
#include <stddef.h> /*NULL*/
#include <string.h> /*strncmp*/
#include <assert.h> /*assert*/

#include "recursion.h" /*Typedefs and functiion declarations*/
#include "stack.h" /*Stack functions*/

#define MIN(a,b) (*(int *)a <= *(int *)b) ? a : b
#define MAX(a,b) (*(int *)a >= *(int *)b) ? a : b

int a = 0;

struct node
{
	struct node *next;
	void *data;
};


/************** Recursion Functions ****************/


int Fibonacci(int element_index)
{
	if (2 > element_index)
	{
		return 1;
	}
	
	return Fibonacci(element_index - 1) + Fibonacci(element_index - 2);
}


node_t *FlipList(node_t *head)
{
	assert(head);
	
	if (NULL != head->next->next)
	{
		FlipList(head->next)->next = head;
	}
	
	head->next->next = head;
	head->next = NULL;
	
	return head;
}


void StackSort(stack_t *stack)
{
	int *peek = NULL;
	
	if (StackIsEmpty(stack))
	{
		return;
	}
	
	peek = (int *)StackPeek(stack);
	StackPop(stack);
		
	StackSort(stack);
		
	StackSortInsert(stack, peek);
	
	
}


void StackSortInsert(stack_t *stack, int *peek)
{
	int peek_insert = 0;
	
	if (StackIsEmpty(stack) || *peek > *(int *)StackPeek(stack))
	{
		StackPush(stack, peek);
		return;
	}
	
	peek_insert = *(int *)StackPeek(stack);
	StackPop(stack);
	
	StackSortInsert(stack, peek);
	
	StackPush(stack, &peek_insert);
}


/********* String Functions ***********/


size_t Strlen(char *str)
{
	if (0 == *str)
	{
		return 0;
	}
	
	return Strlen(str + 1) + 1;
}


int Strcmp(char *str1, char *str2)
{
	if (*str1 != *str2 || 0 == *str1 || 0 == *str2)
	{
		return *str1 - *str2;
	}
	
	return Strcmp(str1 + 1, str2 + 1);
}


char *Strcpy(char *dest, char *src)
{
	if (0 == *src)
	{
		return dest;
	}
	
	*dest = *src;
	
	return Strcpy(dest + 1, src + 1);
}


char *Strcat(char *dest, char *src)
{
	if (0 == *dest)
	{
		Strcpy(dest, src);
		return dest;
	}
	
	return Strcat(dest + 1, src);
}


char *Strstr(char *haystack, char *needle)
{
	if (0 == strncmp(haystack, needle, Strlen(needle)))
	{
		return haystack;
	}
	
	if (0 == *haystack)
	{
		return NULL;
	}

	return Strstr(haystack + 1, needle);
}


/**************** Help Functions ******************/

void SetNode(node_t *node, node_t *next, void *data)
{
	node->next = next;
	node->data = data;
}

void *GetData(node_t *node)
{
	return node->data;
}


node_t *Next(node_t *node)
{
	return node->next;
}


/**************** Stack Overflow Functions ******************/


void StackOverflow(void)
{
	int k = 0, b = 0, c = 0;
	a += 1;
	
	(void)k;
	(void)b;
	(void)c;
	
	printf("iter: %d\n", a);
	StackOverflow();
}





