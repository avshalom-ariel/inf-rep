
#include <stdio.h> /*printf*/
#include <stdlib.h> /*malloc, free*/
 #include <assert.h> /*assert*/
 
#include "sllist.h" /*size_t, linked_list_t, iterator_t vode_t*/

static int NodeCounter();

typedef struct node
{
    void *data;
    struct node* next;
}node_t;

struct linked_list
{
    node_t *head; 
    node_t *tail;
};


linked_list_t *SLListCreate(void)
{
	linked_list_t *sllist = NULL;
	node_t *dummy = NULL;
	
	
	sllist = (linked_list_t *)malloc(sizeof(linked_list_t));
	if (NULL == sllist)
	{
		return NULL;
	}
	
	dummy = (node_t *)malloc(sizeof(node_t));
	if (NULL == dummy)
	{
		free(sllist);
		return NULL;	
	}
	
	sllist -> head = dummy;
	sllist -> tail = dummy;
	
	dummy -> data = sllist;
	dummy -> next = NULL;
	
	return sllist;
}

void SLListDestroy(linked_list_t *sllist)
{
	iterator_t iter_runner = SLListGetBegin(sllist);
	iterator_t next_addres = SLListGetBegin(sllist);
	
	assert(NULL != sllist);
	
	while(iter_runner !=  SLListGetEnd(sllist))
	{
		next_addres = SLListNext(iter_runner);
		
		free(iter_runner);
		
		iter_runner = next_addres;
	}
	
	free(SLListGetEnd(sllist));
	free(sllist);
	
}

iterator_t SLListInsert(linked_list_t *sllist, void *data, iterator_t iter )
{
	iterator_t old_node =  (iterator_t)malloc(sizeof(node_t));
	
	assert(NULL != sllist);
	assert(NULL != data);
	assert(NULL != iter);


	if (NULL == old_node)
	{
		return SLListGetEnd(sllist);
	}
	
	old_node -> data = SLListGetData(iter);
	old_node -> next = SLListNext(iter);
	
	iter -> data = data;
	iter -> next = old_node;
	
	if (SLListIsEqual(SLListGetEnd(sllist), iter))
	{
		sllist -> tail = old_node;
	}

	
	return iter;
}

void SLListRemove(iterator_t iter)
{
	void *adress_to_free = iter -> next;  
	
	iter -> data = SLListGetData(SLListNext(iter));
	iter -> next = SLListNext(SLListNext(iter)); /*i have to use iter -> next for the assignment*/
	
	if (NULL == SLListNext(iter)) /*check if iter should become the new dummy*/
	{
		((linked_list_t *)(SLListGetData(iter))) -> tail = iter;
	}
	
	free(adress_to_free);
}

size_t SLListCount(const linked_list_t *sllist)
{
	size_t count = 0;
	
	count = SLListForEach(sllist -> head, sllist -> tail, NodeCounter, NULL);
	
	return count;
}

void SLListSetData(iterator_t iter, void* data)
{
	iter -> data = data;
}

void *SLListGetData(const iterator_t iter)
{
	return iter -> data;
}

iterator_t SLListFind(iterator_t iter_start, iterator_t iter_end, void* data, action_func_t func)
{
	iterator_t runner = iter_start;
	
	while (!SLListIsEqual(runner, SLListNext(iter_end)))
	{
		if (func(data, SLListGetData(runner)))
		{
			return runner;
		}
		
		runner = SLListNext(runner);
	}
	
	/*to return the tail (invalid operator) without the sllist:*/
	while (NULL != SLListNext(runner))
	{
		runner = SLListNext(runner);
	}
	
	/*other option is to get the sslist as argument, which mean to change the API*/
	
	return runner;
}

iterator_t SLListNext(iterator_t iter)
{
	return (iter -> next);
}

int SLListIsEmpty(const linked_list_t* sllist)
{
	assert(NULL != sllist);
	
	return (sllist -> head == sllist -> tail);
}

iterator_t SLListGetBegin(linked_list_t* sllist)
{
	return sllist -> head;
}


iterator_t SLListGetEnd(linked_list_t* sllist)
{
		return sllist -> tail;
}

size_t SLListForEach(iterator_t iter_start, iterator_t iter_end, action_func_t func, void * data)
{
	int result = 0;
	iterator_t runner = iter_start;
	
	while (!SLListIsEqual(runner, iter_end))
	{
		result += func(runner -> data, data);
		runner = runner -> next; 
	}

	return result;
}

int SLListIsEqual(iterator_t iter1, iterator_t iter2)
{
	return (iter1 == iter2);
}

linked_list_t *SLListAppend(linked_list_t *sllist1, linked_list_t *sllist2)
{
	
	SLListGetEnd(sllist1) -> data = SLListGetBegin(sllist2) -> data;
	SLListGetEnd(sllist1) -> next = SLListGetBegin(sllist2) -> next;
	
	sllist1 -> tail = sllist2 -> tail;
	
	(sllist1 -> tail) -> data = sllist1;

	SLListGetBegin(sllist2) -> data = sllist2;
	SLListGetBegin(sllist2) -> next = NULL;	
	
	sllist2 -> tail = SLListGetBegin(sllist2);
	
	return sllist1;

}

static int NodeCounter()
{
	return 1;
}


