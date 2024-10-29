
#include <stdio.h> /*printf*/

#include "queue.h" /*typedefs function declarations*/

#define LEFT(node) node->left
#define RIGHT(node) node->right
#define DATA(node) node->data

typedef struct node
{
	struct node *right;
	struct node *left;
	void *data;
}node_t;

static void LevelBLevelPrint(node_t *root, queue_t *queue);

int main(void)
{
	int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	size_t i = 0;
	queue_t *queue = QueueCreate();
	
	node_t node1 = {0};
	node_t node2 = {0};
	node_t node3 = {0};
	node_t node4 = {0};
	node_t node5 = {0};
	node_t node6 = {0};
	node_t node7 = {0};
	node_t node8 = {0};
	node_t node9 = {0};
	
	node1.left = &node2;
	node1.right = &node3;
	
	node2.left = &node4;
	node2.right = &node5;
	
	node3.left = &node6;
	node3.right = &node7;
	
	node4.left = &node8;
	node4.right = &node9;
	
	node5.left = NULL;
	node5.right = NULL;
	
	node6.left = NULL;
	node6.right = NULL;
	
	node7.left = NULL;
	node7.right = NULL;
	
	node8.left = NULL;
	node8.right = NULL;
	
	node9.left = NULL;
	node9.right = NULL;
	
	node1.data = data + 8;
	node2.data = data + 7;
	node3.data = data + 6;
	node4.data = data + 5;
	node5.data = data + 4;
	node6.data = data + 3;
	node7.data = data + 2;
	node8.data = data + 1;
	node9.data = data + 0;
	
	LevelBLevelPrint(&node1, queue);
	
	return 0;
}


void LevelBLevelPrint(node_t *root, queue_t *queue)
{
	node_t *curr = root;
	QueueEnqueue(queue, DATA(curr));
	
	while(!QueueIsEmpty(queue))
	{
		if(LEFT(curr))
		{
			QueueEnqueue(queue, (LEFT(curr)));
		}
		
		if(RIGHT(curr))
		{
			QueueEnqueue(queue, (RIGHT(curr)));
		}
		
		printf("%d\n", *(int *)DATA(curr));
		
		QueueDequeue(queue);
		curr = (node_t *)QueuePeek(queue);
	}
}


