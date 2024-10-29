
#include <stdio.h> /*printf*/

#include "fsa.h" /*fsa_t, FSAfunction declarations*/
#include "test_utility.h" /*Test functions*/

#define WORD_SIZE sizeof(void *)

static void FSASuggestSizeTest(void);
void FSAInitCountTest(void);
void FSAAllocTest(void);
void FSAFreeTest(void);
void FSAAllocFreeFullTest(void);


int main(void)
{
	
	FSASuggestSizeTest();
	FSAInitCountTest();
	FSAAllocTest();
	FSAFreeTest();
	FSAAllocFreeFullTest();
	
	
	
	Test();

	return 0;
}


void FSASuggestSizeTest(void)
{
	size_t block_size = 20;
	size_t block_count = 100;
	
	size_t res = block_size * block_count + WORD_SIZE;
	
	TestInt("FSASuggestSizeTest", __FILE__, __LINE__, res, FSASuggestSize(block_size,
			 block_count));

}


void FSAInitCountTest(void)
{
	char pool[100] = {0};
	fsa_t *fsa = FSAInit(pool, 8, 100);
	
	TestSizeT("FSAInitTest", __FILE__, __LINE__, 11, FSACountFree(fsa));
}


void FSAAllocTest(void)
{
	char pool[100] = {0};
	size_t block_size = 8;
	size_t pool_size = 100;
	fsa_t *fsa = FSAInit(pool, block_size, pool_size);
	double *block1 = NULL;
	double *block2 = NULL;
	double *block3 = NULL;
	size_t offset = 0;
	
	TestSizeT("FSAAllocTest", __FILE__, __LINE__, 11, FSACountFree(fsa));
	
	block1 = (double *)FSAAlloc(fsa);
	block2 = (double *)FSAAlloc(fsa);
	block3 = (double *)FSAAlloc(fsa);
	
	TestSizeT("FSAAllocTest", __FILE__, __LINE__, 8, FSACountFree(fsa));
	
	*block1 = 10.1;
	*block2 = 20.2;
	*block3 = 30.3;
	
	TestDouble("FSAAllocTest", __FILE__, __LINE__, 10.1, *block1);
	TestDouble("FSAAllocTest", __FILE__, __LINE__, 20.2, *block2);
	TestDouble("FSAAllocTest", __FILE__, __LINE__, 30.3, *block3);
	
	offset = (size_t)block1 % WORD_SIZE;
	
	TestSizeT("FSAAllocTest", __FILE__, __LINE__, 0, offset);
	
	offset = (size_t)block2 % WORD_SIZE;
	
	TestSizeT("FSAAllocTest", __FILE__, __LINE__, 0, offset);
	
	offset = (size_t)block3 % WORD_SIZE;
	
	TestSizeT("FSAAllocTest", __FILE__, __LINE__, 0, offset);
}


void FSAFreeTest(void)
{
	char pool[100] = {0};
	size_t block_size = 8;
	size_t block_count = 100;
	fsa_t *fsa = FSAInit(pool, block_size, block_count);
	double *block1 = NULL;
	double *block2 = NULL;
	double *block3 = NULL;
	double *block4 = NULL;
	
	TestSizeT("FSAFreeTest", __FILE__, __LINE__, 11, FSACountFree(fsa));
	
	block1 = (double *)FSAAlloc(fsa);
	block2 = (double *)FSAAlloc(fsa);
	block3 = (double *)FSAAlloc(fsa);
	block4 = (double *)FSAAlloc(fsa);
	
	TestSizeT("FSAFreeTest", __FILE__, __LINE__, 7, FSACountFree(fsa));
	
	*block1 = 10.1;
	*block2 = 20.2;
	*block3 = 30.3;
	*block4 = 40.4;
	
	TestDouble("FSAFreeTest", __FILE__, __LINE__, 10.1, *block1);
	TestDouble("FSAFreeTest", __FILE__, __LINE__, 20.2, *block2);
	TestDouble("FSAFreeTest", __FILE__, __LINE__, 30.3, *block3);
	TestDouble("FSAFreeTest", __FILE__, __LINE__, 40.4, *block4);
	
	FSAFree(fsa, block1);
	FSAFree(fsa, block2);
	FSAFree(fsa, block3);
	FSAFree(fsa, block4);
	
	TestSizeT("FSAFreeTest", __FILE__, __LINE__, 11, FSACountFree(fsa));
}


