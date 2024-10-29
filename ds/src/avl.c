/*
Author: Avshalom Ariel
Review by: Amit
Review date: 25/06/2024
Status: Approved
*/

#include <stdlib.h>/*malloc, free*/
#include <assert.h> /*assert*/

#include "avl.h" /*avl_t, AVLFunction declarations*/

#define NODE_CHILD(node, direction) node->childs[direction]
#define LEFT_CHILD(node) node->childs[0]
#define RIGHT_CHILD(node) node->childs[1]
#define LEFT 0
#define RIGHT 1
#define NODE_DATA(node) node->data
#define NODE_GET_DATA(node) (!node) ? NULL : node->data
#define NUM_OF_CHILDREN 2
#define MAX(a, b) (a >= b) ? a : b
#define GET_NODE_HEIGHT(node) (!node) ? 0 : node->height
#define NODE_HEIGHT(node) node->height
#define DIRECTION(a) (a < 0)


typedef struct avl_node
{
	struct avl_node *childs[NUM_OF_CHILDREN];
	void *data;
	long height;
}avl_node_t;


struct avl
{
	avl_cmp_func_t cmp_func;
	avl_node_t *root;
};


static avl_node_t *AVLRemoveRecursion(avl_node_t *node, const void *data, avl_cmp_func_t cmp_func);
static avl_node_t *InsertRecursion(avl_node_t *root, avl_node_t *child, avl_cmp_func_t cmp_func);
static void PostOrderFree(avl_node_t *node);
static size_t PreOrderCount(avl_node_t *node);
static int InOrderForEach(avl_node_t *node, avl_action_func_t action, void* params, int status);
static avl_node_t *AVLFindRecursion(avl_node_t *node, const void *data, avl_cmp_func_t compare);
static avl_node_t *CreateNode(void *data);
static int HasKids(avl_node_t *node);
static void CopyNode(avl_node_t *dest, avl_node_t *src);
static long KidsHeightDiff(avl_node_t *node);
static int BalanceDirection(avl_node_t *node);
static avl_node_t *Rotate(avl_node_t *node, int direction);
static void HeightUpdate(avl_node_t *node);
static int BalanceCheck(avl_node_t *node);
static avl_node_t *FixBalance(avl_node_t *node);
static avl_node_t *SmallestElement(avl_node_t *node);
static avl_node_t *GetOneKid(avl_node_t *node);
static long Abs(long num);


/********************************************/
/*			   API Functions				*/
/********************************************/


avl_t *AVLCreate(avl_cmp_func_t cmp_func)
{
	avl_t *avl = NULL;
	
	assert(cmp_func);
	
	avl = (avl_t *)malloc(sizeof(avl_t));
	if (NULL == avl)
	{
		return avl;
	}

	avl->cmp_func = cmp_func;
	avl->root = NULL;

	return avl;
}


void AVLDestroy(avl_t *avl)
{
	assert(avl);
	
	PostOrderFree(avl->root);
	
	free(avl);
}


int AVLInsert(avl_t *avl, void *data)
{
	avl_node_t *child = NULL;
	
	assert(avl);
	
	child = CreateNode(data);
	if(!child)
	{
		return -1;
	}

	avl->root = InsertRecursion(avl->root, child, avl->cmp_func);
	
	return 0;
}


void AVLRemove(avl_t *avl, void *data)
{
	assert(avl);
	
	avl->root = AVLRemoveRecursion(avl->root, data, avl->cmp_func);
}


int AVLIsEmpty(const avl_t *avl)
{
	assert(avl);
	
	return !(avl->root);
}


size_t AVLCount(const avl_t *avl)
{
	assert(avl);
	
	return PreOrderCount(avl->root);
}

int AVLForEach(avl_t *avl, avl_action_func_t action, void* params)
{
	assert(avl);
	assert(action);
	
	return InOrderForEach(avl->root, action, params, 0);
}


void *AVLFind(const avl_t *avl, const void *data)
{
	assert(avl);
	
	return NODE_GET_DATA(AVLFindRecursion(avl->root, data, avl->cmp_func));
}


size_t AVLHeight(const avl_t *avl)
{
	assert(avl);
	
	return GET_NODE_HEIGHT(avl->root);
}


/********************************************/
/*			   Help Functions				*/
/********************************************/


avl_node_t *CreateNode(void *data)
{
	avl_node_t *node = NULL;
	
	node = (avl_node_t *)malloc(sizeof(avl_node_t));
	if (NULL == node)
	{
		return NULL;
	}
	
	NODE_DATA(node) = data;
	LEFT_CHILD(node) = NULL;
	RIGHT_CHILD(node) = NULL;
	NODE_HEIGHT(node) = 1;
	
	return node;
}

int HasKids(avl_node_t *node)
{
	return LEFT_CHILD(node) || RIGHT_CHILD(node);
}

int HasTwoKids(avl_node_t *node)
{
	return LEFT_CHILD(node) && RIGHT_CHILD(node);
}

int HasLeft(avl_node_t *node)
{
	return NULL != LEFT_CHILD(node);
}

int HasRight(avl_node_t *node)
{
	return NULL != RIGHT_CHILD(node);
}

void PostOrderFree(avl_node_t *node)
{
	if(!node)
	{
		return;
	}
	
	PostOrderFree(LEFT_CHILD(node));
	
	PostOrderFree(RIGHT_CHILD(node));
	
	free(node);
}

size_t PreOrderCount(avl_node_t *node)
{
	if(!node)
	{
		return 0;
	}
	
	return PreOrderCount(LEFT_CHILD(node)) + PreOrderCount(RIGHT_CHILD(node)) + 1;
}


