/*
Name: Avshalom Ariel
Reveiwer: Jorge
date: 05/06/2024
status: Approved
*/

#include <stddef.h> /*size_t*/
#include <assert.h> /*assert*/
#include "fsa.h" /*fsa_t, FSAfunction declarations*/

#define WORD_SIZE sizeof(void *)

struct fsa
{
	size_t head;
};

fsa_t *FSAInit(void *memory_pool, size_t block_size, size_t pool_size)
{
	fsa_t *flist = memory_pool;
	size_t *runner = NULL;
	size_t offset = sizeof(fsa_t);
	size_t step = 0;
	
	assert(memory_pool);
	
	step = block_size;
	
	if(step % WORD_SIZE)
	{
		step = step + WORD_SIZE - (step % WORD_SIZE);
	}

	flist -> head = sizeof(fsa_t);
	
	runner = (size_t *)((char *)flist + sizeof(fsa_t));
	
	while(offset < pool_size - step)
	{	
		offset += step;
		*runner = offset;
		
		runner = (size_t *)((char *)runner + step);
	}
	*runner = 0;
	
	return flist;
}

void *FSAAlloc(fsa_t *flist)
{
	size_t *result = NULL;
	
	result = (size_t *)((char *)flist + flist -> head);
	
	flist -> head = *result;

	return result;
}

void FSAFree(fsa_t *flist, void *mem_to_free_ptr)
{	
	size_t *new_head = NULL;
	
	assert(flist);
	assert(mem_to_free_ptr);
	
	new_head = (size_t *)mem_to_free_ptr;
	
	*new_head = flist -> head;
	
	flist -> head = (size_t)new_head - (size_t)flist;
}

size_t FSACountFree(fsa_t *flist)
{
	size_t *runner = NULL;
	size_t count = 0;
	
	assert(flist);
	
	runner = (size_t *)((char *)flist + flist -> head);
	
	while(*runner != 0)
	{
		runner = (size_t *)((char *)flist + *runner);
		++count;
	}

	return count;
}

size_t FSASuggestSize(size_t block_size, size_t block_count)
{
	return block_size * block_count + WORD_SIZE;
}


