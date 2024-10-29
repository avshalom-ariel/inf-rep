#include "dvector.h" /*vector_t and all functions, GROWTH_FACTOR DECREASE_FACTOR*/
#include <assert.h> /*assert*/
#include <stdio.h> /*printf*/


int main(void)
{

	int var1 = 1;
	int var2 = 2;
	int var3 = 3;
	int var4 = 4;
	int var5 = 5;
	int var6 = 6;
	int var7 = 7;
	
	vector_t *vector = VectorCreate(4, sizeof(int));
	assert(NULL != vector);
	assert(4 == VectorCapacity(vector));
	assert(0 == VectorElementCount(vector));
	
	
	VectorPushBack(vector, &var1);
	assert(4 == VectorCapacity(vector));
	assert(1 == VectorElementCount(vector));
	
	VectorPushBack(vector, &var2);
	assert(4 == VectorCapacity(vector));
	assert(2 == VectorElementCount(vector));

	
	VectorPushBack(vector, &var3);
	assert(3 == VectorElementCount(vector));
	assert(4 == VectorCapacity(vector));
		
	VectorPushBack(vector, &var4);
	assert(4 == VectorElementCount(vector));
	assert(4 == VectorCapacity(vector));	
	
	
	
	VectorPushBack(vector, &var5);
	assert(5 == VectorElementCount(vector));
	assert(8 == VectorCapacity(vector));	
	
	
	VectorPopBack(vector);
	assert(4 == VectorElementCount(vector));
	assert(4 == VectorCapacity(vector));
	
	
	VectorPushBack(vector, &var6);
	assert(5 == VectorElementCount(vector));
	assert(8 == VectorCapacity(vector));	
	
	
	VectorShrink(vector);
	assert(5 == VectorElementCount(vector));
	assert(5 == VectorCapacity(vector));	
	
	
	VectorReserve(vector, 1);
	assert(5 == VectorElementCount(vector));
	assert(6 == VectorCapacity(vector));
	
	
	VectorPushBack(vector, &var6);
	assert(6 == VectorElementCount(vector));
	assert(6 == VectorCapacity(vector));	
	
	
	VectorPushBack(vector, &var7);
	assert(7 == VectorElementCount(vector));
	assert(12 == VectorCapacity(vector));
	
	
	assert(var2 == *((int *)(VectorAccessVal(vector, 2))));
	
	*((int *)(VectorAccessVal(vector, 2))) = 20;
	
	assert(20 == *((int *)(VectorAccessVal(vector, 2))));
	
	VectorDestroy(vector);
	
	printf("All tests passed!\n");
	
	return 0;
}























