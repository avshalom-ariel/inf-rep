
#include <stdio.h> /*printf*/

#include "sllist.h"


iterator_t FindNElementFromEnd(linked_list_t *sll, size_t n);


int main(void)
{
	int data1 = 10;
	int data2 = 20;
	int data3 = 30;
	int data4 = 40;
	
	iterator_t iter = NULL;
	
	linked_list_t *sllist = SLListCreate();
	
	SLListInsert(sllist, &data4, SLListGetBegin(sllist));
	SLListInsert(sllist, &data3, SLListGetBegin(sllist));
	SLListInsert(sllist, &data2, SLListGetBegin(sllist));
	SLListInsert(sllist, &data1, SLListGetBegin(sllist));
	
	iter = FindNElementFromEnd(sllist, 1);
	
	printf("%d\n", *(int *)SLListGetData(iter));

	return 0;
}



iterator_t FindNElementFromEnd(linked_list_t *sll, size_t n)
{
	size_t count = 0;
	iterator_t runner = SLListGetBegin(sll);
	iterator_t result = SLListGetBegin(sll);
	
	while(!SLListIsEqual(runner, SLListGetEnd(sll)))
	{
		runner = SLListNext(runner);
		
		if(count > n)
		{
			result = SLListNext(result);
		}
		
		++count;
	}
	
	return result;
}






