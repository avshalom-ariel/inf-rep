
#include <stdio.h> 				/*printf*/
#include <stdlib.h> 			/*printf*/

#include "heap_pq_scheduler.h" 	/*heap_pq_scheduler_t typedefs and functions*/
#include "uid.h" 				/*ilrd_uid_t*/
#include "test_utility.h" 		/*TestFunctions*/

static int ActionFunc1(void *data);
static int ActionFunc2(void *data);
static int ActionFunc3(void *data);
static int ActionAlloc(void *data);

static void DummyClean();
static void CleanAlooc();

static void Heap_PQ_SchedulerAddTaskTest(void);
static void Heap_PQ_SchedulerAddTaskRemoveTest(void);
static void Heap_PQ_SchedulerIsEmptyTest(void);
static void Heap_PQ_SchedulerRunStopTest(void);
static void Heap_PQ_SchedulerClearTest(void);

static int *dirt;

int main(void)
{
	Heap_PQ_SchedulerAddTaskTest();	
	Heap_PQ_SchedulerAddTaskRemoveTest();
	Heap_PQ_SchedulerIsEmptyTest();
	Heap_PQ_SchedulerRunStopTest();
	Heap_PQ_SchedulerClearTest();
	
	YardenTest();
	
	Test();
	
	return 0;
}


/********************************************/
/*			   Test Functions				*/
/********************************************/


void Heap_PQ_SchedulerAddTaskTest(void)
{
	heap_pq_scheduler_t *scheduler = Heap_PQ_SchedulerCreate();
	
	TestInt("Heap_PQ_SchedulerAddTaskTest", __FILE__, __LINE__, 0, Heap_PQ_SchedulerSize(scheduler));
	
	Heap_PQ_SchedulerAddTask(scheduler, ActionFunc1, DummyClean, NULL, 50);
	
	TestInt("Heap_PQ_SchedulerAddTaskTest", __FILE__, __LINE__, 1, Heap_PQ_SchedulerSize(scheduler));
	
	Heap_PQ_SchedulerAddTask(scheduler, ActionFunc2, DummyClean, NULL, 40);
	
	TestInt("Heap_PQ_SchedulerAddTaskTest", __FILE__, __LINE__, 2, Heap_PQ_SchedulerSize(scheduler));
	
	Heap_PQ_SchedulerDestroy(scheduler);
}


void Heap_PQ_SchedulerAddTaskRemoveTest(void)
{
	heap_pq_scheduler_t *scheduler = Heap_PQ_SchedulerCreate();

	ilrd_uid_t uid1 = Heap_PQ_SchedulerAddTask(scheduler, ActionFunc1, DummyClean, NULL, 50);
	ilrd_uid_t uid2 = Heap_PQ_SchedulerAddTask(scheduler, ActionFunc2, DummyClean, NULL, 40);
	ilrd_uid_t uid3 = Heap_PQ_SchedulerAddTask(scheduler, ActionFunc3, DummyClean, NULL, 30);
	
	TestInt("Heap_PQ_SchedulerAddTaskRemoveTest", __FILE__, __LINE__, 3, Heap_PQ_SchedulerSize(scheduler));
	
	Heap_PQ_SchedulerRemove(scheduler, uid1);
	
	TestInt("Heap_PQ_SchedulerAddTaskRemoveTest", __FILE__, __LINE__, 2, Heap_PQ_SchedulerSize(scheduler));
	
	Heap_PQ_SchedulerRemove(scheduler, uid2);
	
	TestInt("Heap_PQ_SchedulerAddTaskRemoveTest", __FILE__, __LINE__, 1, Heap_PQ_SchedulerSize(scheduler));

	Heap_PQ_SchedulerRemove(scheduler, uid3);	
	
	TestInt("Heap_PQ_SchedulerAddTaskRemoveTest", __FILE__, __LINE__, 0, Heap_PQ_SchedulerSize(scheduler));
	
	Heap_PQ_SchedulerDestroy(scheduler);
}


