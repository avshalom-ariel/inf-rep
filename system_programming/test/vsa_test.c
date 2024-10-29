
#include <stdio.h> 					/*printf*/
#include <assert.h> 				/*assert*/


/*#include "vsa.h" */				/*vsa_t, VSAfunction declaration*/
#include "test_utility.h" 			/*Test function declarations*/
#include "AvshalomToEvelinCRvsa.h" 

#define WORD_SIZE sizeof(void *)

static void VSAInitializeAllocTest(void);
static void VSAInitializeAllocFreeTest(void);
static void VSALargestChunkAvailableTest(void);
static void VSAInitializeAllocFreeDebugTest(void);
static void VSAYardeTest(void);

int main(void)
{
	VSAInitializeAllocTest();
	VSAInitializeAllocFreeTest();
	VSALargestChunkAvailableTest();
	VSAInitializeAllocFreeDebugTest();
	VSAYardeTest();
	
	
	Test();
	
	return 0;
}

void VSAInitializeAllocTest(void)
{
	char memory_pool[1000];
	size_t pool_size = 1000;
	vsa_t *vsa = VSAInitialize(memory_pool, pool_size);
	void *block1 = NULL;
	void *block2 = NULL;
	void *block3 = NULL;
	
	block1 = VSAAlloc(vsa, 10);
	block2 = VSAAlloc(vsa, 20);
	block3 = VSAAlloc(vsa, 30);

	TestSizeT("VSAInitializeAllocTest", __FILE__, __LINE__, 0, (size_t)block1 % WORD_SIZE);
	TestSizeT("VSAInitializeAllocTest", __FILE__, __LINE__, 0, (size_t)block2 % WORD_SIZE);
	TestSizeT("VSAInitializeAllocTest", __FILE__, __LINE__, 0, (size_t)block3 % WORD_SIZE);
	
	*(int *)block1 = 1;
	*(int *)block2 = 2;
	*(int *)block3 = 3;
	
	TestInt("VSAInitializeAllocTest", __FILE__, __LINE__, 1, *(int *)block1);
	TestInt("VSAInitializeAllocTest", __FILE__, __LINE__, 2, *(int *)block2);
	TestInt("VSAInitializeAllocTest", __FILE__, __LINE__, 3, *(int *)block3);
	
}


void VSAInitializeAllocFreeTest(void)
{
	char memory_pool[1000];
	size_t pool_size = 1000;
	vsa_t *vsa = VSAInitialize(memory_pool, pool_size);
	void *block1 = NULL;
	void *block2 = NULL;
	void *block3 = NULL;
	void *block4 = NULL;
	void *block5 = NULL;
	
	TestSizeT("VSAInitializeAllocTest", __FILE__, __LINE__, 960, VSALargestChunkAvailable(vsa));
	
	block1 = VSAAlloc(vsa, 10);
	block2 = VSAAlloc(vsa, 20);
	block3 = VSAAlloc(vsa, 30);
	block4 = VSAAlloc(vsa, 60);
	block5 = VSAAlloc(vsa, 200);
	
	assert(NULL != block1);
	assert(NULL != block2);
	assert(NULL != block3);
	assert(NULL != block4);
	assert(NULL != block5);
	
	TestSizeT("VSAInitializeAllocTest", __FILE__, __LINE__, 0, (size_t)block1 % WORD_SIZE);
	TestSizeT("VSAInitializeAllocTest", __FILE__, __LINE__, 0, (size_t)block2 % WORD_SIZE);
	TestSizeT("VSAInitializeAllocTest", __FILE__, __LINE__, 0, (size_t)block3 % WORD_SIZE);
	TestSizeT("VSAInitializeAllocTest", __FILE__, __LINE__, 0, (size_t)block4 % WORD_SIZE);
	TestSizeT("VSAInitializeAllocTest", __FILE__, __LINE__, 0, (size_t)block5 % WORD_SIZE);
	
	TestSizeT("VSAInitializeAllocTest", __FILE__, __LINE__, 544, VSALargestChunkAvailable(vsa));
	
	VSAFree(block5);
	
	TestSizeT("VSAInitializeAllocTest", __FILE__, __LINE__, 760, VSALargestChunkAvailable(vsa));
	
	VSAFree(block4);
	VSAFree(block2);
	
	TestSizeT("VSAInitializeAllocTest", __FILE__, __LINE__, 840, VSALargestChunkAvailable(vsa));
	
	block2 = VSAAlloc(vsa, 80);
	block4 = VSAAlloc(vsa, 70);
	block5 = VSAAlloc(vsa, 80);
	
	*(int *)block1 = 1;
	*(int *)block2 = 2;
	*(int *)block3 = 3;
	*(int *)block4 = 4;
	*(int *)block5 = 5;
	
	TestInt("VSAInitializeAllocTest", __FILE__, __LINE__, 1, *(int *)block1);
	TestInt("VSAInitializeAllocTest", __FILE__, __LINE__, 2, *(int *)block2);
	TestInt("VSAInitializeAllocTest", __FILE__, __LINE__, 3, *(int *)block3);
	TestInt("VSAInitializeAllocTest", __FILE__, __LINE__, 4, *(int *)block4);
	TestInt("VSAInitializeAllocTest", __FILE__, __LINE__, 5, *(int *)block5);
}


