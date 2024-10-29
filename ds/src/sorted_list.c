/*
Name: Avshalom Ariel
Reveiwer: Shahar Marom
date: 22/05/2024
status: Approved
*/

#include <assert.h> /*assert*/
#include <stdlib.h> /*malloc, free*/

#include "sorted_list.h"/*sllt_t, function declarations*/
#include "dllist.h" /*slist_t, slist_iterator_t, function declaration*/

struct sorted_list
{
	dll_t *dll;
	slist_compare_func_t cmp_func;
};


slist_t *SListCreate(slist_compare_func_t cmp_func)
{
	slist_t *sllist = (slist_t *)malloc(sizeof(slist_t));
	
	if (NULL == sllist)
	{
		return NULL;
	}
	
	sllist -> dll = DLListCreate();
	if(NULL == sllist -> dll)
	{
		free(sllist);
		return NULL;
	}
	sllist -> cmp_func = cmp_func;
	
	return sllist;
}


void SListDestroy(slist_t *list)
{
	assert(NULL != list);
	
	DLListDestroy(list -> dll);
	free(list);
}


slist_iterator_t SListInsert(slist_t *list,  void *data)
{
	slist_iterator_t runner = SListBegin(list);

	while(!(SListIsEqualIter(runner, SListEnd(list)))) /*use find*/
	{
		if((list -> cmp_func)(SListGetData(runner), data) > 0)
		{
			break;
		}
		
		runner = SListNext(runner);
	}
	
	DLListInsert(list -> dll, runner.iter, data); /*never use runner.iter*/
	
	return runner;
}


slist_iterator_t SListRemove(slist_iterator_t iter)
{
	slist_iterator_t next = SListNext(iter);
	
	DLListRemove(iter.iter);

	return next;
}


size_t SListCount(const slist_t *list)
{
	return DLListCount(list -> dll);
}


void *SListGetData(slist_iterator_t iter)
{
	assert(NULL != iter.iter);
	
	return DLListGetData(iter.iter);
}


void *SListPopFront(slist_t *list)
{
	return DLListPopFront(list -> dll);
}


void *SListPopBack(slist_t *list)
{
	return DLListPopBack(list -> dll);
}


slist_iterator_t SListFind(slist_t *list, slist_iterator_t start_iter, 
                           slist_iterator_t end_iter, void* data)
{
	slist_iterator_t runner = start_iter;
	
	assert(start_iter.sorted_list == end_iter.sorted_list);
	
	while(!(SListIsEqualIter(runner, SListEnd(list))) )
	{
		if(0 <= (list -> cmp_func)(SListGetData(runner), data))
		{
			return runner;
		}
		
		runner = SListNext(runner);
	}
	
	return runner;
}


slist_iterator_t SListFindIf(slist_iterator_t start_iter, slist_iterator_t end_iter, 
							void* data, slist_match_func_t func)
{
	slist_iterator_t result = {0};
	
	assert(start_iter.sorted_list == end_iter.sorted_list);
	
	result.iter = DLListFind(start_iter.iter, end_iter.iter, data, func);
	#ifndef NDEBUG
    result.sorted_list = start_iter.sorted_list;
	#endif /* _DEBUG */
	
	return result;
	
}


slist_iterator_t SListNext(slist_iterator_t iter)
{
	slist_iterator_t next = {0};
	
	next.iter = DLListNext(iter.iter);
	#ifndef NDEBUG
    next.sorted_list = iter.sorted_list;
	#endif /* _DEBUG */
	
	return next;
}


slist_iterator_t SListPrev(slist_iterator_t iter)
{
	slist_iterator_t prev = {0};
	
	prev.iter = DLListPrev(iter.iter);
	#ifndef NDEBUG
    prev.sorted_list = iter.sorted_list;
	#endif /* _DEBUG */
	
	return prev;
}


int SListIsEmpty(const slist_t* list)
{

	return DLListIsEmpty(list -> dll);
}


slist_iterator_t SListBegin(const slist_t* list)
{
	slist_iterator_t begin = {0};
	
	begin.iter = DLListBegin(list -> dll);
	#ifndef NDEBUG
    begin.sorted_list = (slist_t*)list;
	#endif /* _DEBUG */
	
	return begin;
}


slist_iterator_t SListEnd(const slist_t* list)
{
	slist_iterator_t end = {0};
	
	end.iter = DLListEnd(list -> dll);
	#ifndef NDEBUG
    end.sorted_list = (slist_t*)list;
	#endif /* _DEBUG */
	
	return end;
}


slist_iterator_t SDLListForeach(slist_iterator_t start_iterator, slist_iterator_t end_iterator, void* data, slist_action_func_t func)
{
	slist_iterator_t result = {0};
	
	assert(start_iterator.sorted_list == end_iterator.sorted_list);
	
	result.iter = DLListForEach(start_iterator.iter, end_iterator.iter, data, func);
	#ifndef NDEBUG
    result.sorted_list = start_iterator.sorted_list;
	#endif /* _DEBUG */

	return result;
}


int SListIsEqualIter(slist_iterator_t it1, slist_iterator_t it2)
{
	assert(it1.sorted_list == it2.sorted_list);
	
	return DLListIsEqualIter(it1.iter, it2.iter);
}


slist_t* SDLListMerge(slist_t *dest_list, slist_t *src_list)
{
	slist_iterator_t dest = SListBegin(dest_list);
	slist_iterator_t from = SListBegin(src_list);	
	slist_iterator_t to = SListNext(SListBegin(src_list));
	
	while(!SListIsEmpty(src_list))
	{
		from = SListBegin(src_list);
		to = SListNext(SListBegin(src_list));
		dest = SListBegin(dest_list);
		
		while((dest_list -> cmp_func)(SListGetData(dest), SListGetData(from)) < 0)
		{
			dest = SListNext(dest);
		}
		
		while((dest_list -> cmp_func)(SListGetData(dest), SListGetData(to)) > 0
			  && !(SListIsEqualIter(to, SListEnd(src_list))))
		{
			to = SListNext(to);
		}
		
		DLListSplice(from.iter, to.iter, dest.iter);
		
	}
	
	return dest_list;	
}


/************ Help Functions ****************/














