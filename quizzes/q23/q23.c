
#include <stdio.h> /*printf*/
#include <stdlib.h> /*,alloc free*/
#include <assert.h> /*assert*/


typedef struct node
{
	void *data;
	struct node *next;
}node_t;

static node_t *IntersectCheck(node_t *head1, node_t *head2);
static void Seperate(node_t *head1, node_t *head2);
static size_t Count(node_t *head);


int main(void)
{
	int arr1[6] = {1, 2, 3, 4, 5, 6}; 
	int arr2[10] = {10, 20, 30, 40};
	
	node_t *f_node1 = (node_t *)malloc(sizeof(node_t));
	node_t *f_node2 = (node_t *)malloc(sizeof(node_t));
	node_t *f_node3 = (node_t *)malloc(sizeof(node_t));
	node_t *f_node4 = (node_t *)malloc(sizeof(node_t));
	node_t *f_node5 = (node_t *)malloc(sizeof(node_t));
	node_t *f_node6 = (node_t *)malloc(sizeof(node_t));
	node_t *s_node1 = (node_t *)malloc(sizeof(node_t));
	node_t *s_node2 = (node_t *)malloc(sizeof(node_t));
	node_t *s_node3 = (node_t *)malloc(sizeof(node_t));
	node_t *s_node4 = (node_t *)malloc(sizeof(node_t));
	
	f_node1->next = f_node2;
	f_node2->next = f_node3;
	f_node3->next = f_node4;
	f_node4->next = f_node5;
	f_node5->next = f_node6;
	f_node6->next = NULL;
	
	s_node1->next = s_node2;
	s_node2->next = s_node3;
	s_node3->next = s_node4;
	s_node4->next = f_node4;
	
	f_node1->data = arr1;
	f_node2->data = arr1 + 1;
	f_node3->data = arr1 + 2;
	f_node4->data = arr1 + 3;
	f_node5->data = arr1 + 4;
	f_node6->data = arr1 + 5;
	
	s_node1->data = arr2;
	s_node2->data = arr2 + 1;
	s_node3->data = arr2 + 2;
	s_node4->data = arr2 + 3;
	
	printf("intersection point, should result 40. the result is: %d\n",
			*(int *)IntersectCheck(f_node1, s_node1)->data);
	
	Seperate(f_node1, s_node1);
	
	printf("check the node before intersection points to NULL, should return 1. result: %d\n",
			NULL == s_node4->next);
	
	return 0;
}


/********  Main functions **********/


node_t *IntersectCheck(node_t *head1, node_t *head2)
{
	node_t *runner1 = head1;
	node_t *runner2 = head2;
	
	size_t count1 = 0;
	size_t count2 = 0;
	
	assert(head1);
	assert(head2);
	
	count1 = Count(head1);
	count2 = Count(head2);
	
	while (count1 < count2)
	{
		runner2 = runner2->next;
		--count2;
	}
	
	while (count1 > count2)
	{
		runner1 = runner1->next;
		--count1;
	}
	
	while (runner1->next != runner2->next)
	{
		runner1 = runner1->next;
		runner2 = runner2->next;		
	}
	
	if (NULL == runner1->next)
	{
		return NULL;
	}
	
	return runner2;
}


void Seperate(node_t *head1, node_t *head2)
{
	node_t *tail = NULL;
	
	assert(head1);
	assert(head2);
	
	tail = IntersectCheck(head1, head2);
	
	if(NULL == tail)
	{
		return;
	}
	
	tail->next = NULL;
}

/****** Help Function ******/

size_t Count(node_t *head)
{
	size_t count = 0;
	
	assert(head);
	
	while(NULL != head)
	{
		++count;
		head = head->next;
	}
	
	return count;
}


