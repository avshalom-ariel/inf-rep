
#include <stddef.h> /*size_t*/
#include <stdio.h> /*printf*/
#include <stdlib.h> /*malloc free*/
#include <string.h> /*string functions*/

#include "recursion.h" /*Recursion function declarations*/
#include "test_utility.h" /*test functions*/
#include "stack.h" /*Stack functions*/

static void FibonacciTest(void);
static void FlipListTest(void);
static void StrlenTest(void);
static void StrcmpTest(void);
static void StrcpyTest(void);
static void StrcatTest(void);
static void StrstrTest(void);
static void StackSortTest(void);

static void StackOverflowTest(void);


int main(void)
{
	FibonacciTest();
	FlipListTest();
	StrlenTest();
	StrcmpTest();
	StrcpyTest();
	StrcatTest();
	StrstrTest();
	StackSortTest();
	
	StackOverflowTest();
	
	Test();
	
	return 0;
}

/**************** Test Functions ******************/


void FibonacciTest(void)
{
	int fib_arr[15] = {1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610};
	size_t i = 0;
	
	for (; i < 15; ++i)
	{
		TestInt("FibonacciTest", __FILE__, __LINE__, fib_arr[i], Fibonacci(i));
	}
	
}


void FlipListTest(void)
{
	int vals[5] = {89, 144, 233, 377, 610};
	node_t *node1 = (node_t *)malloc(sizeof(void *) * 2);
	node_t *node2 = (node_t *)malloc(sizeof(void *) * 2);
	node_t *node3 = (node_t *)malloc(sizeof(void *) * 2);
	node_t *node4 = (node_t *)malloc(sizeof(void *) * 2);
	node_t *node5 = (node_t *)malloc(sizeof(void *) * 2);
	node_t *runner = NULL;
	
	SetNode(node1, node2, vals);
	SetNode(node2, node3, vals + 1);
	SetNode(node3, node4, vals + 2);
	SetNode(node4, node5, vals + 3);
	SetNode(node5, NULL, vals + 4);
	
	runner = node1;
	
	TestInt("FlipListTest", __FILE__, __LINE__, *(vals), *(int *)GetData(runner));
	
	runner = Next(runner);
	
	TestInt("FlipListTest", __FILE__, __LINE__, *(vals + 1), *(int *)GetData(runner));
	
	runner = Next(runner);
	
	TestInt("FlipListTest", __FILE__, __LINE__, *(vals + 2), *(int *)GetData(runner));
	
	runner = Next(runner);
	
	TestInt("FlipListTest", __FILE__, __LINE__, *(vals + 3), *(int *)GetData(runner));

	runner = Next(runner);

	TestInt("FlipListTest", __FILE__, __LINE__, *(vals + 4), *(int *)GetData(runner));
	
	FlipList(node1);
	
	TestInt("FlipListTest", __FILE__, __LINE__, *(vals + 4), *(int *)GetData(runner));
	
	runner = Next(runner);
	
	TestInt("FlipListTest", __FILE__, __LINE__, *(vals + 3), *(int *)GetData(runner));

	runner = Next(runner);

	TestInt("FlipListTest", __FILE__, __LINE__, *(vals + 2), *(int *)GetData(runner));

	runner = Next(runner);

	TestInt("FlipListTest", __FILE__, __LINE__, *(vals + 1), *(int *)GetData(runner));

	runner = Next(runner);

	TestInt("FlipListTest", __FILE__, __LINE__, *(vals), *(int *)GetData(runner));
	
	free(node1);
	free(node2);
	free(node3);
	free(node4);
	free(node5);
	
}


void StackSortTest(void)
{
	int arr[15] = {1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610};
	stack_t *stack = StackCreate(20, 4);
	size_t i = 0;
	
	StackPush(stack, arr + 5);
	StackPush(stack, arr + 8);
	StackPush(stack, arr + 4);
	StackPush(stack, arr + 3);
	StackPush(stack, arr + 0);
	StackPush(stack, arr + 9);
	StackPush(stack, arr + 12);
	StackPush(stack, arr + 11);
	StackPush(stack, arr + 14);
	StackPush(stack, arr + 2);
	StackPush(stack, arr + 6);
	StackPush(stack, arr + 7);
	StackPush(stack, arr + 10);
	StackPush(stack, arr + 13);
	StackPush(stack, arr + 1);
	
	StackSort(stack);
	
	for (; i < 15; ++i)
	{
		TestInt("StackSortTest", __FILE__, __LINE__, Fibonacci(14 - i), *(int *)StackPeek(stack));
		StackPop(stack);
	}
}


void StrlenTest(void)
{
	char *str = "Avshalom PROgrammer";
	
	TestSizeT("StrlenTest", __FILE__, __LINE__, strlen(str), Strlen(str));
}


void StrcmpTest(void)
{
	char *str1 = "Avshalom PROgrammer";
	char *str2 = "Avshalom PROgrammeR";
	
	TestInt("StrcmpTest", __FILE__, __LINE__, 0, Strcmp(str1, str1));
	TestInt("StrcmpTest", __FILE__, __LINE__, 1, 0 != Strcmp(str1, str2));
}


void StrcpyTest(void)
{
	char *str1 = (char *)malloc(sizeof(char) * 20);
	char *str2 = "Avshalom PROgrammer";
	
	Strcpy(str1, str2);
	
	TestInt("StrcpyTest", __FILE__, __LINE__, 0, strcmp(str1, str2));
}


void StrcatTest(void)
{
	char *str1 = (char *)malloc(sizeof(char) * 50);
	char *str2 = "Avshalom PROgrammer";
	
	*(str1) = 'h';
	*(str1 + 1) = 'e';
	*(str1 + 2) = 'y';
	*(str1 + 3) = '\0';
	
	Strcat(str1, str2);
	
	TestInt("StrcatTest", __FILE__, __LINE__, 0, Strcmp("heyAvshalom PROgrammer", str1));
}


void StrstrTest(void)
{
	char *haystack = "kbJkjHBjByJBkJBHKjAvshalom PROgrammerKJBHLKNUYCFT";
	char *needle = "Avshalom PROgrammer";
	
	TestInt("StrcatTest", __FILE__, __LINE__, 0, strncmp(needle, Strstr(haystack, needle), strlen(needle)));
}


void StackOverflowTest(void)
{
	StackOverflow();
}







