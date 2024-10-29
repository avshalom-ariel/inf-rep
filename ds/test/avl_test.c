
#include <stdio.h> /*printf*/

#include "avl.h" /*avl_t, AVLFunction declarations*/
#include "test_utility.h" /*test functions*/

static void AVLCreateDestroyTest(void);
static void AVLInsertTest(void);
static void AVLIsEmptyTest(void);
static void AVLCountInsertTest(void);
static void AVLFindTest(void);
static void AVLForEachTest(void);
static void AVLHeightTest(void);
static void AVLCountInsertRemoveTest(void);


static int CompInt(const void *num1, const void *num2);
static int MultipleInt(void *data, void *multi_factor);

int main(void)
{
	AVLCreateDestroyTest();
	AVLInsertTest();
	AVLIsEmptyTest();
	AVLCountInsertTest();
	AVLFindTest();
	AVLForEachTest();
	AVLHeightTest();
	AVLCountInsertRemoveTest();
	
	
	
	Test();

	return 0;
}


/********** Test Functions ************/


void AVLCreateDestroyTest(void)
{
	avl_t *avl = AVLCreate(CompInt);
	
	AVLDestroy(avl);
}


void AVLIsEmptyTest(void)
{
	avl_t *avl = AVLCreate(CompInt);
	int data = 1;
	
	TestInt("AVLIsEmptyTest", __FILE__, __LINE__, 1, AVLIsEmpty(avl));
	
	AVLInsert(avl, &data);
	
	TestInt("AVLIsEmptyTest", __FILE__, __LINE__, 0, AVLIsEmpty(avl));
	
	AVLDestroy(avl);
}


void AVLInsertTest(void)
{
	avl_t *avl = AVLCreate(CompInt);
	int data[] = {7, 4, 6 ,8 ,3, 5, 2, 10, 20, 9, 1, 30, 25};
	size_t i = 0;
	
	for (; i < sizeof(data) / sizeof(int); ++i)
	{
		AVLInsert(avl, data + i);
	}
	
	AVLDestroy(avl);
}


void AVLCountInsertTest(void)
{
	avl_t *avl = AVLCreate(CompInt);
	int data[] = {7, 4, 6 ,8 ,3, 5, 2, 10, 20, 9, 1, 30, 25};
	size_t i = 0;
	
	TestInt("AVLCountTest", __FILE__, __LINE__, 0, AVLCount(avl));
	
	for (; i < sizeof(data) / sizeof(int); ++i)
	{
		TestInt("AVLCountTest", __FILE__, __LINE__, i, AVLCount(avl));
		AVLInsert(avl, data + i);
	}
	
	TestInt("AVLCountTest", __FILE__, __LINE__, 13, AVLCount(avl));
	
	AVLDestroy(avl);
}


void AVLFindTest(void)
{
	avl_t *avl = AVLCreate(CompInt);
	int data[] = {7, 4, 6 ,8 ,3, 5, 2, 10, 20, 9, 1, 30, 25};
	int not_in = 1000;
	size_t i = 0;
	
	for (; i < sizeof(data) / sizeof(int); ++i)
	{
		TestInt("AVLFindTest", __FILE__, __LINE__, 1, NULL == AVLFind(avl, data + i));
		AVLInsert(avl, data + i);
		TestInt("AVLFindTest", __FILE__, __LINE__, *(int *)(data + i), *(int *)AVLFind(avl, 
				data + i));
	}
	
	TestInt("AVLFindTest", __FILE__, __LINE__, *(int *)(data + 5), *(int *)AVLFind(avl, data + 5));
	
	TestInt("AVLFindTest", __FILE__, __LINE__, 1, NULL == AVLFind(avl, &not_in));
	
	
	AVLDestroy(avl);
}


