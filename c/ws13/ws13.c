#include<stddef.h> /*size_t*/
#include <stdio.h> /*printf*/
#include <string.h>/*strncat*/
#include "header.h"

void *MyMemset(void *dest, int c, size_t num)
{
	void *result = dest;
	unsigned int word_size_chunk;
	size_t reminder;
	size_t i;
	
	
	
	word_size_chunk = (c % 256) | ((c % 256) << 8 ) | ((c % 256) << 16) | ((c % 256) << 24);
	

	while (num && ((size_t)result % WORD))
	{
		*((char *)result) = (unsigned char)c;
		
		--num;
		
		result = (char *)((size_t)result + 1);
	}
	
	reminder = num % WORD;
	num = num/WORD;
	
	
	for (i = 0; i < num; ++i)
	{
		*((int *)result) = word_size_chunk;
		result = (int *)((size_t)result + WORD);
	}
	
	if (reminder)
	{
		for(i = 0; i < reminder; ++i)
		{
			*((char *)result) = (char)c;
			result = (char *)((size_t)result + 1);
		}
	}
	
	return dest;	
}



void *MyMemcpy(void *dest, void * src, size_t num)
{

	void *result = dest;
	size_t reminder;
	size_t i;

	while (num && ((size_t)result % WORD))
	{
		*((char *)result) = *((char *)src);
		
		--num;
		
		result = (char *)((size_t)result + 1);
		src = (char *)((size_t)src + 1);
	}
	
	reminder = num % WORD;
	num = num/WORD;
	
	for (i = 0; i < num; ++i)
	{
		*((int *)result) = *((int *)src);
		
		result = (int *)((size_t)result + WORD);
		src = (int *)((size_t)src + WORD);
	}
	
	if (reminder)
	{
		for(i = 0; i < reminder; ++i)
		{
			*((char *)result) = *((char *)src);
			
			result = (char *)((size_t)result + 1);
			src = (char *)((size_t)src + 1);
		}
	}	
	return dest;
}


void *MyMemmove(void *dest, const void *src, size_t num) 
{
    unsigned char *dest_data = dest;
    const unsigned char *src_data = src;
	size_t i;
	
    if (dest_data < src_data) 
    {
        for (i = 0; i < num; ++i) 
        {
            dest_data[i] = src_data[i];
        }
    } 
    else if (dest_data > src_data) 
    {
        for (i = num; i != 0; --i) 
        {
            dest_data[i - 1] = src_data[i - 1];
        }
    }
    
    return dest;
}