void VSAInitializeAllocFreeDebugTest(void)
{
	char memory_pool[1000];
	size_t pool_size = 1000;
	vsa_t *vsa = VSAInitialize(memory_pool, pool_size);
	void *block1 = NULL;
	void *block2 = NULL;
	void *block3 = NULL;
	void *block4 = NULL;
	void *block5 = NULL;
	
	TestSizeT("VSAInitializeAllocTest", __FILE__, __LINE__, 960, VSALargestChunkAvailable(vsa));
	
	block1 = VSAAlloc(vsa, 10);
	block2 = VSAAlloc(vsa, 20);
	block3 = VSAAlloc(vsa, 30);
	block4 = VSAAlloc(vsa, 60);
	block5 = VSAAlloc(vsa, 100);
	
	assert(NULL != block1);
	assert(NULL != block2);
	assert(NULL != block3);
	assert(NULL != block4);
	assert(NULL != block5);
	
	TestSizeT("VSAInitializeAllocTest", __FILE__, __LINE__, 0, (size_t)block1 % WORD_SIZE);
	TestSizeT("VSAInitializeAllocTest", __FILE__, __LINE__, 0, (size_t)block2 % WORD_SIZE);
	TestSizeT("VSAInitializeAllocTest", __FILE__, __LINE__, 0, (size_t)block3 % WORD_SIZE);
	TestSizeT("VSAInitializeAllocTest", __FILE__, __LINE__, 0, (size_t)block4 % WORD_SIZE);
	TestSizeT("VSAInitializeAllocTest", __FILE__, __LINE__, 0, (size_t)block5 % WORD_SIZE);
	
	TestSizeT("VSAInitializeAllocTest", __FILE__, __LINE__, 640, VSALargestChunkAvailable(vsa));
	
	VSAFree(block5);
	
	TestSizeT("VSAInitializeAllocTest", __FILE__, __LINE__, 760, VSALargestChunkAvailable(vsa));
	
	VSAFree(block4);
	VSAFree(block2);
	
	TestSizeT("VSAInitializeAllocTest", __FILE__, __LINE__, 840, VSALargestChunkAvailable(vsa));
	
	block2 = VSAAlloc(vsa, 80);
	block4 = VSAAlloc(vsa, 70);
	block5 = VSAAlloc(vsa, 80);
	
	*(int *)block1 = 1;
	*(int *)block2 = 2;
	*(int *)block3 = 3;
	*(int *)block4 = 4;
	*(int *)block5 = 5;
	
	TestInt("VSAInitializeAllocTest", __FILE__, __LINE__, 1, *(int *)block1);
	TestInt("VSAInitializeAllocTest", __FILE__, __LINE__, 2, *(int *)block2);
	TestInt("VSAInitializeAllocTest", __FILE__, __LINE__, 3, *(int *)block3);
	TestInt("VSAInitializeAllocTest", __FILE__, __LINE__, 4, *(int *)block4);
	TestInt("VSAInitializeAllocTest", __FILE__, __LINE__, 5, *(int *)block5);
}


