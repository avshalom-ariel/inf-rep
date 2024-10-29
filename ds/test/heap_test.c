
#include "heap.h" 			/*Typedefs, function declarations*/
#include "test_utility.h" 	/*Test functions*/

static void HeapCreateDestroySizeTest(void);
static void HeapCreateDestroyIsEmptyTest(void);
static void HeapPushSizeTest(void);
static void HeapPushPeekTest(void);
static void HeapPopTest(void);
static void HeapRemoveTest(void);

static int CompFunc(const void *num1, const void *num2);
static int MatchFunc(const void *num1, const void *num2);

int main(void)
{
	HeapCreateDestroySizeTest();
	HeapCreateDestroyIsEmptyTest();
	HeapPushSizeTest();
	HeapPushPeekTest();
	HeapPopTest();
	HeapRemoveTest();
	
	
	Test();

	return 0;
}


/********************************************/
/*			 API Functions Tests			*/
/********************************************/


void HeapCreateDestroySizeTest(void)
{
	heap_t *heap = HeapCreate(CompFunc);
	
	TestInt("HeapCreateDestroySizeTest", __FILE__, __LINE__, 0, HeapSize(heap));
	
	HeapDestroy(heap);
}

void HeapCreateDestroyIsEmptyTest(void)
{
	heap_t *heap = HeapCreate(CompFunc);
	
	TestInt("HeapCreateDestroyIsEmptyTest", __FILE__, __LINE__, 1, HeapIsEmpty(heap));
	
	HeapDestroy(heap);
}

void HeapPushSizeTest(void)
{
	heap_t *heap = HeapCreate(CompFunc);
	size_t data[] = {1, 2, 3, 5, 45, 6, 85, 4, 92, 40};
	size_t i = 0;
	
	for (; i < (sizeof(data) / sizeof(size_t)); ++i)
	{
		TestInt("HeapPushSizeTest", __FILE__, __LINE__, i, HeapSize(heap));
		TestInt("HeapPushSizeTest", __FILE__, __LINE__, 0, HeapPush(heap, data + i));
	}
	
	HeapDestroy(heap);
}

void HeapPushPeekTest(void)
{
	heap_t *heap = HeapCreate(CompFunc);
	size_t data[] = {1, 2, 3, 5, 45, 6, 85, 4, 92, 40};
	size_t i = 0;
	
	
	TestSizeT("HeapPushPeekTest", __FILE__, __LINE__, 0, HeapPush(heap, data + 0));
	
	TestSizeT("HeapPushPeekTest", __FILE__, __LINE__, 1, *(size_t *)HeapPeek(heap));
	
	TestSizeT("HeapPushPeekTest", __FILE__, __LINE__, 0, HeapPush(heap, data + 1));
	
	TestSizeT("HeapPushPeekTest", __FILE__, __LINE__, 2, *(size_t *)HeapPeek(heap));
	
	TestSizeT("HeapPushPeekTest", __FILE__, __LINE__, 0, HeapPush(heap, data + 2));

	TestSizeT("HeapPushPeekTest", __FILE__, __LINE__, 3, *(size_t *)HeapPeek(heap));

	TestSizeT("HeapPushPeekTest", __FILE__, __LINE__, 0, HeapPush(heap, data + 3));

	TestSizeT("HeapPushPeekTest", __FILE__, __LINE__, 5, *(size_t *)HeapPeek(heap));

	TestSizeT("HeapPushPeekTest", __FILE__, __LINE__, 0, HeapPush(heap, data + 4));

	TestSizeT("HeapPushPeekTest", __FILE__, __LINE__, 45, *(size_t *)HeapPeek(heap));

	TestSizeT("HeapPushPeekTest", __FILE__, __LINE__, 0, HeapPush(heap, data + 5));

	TestSizeT("HeapPushPeekTest", __FILE__, __LINE__, 45, *(size_t *)HeapPeek(heap));

	TestSizeT("HeapPushPeekTest", __FILE__, __LINE__, 0, HeapPush(heap, data + 6));

	TestSizeT("HeapPushPeekTest", __FILE__, __LINE__, 85, *(size_t *)HeapPeek(heap));

	TestSizeT("HeapPushPeekTest", __FILE__, __LINE__, 0, HeapPush(heap, data + 7));

	TestSizeT("HeapPushPeekTest", __FILE__, __LINE__, 85, *(size_t *)HeapPeek(heap));

	TestSizeT("HeapPushPeekTest", __FILE__, __LINE__, 0, HeapPush(heap, data + 8));

	TestSizeT("HeapPushPeekTest", __FILE__, __LINE__, 92, *(size_t *)HeapPeek(heap));

	TestSizeT("HeapPushPeekTest", __FILE__, __LINE__, 0, HeapPush(heap, data + 9));

	TestSizeT("HeapPushPeekTest", __FILE__, __LINE__, 92, *(size_t *)HeapPeek(heap));
	
	HeapDestroy(heap);
}

