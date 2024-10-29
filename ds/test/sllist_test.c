

#include <stdio.h> /*printf */
#include <assert.h> /*assert */

#include "sllist.h" /*types, function declarations*/


static int DoubleData(void *data ,void *input_data);
static int CompFunc(void *data1, void *data2);



int main(void)
{
	linked_list_t *sllist = NULL;
	iterator_t iter1 = NULL;
	iterator_t iter2 = NULL;
	iterator_t iter3 = NULL;
	iterator_t iter4 = NULL;
	iterator_t find_iter = NULL;
	int data1 = 10;
	int data2 = 20;
	int data3 = 30;
	int data4 = 40;
	
	
	sllist = SLListCreate();
	
	assert(1 == SLListIsEmpty(sllist));
	
	
	
	/* 1 -> d */
	/* iter1 = 1 */
	iter1 = SLListGetBegin(sllist);
	iter1 = SLListInsert(sllist, &data1, iter1);
	assert(SLListGetEnd(sllist) != iter1);

	
	/* 2 -> 1 -> d */
	/* iter1 = iter2 = 2 */
	iter2 = SLListGetBegin(sllist);
	iter2 = SLListInsert(sllist, &data2, iter2);
	assert(SLListGetEnd(sllist) != iter2);

	
	/* 3 -> 2 -> 1 -> d */
	/* iter1 = iter2 = iter3 = 3 */
	iter3 = SLListGetBegin(sllist);
	iter3 = SLListInsert(sllist, &data3, iter3);
	assert(SLListGetEnd(sllist) != iter3);

	
	/* 4 -> 3 -> 2 -> 1 */
	/* iter1 = iter2 = iter3 = iter4 = 4 */
	iter4 = SLListGetBegin(sllist);
	iter4 = SLListInsert(sllist, &data4, iter4);
	assert(SLListGetEnd(sllist) != iter4);

	
	
	assert(1 == SLListIsEqual(iter1, iter1));
	
	
	
	iter1 = SLListNext(iter1);
	iter1 = SLListNext(iter1);
	iter1 = SLListNext(iter1);
	
	iter2 = SLListNext(iter2);
	iter2 = SLListNext(iter2);
	
	iter3 = SLListNext(iter3);

	
	assert(10 == *(int *)SLListGetData(iter1));
	assert(20 == *(int *)SLListGetData(iter2));
	assert(30 == *(int *)SLListGetData(iter3));
	assert(40 == *(int *)SLListGetData(iter4));

	
	/*Get check + Next check*/
	assert(data1 == *(int *)SLListGetData(iter1));
	assert(data2 == *(int *)SLListGetData(iter2));
	assert(data3 == *(int *)SLListGetData(iter3));
	assert(data4 == *(int *)SLListGetData(iter4));
	
	
	SLListForEach(SLListGetBegin(sllist), SLListGetEnd(sllist), &DoubleData, NULL);
	
	assert(20 == *(int *)SLListGetData(iter1));
	assert(40 == *(int *)SLListGetData(iter2));
	assert(60 == *(int *)SLListGetData(iter3));
	assert(80 == *(int *)SLListGetData(iter4));
	
	assert(data1 == *(int *)SLListGetData(iter1));
	assert(data2 == *(int *)SLListGetData(iter2));
	assert(data3 == *(int *)SLListGetData(iter3));
	assert(data4 == *(int *)SLListGetData(iter4));
	
	
	find_iter = SLListFind(SLListGetBegin(sllist), SLListGetEnd(sllist), &data1, &CompFunc);
	assert(find_iter == iter1);
	
	assert(4 == SLListCount(sllist));

	SLListRemove(iter1);
	
	assert(3 == SLListCount(sllist));
	
	assert(0 == SLListIsEqual(iter1, iter2));
	assert(1 == SLListIsEqual(iter1, iter1));
	
	assert(0 == SLListIsEmpty(sllist));
	
	SLListDestroy(sllist);
	 
	printf("All test passed!\n");
	return 0;
}



static int DoubleData(void *data ,void *input_data)
{
	(void)input_data;
	*((int *)data) *= 2;
	
	return 1;
}


static int CompFunc(void *data1, void *data2)
{
	return data1 == data2;
}




















