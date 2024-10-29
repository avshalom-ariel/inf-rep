
#include <stdio.h> /*printf*/

#include "bst.h" /*BST Structs and BST Function declaration*/
#include "test_utility.h" /*Test function declarations*/

static int IntCmp(const void *data1, const void *data2);
static int MultipleIntTree(void *iter_data, void *multi_val);

static void BSTInsertSizeTest(void);
static void BSTRemoveSizeTest(void);
static void BSTIsEmptyTest(void);
static void BSTIsEmptyTest(void);
static void BSTBeginEndGetDataTest(void);
static void BSTIsSameIterTest(void);
static void BSTPrevNextTest(void);
static void BSTFindTest(void);
void BSTForEachTest(void);


int main(void)
{
	BSTInsertSizeTest();
	BSTRemoveSizeTest();
	BSTIsEmptyTest();
	BSTIsEmptyTest();
	BSTBeginEndGetDataTest();
	BSTIsSameIterTest();
	BSTPrevNextTest();
	BSTFindTest();
	BSTForEachTest();

	Test();
	
	return 0;
}


/*********** Test Functions ************/


void BSTInsertSizeTest(void)
{
	bst_t *bst = NULL;
	int data1 = 1;
	int data2 = 2;
	int data3 = 3;
	int data4 = 4;
	int data5 = 5;
	int data6 = 6;
	
	bst = BSTCreate(IntCmp);

	TestSizeT("BSTInsertSizeTest", __FILE__, __LINE__, 0, BSTSize(bst));

	BSTInsert(bst, &data4);

	TestSizeT("BSTInsertSizeTest", __FILE__, __LINE__, 1, BSTSize(bst));
	
	BSTInsert(bst, &data2);
	
	TestSizeT("BSTInsertSizeTest", __FILE__, __LINE__, 2, BSTSize(bst));
	
	BSTInsert(bst, &data3);

	TestSizeT("BSTInsertSizeTest", __FILE__, __LINE__, 3, BSTSize(bst));

	BSTInsert(bst, &data1);

	TestSizeT("BSTInsertSizeTest", __FILE__, __LINE__, 4, BSTSize(bst));

	BSTInsert(bst, &data5);

	TestSizeT("BSTInsertSizeTest", __FILE__, __LINE__, 5, BSTSize(bst));

	BSTInsert(bst, &data6);

	TestSizeT("BSTInsertSizeTest", __FILE__, __LINE__, 6, BSTSize(bst));

	BSTDestroy(bst);
}


void BSTRemoveSizeTest(void)
{
	bst_t *bst = NULL;
	int data1 = 1;
	int data2 = 2;
	int data3 = 3;
	int data4 = 4;
	int data5 = 5;
	int data6 = 6;
	bst_iter_t iter1 = {0};
	bst_iter_t iter2 = {0};
	bst_iter_t iter3 = {0};
	bst_iter_t iter4 = {0};
	bst_iter_t iter5 = {0};
	bst_iter_t iter6 = {0};
	
	bst = BSTCreate(IntCmp);

	TestSizeT("BSTRemoveSizeTest", __FILE__, __LINE__, 0, BSTSize(bst));

	iter4 = BSTInsert(bst, &data4);

	TestSizeT("BSTRemoveSizeTest", __FILE__, __LINE__, 1, BSTSize(bst));
	
	iter2 = BSTInsert(bst, &data2);
	
	TestSizeT("BSTRemoveSizeTest", __FILE__, __LINE__, 2, BSTSize(bst));
	
	iter3 = BSTInsert(bst, &data3);

	TestSizeT("BSTRemoveSizeTest", __FILE__, __LINE__, 3, BSTSize(bst));

	iter1 = BSTInsert(bst, &data1);

	TestSizeT("BSTRemoveSizeTest", __FILE__, __LINE__, 4, BSTSize(bst));

	iter5 = BSTInsert(bst, &data5);

	TestSizeT("BSTRemoveSizeTest", __FILE__, __LINE__, 5, BSTSize(bst));

	iter6 = BSTInsert(bst, &data6);

	TestSizeT("BSTRemoveSizeTest", __FILE__, __LINE__, 6, BSTSize(bst));

	BSTRemove(iter1);

	TestSizeT("BSTRemoveSizeTest", __FILE__, __LINE__, 5, BSTSize(bst));

	BSTRemove(iter2);

	TestSizeT("BSTRemoveSizeTest", __FILE__, __LINE__, 4, BSTSize(bst));

	BSTRemove(iter3);

	TestSizeT("BSTRemoveSizeTest", __FILE__, __LINE__, 3, BSTSize(bst));

	BSTRemove(iter4);

	TestSizeT("BSTRemoveSizeTest", __FILE__, __LINE__, 2, BSTSize(bst));

	BSTRemove(iter5);

	TestSizeT("BSTRemoveSizeTest", __FILE__, __LINE__, 1, BSTSize(bst));
	
	BSTRemove(iter6);

	TestSizeT("BSTRemoveSizeTest", __FILE__, __LINE__, 0, BSTSize(bst));

	BSTDestroy(bst);
}


