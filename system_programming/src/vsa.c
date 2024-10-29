/*
Name: Avshalom Ariel
Reveiwer: Shahar Marom
date: 06/06/2024
status: approved
*/

#include <stddef.h> /*size_t*/
#include <assert.h> /*assert*/

#include "vsa.h" /*fsa_t, FSAfunction declarations*/

#define WORD_SIZE sizeof(void *)
#define MAGIC_NUMBER 101

struct vsa
{
	long pool_size;
};

typedef struct block
{
	long block_size;
	#ifndef NDEBUG
	size_t magic_num;
	#endif
}block_t;

static long AlignPointer(void *ptr);
static long AlignNum(long num);
static long Abs(long num);
static void DeFrag(block_t *block);
static block_t *NextBlock(block_t *block);
static void CreateBlock(block_t *block_add, long size);


/********* API Functions ****************/


vsa_t *VSAInitialize(void *memory_pool, long pool_size)
{
	vsa_t *vsa = NULL;
	size_t align_offset = 0;
	
	assert(memory_pool);
	assert((long)(sizeof(vsa_t) + sizeof(block_t) + WORD_SIZE) < pool_size);
	
	align_offset = AlignPointer(memory_pool);
	pool_size -= align_offset;
	pool_size -= pool_size % WORD_SIZE;
	
	vsa = (vsa_t *)((char *)memory_pool + align_offset);
	
	vsa->pool_size = pool_size;
	
	CreateBlock((block_t *)((char *)vsa + sizeof(vsa_t)), pool_size - 
				sizeof(vsa_t) - 2 * sizeof(block_t));
	CreateBlock((block_t *)((char *)vsa + pool_size - sizeof(block_t)), 0);
	
	return vsa;
}


void *VSAAlloc(vsa_t *vsa, long block_size)
{
	block_t *runner = NULL;
	block_t *result = NULL;
	block_t *next = NULL;
	long old_size = 0;
	
	assert(vsa);
	
	runner = (block_t *)((char *)vsa + sizeof(vsa_t));
	block_size = AlignNum(block_size);

	while(block_size > runner->block_size)
	{
		runner = NextBlock(runner);
		DeFrag(runner);
	}
	
	if (0 == runner->block_size)
	{
		return NULL;
	}
	
	old_size = runner->block_size;
	
	CreateBlock(runner, -block_size);
	
	next = NextBlock(runner);
	
	CreateBlock(next , old_size - block_size - sizeof(block_t));
	
	result = (block_t *)((char *)runner + sizeof(block_t));
	
	return result;
}


void VSAFree(void *block)
{
	assert(block);
	
	block = ((char *)block - sizeof(block_t));
	
	assert(MAGIC_NUMBER == ((block_t *)block)->magic_num);
	
	((block_t *)block)->block_size = (-1) * (((block_t *)block)->block_size);
}


size_t VSALargestChunkAvailable(vsa_t *vsa)
{
	block_t *runner = NULL;
	long result = 0;
	
	assert(vsa);
	
	runner = (block_t *)((char *)vsa + sizeof(vsa_t));

	while(0 != runner->block_size)
	{
		if (runner->block_size > result)
		{
			result = runner->block_size;
		}
		
		runner = NextBlock(runner);
		DeFrag(runner);
	}
	
	return result;
}


/********* Helpers **********/


long AlignPointer(void *ptr)
{
	size_t offset = (size_t)ptr % WORD_SIZE;

	if(offset)
	{
		offset = WORD_SIZE - (size_t)ptr % WORD_SIZE;
	}

	return offset;
}


long AlignNum(long num)
{
	size_t offset = num % WORD_SIZE;

	if(offset)
	{
		offset = WORD_SIZE - num % WORD_SIZE;
	}

	return num + offset;
}


long Abs(long num)
{
	if(0 > num)
	{
		num *= -1;
	}
	
	return num;
}

static void DeFrag(block_t *block) 
{
	block_t *next = NULL;
	long block_size = 0;

	assert(block);
	
	block_size = block->block_size;
	next = NextBlock(block);
	
	while (0 < next->block_size && 0 < block->block_size)
	{
		block_size += next->block_size + sizeof(block_t);
		next = NextBlock(next);
	} 
	
	block->block_size = block_size;
}

static block_t *NextBlock(block_t *block)
{
	block_t *next = NULL;
	
	assert(block);
	
	next = ((block_t*)((char*)block + Abs(block->block_size) + sizeof(block_t)));
	
	return next;
}

static void CreateBlock(block_t *block_add, long size)
{ 
	assert(block_add);
	
	block_add->block_size = size;
	#ifndef NDEBUG
	block_add->magic_num = MAGIC_NUMBER;
	#endif
}


