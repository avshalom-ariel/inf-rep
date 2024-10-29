
#include <stdio.h> /*printf*/



#include "dllist.h" /*function declarations and type defs*/
#include "test_utility.h" /*Test functions*/


static void TestIsEmpty();
static void TestIsEqual();
static void TestGetData();
static void TestCount(size_t iteraions);
static void TestNext();
static void TestGetDataMulti(size_t iteraions);
static void TestGetBegin();
static void TestRemove();
static void TestForEach();
static void TestSplice();
static void TestMultiFind();
static void TestPopFront();
static void TestPushFront();
static void TestPopBack();
static void TestPushBack();
static void TestFind();

static int MultiTenToData(void *data_to_change, void *input_data);
static int CompData(const void *data1, const void *data2);

int main(void)
{
	TestIsEmpty();
	TestIsEqual();
	TestGetData();
	TestCount(10);
	TestNext();
	TestGetDataMulti(8);
	TestGetBegin();
	TestRemove();
	TestFind();
	TestForEach();
	TestSplice();
	TestMultiFind();
	TestPopFront();
	TestPushFront();
	TestPopBack();
	TestPushBack();
	
	Test();
	
	return 0;
}


void TestIsEmpty()
{
	dll_t *dll = DLListCreate();
	int data = 7;
	int res = DLListIsEmpty(dll);
	
	TestInt("TestIsEmpty", __FILE__, __LINE__, 1, res);
	
	DLListInsert(dll, DLListBegin(dll), &data);
	
	res = (0 == DLListIsEmpty(dll));
	
	TestInt("TestIsEmpty", __FILE__, __LINE__, 1, res);
	
	DLListDestroy(dll);
}

void TestIsEqual()
{
	dll_t *dll = DLListCreate();

	int res = DLListIsEqualIter(DLListBegin(dll), DLListEnd(dll));
	
	TestInt("TestIsEqual", __FILE__, __LINE__, 1, res);
	
	DLListDestroy(dll);
}


void TestGetData()
{
	dll_t *dll = DLListCreate();
	int data = 7;
	int *res_data = NULL;
	
	res_data = DLListGetData(DLListInsert(dll, DLListBegin(dll), &data));
	
	TestInt("TestGetData", __FILE__, __LINE__, data, *res_data);
	
	DLListDestroy(dll);
}


void TestCount(size_t iteraions)
{
	dll_t *dll = DLListCreate();
	int data = 1;
	size_t i = 0;
	size_t res = 0;
	
	for (; i < iteraions; ++i)
	{
		DLListInsert(dll, DLListBegin(dll), &data);
	}
	
	res = DLListCount(dll);
	
	TestSizeT("TestCount", __FILE__, __LINE__, iteraions, res);
	
	DLListDestroy(dll);
}

void TestNext()
{
	dll_t *dll = DLListCreate();
	int data1 = 1;
	int data2 = 2;
	int *res_data = NULL;
	dll_iterator_t res = NULL;
	dll_iterator_t res_next = NULL;
	
	res = DLListInsert(dll, DLListBegin(dll), &data1);
	DLListInsert(dll, DLListEnd(dll), &data2);
	
	res_next = DLListNext(res);
	res_data = DLListGetData(res_next);
	
	TestInt("TestNext", __FILE__, __LINE__, data2, *res_data);
	
	DLListDestroy(dll);
}


void TestGetDataMulti(size_t iteraions)
{
	dll_t *dllist = DLListCreate();
	int data[] = {1, 2, 3, 4, 5, 6, 7, 8};
	size_t i = 0;
	dll_iterator_t res = NULL;
	int *res_data = NULL;
	
	for (; i < iteraions; ++i)
	{
		res = DLListInsert(dllist, DLListBegin(dllist), data + i);
		
		res_data = DLListGetData(res);
		
		TestInt("TestGetDataMulti", __FILE__, __LINE__, data[i], *res_data);
	}
	
	DLListDestroy(dllist);
}