void BSTIsEmptyTest(void)
{
	bst_t *bst = NULL;
	int data1 = 1;
	int data2 = 2;
	bst_iter_t iter1 = {0};
	bst_iter_t iter2 = {0};
	
	bst = BSTCreate(IntCmp);
	
	TestInt("BSTIsEmptyTest", __FILE__, __LINE__, 1, BSTIsEmpty(bst));
	
	iter1 = BSTInsert(bst, &data1);
	iter2 = BSTInsert(bst, &data2);
	
	TestInt("BSTIsEmptyTest", __FILE__, __LINE__, 0, BSTIsEmpty(bst));
	
	BSTRemove(iter2);

	TestInt("BSTIsEmptyTest", __FILE__, __LINE__, 0, BSTIsEmpty(bst));

	BSTRemove(iter1);

	TestInt("BSTIsEmptyTest", __FILE__, __LINE__, 1, BSTIsEmpty(bst));
	
	BSTDestroy(bst);
}


void BSTBeginEndGetDataTest(void)
{
	bst_t *bst = NULL;
	int data1 = 1;
	int data2 = 2;
	int data3 = 3;
	int data4 = 4;
	bst_iter_t iter1 = {0};
	bst_iter_t iter2 = {0};
	bst_iter_t iter3 = {0};
	bst_iter_t iter4 = {0};
	
	bst = BSTCreate(IntCmp);

	TestSizeT("BSTBeginEndGetDataTest", __FILE__, __LINE__, 0, BSTSize(bst));

	iter4 = BSTInsert(bst, &data4);

	TestSizeT("BSTBeginEndGetDataTest", __FILE__, __LINE__, 1, BSTSize(bst));
	
	iter2 = BSTInsert(bst, &data2);
	
	TestSizeT("BSTBeginEndGetDataTest", __FILE__, __LINE__, 2, BSTSize(bst));
	
	iter3 = BSTInsert(bst, &data3);

	TestSizeT("BSTBeginEndGetDataTest", __FILE__, __LINE__, 3, BSTSize(bst));
	
	iter1 = BSTInsert(bst, &data1);

	TestSizeT("BSTBeginEndGetDataTest", __FILE__, __LINE__, 4, BSTSize(bst));

	TestInt("BSTBeginEndGetDataTest", __FILE__, __LINE__, 1, *(int *)BSTGetData(iter1));
	TestInt("BSTBeginEndGetDataTest", __FILE__, __LINE__, 2, *(int *)BSTGetData(iter2));
	TestInt("BSTBeginEndGetDataTest", __FILE__, __LINE__, 3, *(int *)BSTGetData(iter3));
	TestInt("BSTBeginEndGetDataTest", __FILE__, __LINE__, 4, *(int *)BSTGetData(iter4));
		
	TestInt("BSTBeginEndGetDataTest", __FILE__, __LINE__, 1, *(int *)BSTGetData(BSTBegin(bst)));
	
	BSTRemove(iter2);
	BSTRemove(iter1);
	
	TestInt("BSTBeginEndGetDataTest", __FILE__, __LINE__, 3, *(int *)BSTGetData(BSTBegin(bst)));

	BSTDestroy(bst);
}