void Heap_PQ_SchedulerIsEmptyTest(void)
{
	ilrd_uid_t uid1;
	heap_pq_scheduler_t *scheduler = Heap_PQ_SchedulerCreate();
	
	TestInt("Heap_PQ_SchedulerIsEmptyTest", __FILE__, __LINE__, 1, Heap_PQ_SchedulerIsEmpty(scheduler));

	uid1 = Heap_PQ_SchedulerAddTask(scheduler, ActionFunc1, DummyClean, NULL, 50);
	
	TestInt("Heap_PQ_SchedulerIsEmptyTest", __FILE__, __LINE__, 0, Heap_PQ_SchedulerIsEmpty(scheduler));
	
	Heap_PQ_SchedulerRemove(scheduler, uid1);
	
	TestInt("Heap_PQ_SchedulerIsEmptyTest", __FILE__, __LINE__, 1, Heap_PQ_SchedulerIsEmpty(scheduler));
	
	Heap_PQ_SchedulerDestroy(scheduler);
}


void Heap_PQ_SchedulerRunStopTest(void)
{
	heap_pq_scheduler_t *scheduler = Heap_PQ_SchedulerCreate();
	
	Heap_PQ_SchedulerAddTask(scheduler, ActionFunc1, DummyClean, NULL, 5);
	Heap_PQ_SchedulerAddTask(scheduler, ActionFunc2, DummyClean, NULL, 3);
	Heap_PQ_SchedulerAddTask(scheduler, ActionFunc3, DummyClean, NULL, 1);
	Heap_PQ_SchedulerAddTask(scheduler, (scheduler_action_func_t)Heap_PQ_SchedulerStop, 
					 DummyClean, scheduler, 15);
	
	Heap_PQ_SchedulerRun(scheduler);
	
	Heap_PQ_SchedulerDestroy(scheduler);
}


void Heap_PQ_SchedulerClearTest(void)
{
	heap_pq_scheduler_t *scheduler = Heap_PQ_SchedulerCreate();
	
	Heap_PQ_SchedulerAddTask(scheduler, ActionFunc1, DummyClean, NULL, 5);
	Heap_PQ_SchedulerAddTask(scheduler, ActionFunc2, DummyClean, NULL, 3);
	Heap_PQ_SchedulerAddTask(scheduler, ActionFunc3, DummyClean, NULL, 1);
	Heap_PQ_SchedulerAddTask(scheduler, ActionAlloc, CleanAlooc, NULL, 11);
	Heap_PQ_SchedulerAddTask(scheduler, (scheduler_action_func_t)Heap_PQ_SchedulerStop, 
					 DummyClean, scheduler, 15);
					 
	TestInt("Heap_PQ_SchedulerClearTest", __FILE__, __LINE__, 5, Heap_PQ_SchedulerSize(scheduler));
	
	Heap_PQ_SchedulerClear(scheduler);
	
	TestInt("Heap_PQ_SchedulerClearTest", __FILE__, __LINE__, 0, Heap_PQ_SchedulerSize(scheduler));
	
	Heap_PQ_SchedulerDestroy(scheduler);
}


/********************************************/
/*			   Help Functions				*/
/********************************************/


int ActionFunc1(void *data)
{
	(void)data;
	printf("wake up every 5 seconds\n");
	
	return 0;
}


int ActionFunc2(void *data)
{
	(void)data;
	printf("wake up every 3 seconds\n");
	
	return 0;
}


int ActionFunc3(void *data)
{
	(void)data;
	printf("wake up every 1 seconds\n");
	
	return 0;
}


int ActionAlloc(void *data)
{
	dirt = (int *)malloc(3 * sizeof(int));
	
	(void)data;
	*dirt = 7;
	
	return 0;
}


void DummyClean()
{
	return;
}


void CleanAlooc(void *data)
{
	(void)data;
	free(dirt);
}



