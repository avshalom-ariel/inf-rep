/*
Name: Avshalom Ariel
Reveiwer: Itay
Date: 20/05/2024
status: Approved
*/

#include <stdlib.h> /*malloc, free*/
#include <assert.h> /*assert*/

#include "dllist.h" /*dll_t, defined functions declarations*/


static int NodeCounter(void* dummy, void *count);

typedef struct node
{
    void *data;
    struct node* prev;
    struct node* next;
    
}node_t;


struct dll
{
    node_t *head; 
    node_t *tail;
};


dll_t *DLListCreate(void)
{
	dll_t *dll = NULL;
	node_t *dummy = NULL;
	
	dll = (dll_t *)malloc(sizeof(dll_t));
	if (NULL == dll)
	{
		return NULL;
	}
	
	dummy = (node_t *)malloc(sizeof(node_t));
	if (NULL == dummy)
	{
		free(dll);
		return NULL;	
	}
	
	dll -> head = dummy;
	dll -> tail = dummy;
	
	dummy -> data = dll;
	dummy -> prev = (node_t *)dll;
	dummy -> next = NULL;
	
	return dll;
}



void DLListDestroy(dll_t *dll)
{
	dll_iterator_t iter_runner = DLListBegin(dll);
	dll_iterator_t next_addres = DLListBegin(dll);
	
	assert(NULL != dll);
	
	while(iter_runner !=  DLListEnd(dll))
	{
		next_addres = DLListNext(iter_runner);
		
		free(iter_runner);
		
		iter_runner = next_addres;
	}
	
	free(DLListEnd(dll));
	free(dll);
	
}


dll_iterator_t DLListInsert(dll_t *dll, dll_iterator_t iter, void *data)
{
	dll_iterator_t old_node =  (dll_iterator_t)malloc(sizeof(node_t));
	
	assert(NULL != dll);
	assert(NULL != iter);

	if (NULL == old_node)
	{
		return DLListEnd(dll);
	}
	
	old_node -> data = DLListGetData(iter);
	old_node -> prev = iter;
	old_node -> next = DLListNext(iter);
	
	iter -> data = data;
	iter -> next = old_node;
	
	if (DLListIsEqualIter(DLListEnd(dll), iter))
	{
		dll -> tail = old_node;
	}
	else
	{
		(old_node -> next) -> prev = old_node;
	}
	
	return iter;
}


dll_iterator_t DLListRemove(dll_iterator_t iter)
{
	void *adress_to_free = iter -> next; 
	
	assert(NULL != iter);
	
	iter -> data = DLListGetData(DLListNext(iter));
	iter -> next = DLListNext(DLListNext(iter));
	
	
	if (NULL == DLListNext(iter))
	{
		((dll_t *)(DLListGetData(iter))) -> tail = iter;
	}
	else
	{
		iter -> prev = DLListPrev(DLListNext(iter));
	}
	
	free(adress_to_free);
	
	return iter;
}


size_t DLListCount(const dll_t *dll)
{
	size_t count = 0;
	
	assert(NULL != dll);
	
	DLListForEach(DLListBegin(dll), DLListEnd(dll), &count, NodeCounter);
	
	return count;
}


void DLListSetData(dll_iterator_t iter, void* data)
{
	assert(NULL != iter);
		
	iter -> data = data;
}


void *DLListGetData(const dll_iterator_t iter)
{
	assert(NULL != iter);
	
	return iter -> data;
}


dll_iterator_t DLListFind(dll_iterator_t iter_start, dll_iterator_t iter_end,
 						  void* data, dll_match_func_t func)
{
	dll_iterator_t result = iter_end;
	
	assert(NULL != iter_start);
	assert(NULL != iter_end);
	
	result = DLListForEach(iter_start, iter_end, data, (dll_action_func_t)func);
	
	return result;
}


dll_iterator_t DLListNext(dll_iterator_t iter)
{
	assert(NULL != iter);
	
	return (iter -> next);
}

dll_iterator_t DLListPrev(dll_iterator_t iter)
{
	assert(NULL != iter);
	
	return (iter -> prev);
}


