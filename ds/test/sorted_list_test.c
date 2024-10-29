


#include "sorted_list.h"
#include "test_utility.h" /*Test functions*/

static int cmp_func(const void *data1, const void *data2);

static int match_func(const void *data1, const void *data2);

static int MultiTenToData(void *data ,void *input_data);

void TestIsEmpty();
void TestIsEqual();
void TestGetData();
void TestCount();
void TestNext();
void TestPrev();
void TestGetBegin();
void TestRemove();
void TestFind();
void TestFindIf();
void TestPopFront();
void TestPopBack();
void TestForEach();
void TestMerge();


int main(void)
{
	
	TestIsEmpty();
	TestIsEqual();
	TestGetData();
	TestCount();
	TestNext();
	TestPrev();
	TestGetBegin();
	TestRemove();
	TestFind();
	TestFindIf();
	TestPopFront();
	TestPopBack();
	TestForEach();
	TestMerge();
	
	Test();
	
	return 0;
}


void TestIsEmpty()
{
	slist_t *list = SListCreate(cmp_func);

	int res = SListIsEmpty(list);
		
	TestInt("TestIsEmpty", __FILE__, __LINE__, 1, res);
	
	SListDestroy(list);

}


void TestIsEqual()
{
	slist_t *list = SListCreate(cmp_func);
	
	int res = SListIsEqualIter(SListBegin(list), SListEnd(list));
	
	TestInt("TestIsEqual", __FILE__, __LINE__, 1, res);
	
	SListDestroy(list);
}


void TestGetData()
{
	slist_t *list = SListCreate(cmp_func);
	int data = 7;
	int *res_data = NULL;
	
	res_data = SListGetData(SListInsert(list, &data));
	
	TestInt("TestGetData", __FILE__, __LINE__, data, *res_data);
	
	SListDestroy(list);
}


void TestCount()
{
	slist_t *list = SListCreate(cmp_func);
	int data1 = 1;
	int data2 = 5;
	int data3 = 3;
	int data4 = 4;

	size_t res = 0;
	
	SListInsert(list, &data1);
	SListInsert(list, &data2);
	SListInsert(list, &data3);
	SListInsert(list, &data4);
	
	res = SListCount(list);
	
	TestSizeT("TestCount", __FILE__, __LINE__, 4, res);
	
	SListDestroy(list);
}



void TestNext()
{
	slist_t *list = SListCreate(cmp_func);
	int data1 = 1;
	int data2 = 2;
	slist_iterator_t res = {0};
	
	res = SListInsert(list, &data1);
	SListInsert(list, &data2);
		
	TestInt("TestNext", __FILE__, __LINE__, data1, *(int *)SListGetData(res));
	
	res = SListNext(res);
	
	TestInt("TestNext", __FILE__, __LINE__, data2, *(int *)SListGetData(res));
	
	SListDestroy(list);
}


void TestPrev()
{
	slist_t *list = SListCreate(cmp_func);
	int data1 = 1;
	int data2 = 2;
	slist_iterator_t res = {0};

	SListInsert(list, &data1);
	res = SListInsert(list, &data2);
	
	
	TestInt("TestPrev", __FILE__, __LINE__, data1, *(int *)SListGetData(SListPrev(res)));
	
	SListDestroy(list);
}


void TestGetBegin()
{
	slist_t *list = SListCreate(cmp_func);
	int data[] = {1, 2, 3, 4, 5, 6, 7, 8};
	size_t i = 0;
	slist_iterator_t head = {0};
	int *res_data = NULL;
	
	for (; i < sizeof(data) / sizeof(int); ++i)
	{
		SListInsert(list, data + i);
	}
	
	head = SListBegin(list);
	res_data = SListGetData(head);
	
	TestInt("TestGetBegin", __FILE__, __LINE__, data[0], *res_data);
	
	SListDestroy(list);
}


void TestRemove()
{
	slist_t *list = SListCreate(cmp_func);
	int data[] = {1, 2, 3, 4, 5, 6, 7, 8};
	size_t i = 0;
	slist_iterator_t head = {0};
	int *res_data = NULL;
	size_t count = 0;
	
	for (; i < sizeof(data) / sizeof(int); ++i)
	{
		SListInsert(list, data + i);
	}
	
	SListRemove(SListBegin(list));
	count += 1;
	
	head = SListBegin(list);
	res_data = SListGetData(head);
	
	TestInt("TestRemove", __FILE__, __LINE__, data[count], *res_data);
	
	SListDestroy(list);
}


void TestFind()
{
	slist_t *list = SListCreate(cmp_func);
	int data[] = {1, 2, 3, 4, 5, 6, 7, 8};
	size_t i = 0;
	slist_iterator_t res = {0};
	int *res_data = NULL;
	
	for (; i < sizeof(data) / sizeof(int); ++i)
	{
		SListInsert(list, data + i);
	}
	
	res = SListFind(list, SListBegin(list), SListEnd(list), data + 4);
	res_data = SListGetData(res);
	 
	TestInt("TestFind", __FILE__, __LINE__, *(data + 4), *res_data); 
	
	SListDestroy(list);
}


