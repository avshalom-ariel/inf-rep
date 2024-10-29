
#include <stdio.h> /*printf*/
#include <stdlib.h> /*malloc*/

typedef struct
{
	size_t size;
	int buffer[10];
} stack_t;


typedef struct
{
	stack_t stack1;
	stack_t stack2;
} queue_t;


void StackPush(stack_t *stack, int new_element);
int StackPop(stack_t *stack);
int StackIsEmpty(stack_t stack);


void Enqueue(queue_t *queue, int new_element);
int Dequeue(queue_t *queue);


int main(void)
{
	queue_t *queue = (queue_t *)malloc(sizeof(queue_t));
	
	int data1 = 1;
	int data2 = 2;
	int data3 = 3;
	int data4 = 4;
	
	Enqueue(queue, data1);
	Enqueue(queue, data2);
	Enqueue(queue, data3);
	Enqueue(queue, data4);
	
	printf("first Dequeue (should be 1): %d\n", Dequeue(queue));
	printf("second Dequeue (should be 2): %d\n", Dequeue(queue));
	printf("third Dequeue (should be 3): %d\n", Dequeue(queue));
	printf("fourth Dequeue (should be 4): %d\n", Dequeue(queue));
	
	return 0;
}


void StackPush(stack_t *stack, int new_element)
{
	stack->buffer[stack->size] = new_element;
	++stack->size;
}


int StackPop(stack_t *stack)
{
	--stack->size;
	return stack->buffer[stack->size];
}


int StackIsEmpty(stack_t stack)
{
	return (0 == stack.size);
}


void Enqueue(queue_t *queue, int new_element)
{
	while (!StackIsEmpty(queue->stack1))
	{
		StackPush(&(queue->stack2), StackPop(&(queue->stack1)));
	}
	
	StackPush(&(queue->stack1), new_element);
	
	while (!StackIsEmpty(queue->stack2))
	{
		StackPush(&(queue->stack1), StackPop(&(queue->stack2)));
	}
}


int Dequeue(queue_t *queue)
{
	return StackPop(&(queue->stack1));
}


