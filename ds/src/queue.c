
#include <stddef.h> /*size_t*/
#include <stdlib.h> /*malloc free*/
#include <assert.h>/*assert*/

#include "queue.h" 
#include "sllist.h" 


struct queue
{
    struct linked_list *list; 
};


queue_t *QueueCreate(void)
{
	queue_t *queue = (queue_t *)malloc(sizeof(queue_t)); 
	
	queue -> list = SLListCreate();

	return queue;
}



void QueueDestroy(queue_t *queue)
{

	assert(NULL != queue);
	
	SLListDestroy(queue -> list);
	
	free(queue);
}


int QueueEnqueue(queue_t *queue, void *data)
{
	assert(NULL != queue);
	
	SLListInsert(queue -> list, data, SLListGetEnd(queue -> list));
	
	return 1;

}


void QueueDequeue(queue_t *queue)
{
	assert(NULL != queue);
	
	SLListRemove(SLListGetBegin(queue -> list));
	
}


void *QueuePeek(const queue_t *queue)
{
	assert(NULL != queue);
		
	return (void *)SLListGetData(SLListGetBegin(queue -> list));
}


size_t QueueSize(queue_t *queue)
{
	assert(NULL != queue);

	return SLListCount(queue -> list);
}



int QueueIsEmpty(queue_t *queue)
{
	assert(NULL != queue);
	
	return SLListIsEmpty(queue -> list);
}



queue_t *QueueAppend(queue_t *queue1, queue_t *queue2)
{
	
	assert(NULL != queue1);
	assert(NULL != queue2);
	
	SLListAppend(queue1 -> list, queue2 -> list);

	return queue1;
}