void HeapPopTest(void)
{
	heap_t *heap = HeapCreate(CompFunc);
	size_t data[] = {1, 2, 3, 5, 45, 6, 85, 4, 92, 40};
	size_t i = 0;
	
	for (; i < (sizeof(data) / sizeof(size_t)); ++i)
	{
		TestInt("HeapPopTest", __FILE__, __LINE__, 0, HeapPush(heap, data + i));
	}
	
	TestSizeT("HeapPopTest", __FILE__, __LINE__, 92, *(size_t *)HeapPeek(heap));
	TestInt("HeapPopTest", __FILE__, __LINE__, 10, HeapSize(heap));
	
	HeapPop(heap);

	TestSizeT("HeapPopTest", __FILE__, __LINE__, 85, *(size_t *)HeapPeek(heap));
	TestInt("HeapPopTest", __FILE__, __LINE__, 9, HeapSize(heap));
	
	HeapPop(heap);

	TestSizeT("HeapPopTest", __FILE__, __LINE__, 45, *(size_t *)HeapPeek(heap));
	TestInt("HeapPopTest", __FILE__, __LINE__, 8, HeapSize(heap));
	
	HeapPop(heap);

	TestSizeT("HeapPopTest", __FILE__, __LINE__, 40, *(size_t *)HeapPeek(heap));
	TestInt("HeapPopTest", __FILE__, __LINE__, 7, HeapSize(heap));
	
	HeapPop(heap);

	TestSizeT("HeapPopTest", __FILE__, __LINE__, 6, *(size_t *)HeapPeek(heap));
	TestInt("HeapPopTest", __FILE__, __LINE__, 6, HeapSize(heap));
	
	HeapPop(heap);

	TestSizeT("HeapPopTest", __FILE__, __LINE__, 5, *(size_t *)HeapPeek(heap));
	TestInt("HeapPopTest", __FILE__, __LINE__, 5, HeapSize(heap));
	
	HeapPop(heap);

	TestSizeT("HeapPopTest", __FILE__, __LINE__, 4, *(size_t *)HeapPeek(heap));
	TestInt("HeapPopTest", __FILE__, __LINE__, 4, HeapSize(heap));
	
	HeapPop(heap);

	TestSizeT("HeapPopTest", __FILE__, __LINE__, 3, *(size_t *)HeapPeek(heap));
	TestInt("HeapPopTest", __FILE__, __LINE__, 3, HeapSize(heap));
	
	HeapPop(heap);

	TestSizeT("HeapPopTest", __FILE__, __LINE__, 2, *(size_t *)HeapPeek(heap));
	TestInt("HeapPopTest", __FILE__, __LINE__, 2, HeapSize(heap));
	
	HeapPop(heap);

	TestSizeT("HeapPopTest", __FILE__, __LINE__, 1, *(size_t *)HeapPeek(heap));
	TestInt("HeapPopTest", __FILE__, __LINE__, 1, HeapSize(heap));
	
	HeapPop(heap);

	TestInt("HeapPopTest", __FILE__, __LINE__, 0, HeapSize(heap));	
	
	HeapDestroy(heap);
}

void HeapRemoveTest(void)
{
	heap_t *heap = HeapCreate(CompFunc);
	size_t data[] = {1, 2, 3, 5, 45, 6, 85, 4, 92, 40};
	void *result = NULL;
	size_t i = 0;
	
	for (; i < (sizeof(data) / sizeof(size_t)); ++i)
	{
		TestInt("HeapRemoveTest", __FILE__, __LINE__, 0, HeapPush(heap, data + i));
	}
	
	result = HeapRemove(heap, MatchFunc, data + 6);

	TestSizeT("HeapRemoveTest", __FILE__, __LINE__, 9, HeapSize(heap));
	
	TestSizeT("HeapRemoveTest", __FILE__, __LINE__, *(data + 3), *(size_t *)HeapRemove(heap, 
																		MatchFunc, data + 3));
	TestSizeT("HeapRemoveTest", __FILE__, __LINE__, 8, HeapSize(heap));
	
	TestSizeT("HeapRemoveTest", __FILE__, __LINE__, *(data + 2), *(size_t *)HeapRemove(heap, 
																		MatchFunc, data + 2));
	TestSizeT("HeapRemoveTest", __FILE__, __LINE__, 7, HeapSize(heap));
	
	TestSizeT("HeapRemoveTest", __FILE__, __LINE__, *(data + 7), *(size_t *)HeapRemove(heap, 
																		MatchFunc, data + 7));
	TestSizeT("HeapRemoveTest", __FILE__, __LINE__, 6, HeapSize(heap));
	
	TestSizeT("HeapRemoveTest", __FILE__, __LINE__, 1, NULL == HeapRemove(heap, MatchFunc, data + 7));

	TestSizeT("HeapRemoveTest", __FILE__, __LINE__, 6, HeapSize(heap));
	
	HeapDestroy(heap);
}


/********************************************/
/*			 	Help Functions				*/
/********************************************/


int CompFunc(const void *num1, const void *num2)
{
	return *(size_t *)num1 - *(size_t *)num2;
}

int MatchFunc(const void *num1, const void *num2)
{
	return *(size_t *)num1 == *(size_t *)num2;
}