void AVLCountInsertRemoveTest(void)
{
	avl_t *avl = AVLCreate(CompInt);
	int data[] = {7, 4, 6 ,8 ,3, 5, 2, 10, 20, 9, 1, 30, 25};
	size_t i = 0;
	
	for (; i < sizeof(data) / sizeof(int); ++i)
	{
		AVLInsert(avl, data + i);
	}
	
	TestInt("AVLCountTest", __FILE__, __LINE__, 13, AVLCount(avl));
	TestInt("AVLFindTest", __FILE__, __LINE__, *(int *)(data + 2), *(int *)AVLFind(avl, data + 2));
	
	AVLRemove(avl, data + 2);

	TestInt("AVLCountTest", __FILE__, __LINE__, 12, AVLCount(avl));
	TestInt("AVLFindTest", __FILE__, __LINE__, 1, NULL == AVLFind(avl, data + 2));
	TestInt("AVLFindTest", __FILE__, __LINE__, *(int *)(data + 5), *(int *)AVLFind(avl, data + 5));
	
	AVLRemove(avl, data + 5);

	TestInt("AVLCountTest", __FILE__, __LINE__, 11, AVLCount(avl));
	TestInt("AVLFindTest", __FILE__, __LINE__, 1, NULL == AVLFind(avl, data + 5));
	TestInt("AVLFindTest", __FILE__, __LINE__, *(int *)(data + 9), *(int *)AVLFind(avl, data + 9));
	
	AVLRemove(avl, data + 9);

	TestInt("AVLCountTest", __FILE__, __LINE__, 10, AVLCount(avl));
	TestInt("AVLFindTest", __FILE__, __LINE__, 1, NULL == AVLFind(avl, data + 9));
	TestInt("AVLFindTest", __FILE__, __LINE__, *(int *)(data + 0), *(int *)AVLFind(avl, data + 0));
	
	AVLRemove(avl, data + 0);

	TestInt("AVLCountTest", __FILE__, __LINE__, 9, AVLCount(avl));
	TestInt("AVLFindTest", __FILE__, __LINE__, 1, NULL == AVLFind(avl, data + 0));
	TestInt("AVLFindTest", __FILE__, __LINE__, *(int *)(data + 4), *(int *)AVLFind(avl, data + 4));
	
	AVLRemove(avl, data + 4);

	TestInt("AVLCountTest", __FILE__, __LINE__, 8, AVLCount(avl));
	TestInt("AVLFindTest", __FILE__, __LINE__, 1, NULL == AVLFind(avl, data + 4));
	TestInt("AVLFindTest", __FILE__, __LINE__, *(int *)(data + 12), *(int *)AVLFind(avl, data + 12));
	
	AVLRemove(avl, data + 12);

	TestInt("AVLCountTest", __FILE__, __LINE__, 7, AVLCount(avl));
	TestInt("AVLFindTest", __FILE__, __LINE__, 1, NULL == AVLFind(avl, data + 12));
	
	AVLDestroy(avl);
}


void AVLForEachTest(void)
{
	avl_t *avl = AVLCreate(CompInt);
	int data[] = {7, 4, 6 ,8 ,3, 5, 2, 10, 20, 9, 1, 30, 25};
	int multi_factor = 10;
	size_t i = 0;
	
	for (; i < sizeof(data) / sizeof(int); ++i)
	{
		TestInt("AVLForEachTest", __FILE__, __LINE__, i, AVLCount(avl));
		AVLInsert(avl, data + i);
	}
	
	AVLForEach(avl, MultipleInt, &multi_factor);
	
	for (i = 0; i < sizeof(data) / sizeof(int); ++i)
	{
		TestInt("AVLForEachTest", __FILE__, __LINE__, 0, NULL == AVLFind(avl, data + i));
		TestInt("AVLForEachTest", __FILE__, __LINE__, *(int *)(data + i), 
				*(int *)AVLFind(avl, data + i));
	}
	
	AVLDestroy(avl);
}


void AVLHeightTest(void)
{
	avl_t *avl = AVLCreate(CompInt);
	int data[] = {7, 4, 6 ,8 ,3, 5, 2, 10, 20, 9, 1, 30, 25};
	size_t i = 0;

	TestInt("AVLForEachTest", __FILE__, __LINE__, 0, AVLHeight(avl));
	
	for (; i < sizeof(data) / sizeof(int); ++i)
	{
		TestInt("AVLForEachTest", __FILE__, __LINE__, i, AVLCount(avl));
		AVLInsert(avl, data + i);
	}

	TestInt("AVLForEachTest", __FILE__, __LINE__, 4, AVLHeight(avl));
	
	AVLDestroy(avl);
}


/* Debug Commands

p *(int *)parent->data
p *(int *)child->data
p *(int *)node->data
p *(int *)avl->root->data
p *(int *)avl->root->height
p node->height
p child->height
p parent->height
p *(int *)data

p parent->childs[1]->height

p node->childs[1]->height
p node->childs[0]->height

p *(int *)avl->root->childs[0]->data
p *(int *)avl->root->childs[1]->data
p *(int *)avl->root->childs[0]->childs[0]->data
p *(int *)avl->root->childs[0]->childs[0]->childs[0]->data

p avl->root->childs[0]->height
p avl->root->childs[1]->height
p avl->root->childs[0]->childs[0]->height
p avl->root->childs[0]->childs[0]->childs[0]->height

p *(int *)node->data
p *(int *)node->childs[0]->data
p *(int *)node->childs[1]->data
p *(int *)node->childs[0]->childs[1]->data



p *(int *)parent->data
p *(int *)parent->childs[0]->data
p *(int *)parent->childs[1]->data
p *(int *)parent->childs[0]->childs[1]->data




p *(int *)child->data
p *(int *)child->childs[0]->data
p *(int *)child->childs[1]->data
p *(int *)child->childs[0]->childs[1]->data


p *(int *)root->data
p *(int *)root->childs[0]->data
p *(int *)root->childs[1]->data
p *(int *)root->childs[0]->childs[1]->data




b avl.c: 101
*/





/********** Help Functions ************/

int CompInt(const void *num1, const void *num2)
{
	return *(int *)num1 - *(int *)num2;
}


int MultipleInt(void *data, void *multi_factor)
{
	*(int *)data *= *(int *)multi_factor;
	
	return 0;
}


