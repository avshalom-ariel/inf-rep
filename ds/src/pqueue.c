/*
Name: Avshalom Ariel
Reveiwer: Shahar Marom
Date: 29/05/2024
status: Approved
*/

#include <assert.h> /*assert*/
#include <stdlib.h> /*malloc, free*/

#include "sorted_list.h" /*slist_t*/
#include "pqueue.h" /*pqueue_t*/

struct pqueue
{
	slist_t *list;
};


pqueue_t *PQCreate(pqcompare_func_t cmp_func)
{
	pqueue_t *pqueue = (pqueue_t *)malloc(sizeof(pqueue_t));
	
	if(NULL == pqueue)
	{
		return pqueue;
	}
	
	pqueue -> list = SListCreate(cmp_func);
	
	if(NULL == pqueue -> list)
	{
		free(pqueue);
		return NULL;
	}
	
	return pqueue;
}


void PQDestroy(pqueue_t *pqueue)
{
	assert(NULL != pqueue);
	
	SListDestroy(pqueue -> list);
	free(pqueue);
}


int PQEnqueue(pqueue_t *pqueue, void *data)
{
	assert(NULL != pqueue);
	
	return(SListIsEqualIter(SListEnd(pqueue -> list), SListInsert(pqueue -> list, data)));
}


void *PQDequeue(pqueue_t *pqueue)
{
	assert(NULL != pqueue);
	
	return SListPopFront(pqueue -> list);
}


void *PQPeek(const pqueue_t *pqueue)
{
	assert(NULL != pqueue);
	
	return SListGetData(SListBegin(pqueue -> list));
}


int PQIsEmpty(const pqueue_t *pqueue)
{
	assert(NULL != pqueue);
	
	return SListIsEmpty(pqueue -> list);
}


size_t PQSize(const pqueue_t *pqueue)
{
	assert(NULL != pqueue);
	
	return SListCount(pqueue -> list);
}


void PQClear(pqueue_t *pqueue)
{
	assert(NULL != pqueue);
	
	while(!PQIsEmpty(pqueue))
	{
		PQDequeue(pqueue);
	}
}


void *PQErase(pqueue_t *pqueue, pqmatch_func_t is_match, void *data)
{
	void *result = NULL;	
	
	assert(NULL != pqueue);
	
	result = SListGetData(SListFindIf(SListBegin(pqueue -> list), 
						  SListEnd(pqueue -> list), data, (slist_match_func_t)is_match));
	
	SListRemove(SListFindIf(SListBegin(pqueue -> list), 
				SListEnd(pqueue -> list), data, (slist_match_func_t)is_match));
	
	return result;
}