void BSTIsSameIterTest(void)
{
	bst_t *bst = NULL;
	int data1 = 1;
	int data2 = 2;
	int data3 = 3;
	int data4 = 4;
	bst_iter_t iter1 = {0};
	bst_iter_t iter2 = {0};
	bst_iter_t iter3 = {0};
	bst_iter_t iter4 = {0};
	
	bst = BSTCreate(IntCmp);
	
	iter4 = BSTInsert(bst, &data4);
	iter2 = BSTInsert(bst, &data2);
	iter3 = BSTInsert(bst, &data3);
	iter1 = BSTInsert(bst, &data1);
		
	TestInt("BSTIsSameIterTest", __FILE__, __LINE__, 0, BSTIsSameIter(iter1, iter2));
	TestInt("BSTIsSameIterTest", __FILE__, __LINE__, 0, BSTIsSameIter(iter2, iter3));
	TestInt("BSTIsSameIterTest", __FILE__, __LINE__, 0, BSTIsSameIter(iter3, iter4));
	TestInt("BSTIsSameIterTest", __FILE__, __LINE__, 0, BSTIsSameIter(iter1, iter4));
	TestInt("BSTIsSameIterTest", __FILE__, __LINE__, 1, BSTIsSameIter(iter1, iter1));
	TestInt("BSTIsSameIterTest", __FILE__, __LINE__, 1, BSTIsSameIter(iter2, iter2));	
	TestInt("BSTIsSameIterTest", __FILE__, __LINE__, 1, BSTIsSameIter(iter3, iter3));	
	TestInt("BSTIsSameIterTest", __FILE__, __LINE__, 1, BSTIsSameIter(iter4, iter4));	
	
	BSTDestroy(bst);
}


void BSTPrevNextTest(void)
{
	bst_t *bst = NULL;
	int data1 = 1;
	int data2 = 2;
	int data3 = 3;
	int data4 = 4;
	bst_iter_t iter1 = {0};
	bst_iter_t iter2 = {0};
	bst_iter_t iter3 = {0};
	bst_iter_t iter4 = {0};
	
	bst = BSTCreate(IntCmp);
	
	iter4 = BSTInsert(bst, &data4);
	iter2 = BSTInsert(bst, &data2);
	iter3 = BSTInsert(bst, &data3);
	iter1 = BSTInsert(bst, &data1);
	
	TestInt("BSTIsSameIterTest", __FILE__, __LINE__, 1, BSTIsSameIter(BSTNext(iter1), iter2));
	TestInt("BSTIsSameIterTest", __FILE__, __LINE__, 1, BSTIsSameIter(iter2, BSTPrev(iter3)));
	TestInt("BSTIsSameIterTest", __FILE__, __LINE__, 1, BSTIsSameIter(BSTNext(iter2), BSTPrev(iter4)));
	TestInt("BSTIsSameIterTest", __FILE__, __LINE__, 0, BSTIsSameIter(BSTNext(BSTNext(iter1)), BSTPrev(BSTPrev(iter4))));
	TestInt("BSTIsSameIterTest", __FILE__, __LINE__, 1, BSTIsSameIter(iter1, iter1));
	TestInt("BSTIsSameIterTest", __FILE__, __LINE__, 1, BSTIsSameIter(iter2, iter2));	
	TestInt("BSTIsSameIterTest", __FILE__, __LINE__, 1, BSTIsSameIter(iter3, iter3));	
	TestInt("BSTIsSameIterTest", __FILE__, __LINE__, 1, BSTIsSameIter(iter4, iter4));


	BSTDestroy(bst);
}