void TestGetBegin()
{
	dll_t *dllist = DLListCreate();
	int data[] = {1, 2, 3, 4, 5, 6, 7, 8};
	size_t i = 0;
	dll_iterator_t head = NULL;
	int *res_data = NULL;
	
	for (; i < sizeof(data) / sizeof(int); ++i)
	{
		DLListInsert(dllist, DLListBegin(dllist), data + i);
	}
	
	head = DLListBegin(dllist);
	res_data = DLListGetData(head);
	
	TestInt("TestGetBegin", __FILE__, __LINE__, data[7], *res_data);
	
	DLListDestroy(dllist);
}

void TestRemove()
{
	dll_t *dllist = DLListCreate();
	int data[] = {1, 2, 3, 4, 5, 6, 7, 8};
	size_t i = 0;
	dll_iterator_t head = NULL;
	int *res_data = NULL;
	size_t count = 0;
	
	for (; i < sizeof(data) / sizeof(int); ++i)
	{
		DLListInsert(dllist, DLListBegin(dllist), data + i);
	}
	
	DLListRemove(DLListBegin(dllist));
	count = DLListCount(dllist);
	
	head = DLListBegin(dllist);
	res_data = DLListGetData(head);
	
	TestInt("TestRemove", __FILE__, __LINE__, data[6], *res_data);
	TestSizeT("TestRemove", __FILE__, __LINE__, sizeof(data) / sizeof(int) - 1,
	          count);
	
	DLListDestroy(dllist);
}


static int CompData(const void *data1, const void *data2)
{
	return (*(int *)data1 == *(int *)data2);	
}

void TestFind()
{
	dll_t *dllist = DLListCreate();
	int data[] = {1, 2, 3, 4, 5, 6, 7, 8};
	size_t i = 0;
	dll_iterator_t res = NULL;
	int *res_data = NULL;
	
	for (; i < sizeof(data) / sizeof(int); ++i)
	{
		DLListInsert(dllist, DLListBegin(dllist), data + i);
	}
	
	res = DLListFind(DLListBegin(dllist), DLListEnd(dllist), data + 5, &CompData);
	res_data = DLListGetData(res);
	 
	TestInt("TestFind", __FILE__, __LINE__, *(data + 5), *res_data); 
	
	DLListDestroy(dllist);
}

static int MultiTenToData(void *data ,void *input_data)
{
	(void)input_data;
	
	*((int *)data) *= 10;
	
	return 0;
}


void TestForEach()
{
	dll_t *dllist = DLListCreate();
	int data[] = {1, 2, 3, 4, 5, 6, 7, 8};
	int comp_data[] = {10, 20, 30, 40, 50, 60, 70, 80};
	size_t i = 0;
	dll_iterator_t res = NULL;
	int *res_data = NULL;
	
	for (; i < sizeof(data) / sizeof(int); ++i)
	{
		DLListInsert(dllist, DLListEnd(dllist), data + i);
	}
	
	DLListForEach(DLListBegin(dllist), DLListEnd(dllist), NULL,
	              &MultiTenToData);
	
	for (i = 0, res = DLListBegin(dllist); i < sizeof(data) / sizeof(int);
	     ++i, res = DLListNext(res))
	{
		res_data = DLListGetData(res);
		
		TestInt("TestForEach", __FILE__, __LINE__, comp_data[i], *res_data);
	}
	
	DLListDestroy(dllist);
}


void TestSplice()
{
	dll_t *dllist = DLListCreate();
	dll_t *dllist2 = DLListCreate();
	int data[] = {1, 2, 3, 4, 5, 6, 7, 8};
	int data2[] = {9 ,10 ,11};
	size_t i = 0;
	dll_iterator_t runner = NULL;
	int *res_data = NULL;
	
	for (; i < sizeof(data) / sizeof(int); ++i)
	{
		DLListInsert(dllist, DLListEnd(dllist), data + i);
	}
	
	for (i = 0; i < sizeof(data2) / sizeof(int); ++i)
	{
		DLListInsert(dllist2, DLListEnd(dllist2), data2 + i);
	}
	
	runner = DLListSplice(DLListBegin(dllist) ,DLListEnd(dllist),
	                   DLListBegin(dllist2)); 
	
	for (i = 0; i < sizeof(data) / sizeof(int); ++i)
	{
		res_data = DLListGetData(runner);
		
		runner = DLListNext(runner);
		
		TestInt("TestSplice", __FILE__, __LINE__, data[i], *res_data);
	}
	
	for (i = 0; i < sizeof(data2) / sizeof(int); ++i)
	{
		res_data = DLListGetData(runner);
		
		runner = DLListNext(runner);
		
		TestInt("TestSplice", __FILE__, __LINE__, data2[i], *res_data);
	}
	
	DLListDestroy(dllist);
	DLListDestroy(dllist2);
}


