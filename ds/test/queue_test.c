
#include <stdlib.h> /*malloc free*/
#include <assert.h> /*assert*/
#include <stdio.h> /*printf*/

#include "queue.h" /*size_t*/


static int QueueAppendTest(void);
static int QueueEnqueueTest(void);
static int QueueDequeueTest(void);
static int QueuePeekTest(void);
static int QueueSizeTest(void);
static int QueueIsEmptyTest(void);


int main(void)
{
	
	assert(0 == QueueAppendTest());
	assert(0 == QueueEnqueueTest());
	assert(0 == QueueDequeueTest());
	assert(0 == QueuePeekTest());
	assert(0 == QueueSizeTest());
	assert(0 == QueueIsEmptyTest());
	
	
	
	printf("All Tests Passed!\n");
	
	return 0;
}



int QueueAppendTest(void)
{
	queue_t *queue1 = NULL;
	queue_t *queue2 = NULL;
	
	int data1 = 1;
	int data2 = 2;
	int data3 = 3;
	int data4 = 4;
	int data5 = 5;
	
	queue1 = QueueCreate();
	queue2 = QueueCreate();
	
	assert(1 == QueueIsEmpty(queue1));
	
	assert(1 == QueueEnqueue(queue1, &data1));
	assert(1 == QueueSize(queue1));
	
	assert(1 == QueueEnqueue(queue1, &data2));
	assert(2 == QueueSize(queue1));
		
	assert(1 == QueueEnqueue(queue1, &data3));
	assert(3 == QueueSize(queue1));
	
	assert(1 == QueueEnqueue(queue2, &data4));
	assert(1 == QueueSize(queue2));
	
	assert(1 == QueueEnqueue(queue2, &data5));
	assert(2 == QueueSize(queue2));
	
	assert(4 ==  *(int *)QueuePeek(queue2));
	
	QueueAppend(queue1, queue2);
	
	assert(1 ==  *(int *)QueuePeek(queue1));
	QueueDequeue(queue1);
	
	assert(2 ==  *(int *)QueuePeek(queue1));
	QueueDequeue(queue1);
	
	assert(3 ==  *(int *)QueuePeek(queue1));
	QueueDequeue(queue1);
	
	assert(4 ==  *(int *)QueuePeek(queue1));
	QueueDequeue(queue1);
	
	assert(5 ==  *(int *)QueuePeek(queue1));
	QueueDequeue(queue1);
	
	printf("%d", *(int *)QueuePeek(queue1));
	
	assert(1 == QueueIsEmpty(queue1));
	
	
	QueueDestroy(queue1);
	QueueDestroy(queue2);
	
	printf("QueueAppend Test Passed!\n");
	
	return 0;
}



int QueueEnqueueTest(void)
{
	queue_t *queue = NULL;
	
	int data1 = 1;
	int data2 = 2;
	int data3 = 3;
	int data4 = 4;
	int data5 = 5;
	
	queue = QueueCreate();
	
	assert(1 == QueueIsEmpty(queue));
	
	assert(1 == QueueEnqueue(queue, &data1));
	assert(1 == QueueSize(queue));
	
	assert(1 == QueueEnqueue(queue, &data2));
	assert(2 == QueueSize(queue));
		
	assert(1 == QueueEnqueue(queue, &data3));
	assert(3 == QueueSize(queue));
	
	assert(1 == QueueEnqueue(queue, &data4));
	assert(4 == QueueSize(queue));
	
	assert(1 == QueueEnqueue(queue, &data5));
	assert(5 == QueueSize(queue));
	
	assert(1 ==  *(int *)QueuePeek(queue));
	
	QueueDequeue(queue);
	
	assert(4 == QueueSize(queue));
	assert(2 ==  *(int *)QueuePeek(queue));
	
	assert(0 == QueueIsEmpty(queue));
	
	
	QueueDestroy(queue);
	
	printf("QueueEnqueue Test Passed!\n");
	
	return 0;
	
}


