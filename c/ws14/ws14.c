
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "ws14.h"


void MyItoa(char *str, int num, const int base)
{
    int i;
    int rem; 
 	char convert_str[64];
 	char null = '\0';
 	
 	i = 0;
	
    while(num)
    {
        rem = num % base;
        num = num / base;
        convert_str[i] = LUT[rem];
        ++i; 
    }
    
   while (i-1)
   {
		strncat(str , &convert_str[i-1], 1);
   		--i;  		
   }
	strncat(str , &convert_str[i-1], 1);
	strncat(str , &null, 1);
}




int MyAtoi(char str[], int base)
{
    int i;
    int j;
    int LUT_index;
    int len = strlen(str);
    int num = 0;
    
 
    for (i = 0; i < len; ++i)
    {
        for (j = 0; j < 36; ++j)
 		{
 			if (str[len - (i + 1)] == LUT[j])
 			{
 				LUT_index = j;
 				break;
 			}
 		}
        num = num + LUT_index * Pow(base, i);
    }
 
   return num;
}

size_t Pow(size_t base, int exp)
{
	size_t result = 1;
	while(exp)
	{
		result = result * base;
		--exp;
	}
	return result;
}





void AtoiTest(char* str)
{
	if (atoi(str) == MyAtoi(str, 10))
	{
		printf("test succeed!\n");
	}
	else
	{
		printf("test failed:(\n");
	}
}


void AtoiExamples(void)
{
	AtoiTest("0");
	AtoiTest("2");
	AtoiTest("2147483647");
	AtoiTest("2147483454545456648");
}


void DoubleParallelArray(char *arr1, char *arr2, char *arr3, size_t size1, size_t size2, size_t size3)
{
	char LUT[256] = {0};
	size_t i = 0;
	
	for (i = 0; i < size1; ++i)
	{
		LUT[(int)arr1[i]] = 1;
	}
	for (i = 0; i < size2; ++i)
	{
		LUT[(int)arr2[i]] = LUT[(int)arr2[i]] * 2;
	}
	for (i = 0; i < size3; ++i)
	{
		LUT[(int)arr3[i]] = 0;
	}
	
	for (i = 0; i < 256; ++i)
	{
		if (LUT[i] > 1)
		{
			printf("%c\n",(char)i);
		}
	}
}


void EndianCheck(void)
{
   unsigned int num = 1;

   if (*(char*)&num == 1)
	{
		printf("Little endian\n");
	}
   else
   {
        printf("Big endian\n");
   }   
}