void TestMultiFind()
{
	dll_t *dll1 = DLListCreate();
	dll_t *dll2 = DLListCreate();
	int data[] = {1, 2, 3, 2, 5, 2, 7, 8, 2};
	int comp_data = 2;
	size_t i = 0;
	size_t count_res = 0;
	
	for (; i < sizeof(data) / sizeof(int); ++i)
	{
		DLListInsert(dll1, DLListEnd(dll1), data + i);
	}
	
	DLListMultiFind(dll2, DLListBegin(dll1), DLListEnd(dll1), &comp_data, &CompData);
	
	count_res = DLListCount(dll2);
	
	TestSizeT("TestCount", __FILE__, __LINE__, 4, count_res);
	
	DLListDestroy(dll1);
	DLListDestroy(dll2);
}


void TestPopFront()
{
	dll_t *dllist = DLListCreate();
	int data[] = {1, 2, 3, 4, 5, 6, 7, 8};
	size_t i = 0;
	size_t res_count = 0;
	int *res_data = 0; 
	
	for (; i < sizeof(data) / sizeof(int); ++i)
	{
		DLListInsert(dllist, DLListBegin(dllist), data + i);
	}
	
	res_data = DLListPopFront(dllist);
	
	TestInt("TestPopFront", __FILE__, __LINE__, 8, *res_data);
	
	res_count = DLListCount(dllist);
	
	TestSizeT("TestPopFront", __FILE__, __LINE__, 7, res_count);
	
	DLListDestroy(dllist);
}

void TestPushFront()
{
	dll_t *dllist = DLListCreate();
	int data[] = {1, 2, 3, 4, 5, 6, 7, 8};
	size_t i = 0;
	size_t res_count = 0;
	int extra_data = 9; 
	
	for (; i < sizeof(data) / sizeof(int); ++i)
	{
		DLListInsert(dllist, DLListBegin(dllist), data + i);
	}
	
	DLListPushFront(dllist, &extra_data);
	
	TestInt("TestPushFront", __FILE__, __LINE__, 9, 
	        *(int *)DLListGetData(DLListBegin(dllist)));
	
	res_count = DLListCount(dllist);
	
	TestSizeT("TestPushFront", __FILE__, __LINE__, 9, res_count);
	
	DLListDestroy(dllist);
}

void TestPopBack()
{
	dll_t *dllist = DLListCreate();
	int data[] = {1, 2, 3, 4, 5, 6, 7, 8};
	size_t i = 0;
	size_t res_count = 0;
	int *res_data = 0;
	
	for (; i < sizeof(data) / sizeof(int); ++i)
	{
		DLListInsert(dllist, DLListBegin(dllist), data + i);
	}
	
	res_data = DLListPopBack(dllist);
	
	TestInt("TestPopBack", __FILE__, __LINE__, 1, *res_data);

	res_count = DLListCount(dllist);
	
	TestSizeT("TestPopBack", __FILE__, __LINE__, 7, res_count);
	
	DLListDestroy(dllist);
}

void TestPushBack()
{
	dll_t *dllist = DLListCreate();
	int data[] = {1, 2, 3, 4, 5, 6, 7, 8};
	size_t i = 0;
	size_t res_count = 0;
	int extra_data = 9; 
	
	for (; i < sizeof(data) / sizeof(int); ++i)
	{
		DLListInsert(dllist, DLListBegin(dllist), data + i);
	}
	
	DLListPushBack(dllist, &extra_data);
	
	TestInt("TestPushBack", __FILE__, __LINE__, 9, 
	        *(int *)DLListGetData(DLListPrev(DLListEnd(dllist))));
	
	res_count = DLListCount(dllist);
	
	TestSizeT("TestPushBack", __FILE__, __LINE__, 9, res_count);
	
	DLListDestroy(dllist);
}