int QueueDequeueTest(void)
{
	queue_t *queue = NULL;
	
	int data1 = 1;
	int data2 = 2;
	int data3 = 3;
	int data4 = 4;
	int data5 = 5;
	
	queue = QueueCreate();
	
	assert(1 == QueueIsEmpty(queue));
	
	assert(1 == QueueEnqueue(queue, &data1));
	assert(1 == QueueSize(queue));
	
	assert(1 == QueueEnqueue(queue, &data2));
	assert(2 == QueueSize(queue));
		
	assert(1 == QueueEnqueue(queue, &data3));
	assert(3 == QueueSize(queue));
	
	assert(1 == QueueEnqueue(queue, &data4));
	assert(4 == QueueSize(queue));
	
	assert(1 == QueueEnqueue(queue, &data5));
	assert(5 == QueueSize(queue));
	
	assert(1 ==  *(int *)QueuePeek(queue));
	
	QueueDequeue(queue);
	
	assert(4 == QueueSize(queue));
	assert(2 ==  *(int *)QueuePeek(queue));
	
	assert(0 == QueueIsEmpty(queue));
	
	
	QueueDestroy(queue);
	
	printf("QueueDequeue Test Passed!\n");
	
	return 0;
}


int QueuePeekTest(void)
{
	queue_t *queue = NULL;
	
	int data1 = 1;
	int data2 = 2;
	int data3 = 3;
	int data4 = 4;
	int data5 = 5;
	
	queue = QueueCreate();
	
	assert(1 == QueueIsEmpty(queue));
	
	assert(1 == QueueEnqueue(queue, &data1));
	assert(1 == QueueSize(queue));
	
	assert(1 == QueueEnqueue(queue, &data2));
	assert(2 == QueueSize(queue));
		
	assert(1 == QueueEnqueue(queue, &data3));
	assert(3 == QueueSize(queue));
	
	assert(1 == QueueEnqueue(queue, &data4));
	assert(4 == QueueSize(queue));
	
	assert(1 == QueueEnqueue(queue, &data5));
	assert(5 == QueueSize(queue));
	
	assert(1 ==  *(int *)QueuePeek(queue));
	
	QueueDequeue(queue);
	
	assert(4 == QueueSize(queue));
	assert(2 ==  *(int *)QueuePeek(queue));
	
	assert(0 == QueueIsEmpty(queue));
	
	
	QueueDestroy(queue);
	
	printf("QueuePeek Test Passed!\n");
	
	return 0;
}


int QueueSizeTest(void)
{
	queue_t *queue = NULL;
	
	int data1 = 1;
	int data2 = 2;
	int data3 = 3;
	int data4 = 4;
	int data5 = 5;
	
	queue = QueueCreate();
	
	assert(1 == QueueIsEmpty(queue));
	
	assert(1 == QueueEnqueue(queue, &data1));
	assert(1 == QueueSize(queue));
	
	assert(1 == QueueEnqueue(queue, &data2));
	assert(2 == QueueSize(queue));
		
	assert(1 == QueueEnqueue(queue, &data3));
	assert(3 == QueueSize(queue));
	
	assert(1 == QueueEnqueue(queue, &data4));
	assert(4 == QueueSize(queue));
	
	assert(1 == QueueEnqueue(queue, &data5));
	assert(5 == QueueSize(queue));
	
	assert(1 ==  *(int *)QueuePeek(queue));
	
	QueueDequeue(queue);
	
	assert(4 == QueueSize(queue));
	assert(2 ==  *(int *)QueuePeek(queue));
	
	assert(0 == QueueIsEmpty(queue));
	
	
	QueueDestroy(queue);
	
	printf("QueueSize Test Passed!\n");
	
	return 0;
}



int QueueIsEmptyTest(void)
{
	queue_t *queue = NULL;
	
	int data1 = 1;
	int data2 = 2;
	int data3 = 3;
	int data4 = 4;
	int data5 = 5;
	
	queue = QueueCreate();
	
	assert(1 == QueueIsEmpty(queue));
	
	assert(1 == QueueEnqueue(queue, &data1));
	assert(1 == QueueSize(queue));
	
	assert(1 == QueueEnqueue(queue, &data2));
	assert(2 == QueueSize(queue));
		
	assert(1 == QueueEnqueue(queue, &data3));
	assert(3 == QueueSize(queue));
	
	assert(1 == QueueEnqueue(queue, &data4));
	assert(4 == QueueSize(queue));
	
	assert(1 == QueueEnqueue(queue, &data5));
	assert(5 == QueueSize(queue));
	
	assert(1 ==  *(int *)QueuePeek(queue));
	
	QueueDequeue(queue);
	
	assert(4 == QueueSize(queue));
	assert(2 ==  *(int *)QueuePeek(queue));
	
	assert(0 == QueueIsEmpty(queue));
	
	
	QueueDestroy(queue);
	
	printf("QueueSize Test Passed!\n");
	
	return 0;
}


