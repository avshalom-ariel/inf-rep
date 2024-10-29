/*
Author: Avshalom Ariel
Review by: 
Review date:
Status:
*/

#include <stdlib.h> /*malloc free*/
#include <assert.h> /*assert*/

#include <bst.h> /*bst_t, bst_iter_t, function declarations*/

#define LEFT_CHILD(node) node->childs[0]
#define RIGHT_CHILD(node) node->childs[1]
#define NEXT 1
#define PREV 0
#define NUM_OF_CHILDRENS 2

static bst_iter_t CreateNode(void *data, bst_iter_t parent);
static int Count(void *data1, void *data2);
static int IsLeftChild(bst_iter_t parent, bst_iter_t iter);
static bst_iter_t Iterative(bst_iter_t iter, int child);

struct bst_node
{
	struct bst_node *childs[2];
	struct bst_node *parent;
	void *data;
};

struct bst
{
	bst_node_t *dummy;
	bst_cmp_func_t cmp_func;
};


/******** API Functions ********/


bst_t *BSTCreate(bst_cmp_func_t cmp_func)
{
	bst_t *bst = NULL;
	bst_iter_t dummy = NULL;
	
	assert(cmp_func);
	
	bst = (bst_t *)malloc(sizeof(bst_t));
	if (NULL == bst)
	{
		return bst;
	}
	
	dummy = CreateNode(bst, NULL);
	if (NULL == dummy)
	{
		free(bst);
		return NULL;
	}
	
	bst->dummy = dummy;
	bst->cmp_func = cmp_func;
	
	return bst;
}


void BSTDestroy(bst_t *tree)
{
	assert(tree);
	
	while (!BSTIsEmpty(tree))
	{
		BSTRemove(BSTBegin(tree));
	}
	
	free(tree->dummy);
	free(tree);
}


bst_iter_t BSTInsert(bst_t *tree, void *data)
{
	bst_iter_t runner = NULL;
	bst_iter_t new_node = NULL;
	size_t child = 0;
	
	assert(tree);
	
	runner = tree->dummy;
	
	while(runner)
	{
		if ((BSTIsSameIter(BSTEnd(tree), runner)) || 
			(0 < tree->cmp_func(BSTGetData(runner), data)))
		{
			child = 0;
		}
		else
		{
			child = 1;
		}
		
		if (runner->childs[child])
		{
			runner = runner->childs[child];
		}
		else
		{
			new_node = CreateNode(data, runner);
			
			if (NULL == new_node)
			{
				return BSTEnd(tree);
			}
			
			runner->childs[child] = new_node;
			
			return new_node;
		}
	}
	
	return BSTEnd(tree);
}


void *BSTRemove(bst_iter_t iter)
{
	bst_iter_t next_iter = NULL;
	void *data = BSTGetData(iter);
	
	if (!iter->childs[0] && !iter->childs[1])
	{
		if (IsLeftChild(iter->parent, iter))
		{
			iter->parent->childs[0] = NULL;
		}
		else
		{
			iter->parent->childs[1] = NULL;
		}
		
		free(iter);
	}
	else if (!iter->childs[1])
	{
		if (IsLeftChild(iter->parent, iter))
		{
			iter->parent->childs[0] = iter->childs[0];
			iter->childs[0]->parent = iter->parent;
		}
		else
		{
			iter->parent->childs[1] = iter->childs[0];
			iter->childs[0]->parent = iter->parent;
		}
		
		free(iter);
	}
	else if (!iter->childs[0])
	{
		if (IsLeftChild(iter->parent, iter))
		{
			iter->parent->childs[0] = iter->childs[1];
			iter->childs[1]->parent = iter->parent;
		}
		else
		{
			iter->parent->childs[1] = iter->childs[1];
			iter->childs[1]->parent = iter->parent;
		}
		
		free(iter);
	}
	else
	{
		next_iter = BSTNext(iter);
		
		iter->data = next_iter->data;
		
		if (BSTIsSameIter(next_iter->parent, iter))
		{
			iter->childs[1] = next_iter->childs[1];
			if (next_iter->childs[1])
			{
				next_iter->childs[1]->parent = iter;
			}
		}
		else
		{
			next_iter->parent->childs[0] = next_iter->childs[1];
			if (next_iter->childs[1])
			{
				next_iter->childs[1]->parent = next_iter->parent;
			}
		}
		
		free(next_iter);
	}
	
	return data;
}


