#include <stdio.h> /* printf sizeof */
#include <stdlib.h> /* realloc free */
#include <string.h> /* strlen */


static int DigitCount(int num);

void AddInt(int *ptr_int, int num_to_add)
{
	*ptr_int += num_to_add;
}

void AddFloat(float *ptr_float, int num_to_add)
{
	*ptr_float += num_to_add;
}

void AddString(char **str, int num_to_add)
{
	int len = strlen(*str);
	int new_len = strlen(*str)*sizeof(char) + DigitCount(num_to_add) + 1;
	*str = (char *)realloc(*str,new_len);
	
	if (NULL == *str)
	{
		printf("error in realloc\n");
		return;
	}
	
	sprintf(*str + len, "%d", num_to_add);
}


void PrintInt(int *ptr)
{
	printf("%d\n", *ptr);
}

void PrintFloat(float *ptr)
{
	printf("%f\n", *ptr);
}

void PrintString(char **ptr)
{
	printf("%s\n", *ptr);
}

void Clean(char **ptr)
{
	free(*ptr);
}


void DoNothing()
{
}


static int DigitCount(int num)
{
	int count = 0;
	
	while(num)
	{
		num /= 10;
		++count;
	}
	return count;
}



























