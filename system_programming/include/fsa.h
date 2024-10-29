#ifndef __FSA_H__
#define __FSA_H__

#include <stddef.h> /* size_t */

typedef struct fsa fsa_t;

/*
description: Initializes new fixed size allocator. Allocates memory dynamically.
input: size of each block and number of blocks that the allocator will handle.
return: a pointer to a allocator. if failed, returns NULL.
time complexity: O(1)
space complexity: O(n)
*/
fsa_t *FSAInit(void *memory_pool, size_t block_size, size_t pool_size);

/*
description: allocates a fixed size memory block. Doesn't allocate any additional memory from the Heap.
input: Pointer to allocator.
return: pointer to memory allocated, aligned
time complexity: O(1)
space complexity: O(1)
*/
void *FSAAlloc(fsa_t *allocator);

/*
description: Frees a specific block of memory from the allocator.
input: Pointer to allocator, pointer to memory block.
return: void.
time complexity: O(1)
space complexity: O(1)
*/
void FSAFree(fsa_t *allocator, void *mem_to_free_ptr);

/*
description: Returns number of free blocks
input: Pointer to allocator
return: number of free blocks.
time complexity: O(n)
space complexity: O(1)
*/
size_t FSACountFree(fsa_t *allocator);

/*
description: Calculates the suggested size to pass the the Initialize() function, to consider system requirements and overhead by the API functions
input: block size and block count
return: (size_t) number of bytes suggested to be allocated by the user
time complexity: O(1)
space complexity: O(1)
*/
size_t FSASuggestSize(size_t block_size, size_t block_count);

#endif /* __FSA_H__ */
