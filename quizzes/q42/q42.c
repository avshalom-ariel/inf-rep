
#include <stddef.h>	/*size_t*/
#include <stdio.h>	/*printf*/

#define WORD_SIZE sizeof(size_t)

static void GenericSwap(void *element1, void *element2, size_t element_size);
static void SwapByte(void *element1, void *element2);
static void SwapWord(void *element1, void *element2);

typedef struct element
{
	char *str;
	int a;
	int b;
	int c;
	int d;
} element_t;

int main(void)
{
	element_t element1 = {"straight", 1, 2, 3, 4};
	element_t element2 = {"opposite", 4, 3, 2, 1};
	
	printf("-----Before swap:-----\n");
	printf("element1 = {%s, %d, %d, %d, %d}\n", element1.str, element1.a, 
									 element1.b, element1.c, element1.d);
	printf("element2 = {%s, %d, %d, %d, %d}\n", element2.str, element2.a, 
									 element2.b, element2.c, element2.d);
	
	GenericSwap(&element1, &element2, sizeof(element_t));
	
	printf("\n-----After swap:-----\n");
	printf("element1 = {%s, %d, %d, %d, %d}\n", element1.str, element1.a, 
									 element1.b, element1.c, element1.d);
	printf("element2 = {%s, %d, %d, %d, %d}\n", element2.str, element2.a, 
									 element2.b, element2.c, element2.d);
	
	return 0;
}




void GenericSwap(void *element1, void *element2, size_t element_size)
{
	if (element1 == element2)
	{
		return;
	}

	while (element_size && 0 != (size_t)element1 % WORD_SIZE &&
							 0 != (size_t)element2 % WORD_SIZE)	
	{
		SwapByte(element1, element2);
		element1 = (char *)element1 + 1;
		element2 = (char *)element2 + 1;
		--element_size;
	}
	
	while (element_size && 0 == (size_t)element1 % WORD_SIZE &&
							 0 == (size_t)element2 % WORD_SIZE)
	{
		SwapWord(element1, element2);
		element1 = (char *)element1 + WORD_SIZE;
		element2 = (char *)element2 + WORD_SIZE;
		element_size -= WORD_SIZE;
	}
	
	while (element_size)
	{
		SwapByte(element1, element2);
		element1 = (char *)element1 + WORD_SIZE;
		element2 = (char *)element2 + WORD_SIZE;
		--element_size;
	}
}


void SwapByte(void *element1, void *element2)
{
	char temp = *(char *)element1;
	*(char *)element1 = *(char *)element2;
	*(char *)element2 = temp;
}

void SwapWord(void *element1, void *element2)
{
	size_t temp = *(size_t *)element1;
	*(size_t *)element1 = *(size_t *)element2;
	*(size_t *)element2 = temp;
}

