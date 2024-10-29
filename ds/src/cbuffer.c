/*
Name: Avshalom Ariel
Reveiwer: Shahae Marom
Date: 21/05/2024
status: Approved
*/

#include <stddef.h> /*size_t*/
#include <stdlib.h> /*malloc, free*/
#include <assert.h> /*assert*/
#include <string.h> /*memcpy*/

#include "cbuffer.h" /*cbuffer_t  defined functions declarations*/

struct cbuffer
{
  size_t available_place;              
  size_t capacity;   
  char *write;           
  char buffer[1];           
};   


cbuffer_t *CBufferCreate(size_t buffer_size)
{
	cbuffer_t *cbuffer = (cbuffer_t *)malloc(sizeof(struct cbuffer) + buffer_size - 8);
	
	if(NULL == cbuffer)
	{
		return NULL;
	}
	
	cbuffer -> capacity = buffer_size;
	cbuffer -> available_place = buffer_size;
	cbuffer -> write = (char *)(cbuffer -> buffer);
	
	return cbuffer;
}


void CBufferDestroy(cbuffer_t *cbuffer)
{
	assert(NULL != cbuffer);
	
	free(cbuffer);
}


size_t CBufferAvailableSpace(const cbuffer_t *cbuffer)
{
	assert(NULL != cbuffer);
	
	return cbuffer -> available_place;
}


size_t CBufferBufsiz(const cbuffer_t *cbuffer)
{
	assert(NULL != cbuffer);
	
	return cbuffer -> capacity;
}


ssize_t CBufferRead(cbuffer_t *cbuffer, void *dest, size_t count)
{
	size_t read_offset = ((size_t)(cbuffer -> write) - (size_t)(cbuffer -> buffer) +
						cbuffer -> available_place) % cbuffer -> capacity;
	size_t steps_until_loop = cbuffer -> capacity - read_offset;
	size_t left_after_loop = (count > steps_until_loop) ? count - steps_until_loop : 0;
	
	assert(NULL != cbuffer);
	assert(NULL != dest);
	
	if(0 == left_after_loop)
	{
		memcpy(dest , cbuffer -> buffer + read_offset, count);
		cbuffer -> available_place += count;
		return ((ssize_t)count);
	}
	else
	{
		memcpy(dest , cbuffer -> buffer + read_offset, steps_until_loop);
		cbuffer -> available_place += count;
		cbuffer -> available_place += steps_until_loop;
	}
	
	memcpy(dest , cbuffer -> buffer, left_after_loop);
	
	cbuffer -> available_place += left_after_loop;
	
	return (ssize_t)(steps_until_loop + left_after_loop);
}


ssize_t CBufferWrite(cbuffer_t *cbuffer, void *src, size_t count)
{
	size_t steps_until_loop = (size_t)((cbuffer -> buffer) + 
							  cbuffer -> capacity) - (size_t)(cbuffer -> write);
	size_t left_after_loop = (count > steps_until_loop) ? count - steps_until_loop : 0;
	
	assert(NULL != cbuffer);
	assert(NULL != src);
	
	if(count <= steps_until_loop)
	{
		memcpy(cbuffer -> buffer, src, count);
		cbuffer -> available_place -= count;
		return (count);
	}
	else
	{
		memcpy(cbuffer -> buffer, src, steps_until_loop);
		cbuffer -> available_place -= steps_until_loop;
	}
	
	memcpy((char *)src + left_after_loop, cbuffer -> buffer, left_after_loop);
	
	cbuffer -> available_place -= left_after_loop;
	
	
	return (ssize_t)(steps_until_loop + left_after_loop);
}


int CBufferIsEmpty(const cbuffer_t *cbuffer)
{
	assert(NULL != cbuffer);
	
	return (cbuffer -> capacity == cbuffer -> available_place);
}