void FSAAllocFreeFullTest(void)
{
	char pool[100] = {0};
	size_t block_size = 8;
	size_t block_count = 100;
	fsa_t *fsa = FSAInit(pool, block_size, block_count);
	double *block1 = NULL;
	double *block2 = NULL;
	double *block3 = NULL;
	double *block4 = NULL;
	double *block5 = NULL;
	double *block6 = NULL;
	double *block7 = NULL;
	double *block8 = NULL;
	double *block9 = NULL;
	double *block10 = NULL;
	double *block11 = NULL;
	
	TestSizeT("FSAFreeTest", __FILE__, __LINE__, 11, FSACountFree(fsa));
	
	block1 = (double *)FSAAlloc(fsa);
	block2 = (double *)FSAAlloc(fsa);
	block3 = (double *)FSAAlloc(fsa);
	block4 = (double *)FSAAlloc(fsa);
	block5 = (double *)FSAAlloc(fsa);
	block6 = (double *)FSAAlloc(fsa);
	block7 = (double *)FSAAlloc(fsa);
	block8 = (double *)FSAAlloc(fsa);
	block9 = (double *)FSAAlloc(fsa);
	block10 = (double *)FSAAlloc(fsa);
	block11 = (double *)FSAAlloc(fsa);
	
	TestSizeT("FSAFreeTest", __FILE__, __LINE__, 0, FSACountFree(fsa));
	
	*block1 = 10.1;
	*block2 = 20.2;
	*block3 = 30.3;
	*block4 = 40.4;
	*block5 = 50.5;
	*block6 = 60.6;
	*block7 = 70.7;
	*block8 = 80.8;
	*block9 = 90.9;
	*block10 = 100.0;
	*block11 = 110.0;
	
	TestDouble("FSAFreeTest", __FILE__, __LINE__, 10.1, *block1);
	TestDouble("FSAFreeTest", __FILE__, __LINE__, 20.2, *block2);
	TestDouble("FSAFreeTest", __FILE__, __LINE__, 30.3, *block3);
	TestDouble("FSAFreeTest", __FILE__, __LINE__, 40.4, *block4);
	TestDouble("FSAFreeTest", __FILE__, __LINE__, 50.5, *block5);
	TestDouble("FSAFreeTest", __FILE__, __LINE__, 60.6, *block6);
	TestDouble("FSAFreeTest", __FILE__, __LINE__, 70.7, *block7);
	TestDouble("FSAFreeTest", __FILE__, __LINE__, 80.8, *block8);
	TestDouble("FSAFreeTest", __FILE__, __LINE__, 90.9, *block9);
	TestDouble("FSAFreeTest", __FILE__, __LINE__, 100.0, *block10);
	TestDouble("FSAFreeTest", __FILE__, __LINE__, 110.0, *block11);
	
	FSAFree(fsa, block1);
	FSAFree(fsa, block2);
	FSAFree(fsa, block3);
	FSAFree(fsa, block4);
	FSAFree(fsa, block5);
	FSAFree(fsa, block6);
	FSAFree(fsa, block7);
	FSAFree(fsa, block8);
	FSAFree(fsa, block9);
	FSAFree(fsa, block10);
	FSAFree(fsa, block11);
	
	TestSizeT("FSAFreeTest", __FILE__, __LINE__, 11, FSACountFree(fsa));
	
	block1 = (double *)FSAAlloc(fsa);
	block2 = (double *)FSAAlloc(fsa);
	block3 = (double *)FSAAlloc(fsa);
	block4 = (double *)FSAAlloc(fsa);
	block5 = (double *)FSAAlloc(fsa);
	block6 = (double *)FSAAlloc(fsa);
	block7 = (double *)FSAAlloc(fsa);
	block8 = (double *)FSAAlloc(fsa);
	block9 = (double *)FSAAlloc(fsa);
	block10 = (double *)FSAAlloc(fsa);
	block11 = (double *)FSAAlloc(fsa);
	
	TestSizeT("FSAFreeTest", __FILE__, __LINE__, 0, FSACountFree(fsa));
	
	*block1 = 10.1;
	*block2 = 20.2;
	*block3 = 30.3;
	*block4 = 40.4;
	*block5 = 50.5;
	*block6 = 60.6;
	*block7 = 70.7;
	*block8 = 80.8;
	*block9 = 90.9;
	*block10 = 100.0;
	*block11 = 110.0;
	
	TestDouble("FSAFreeTest", __FILE__, __LINE__, 10.1, *block1);
	TestDouble("FSAFreeTest", __FILE__, __LINE__, 20.2, *block2);
	TestDouble("FSAFreeTest", __FILE__, __LINE__, 30.3, *block3);
	TestDouble("FSAFreeTest", __FILE__, __LINE__, 40.4, *block4);
	TestDouble("FSAFreeTest", __FILE__, __LINE__, 50.5, *block5);
	TestDouble("FSAFreeTest", __FILE__, __LINE__, 60.6, *block6);
	TestDouble("FSAFreeTest", __FILE__, __LINE__, 70.7, *block7);
	TestDouble("FSAFreeTest", __FILE__, __LINE__, 80.8, *block8);
	TestDouble("FSAFreeTest", __FILE__, __LINE__, 90.9, *block9);
	TestDouble("FSAFreeTest", __FILE__, __LINE__, 100.0, *block10);
	TestDouble("FSAFreeTest", __FILE__, __LINE__, 110.0, *block11);
}