void TestFindIf()
{
	slist_t *list = SListCreate(cmp_func);
	int data[] = {1, 2, 3, 4, 5, 6, 7, 8};
	size_t i = 0;
	slist_iterator_t res = {0};
	int *res_data = NULL;
	
	for (; i < sizeof(data) / sizeof(int); ++i)
	{
		SListInsert(list, data + i);
	}
	
	res = SListFindIf(SListBegin(list), SListEnd(list), data + 4, match_func);
	res_data = SListGetData(res);
	 
	TestInt("TestFindIf", __FILE__, __LINE__, *(data + 4), *res_data); 
	
	SListDestroy(list);
}


void TestPopFront()
{
	slist_t *list = SListCreate(cmp_func);
	int data[] = {1, 2, 3, 4, 5, 6, 7, 8};
	size_t i = 0;
	size_t res_count = 0;
	int *res_data = 0; 
	
	for (; i < sizeof(data) / sizeof(int); ++i)
	{
		SListInsert(list, data + i);
	}
	
	res_data = SListPopFront(list);
	
	TestInt("TestPopFront", __FILE__, __LINE__, 1, *res_data);
	
	res_count = SListCount(list);
	
	TestSizeT("TestPopFront", __FILE__, __LINE__, 7, res_count);
	
	SListDestroy(list);
}


void TestPopBack()
{
	slist_t *list = SListCreate(cmp_func);
	int data[] = {1, 2, 3, 4, 5, 6, 7, 8};
	size_t i = 0;
	size_t res_count = 0;
	int *res_data = 0;
	
	for (; i < sizeof(data) / sizeof(int); ++i)
	{
		SListInsert(list, data + i);
	}
	
	res_data = SListPopBack(list);
	
	TestInt("TestPopBack", __FILE__, __LINE__, 8, *res_data);
	
	res_count = SListCount(list);
	
	TestSizeT("TestPopBack", __FILE__, __LINE__, 7, res_count);
	
	SListDestroy(list);
}


void TestForEach()
{
	slist_t *list = SListCreate(cmp_func);
	int data[] = {1, 2, 3, 4, 5, 6, 7, 8};
	int comp_data[] = {10, 20, 30, 40, 50, 60, 70, 80};
	size_t i = 0;
	slist_iterator_t res = {0};
	int *res_data = NULL;
	
	for (; i < sizeof(data) / sizeof(int); ++i)
	{
		SListInsert(list, data + i);
	}
	
	SDLListForeach(SListBegin(list), SListEnd(list), NULL,
	              MultiTenToData);

	for (i = 0, res = SListBegin(list); i < sizeof(data) / sizeof(int);
	     ++i, res = SListNext(res))
	{
		res_data = SListGetData(res);
		
		TestInt("TestForEach", __FILE__, __LINE__, comp_data[i], *res_data);
	}
	
	SListDestroy(list);
}


void TestMerge()
{
	slist_t *list1 = SListCreate(cmp_func);
	slist_t *list2 = SListCreate(cmp_func);
	int data1[] = {1, 20, 3, 40, 5, 60, 7, 80};
	int data2[] = {10, 2, 30, 4, 50, 6, 70, 8};
	int result[] = {1, 2, 3, 4, 5, 6, 7, 8, 10, 20, 30, 40, 50, 60, 70, 80};
	size_t i = 0;
	slist_iterator_t res = {0};
	int *res_data = NULL;
	
	for (; i < sizeof(data1) / sizeof(int); ++i)
	{
		SListInsert(list1, data1 + i);
		SListInsert(list2, data2 + i);
	}
	
	SDLListMerge(list1, list2);
	
	for (i = 0, res = SListBegin(list1); i < sizeof(result) / sizeof(int);
	     ++i, res = SListNext(res))
	{
		res_data = SListGetData(res);
		
		TestInt("TestMerge", __FILE__, __LINE__, result[i], *res_data);
	}
	
	SListDestroy(list1);
	SListDestroy(list2);
}


int cmp_func(const void *data1, const void *data2)
{
	return (*(int *)data1 - *(int *)data2);
}


int match_func(const void *data1, const void *data2)
{
	return (data1 == data2);
}

static int MultiTenToData(void *data ,void *input_data)
{
	(void)input_data;
	
	*((int *)data) *= 10;
	
	return 0;
}


/*static void PrintListInt(slist_t *list)
{
	slist_iterator_t runner = SListBegin(list);
	
	while(!(SListIsEqualIter(runner, SListEnd(list))))
	{
		printf("%d ", *(int *)SListGetData(runner));
		
		runner = SListNext(runner);
	}
	
	printf("\n");
}*/