void VSALargestChunkAvailableTest(void)
{
	char memory_pool[1000];
	size_t pool_size = 1000;
	vsa_t *vsa = VSAInitialize(memory_pool, pool_size);
	void *block1 = NULL;
	void *block2 = NULL;
	void *block3 = NULL;
	void *block4 = NULL;
	void *block5 = NULL;
	
	TestSizeT("VSAInitializeAllocTest", __FILE__, __LINE__, 960, VSALargestChunkAvailable(vsa));
	
	block1 = VSAAlloc(vsa, 10);
	
	TestSizeT("VSAInitializeAllocTest", __FILE__, __LINE__, 928, VSALargestChunkAvailable(vsa));
	
	block2 = VSAAlloc(vsa, 20);
	
	TestSizeT("VSAInitializeAllocTest", __FILE__, __LINE__, 888, VSALargestChunkAvailable(vsa));
	
	block3 = VSAAlloc(vsa, 30);
	
	TestSizeT("VSAInitializeAllocTest", __FILE__, __LINE__, 840, VSALargestChunkAvailable(vsa));
	
	block4 = VSAAlloc(vsa, 60);
	
	TestSizeT("VSAInitializeAllocTest", __FILE__, __LINE__, 760, VSALargestChunkAvailable(vsa));
	
	block5 = VSAAlloc(vsa, 760);
	
	TestSizeT("VSAInitializeAllocTest", __FILE__, __LINE__, 0, (size_t)block1 % WORD_SIZE);
	TestSizeT("VSAInitializeAllocTest", __FILE__, __LINE__, 0, (size_t)block2 % WORD_SIZE);
	TestSizeT("VSAInitializeAllocTest", __FILE__, __LINE__, 0, (size_t)block3 % WORD_SIZE);
	TestSizeT("VSAInitializeAllocTest", __FILE__, __LINE__, 0, (size_t)block4 % WORD_SIZE);
	TestSizeT("VSAInitializeAllocTest", __FILE__, __LINE__, 0, (size_t)block5 % WORD_SIZE);
	
	*(int *)block1 = 1;
	*(int *)block2 = 2;
	*(int *)block3 = 3;
	*(int *)block4 = 4;
	*(int *)block5 = 5;
	
	TestInt("VSAInitializeAllocTest", __FILE__, __LINE__, 1, *(int *)block1);
	TestInt("VSAInitializeAllocTest", __FILE__, __LINE__, 2, *(int *)block2);
	TestInt("VSAInitializeAllocTest", __FILE__, __LINE__, 3, *(int *)block3);
	TestInt("VSAInitializeAllocTest", __FILE__, __LINE__, 4, *(int *)block4);
	TestInt("VSAInitializeAllocTest", __FILE__, __LINE__, 5, *(int *)block5);
}


void VSAYardeTest(void)
{
	char memory_pool[1024];
	size_t pool_size = 1024;
	vsa_t *vsa = VSAInitialize(memory_pool, pool_size);
	void *block1 = NULL;
	void *block2 = NULL;
	void *block3 = NULL;
	long largest_chunk = 0;
	
	TestSizeT("VSAInitializeAllocTest", __FILE__, __LINE__, 984, VSALargestChunkAvailable(vsa));
	
	block1 = VSAAlloc(vsa, 96);
	
	TestSizeT("VSAInitializeAllocTest", __FILE__, __LINE__, 872, VSALargestChunkAvailable(vsa));
	
	block2 = VSAAlloc(vsa, 125);
	
	TestSizeT("VSAInitializeAllocTest", __FILE__, __LINE__, 728, VSALargestChunkAvailable(vsa));
	
	block3 = VSAAlloc(vsa, 63);
	
	TestSizeT("VSAInitializeAllocTest", __FILE__, __LINE__, 0, (size_t)block1 % WORD_SIZE);
	TestSizeT("VSAInitializeAllocTest", __FILE__, __LINE__, 0, (size_t)block2 % WORD_SIZE);
	TestSizeT("VSAInitializeAllocTest", __FILE__, __LINE__, 0, (size_t)block3 % WORD_SIZE);
	
	*(int *)block1 = 1;
	*(int *)block2 = 2;
	*(int *)block3 = 3;
	
	TestInt("VSAInitializeAllocTest", __FILE__, __LINE__, 1, *(int *)block1);
	TestInt("VSAInitializeAllocTest", __FILE__, __LINE__, 2, *(int *)block2);
	TestInt("VSAInitializeAllocTest", __FILE__, __LINE__, 3, *(int *)block3);
	
	VSAFree(block2);
	VSAFree(block3);
	
	block2 = VSAAlloc(vsa, 204);
	block3 = VSAAlloc(vsa, 70);
	
	TestSizeT("VSAInitializeAllocTest", __FILE__, __LINE__, 0, (size_t)block2 % WORD_SIZE);
	TestSizeT("VSAInitializeAllocTest", __FILE__, __LINE__, 0, (size_t)block3 % WORD_SIZE);
	
	TestSizeT("VSAInitializeAllocTest", __FILE__, __LINE__, 560, VSALargestChunkAvailable(vsa));
}


