
#include <stdio.h> 			/*printf*/

#include "heap_pq.h" 		/*all the PQ functions*/
#include "test_utility.h" 	/*Test functions*/

#define TRUE 1
#define FALSE 0
#define SUCCESS 0
#define FAILIURE 1

int CmpInt(const void *data1, const void *data2);
int MatchInt(const void *data1, const void *data2);

void HeapPQEnqueueTest(void);
void HeapPQDequeueTest(void);
void HeapPQPeekEnqueueDequeueTest(void);
void HeapPQIsEmptyTest(void);
void HeapPQSizeTest(void);
void HeapPQClearTest(void);
void HeapPQEraseTest(void);
void HeapPQEraseTest2(void);

int main(void)
{
	HeapPQEnqueueTest();
	HeapPQDequeueTest();
	HeapPQPeekEnqueueDequeueTest();
	HeapPQIsEmptyTest();
	HeapPQSizeTest();
	HeapPQClearTest();
	HeapPQEraseTest();
	HeapPQEraseTest2();
	
	Test();
	
	return 0;
}


/********************************************/
/*			   Test Functions				*/
/********************************************/


void HeapPQEnqueueTest(void)
{
	heap_pq_t *pqueue= HeapPQCreate(CmpInt);
	int data1 = 1;
	int data2 = 2;
	
	TestInt("HeapPQEnqueueTest", __FILE__, __LINE__, SUCCESS, HeapPQEnqueue(pqueue, &data1));
	TestInt("HeapPQEnqueueTest", __FILE__, __LINE__, SUCCESS, HeapPQEnqueue(pqueue, &data2));
	
	HeapPQDestroy(pqueue);
}

void HeapPQDequeueTest(void)
{
	heap_pq_t *pqueue= HeapPQCreate(CmpInt);
	int data1 = 1;
	int data2 = 2;
	
	HeapPQEnqueue(pqueue, &data1);
	HeapPQEnqueue(pqueue, &data2);
	
	TestInt("HeapPQDequeueTest", __FILE__, __LINE__, data1, *(int *)HeapPQDequeue(pqueue));
	TestInt("HeapPQDequeueTest", __FILE__, __LINE__, data2, *(int *)HeapPQDequeue(pqueue));
	
	HeapPQDestroy(pqueue);
}

void HeapPQPeekEnqueueDequeueTest(void)
{
	heap_pq_t *pqueue= HeapPQCreate(CmpInt);
	int data1 = 1;
	int data2 = 2;
	int data3 = 3;
	int data4 = 4;
	
	HeapPQEnqueue(pqueue, &data3);
	
	TestInt("HeapPQPeekEnqueueDequeueTest", __FILE__, __LINE__, data3, *(int *)HeapPQPeek(pqueue));

	HeapPQEnqueue(pqueue, &data2);

	TestInt("HeapPQPeekEnqueueDequeueTest", __FILE__, __LINE__, data2, *(int *)HeapPQPeek(pqueue));

	HeapPQEnqueue(pqueue, &data1);

	TestInt("HeapPQPeekEnqueueDequeueTest", __FILE__, __LINE__, data1, *(int *)HeapPQPeek(pqueue));
	
	HeapPQEnqueue(pqueue, &data4);

	TestInt("HeapPQPeekEnqueueDequeueTest", __FILE__, __LINE__, data1, *(int *)HeapPQPeek(pqueue));

	HeapPQDequeue(pqueue);

	TestInt("HeapPQPeekEnqueueDequeueTest", __FILE__, __LINE__, data2, *(int *)HeapPQPeek(pqueue));

	HeapPQDequeue(pqueue);

	TestInt("HeapPQPeekEnqueueDequeueTest", __FILE__, __LINE__, data3, *(int *)HeapPQPeek(pqueue));

	HeapPQDequeue(pqueue);

	TestInt("HeapPQPeekEnqueueDequeueTest", __FILE__, __LINE__, data4, *(int *)HeapPQPeek(pqueue));

	HeapPQDestroy(pqueue);
}

void HeapPQIsEmptyTest(void)
{
	heap_pq_t *pqueue= HeapPQCreate(CmpInt);
	int data1 = 1;
	
	TestInt("HeapPQIsEmptyTest", __FILE__, __LINE__, TRUE, HeapPQIsEmpty(pqueue));
	
	HeapPQEnqueue(pqueue, &data1);
	
	TestInt("HeapPQIsEmptyTest", __FILE__, __LINE__, FALSE, HeapPQIsEmpty(pqueue));
	
	HeapPQDequeue(pqueue);
	
	TestInt("HeapPQIsEmptyTest", __FILE__, __LINE__, TRUE, HeapPQIsEmpty(pqueue));
	
	HeapPQDestroy(pqueue);
}

