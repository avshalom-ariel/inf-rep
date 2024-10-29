
#include <stdio.h> /*printf*/
#include <assert.h> /*assert*/

#include "stack.h" 

void MyPush(stack_t *stack, void *new_element);
void MyPop(stack_t *stack);
int GetMinElement();


static int min_element;


int main(void)
{
	stack_t *stack = StackCreate(10, sizeof(int));
	int x1 = 4;
	int x2 = 7;
	int x3 = 9;
	int x4 = 3;
	int x5 = 3;
	int x6 = 5;
	int x7 = 2;
	int x8 = 1;
	int x9 = 20;
	int x10 = 0;
	
	MyPush(stack, &x1);
	
	assert(x1 == GetMinElement());
	
	MyPush(stack, &x2);
	MyPush(stack, &x3);
	
	assert(x1 == GetMinElement());
	
	MyPush(stack, &x4);
	
	assert(x4 == GetMinElement());
	
	MyPush(stack, &x5);
	MyPush(stack, &x6);
	MyPush(stack, &x7);
	
	assert(x7 == GetMinElement());
	
	MyPush(stack, &x8);
	
	assert(x8 == GetMinElement());
	
	MyPush(stack, &x9);
	
	assert(x8 == GetMinElement());
	
	MyPush(stack, &x10);
	
	assert(x10 == GetMinElement());
	
	MyPop(stack);
	
	assert(x8 == GetMinElement());
	
	MyPop(stack);
	MyPop(stack);
	MyPop(stack);
	
	assert(x4 == GetMinElement());
	
	MyPop(stack);
	MyPop(stack);
	MyPop(stack);
	
	assert(x1 == GetMinElement());
	
	StackDestroy(stack);
	
	printf("All tests passed!\n");
	
	return 0;
}


void MyPush(stack_t *stack, void *new_element)
{
	int new_to_push = 0;

	
	if(StackIsEmpty(stack))
	{
		min_element = *(int *)new_element;
	}
	
	if(*(int *)new_element > min_element)
	{
		StackPush(stack, new_element);
	}
	else
	{
		new_to_push = (*(int *)new_element) - min_element;
		min_element = (*(int *)new_element);
		StackPush(stack, &new_to_push);
	}
}
	
	
	
void MyPop(stack_t *stack)
{
	int element_to_pop = *(int *)StackPeek(stack);
	
	if(element_to_pop > min_element)
	{
		StackPop(stack);
	}
	else
	{
		min_element = min_element - element_to_pop;
		StackPop(stack);
	}
}


int GetMinElement()
{
	return min_element;
}