int InOrderForEach(avl_node_t *node, avl_action_func_t action, void* params, int status)
{
	if(!node)
	{
		return status;
	}
	
	status = InOrderForEach(LEFT_CHILD(node), action, params, status);
	
	status = action(NODE_DATA(node) ,params);
	
	status = InOrderForEach(RIGHT_CHILD(node), action, params, status);
	
	return status;
}


avl_node_t *AVLFindRecursion(avl_node_t *node, const void *data, avl_cmp_func_t cmp_func)
{
	
	if(!node || 0 == cmp_func(NODE_DATA(node), data))
	{
		return node;
	}
	
	if(0 > cmp_func(NODE_DATA(node), data))
	{
		return AVLFindRecursion(RIGHT_CHILD(node), data, cmp_func);
	}
	else
	{
		return AVLFindRecursion(LEFT_CHILD(node), data, cmp_func);
	}
}


avl_node_t *AVLRemoveRecursion(avl_node_t *node, const void *data, avl_cmp_func_t cmp_func)
{
	avl_node_t *new_node = NULL;
	int cmp_res = cmp_func(NODE_GET_DATA(node), data);
	
	if (0 != cmp_res)
	{
		NODE_CHILD(node, DIRECTION(cmp_res)) = AVLRemoveRecursion(NODE_CHILD(node,
											   DIRECTION(cmp_res)), data, cmp_func);
	}
	else
	{
		if (HasTwoKids(node))
		{
			new_node = SmallestElement(NODE_CHILD(node, RIGHT));
			
			NODE_DATA(node) = NODE_DATA(new_node);
			
			NODE_CHILD(node, RIGHT) = AVLRemoveRecursion(NODE_CHILD(node, RIGHT), 
														 NODE_GET_DATA(node), cmp_func);
			
		}
		else if (!HasKids(node))
		{
			free(node);
			return NULL;
		}
		else
		{
			new_node = GetOneKid(node);
			
			CopyNode(node, new_node);
			
			free(new_node);
		}
	}
	
	return FixBalance(node);
}

avl_node_t *SmallestElement(avl_node_t *node)
{
	if (!NODE_CHILD(node, LEFT))
	{
		return node;
	}
	
	return SmallestElement(NODE_CHILD(node, LEFT));
}

void CopyNode(avl_node_t *dest, avl_node_t *src)
{
	NODE_CHILD(dest, LEFT) = NODE_CHILD(src, LEFT);
	NODE_CHILD(dest, RIGHT) = NODE_CHILD(src, RIGHT);
	NODE_DATA(dest) = NODE_DATA(src);
	NODE_HEIGHT(dest) = NODE_HEIGHT(src);
}

avl_node_t *Rotate(avl_node_t *node, int direction)
{
	avl_node_t *pivot = NODE_CHILD(node, direction);
	avl_node_t *pivot_child = NODE_CHILD(pivot, !direction);
	
	NODE_CHILD(pivot, !direction) = node;
	NODE_CHILD(node, direction) = pivot_child;

	HeightUpdate(node);
	HeightUpdate(pivot);
	
	return pivot;
}

avl_node_t *GetOneKid(avl_node_t *node)
{
	if (NODE_CHILD(node, LEFT))
	{
		return NODE_CHILD(node, LEFT);
	}
	
	return NODE_CHILD(node, RIGHT);
}

avl_node_t *InsertRecursion(avl_node_t *parent, avl_node_t *child, avl_cmp_func_t cmp_func)
{	
	int direction = 0;
	
	if (!parent)
	{
		return child;
	}

	direction = DIRECTION(cmp_func(NODE_GET_DATA(parent), NODE_GET_DATA(child)));
	
	NODE_CHILD(parent, direction) = InsertRecursion(NODE_CHILD(parent, direction), child, cmp_func);

	return FixBalance(parent);
}

void HeightUpdate(avl_node_t *node)
{
	size_t res = 1;
	size_t r_child = GET_NODE_HEIGHT(node->childs[RIGHT]);
	size_t l_child = GET_NODE_HEIGHT(node->childs[LEFT]);
	
	res += MAX(r_child, l_child);
	
	node->height = res;
}

int BalanceCheck(avl_node_t *node)
{	
	long left_height = GET_NODE_HEIGHT(LEFT_CHILD(node));
	long right_height = GET_NODE_HEIGHT(RIGHT_CHILD(node));
	
	if (Abs(left_height - right_height) <= 1)
	{
		return -1;
	}
	
	if (left_height - right_height > 0)
	{
		return LEFT;
	}
	else
	{	
		return RIGHT;
	}
}

long KidsHeightDiff(avl_node_t *node)
{
	int left_height = GET_NODE_HEIGHT(LEFT_CHILD(node));
	int right_height = GET_NODE_HEIGHT(RIGHT_CHILD(node));
	
	return left_height - right_height;
}

int BalanceDirection(avl_node_t *node)
{
	long diff = KidsHeightDiff(node);
	
	if (diff > 0)
	{
		return LEFT;
	}
	else
	{
		return RIGHT;
	}
}

avl_node_t *FixBalance(avl_node_t *node)
{
	int balance = 0;
	
	HeightUpdate(node);
	
	balance	= BalanceCheck(node);
	
	if (-1 != balance)
	{
		
		if (0 == KidsHeightDiff(NODE_CHILD(node, balance)) || 
		    BalanceDirection(NODE_CHILD(node, balance)) == balance)
		{
			return Rotate(node, balance);
		}
		else
		{
			NODE_CHILD(node, balance) = Rotate(NODE_CHILD(node, balance), !balance);
			return Rotate(node, balance);
		}
	}
	
	return node;
}

long Abs(long num)
{
	return (0 < num) ? num : -num;
}


