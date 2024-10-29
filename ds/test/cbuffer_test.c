
#include <stdio.h> /*printf*/

#include "cbuffer.h" /*all cbuffer functions*/

void CBufferAvailableSpaceTest(void);
void CreateDestroyBufsizTest(void);
void ReadWriteTest(void);
void ReadWriteIsEmptyTest(void);
void ReadWriteAvailableSpaceTest(void);


int main(void)
{
	
	CBufferAvailableSpaceTest();
	CreateDestroyBufsizTest();
	ReadWriteTest();
	ReadWriteIsEmptyTest();
	ReadWriteAvailableSpaceTest();
	
	
	return 0;
}


void CBufferAvailableSpaceTest(void)
{
	
	cbuffer_t *cbuffer = CBufferCreate(10);
	
	if(10 != CBufferAvailableSpace(cbuffer))
	{
		printf("CBufferAvailableSpace Test failed!\n ");
		printf("Expected value: 10 , recived value: %ld\n",CBufferAvailableSpace(cbuffer));
	}
	
	CBufferDestroy(cbuffer);

}


void CreateDestroyBufsizTest(void)
{
	
	cbuffer_t *cbuffer = CBufferCreate(10);
	
	if(10 != CBufferBufsiz(cbuffer))
	{
		printf("CreateDestroyBufsiz Test failed!\n ");
		printf("Expected value: 10 , recived value: %ld\n",CBufferBufsiz(cbuffer));
	}
	
	CBufferDestroy(cbuffer);

}


void ReadWriteTest(void)
{
	char src[] = "abcdefghijk";
	char dest[10] = {0};
	
	
	cbuffer_t *cbuffer = CBufferCreate(10);
	
	
	if (4 != CBufferWrite(cbuffer, &src, 4))
	{
		printf("ReadWriteTest (writing) failed!\n ");
		printf("Expected value: 4 , recived value: %ld\n",CBufferWrite(cbuffer, &src, 4));
	}
	
	if (4 != CBufferWrite(cbuffer, &src, 4))
	{
		printf("ReadWriteTest (reading) failed!\n ");
		printf("Expected value: 4 , recived value: %ld\n",CBufferRead(cbuffer, &dest, 5));
	}	
	
	CBufferDestroy(cbuffer);
}


void ReadWriteIsEmptyTest(void)
{
	char src[] = "abcdefghijk";
	
	
	cbuffer_t *cbuffer = CBufferCreate(10);
	
	
	if (1 != CBufferIsEmpty(cbuffer))
	{
		printf("ReadWriteIsEmptyTest failed!\n ");
		printf("Expected value: 0 , recived value: %d\n", CBufferIsEmpty(cbuffer));
	}
	
	CBufferWrite(cbuffer, &src, 4);
	
	if (0 != CBufferIsEmpty(cbuffer))
	{
		printf("ReadWriteIsEmptyTest failed!\n ");
		printf("Expected value: 1, recived value: %d\n", CBufferIsEmpty(cbuffer));
	}
	
	CBufferDestroy(cbuffer);
}


void ReadWriteAvailableSpaceTest(void)
{
	char src[] = "abcdefghijk";
	
	cbuffer_t *cbuffer = CBufferCreate(10);
	
	
	if (10 != CBufferAvailableSpace(cbuffer))
	{
		printf("CBufferAvailableSpace (writing) failed!\n ");
		printf("Expected value: 10 , recived value: %ld\n", CBufferAvailableSpace(cbuffer));
	}
	
	CBufferWrite(cbuffer, &src, 4);
	
	if (6 != CBufferAvailableSpace(cbuffer))
	{
		printf("CBufferAvailableSpace (writing) failed!\n ");
		printf("Expected value: 6 , recived value: %ld\n", CBufferAvailableSpace(cbuffer));
	}	
	
	CBufferDestroy(cbuffer);
}


