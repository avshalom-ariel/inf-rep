#include <assert.h> /*assert*/
#include <stdio.h> /*printf */


#include "stack.h"


int main(void)
{
	char a = 'A';
	char b = 'B';
	char char_peak = '0';
	stack_t *char_stack = StackCreate(20, sizeof(char));
	
	int num1 = 11005;
	int num2 = 245;
	int int_peak = 0;
	stack_t *int_stack = StackCreate(30,sizeof(int));
	
	assert(char_stack);
	assert(int_stack);
	
	assert(0 == StackGetSize(char_stack));
	assert(0 == StackGetSize(int_stack));
	
	StackPush(char_stack, &a);
	assert(1 == StackGetSize(char_stack));

	StackPush(int_stack, &num1);
	assert(1 == StackGetSize(int_stack));
	
	
	char_peak = *(char *)StackPeek(char_stack);
	assert('A' == char_peak);
	
	int_peak = *(int *)StackPeek(int_stack);
	assert(num1 == int_peak);
	
	
	StackPush(char_stack, &b);
	assert(StackGetSize(char_stack) == 2);
	
	StackPush(int_stack, &num2);
	assert(StackGetSize(int_stack) == 2);
	
	
	char_peak = *(char *)StackPeek(char_stack);
	assert('B' == char_peak);
	
	int_peak = *(int *)StackPeek(int_stack);
	assert(num2 == int_peak);
	
	
	StackPop(char_stack);
	assert(StackGetSize(char_stack) == 1);
	
	StackPop(int_stack);
	assert(StackGetSize(int_stack) == 1);
	
	
	char_peak = *(char *)StackPeek(char_stack);
	assert('A' == char_peak);
	
	int_peak = *(int *)StackPeek(int_stack);
	assert(num1 == int_peak);
	
	
	assert(20 == StackGetCapacity(char_stack));
	
	assert(30 == StackGetCapacity(int_stack));
	
	
	assert(0 == StackIsEmpty(char_stack));
	assert(0 == StackIsEmpty(int_stack));
	
	StackPop(char_stack);
	StackPop(int_stack);
	
	assert(1 == StackIsEmpty(char_stack));
	assert(1 == StackIsEmpty(int_stack));
	
	StackDestroy(char_stack);
	StackDestroy(int_stack);
	
	printf("All tests pased!\n");
	
	return 0;
}




