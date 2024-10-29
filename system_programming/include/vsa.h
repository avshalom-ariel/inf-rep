#ifndef __VSA_H__
#define __VSA_H__

#include <stddef.h> /* size_t */

typedef struct vsa vsa_t;

/*
description: Initializes new variable size allocator.
input: memory pool, pool size.
return: a pointer to a allocator. if failed, returns NULL.
time complexity: O(1)
space complexity: O(1)
*/
vsa_t *VSAInitialize(void *memory_pool, long pool_size);

/*
description: allocates a block of memory of size block_size.
input: Pointer to allocator, long block_size the size in bytes of the block requested.
return: pointer to memory allocated, aligned. if failed returns NULL
time complexity: O(n) (n: number of chunks in the pool)
space complexity: O(1)
*/
void *VSAAlloc(vsa_t *allocator, long block_size); 

/*
description: Frees a specific block of memory from the allocator.
input: Pointer to allocator, pointer to memory block. If NULL does nothing.
return: void.
time complexity: O(1)
space complexity: O(1)
*/
void VSAFree(void *mem_to_free_ptr);

/*
description: Returns the size of largest continuous block in bytes.
input: vsa
return: size of largest block posible for allocation.
time complexity: O(n)
space complexity: O(1)
*/
size_t VSALargestChunkAvailable(vsa_t *vsa);

#endif /* __VSA_H__ */