int DLListIsEmpty(const dll_t* dll)
{
	assert(NULL != dll);
	
	return (DLListBegin(dll) == DLListEnd(dll));
}


dll_iterator_t DLListBegin(const dll_t* dll)
{
	assert(NULL != dll);
	
	return dll -> head;
}


dll_iterator_t DLListEnd(const dll_t* dll)
{
		assert(NULL != dll);
		
		return dll -> tail;
}


dll_iterator_t DLListForEach(dll_iterator_t iter_start, dll_iterator_t iter_end, void* data,
							 dll_action_func_t func)
{
	int result = 0;
	dll_iterator_t runner = iter_start;
	
	assert(NULL != iter_start);
	assert(NULL != iter_end);
	
	while (!DLListIsEqualIter(runner, iter_end))
	{
		result = func(runner -> data, data);
		if (0 != result)
		{
			return runner;
		}
		
		runner = runner -> next; 
	}

	return runner;
}


int DLListIsEqualIter(dll_iterator_t it1, dll_iterator_t it2)
{
	return (it1 == it2);
}


void *DLListPopFront(dll_t *dll)
{
	void *data = DLListGetData(DLListBegin(dll));
	
	assert(NULL != dll);
	
	DLListRemove(DLListBegin(dll));
	
	return data;
}


void *DLListPopBack(dll_t *dll)
{
	void *data = DLListGetData(DLListEnd(dll) -> prev);
	
	assert(NULL != dll);
	
	DLListRemove(DLListEnd(dll) -> prev);
	
	return data;
}


dll_iterator_t DLListPushFront(dll_t *dll, void *data)
{
	assert(NULL != dll);
	
	return (DLListInsert(dll, DLListBegin(dll), data));
}


dll_iterator_t DLListPushBack(dll_t *dll, void *data)
{
	assert(NULL != dll);
	
	return (DLListInsert(dll, DLListEnd(dll), data));
}


dll_iterator_t DLListSplice(dll_iterator_t from_iterator,
							dll_iterator_t to_iterator,
							dll_iterator_t dest_iterator)
{
	dll_iterator_t last_in_splice = DLListPrev(to_iterator);
	
	assert(NULL != from_iterator);
	assert(NULL != to_iterator);
	assert(NULL != dest_iterator);
	
	if (from_iterator == ((dll_t *)(from_iterator -> prev)) -> head)
	{
		((dll_t *)(from_iterator -> prev)) -> head = to_iterator;
	}
	else
	{
		(from_iterator -> prev) -> next = to_iterator;
	}
	
	to_iterator -> prev = from_iterator -> prev;
	
	if (dest_iterator == ((dll_t *)(dest_iterator -> prev)) -> head)
	{
		((dll_t *)(dest_iterator -> prev)) -> head = from_iterator;
	}
	else
	{
		DLListPrev(dest_iterator) -> next = from_iterator;		
	}
	
	from_iterator -> prev = DLListPrev(dest_iterator);
	
	dest_iterator -> prev = last_in_splice;
	
	last_in_splice -> next = dest_iterator;
	
	return from_iterator;
	
}


int DLListMultiFind(dll_t *dest_list ,dll_iterator_t iter_start, dll_iterator_t iter_end, 
					void* data, dll_match_func_t func)
{
	dll_iterator_t runner = iter_start;
	dll_iterator_t insert_res = NULL;
	int count = 0;
	
	assert(NULL != dest_list);
	assert(NULL != iter_start);
	assert(NULL != iter_end);
	
	while (!DLListIsEqualIter(runner, iter_end))
	{
		runner = DLListFind(runner, iter_end, data, func);
		
		if (!DLListIsEqualIter(runner, iter_end))
		{
			insert_res = DLListInsert(dest_list, DLListEnd(dest_list), DLListGetData(runner));
			
			if (DLListIsEqualIter(DLListEnd(dest_list), insert_res)) 
			{
				return -1;
			}
			
			runner = DLListNext(runner);
			++count;
		}
	}
	
	return count;	
}


static int NodeCounter(void* dummy, void *count)
{

	(void)dummy;
	
	*(size_t *)count += 1;
	
	return 0;
}


