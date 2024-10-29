/* 
writen by Avshalom Ariel
in 04/05 was reviewed by Yan
*/


#include <stdlib.h> /*malloc size_t*/
#include <string.h>

typedef struct
{
	size_t capacity;
	size_t size;
	size_t element_size;
	char *buffer;
} stack_t;


stack_t *StackCreate(size_t capacity, size_t element_size)
{
	
	stack_t *stack = (stack_t *)malloc(sizeof(stack_t) + element_size * capacity);
	if (NULL == stack)
	{
		return NULL;
	}
	
	stack -> capacity = capacity;
	stack -> element_size = element_size;
	stack -> size = 0;
	stack -> buffer = (char *)stack + sizeof(stack_t);
	
	return stack;
}


void StackDestroy(stack_t *stack)
{
	if (NULL == stack)
	{
		return;
	}
	
	free(stack);
}


void StackPop(stack_t *stack)
{
	if(stack->size)
	{
		--stack->size;
	}
}


void StackPush(stack_t *stack, void *new_element)
{
	size_t i = 0;
	
	if (stack->size == stack->capacity)
	{
		return;
	}
	
	for (;i < stack->element_size; ++i)
	{
		*(stack->buffer + (stack->size * stack->element_size) + i) = *((char *)new_element + i);
	}
	
	++stack->size;
}


int StackIsEmpty(const stack_t *stack)
{
	return !(stack -> size);
}


size_t StackGetSize(const stack_t *stack)
{
	return (stack -> size);
}


size_t StackGetCapacity(const stack_t *stack)
{
	return (stack -> capacity);
}


void *StackPeek(const stack_t *stack)
{	
	return ((void *)(stack->buffer + ((stack->size - 1) * stack->element_size)));
}