void HeapPQSizeTest(void)
{
	heap_pq_t *pqueue= HeapPQCreate(CmpInt);
	int data1 = 1;
	int data2 = 2;
	int data3 = 3;
	int data4 = 4;
	
	TestInt("HeapPQSizeTest", __FILE__, __LINE__, 0, HeapPQSize(pqueue));
	
	HeapPQEnqueue(pqueue, &data3);
	
	TestInt("HeapPQSizeTest", __FILE__, __LINE__, 1, HeapPQSize(pqueue));

	HeapPQEnqueue(pqueue, &data2);

	TestInt("HeapPQSizeTest", __FILE__, __LINE__, 2, HeapPQSize(pqueue));

	HeapPQEnqueue(pqueue, &data1);

	TestInt("HeapPQSizeTest", __FILE__, __LINE__, 3, HeapPQSize(pqueue));
	
	HeapPQEnqueue(pqueue, &data4);

	TestInt("HeapPQSizeTest", __FILE__, __LINE__, 4, HeapPQSize(pqueue));

	HeapPQDequeue(pqueue);

	TestInt("HeapPQSizeTest", __FILE__, __LINE__, 3, HeapPQSize(pqueue));

	HeapPQDequeue(pqueue);

	TestInt("HeapPQSizeTest", __FILE__, __LINE__, 2, HeapPQSize(pqueue));

	HeapPQDequeue(pqueue);

	TestInt("HeapPQSizeTest", __FILE__, __LINE__, 1, HeapPQSize(pqueue));
	
	HeapPQDequeue(pqueue);

	TestInt("HeapPQSizeTest", __FILE__, __LINE__, 0, HeapPQSize(pqueue));

	HeapPQDestroy(pqueue);
}

void HeapPQClearTest(void)
{
	heap_pq_t *pqueue= HeapPQCreate(CmpInt);
	int data1 = 1;
	int data2 = 2;
	int data3 = 3;
	int data4 = 4;
	
	TestInt("HeapPQClearTest", __FILE__, __LINE__, TRUE, HeapPQIsEmpty(pqueue));
	
	HeapPQEnqueue(pqueue, &data3);
	HeapPQEnqueue(pqueue, &data2);
	HeapPQEnqueue(pqueue, &data1);
	HeapPQEnqueue(pqueue, &data4);

	TestInt("HeapPQClearTest", __FILE__, __LINE__, FALSE, HeapPQIsEmpty(pqueue));
	
	HeapPQClear(pqueue);
	
	TestInt("HeapPQClearTest", __FILE__, __LINE__, TRUE, HeapPQIsEmpty(pqueue));

	HeapPQDestroy(pqueue);
}

void HeapPQEraseTest(void)
{
	heap_pq_t *pqueue= HeapPQCreate(CmpInt);
	int data1 = 1;
	int data2 = 2;
	int data3 = 3;
	int data4 = 4;
	int data5 = 5;
	int data6 = 6;
	
	HeapPQEnqueue(pqueue, &data3);
	HeapPQEnqueue(pqueue, &data2);
	HeapPQEnqueue(pqueue, &data1);
	HeapPQEnqueue(pqueue, &data4);
	HeapPQEnqueue(pqueue, &data6);
	HeapPQEnqueue(pqueue, &data5);

	TestInt("HeapPQEraseTest", __FILE__, __LINE__, 6, HeapPQSize(pqueue));
	
	TestInt("HeapPQEraseTest", __FILE__, __LINE__, data4, *(int *)HeapPQErase(pqueue, MatchInt, &data4));
	
	TestInt("HeapPQEraseTest", __FILE__, __LINE__, 5, HeapPQSize(pqueue));
	
	TestInt("HeapPQEraseTest", __FILE__, __LINE__, data1, *(int *)HeapPQPeek(pqueue));
	
	TestInt("HeapPQEraseTest", __FILE__, __LINE__, data1, *(int *)HeapPQErase(pqueue, MatchInt, &data1));
	
	TestInt("HeapPQEraseTest", __FILE__, __LINE__, 4, HeapPQSize(pqueue));
	
	TestInt("HeapPQEraseTest", __FILE__, __LINE__, data2, *(int *)HeapPQPeek(pqueue));
	
	TestInt("HeapPQEraseTest", __FILE__, __LINE__, data2, *(int *)HeapPQErase(pqueue, MatchInt, &data2));
	
	TestInt("HeapPQEraseTest", __FILE__, __LINE__, 3, HeapPQSize(pqueue));
	
	TestInt("HeapPQEraseTest", __FILE__, __LINE__, data3, *(int *)HeapPQPeek(pqueue));
	
	HeapPQDestroy(pqueue);
}

void HeapPQEraseTest2(void)
{
	heap_pq_t *pqueue= HeapPQCreate(CmpInt);
	int arr[] = {1, 2, 3, 2, 5};
	
	HeapPQEnqueue(pqueue, arr);
	HeapPQEnqueue(pqueue, arr + 1);
	HeapPQEnqueue(pqueue, arr + 2);
	HeapPQEnqueue(pqueue, arr +3);
	HeapPQEnqueue(pqueue, arr +4);

	TestInt("HeapPQEraseTest", __FILE__, __LINE__, 5, HeapPQSize(pqueue));
	
	TestSizeT("HeapPQEraseTest", __FILE__, __LINE__, (size_t)(arr + 1), (size_t)HeapPQErase(pqueue, 
																				MatchInt, arr + 3));
	
	TestInt("HeapPQEraseTest", __FILE__, __LINE__, 4, HeapPQSize(pqueue));
	
	HeapPQDequeue(pqueue);
	
	TestInt("HeapPQEraseTest", __FILE__, __LINE__, *(arr + 1), *(int *)HeapPQPeek(pqueue));
	
	HeapPQDestroy(pqueue);
}


/********************************************/
/*			   Help Functions				*/
/********************************************/


int CmpInt(const void *data1, const void *data2)
{
	return *(int *)data2 - *(int *)data1;
}

int MatchInt(const void *data1, const void *data2)
{
	return *(int *)data1 == *(int *)data2;
}

