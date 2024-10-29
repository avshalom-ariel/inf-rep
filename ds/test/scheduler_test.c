
#include  <stdio.h> 		/*printf*/
#include <stdlib.h> 		/*printf*/

#include "scheduler.h" 		/*scheduler_t typedefs and functions*/
#include "uid.h" 			/*ilrd_uid_t*/
#include "test_utility.h" 	/*TestFunctions*/

static int ActionFunc1(void *data);
static int ActionFunc2(void *data);
static int ActionFunc3(void *data);
static int ActionAlloc(void *data);

static void DummyClean();
static void CleanAlooc();

static void SchedulerSizeAddTest(void);
static void SchedulerSizeAddRemoveTest(void);
static void SchedulerIsEmptyTest(void);
static void SchedulerRunStopTest(void);
static void SchedulerClearTest(void);

static int *dirt;

int main(void)
{
	SchedulerSizeAddTest();	
	SchedulerSizeAddRemoveTest();
	SchedulerIsEmptyTest();
	SchedulerRunStopTest();
	SchedulerClearTest();
	
	Test();
	
	return 0;
}


/********************************************/
/*			   Test Functions				*/
/********************************************/


void SchedulerSizeAddTest(void)
{
	scheduler_t *scheduler = SchedulerCreate();
	
	TestInt("SchedulerSizeAddTest", __FILE__, __LINE__, 0, SchedulerSize(scheduler));
	
	SchedulerAddTask(scheduler, ActionFunc1, DummyClean, NULL, 50);
	
	TestInt("SchedulerSizeAddTest", __FILE__, __LINE__, 1, SchedulerSize(scheduler));
	
	SchedulerAddTask(scheduler, ActionFunc2, DummyClean, NULL, 40);
	
	TestInt("SchedulerSizeAddTest", __FILE__, __LINE__, 2, SchedulerSize(scheduler));
	
	SchedulerDestroy(scheduler);
}

void SchedulerSizeAddRemoveTest(void)
{
	scheduler_t *scheduler = SchedulerCreate();

	ilrd_uid_t uid1 = SchedulerAddTask(scheduler, ActionFunc1, DummyClean, NULL, 50);
	ilrd_uid_t uid2 = SchedulerAddTask(scheduler, ActionFunc2, DummyClean, NULL, 40);
	ilrd_uid_t uid3 = SchedulerAddTask(scheduler, ActionFunc3, DummyClean, NULL, 30);
	
	TestInt("SchedulerSizeAddRemoveTest", __FILE__, __LINE__, 3, SchedulerSize(scheduler));
	
	SchedulerRemove(scheduler, uid1);
	
	TestInt("SchedulerSizeAddRemoveTest", __FILE__, __LINE__, 2, SchedulerSize(scheduler));
	
	SchedulerRemove(scheduler, uid2);
	
	TestInt("SchedulerSizeAddRemoveTest", __FILE__, __LINE__, 1, SchedulerSize(scheduler));

	SchedulerRemove(scheduler, uid3);	
	
	TestInt("SchedulerSizeAddRemoveTest", __FILE__, __LINE__, 0, SchedulerSize(scheduler));
	
	SchedulerDestroy(scheduler);
}

void SchedulerIsEmptyTest(void)
{
	ilrd_uid_t uid1;
	scheduler_t *scheduler = SchedulerCreate();
	
	TestInt("SchedulerIsEmptyTest", __FILE__, __LINE__, 1, SchedulerIsEmpty(scheduler));

	uid1 = SchedulerAddTask(scheduler, ActionFunc1, DummyClean, NULL, 50);
	
	TestInt("SchedulerIsEmptyTest", __FILE__, __LINE__, 0, SchedulerIsEmpty(scheduler));
	
	SchedulerRemove(scheduler, uid1);
	
	TestInt("SchedulerIsEmptyTest", __FILE__, __LINE__, 1, SchedulerIsEmpty(scheduler));
	
	SchedulerDestroy(scheduler);
}

void SchedulerRunStopTest(void)
{
	scheduler_t *scheduler = SchedulerCreate();
	
	SchedulerAddTask(scheduler, ActionFunc1, DummyClean, NULL, 5);
	SchedulerAddTask(scheduler, ActionFunc2, DummyClean, NULL, 3);
	SchedulerAddTask(scheduler, ActionFunc3, DummyClean, NULL, 1);
	SchedulerAddTask(scheduler, (scheduler_action_func_t)SchedulerStop, 
					 DummyClean, scheduler, 15);
	
	SchedulerRun(scheduler);
	
	SchedulerDestroy(scheduler);
}

void SchedulerClearTest(void)
{
	scheduler_t *scheduler = SchedulerCreate();
	
	SchedulerAddTask(scheduler, ActionFunc1, DummyClean, NULL, 5);
	SchedulerAddTask(scheduler, ActionFunc2, DummyClean, NULL, 3);
	SchedulerAddTask(scheduler, ActionFunc3, DummyClean, NULL, 1);
	SchedulerAddTask(scheduler, ActionAlloc, CleanAlooc, NULL, 11);
	SchedulerAddTask(scheduler, (scheduler_action_func_t)SchedulerStop, 
					 DummyClean, scheduler, 15);
					 
	TestInt("SchedulerClearTest", __FILE__, __LINE__, 5, SchedulerSize(scheduler));
	
	SchedulerClear(scheduler);
	
	TestInt("SchedulerClearTest", __FILE__, __LINE__, 0, SchedulerSize(scheduler));
	
	SchedulerDestroy(scheduler);
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


