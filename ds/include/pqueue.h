#ifndef __PQUEUE_H__
#define __PQUEUE_H__

typedef struct pqueue pqueue_t;

/*
*pqcompare_func_t
description: typedef to pointer function that compares two arguments
params: (void *, void *) two elements to compare
return Value: int that represent the status of the matching:
    positive if first argument is larger,
    zero if they equal
    negative if the second argument is larger.
*/
typedef int (*pqcompare_func_t)(const void*, const void*);

/*
*pqmatch_func_t
description: typedef to pointer function that checks if the two arguments are a match
params: (void *, void *) two elements to compare
return value: int that represent the status of the matching, 1 for a match, 0 for not match
*/
typedef int (*pqmatch_func_t)(const void*, const void*);

/*
PQCreate
description: creates a new priority queue
input: compare function that implements the priority
return: a pointer to a priority queue, if failed NULL
time complexity: O(1)
space complexity: O(1)
*/
pqueue_t *PQCreate(pqcompare_func_t cmp_func);

/*
PQDestroy
description: destroy the priority queue
input: pointer to priority queue
return: nothing
time complexity: O(n)
space complexity: O(1)
*/
void PQDestroy(pqueue_t *pqueue);

/*
PQEnqueue
description: adds new element to the queue according to its priority - the priority range is -20 - 19, the lower the number the higher its priority.
input: pointer to priority queue, priority of item, pointer to data
return: success status: 0 success, otherwise failure
time complexity: O(n)
space complexity: O(1)
*/
int PQEnqueue(pqueue_t *pqueue, void *data);

/*
PQDequeue
description: remove the highest priority
input: queue
return: void* to dequeued data  
time complexity: O(1)
space complexity: O(1)
*/
void *PQDequeue(pqueue_t *pqueue);

/* 
PQPeek
description: Peek at the highest priority element without removing it.
Input:  Pointer to the priority queue.
return: the highest priority element data, - If the queue is empty, undefined
Time Complexity: O(1)
Space Complexity: O(1)
 */
void *PQPeek(const pqueue_t *pqueue);

/*
PQIsEmpty
description: check if priority queue is empty
input: pointer to priority queue
return: 1 if priority queue is empty otherwise 0
time complexity: O(1)
space complexity: O(1)
*/
int PQIsEmpty(const pqueue_t *pqueue);

/*
PQSize
description: return the priority queue size
input: pointer to priority queue
return: priority queue size
time complexity: O(n)
space complexity: O(1)
*/
size_t PQSize(const pqueue_t *pqueue);

/*
PQClear
description: remove all elements in priority queue
input: pointer to priority queue
return: nothing
time complexity: O(n)
space complexity: O(1)
*/
void PQClear(pqueue_t *pqueue);

/*
PQErase
description: remove specific elements from priority queue
input: pointer to priority queue, a pointer to match function, and a pointer to a parameter
return: the erased data, and NULL if it didn't erase anything.
time complexity: O(n)
space complexity: O(1)
*/
void *PQErase(pqueue_t *pqueue, pqmatch_func_t is_match, void *data);

#endif /* __PQUEUE_H__ */