void BSTFindTest(void)
{
	bst_t *bst = NULL;
	int data1 = 1;
	int data2 = 2;
	int data3 = 3;
	int data4 = 4;
	
	bst = BSTCreate(IntCmp);
	
	BSTInsert(bst, &data4);
	BSTInsert(bst, &data2);
	BSTInsert(bst, &data3);
	BSTInsert(bst, &data1);

	TestInt("BSTBeginEndGetDataTest", __FILE__, __LINE__, 1, *(int *)BSTGetData(BSTFind(bst, &data1)));
	TestInt("BSTBeginEndGetDataTest", __FILE__, __LINE__, 2, *(int *)BSTGetData(BSTFind(bst, &data2)));
	TestInt("BSTBeginEndGetDataTest", __FILE__, __LINE__, 3, *(int *)BSTGetData(BSTFind(bst, &data3)));
	TestInt("BSTBeginEndGetDataTest", __FILE__, __LINE__, 4, *(int *)BSTGetData(BSTFind(bst, &data4)));

	BSTDestroy(bst);
}


void BSTForEachTest(void)
{
	bst_t *bst = NULL;
	int data1 = 1;
	int data2 = 2;
	int data3 = 3;
	int data4 = 4;
	int multi_val = 10;
	bst_iter_t iter1 = {0};
	bst_iter_t iter2 = {0};
	bst_iter_t iter3 = {0};
	bst_iter_t iter4 = {0};
	
	bst = BSTCreate(IntCmp);
	
	iter4 = BSTInsert(bst, &data4);
	iter2 = BSTInsert(bst, &data2);
	iter3 = BSTInsert(bst, &data3);
	iter1 = BSTInsert(bst, &data1);
	
	TestInt("BSTBeginEndGetDataTest", __FILE__, __LINE__, 1, *(int *)BSTGetData(iter1));
	TestInt("BSTBeginEndGetDataTest", __FILE__, __LINE__, 2, *(int *)BSTGetData(iter2));
	TestInt("BSTBeginEndGetDataTest", __FILE__, __LINE__, 3, *(int *)BSTGetData(iter3));
	TestInt("BSTBeginEndGetDataTest", __FILE__, __LINE__, 4, *(int *)BSTGetData(iter4));
	
	BSTForEach(bst, MultipleIntTree, &multi_val);

	TestInt("BSTBeginEndGetDataTest", __FILE__, __LINE__, 10, *(int *)BSTGetData(iter1));
	TestInt("BSTBeginEndGetDataTest", __FILE__, __LINE__, 20, *(int *)BSTGetData(iter2));
	TestInt("BSTBeginEndGetDataTest", __FILE__, __LINE__, 30, *(int *)BSTGetData(iter3));
	TestInt("BSTBeginEndGetDataTest", __FILE__, __LINE__, 40, *(int *)BSTGetData(iter4));
	
	BSTForEach(bst, MultipleIntTree, &multi_val);

	TestInt("BSTBeginEndGetDataTest", __FILE__, __LINE__, 100, *(int *)BSTGetData(iter1));
	TestInt("BSTBeginEndGetDataTest", __FILE__, __LINE__, 200, *(int *)BSTGetData(iter2));
	TestInt("BSTBeginEndGetDataTest", __FILE__, __LINE__, 300, *(int *)BSTGetData(iter3));
	TestInt("BSTBeginEndGetDataTest", __FILE__, __LINE__, 400, *(int *)BSTGetData(iter4));

	BSTDestroy(bst);
}


/*********** Help Functions ************/


int IntCmp(const void *data1, const void *data2)
{
	return *(int *)data1 - *(int *)data2;
}


int MultipleIntTree(void *iter_data, void *multi_val)
{
	if(!iter_data)
	{
		return 1;
	}
	
	*(int *)iter_data *= *(int *)multi_val;
	
	return 0;
}


