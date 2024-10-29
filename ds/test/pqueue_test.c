
#include <stdio.h> /*printf*/

#include "pqueue.h" /*pqueue_t and all the PQ functions*/
#include "test_utility.h" /*Test functions*/

#define TRUE 1
#define FALSE 0
#define SUCCESS 0
#define FAILIURE 1

int CmpInt(const void *data1, const void *data2);
int MatchInt(const void *data1, const void *data2);

void PQEnqueueTest(void);
void PQDequeueTest(void);
void PQPeekEnqueueDequeueTest(void);
void PQIsEmptyTest(void);
void PQSizeTest(void);
void PQClearTest(void);
void PQEraseTest(void);
void PQEraseTest2(void);

int main(void)
{
	PQEnqueueTest();
	PQDequeueTest();
	PQPeekEnqueueDequeueTest();
	PQIsEmptyTest();
	PQSizeTest();
	PQClearTest();
	PQEraseTest();
	PQEraseTest2();
	
	Test();
	
	return 0;
}


void PQEnqueueTest(void)
{
	pqueue_t *pqueue= PQCreate(CmpInt);
	int data1 = 1;
	int data2 = 2;
	
	TestInt("PQEnqueueTest", __FILE__, __LINE__, SUCCESS, PQEnqueue(pqueue, &data1));
	TestInt("PQEnqueueTest", __FILE__, __LINE__, SUCCESS, PQEnqueue(pqueue, &data2));
	
	PQDestroy(pqueue);
}


void PQDequeueTest(void)
{
	pqueue_t *pqueue= PQCreate(CmpInt);
	int data1 = 1;
	int data2 = 2;
	
	PQEnqueue(pqueue, &data1);
	PQEnqueue(pqueue, &data2);
	
	TestInt("PQDequeueTest", __FILE__, __LINE__, data1, *(int *)PQDequeue(pqueue));
	TestInt("PQDequeueTest", __FILE__, __LINE__, data2, *(int *)PQDequeue(pqueue));
	
	PQDestroy(pqueue);
}


void PQPeekEnqueueDequeueTest(void)
{
	pqueue_t *pqueue= PQCreate(CmpInt);
	int data1 = 1;
	int data2 = 2;
	int data3 = 3;
	int data4 = 4;
	
	PQEnqueue(pqueue, &data3);
	
	TestInt("PQPeekEnqueueDequeueTest", __FILE__, __LINE__, data3, *(int *)PQPeek(pqueue));

	PQEnqueue(pqueue, &data2);

	TestInt("PQPeekEnqueueDequeueTest", __FILE__, __LINE__, data2, *(int *)PQPeek(pqueue));

	PQEnqueue(pqueue, &data1);

	TestInt("PQPeekEnqueueDequeueTest", __FILE__, __LINE__, data1, *(int *)PQPeek(pqueue));
	
	PQEnqueue(pqueue, &data4);

	TestInt("PQPeekEnqueueDequeueTest", __FILE__, __LINE__, data1, *(int *)PQPeek(pqueue));

	PQDequeue(pqueue);

	TestInt("PQPeekEnqueueDequeueTest", __FILE__, __LINE__, data2, *(int *)PQPeek(pqueue));

	PQDequeue(pqueue);

	TestInt("PQPeekEnqueueDequeueTest", __FILE__, __LINE__, data3, *(int *)PQPeek(pqueue));

	PQDequeue(pqueue);

	TestInt("PQPeekEnqueueDequeueTest", __FILE__, __LINE__, data4, *(int *)PQPeek(pqueue));

	PQDestroy(pqueue);
}


void PQIsEmptyTest(void)
{
	pqueue_t *pqueue= PQCreate(CmpInt);
	int data1 = 1;
	
	TestInt("PQIsEmptyTest", __FILE__, __LINE__, TRUE, PQIsEmpty(pqueue));
	
	PQEnqueue(pqueue, &data1);
	
	TestInt("PQIsEmptyTest", __FILE__, __LINE__, FALSE, PQIsEmpty(pqueue));
	
	PQDequeue(pqueue);
	
	TestInt("PQIsEmptyTest", __FILE__, __LINE__, TRUE, PQIsEmpty(pqueue));
	
	PQDestroy(pqueue);
}