size_t BSTSize(const bst_t *tree)
{
	size_t count = 0;
	
	assert(tree);
	
	BSTForEach((bst_t *)tree, Count, &count);
	
	return count;
}


int BSTIsEmpty(const bst_t *tree)
{
	assert(tree);
	assert(tree->dummy);
	
	return (NULL == LEFT_CHILD(tree->dummy));

}


bst_iter_t BSTBegin(const bst_t *tree)
{
	bst_iter_t iter = NULL;
	
	assert(tree);
	
	iter = tree->dummy;
	
	while(NULL != LEFT_CHILD(iter))
	{
		iter = LEFT_CHILD(iter);
	}
	
	return iter;	
}


bst_iter_t BSTEnd(const bst_t *tree)
{
	assert(tree);
	
	return tree->dummy;
}


void *BSTGetData(bst_iter_t iter)
{
	assert(iter);
	
	return iter->data;
}


int BSTIsSameIter(bst_iter_t iter1, bst_iter_t iter2)
{
	return (iter1 == iter2);
}


bst_iter_t BSTPrev(bst_iter_t iter)
{
	assert(iter);
	
	return Iterative(iter, 0);
}


bst_iter_t BSTNext(bst_iter_t iter)
{
	assert(iter);
	
	return Iterative(iter, 1);
}


int BSTForEach(bst_t *tree, bst_action_func_t action_func, void* param)
{
	bst_iter_t runner = NULL;
	int status = 0;
	
	assert(tree);
	
	runner = BSTBegin(tree);
	
	while (!BSTIsSameIter(BSTEnd(tree), runner))
	{
		status += action_func(BSTGetData(runner), param);
		runner = BSTNext(runner);
	}
	
	return status;
}


bst_iter_t BSTFind(const bst_t *tree, const void *data)
{
	bst_iter_t runner = NULL;
	
	assert(tree);
	
	runner = LEFT_CHILD(tree->dummy);
	
	while(runner)
	{
		if (0 < tree->cmp_func(BSTGetData(runner), data))
		{
			runner = LEFT_CHILD(runner);
		}
		else if (0 > tree->cmp_func(BSTGetData(runner), data))
		{
			runner = RIGHT_CHILD(runner);
		}
		else
		{
			return runner;
		}
	}
	
	return BSTEnd(tree);
}


/******** Help Functions ********/


bst_iter_t CreateNode(void *data, bst_iter_t parent)
{
	bst_iter_t node = NULL;
	
	node = (bst_iter_t)malloc(sizeof(bst_node_t));
	if (NULL == node)
	{
		return NULL;
	}
	
	node->data = data;
	node->parent = parent;
	node->childs[0] = NULL;
	node->childs[1] = NULL;
	
	return node;

}


int Count(void *data1, void *data2)
{
	assert(data1);
	assert(data2);
	
	(void)data1;
	
	++(*(size_t *)data2);
	
	return 0;
}


int IsLeftChild(bst_iter_t parent, bst_iter_t iter)
{
	return BSTIsSameIter(LEFT_CHILD(parent), iter);
}


bst_iter_t Iterative(bst_iter_t iter, int child)
{
	bst_iter_t parent = NULL;
	
	if (iter->childs[child])
	{
		iter = iter->childs[child];
		
		while (iter->childs[!child])
		{
			iter = iter->childs[!child];
		}
	}
	else
	{
		parent = iter->parent;
		
		while (!BSTIsSameIter(parent->childs[!child], iter))
		{
			iter = parent;
			parent = iter->parent;
		}
		
		iter = parent;
	}
	
	return iter;
}



