
#include <stddef.h> /*NULL*/
#include <stdio.h> /*printf*/
#include <stdlib.h> /*malloc*/
#include <assert.h> /*assert*/


typedef struct node
{
	void *data;
	struct node *next;
} node_t;


int HasLoop(node_t *head);

void TestHasLoop(void);
void TestOpenLoop(void);

int main(void)
{
	TestHasLoop();
	TestOpenLoop();
	
	printf("\nAll tests passed!\n");
	
	return 0;
}


int HasLoop(node_t *head)
{
	node_t *jump_runner = head;
	node_t *double_jump_runner = head;
	
	while(NULL != double_jump_runner && NULL != jump_runner -> next && 
		  NULL != double_jump_runner -> next)
	{
		jump_runner = jump_runner -> next;
		double_jump_runner = (double_jump_runner -> next) -> next;
		
		if (double_jump_runner == jump_runner)
		{
			return 1;
		}
	}
	
	return 0;
}


void OpenLoop(node_t *head)
{
	node_t *jump_runner = head;
	node_t *double_jump_runner = head;
	
	if(NULL == head || NULL == head -> next)
	{
		return;
	}
	
	while(NULL != double_jump_runner && NULL != jump_runner -> next)
	{
		jump_runner = jump_runner -> next;
		double_jump_runner = (double_jump_runner -> next) -> next;
		
		if (double_jump_runner == jump_runner)
		{
			break;
		}
	}
	
	jump_runner = head;
	
	while(jump_runner ->next != double_jump_runner -> next)
	{
		
		jump_runner = jump_runner -> next;
		double_jump_runner = double_jump_runner -> next;
	}
	
	double_jump_runner -> next = NULL;
}


void TestHasLoop(void)
{
	node_t *node1 = (node_t *)malloc(sizeof(struct node)); 
	node_t *node2 = (node_t *)malloc(sizeof(struct node)); 
	node_t *node3 = (node_t *)malloc(sizeof(struct node));
	
	int data1 = 1;
	int data2 = 2;
	int data3 = 3;
	
	node1 -> data = &data1;
	node2 -> data = &data2;
	node3 -> data = &data3;

	node1 -> next = node2;
	node2 -> next = node3;
	node3 -> next = node1;
	
	assert(1 == HasLoop(node1));
	
	free((node1 -> next) -> next);
	free(node1 -> next);
	free(node1);
	
	printf("HasLoop test passed!\n");
}


void TestOpenLoop(void)
{
	node_t *node1 = (node_t *)malloc(sizeof(struct node)); 
	node_t *node2 = (node_t *)malloc(sizeof(struct node)); 
	node_t *node3 = (node_t *)malloc(sizeof(struct node));
	node_t *node4 = (node_t *)malloc(sizeof(struct node));
	node_t *node5 = (node_t *)malloc(sizeof(struct node));
	
	int data1 = 1;
	int data2 = 2;
	int data3 = 3;
	int data4 = 4;
	int data5 = 5;
	
	node1 -> data = &data1;
	node2 -> data = &data2;
	node3 -> data = &data3;
	node4 -> data = &data4;
	node5 -> data = &data5;

	node1 -> next = node2;
	node2 -> next = node3;
	node3 -> next = node4;
	node4 -> next = node5;
	node5 -> next = node2;
	
	assert(1 == HasLoop(node1));
	
	OpenLoop(node1);
	
	assert(0 == HasLoop(node1));
	
	free((((node1 -> next) -> next) -> next) -> next);
	free(((node1 -> next) -> next) -> next);
	free((node1 -> next) -> next);
	free(node1 -> next);
	free(node1);
	
	printf("TestOpenLoop test passed!\n");
}