void PQSizeTest(void)
{
	pqueue_t *pqueue= PQCreate(CmpInt);
	int data1 = 1;
	int data2 = 2;
	int data3 = 3;
	int data4 = 4;
	
	TestInt("PQSizeTest", __FILE__, __LINE__, 0, PQSize(pqueue));
	
	PQEnqueue(pqueue, &data3);
	
	TestInt("PQSizeTest", __FILE__, __LINE__, 1, PQSize(pqueue));

	PQEnqueue(pqueue, &data2);

	TestInt("PQSizeTest", __FILE__, __LINE__, 2, PQSize(pqueue));

	PQEnqueue(pqueue, &data1);

	TestInt("PQSizeTest", __FILE__, __LINE__, 3, PQSize(pqueue));
	
	PQEnqueue(pqueue, &data4);

	TestInt("PQSizeTest", __FILE__, __LINE__, 4, PQSize(pqueue));

	PQDequeue(pqueue);

	TestInt("PQSizeTest", __FILE__, __LINE__, 3, PQSize(pqueue));

	PQDequeue(pqueue);

	TestInt("PQSizeTest", __FILE__, __LINE__, 2, PQSize(pqueue));

	PQDequeue(pqueue);

	TestInt("PQSizeTest", __FILE__, __LINE__, 1, PQSize(pqueue));
	
	PQDequeue(pqueue);

	TestInt("PQSizeTest", __FILE__, __LINE__, 0, PQSize(pqueue));

	PQDestroy(pqueue);
}


void PQClearTest(void)
{
	pqueue_t *pqueue= PQCreate(CmpInt);
	int data1 = 1;
	int data2 = 2;
	int data3 = 3;
	int data4 = 4;
	
	TestInt("PQClearTest", __FILE__, __LINE__, TRUE, PQIsEmpty(pqueue));
	
	PQEnqueue(pqueue, &data3);
	PQEnqueue(pqueue, &data2);
	PQEnqueue(pqueue, &data1);
	PQEnqueue(pqueue, &data4);

	TestInt("PQClearTest", __FILE__, __LINE__, FALSE, PQIsEmpty(pqueue));
	
	PQClear(pqueue);
	
	TestInt("PQClearTest", __FILE__, __LINE__, TRUE, PQIsEmpty(pqueue));

	PQDestroy(pqueue);
}


void PQEraseTest(void)
{
	pqueue_t *pqueue= PQCreate(CmpInt);
	int data1 = 1;
	int data2 = 2;
	int data3 = 3;
	int data4 = 4;
	int data5 = 5;
	int data6 = 6;
	
	PQEnqueue(pqueue, &data3);
	PQEnqueue(pqueue, &data2);
	PQEnqueue(pqueue, &data1);
	PQEnqueue(pqueue, &data4);
	PQEnqueue(pqueue, &data6);
	PQEnqueue(pqueue, &data5);

	TestInt("PQEraseTest", __FILE__, __LINE__, 6, PQSize(pqueue));
	
	TestInt("PQEraseTest", __FILE__, __LINE__, data4, *(int *)PQErase(pqueue, MatchInt, &data4));
	
	TestInt("PQEraseTest", __FILE__, __LINE__, 5, PQSize(pqueue));
	
	TestInt("PQEraseTest", __FILE__, __LINE__, data1, *(int *)PQPeek(pqueue));
	
	TestInt("PQEraseTest", __FILE__, __LINE__, data1, *(int *)PQErase(pqueue, MatchInt, &data1));
	
	TestInt("PQEraseTest", __FILE__, __LINE__, 4, PQSize(pqueue));
	
	TestInt("PQEraseTest", __FILE__, __LINE__, data2, *(int *)PQPeek(pqueue));
	
	TestInt("PQEraseTest", __FILE__, __LINE__, data2, *(int *)PQErase(pqueue, MatchInt, &data2));
	
	TestInt("PQEraseTest", __FILE__, __LINE__, 3, PQSize(pqueue));
	
	TestInt("PQEraseTest", __FILE__, __LINE__, data3, *(int *)PQPeek(pqueue));
	
	PQDestroy(pqueue);
}


void PQEraseTest2(void)
{
	pqueue_t *pqueue= PQCreate(CmpInt);
	int arr[] = {1, 2, 3, 2, 5};
	
	PQEnqueue(pqueue, arr);
	PQEnqueue(pqueue, arr + 1);
	PQEnqueue(pqueue, arr + 2);
	PQEnqueue(pqueue, arr +3);
	PQEnqueue(pqueue, arr +4);

	TestInt("PQEraseTest", __FILE__, __LINE__, 5, PQSize(pqueue));
	
	TestSizeT("PQEraseTest", __FILE__, __LINE__, (size_t)(arr + 1), (size_t)PQErase(pqueue, MatchInt, arr + 3));
	
	TestInt("PQEraseTest", __FILE__, __LINE__, 4, PQSize(pqueue));
	
	PQDequeue(pqueue);
	
	TestInt("PQEraseTest", __FILE__, __LINE__, *(arr + 1), *(int *)PQPeek(pqueue));
	
	PQDestroy(pqueue);
}



int CmpInt(const void *data1, const void *data2)
{
	return *(int *)data1 - *(int *)data2;
}

int MatchInt(const void *data1, const void *data2)
{
	return *(int *)data1 == *(int *)data2;
}

