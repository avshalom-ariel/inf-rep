#include<string.h>
#include<stdio.h>


int IsRotate(char* str1, char* str2);


int main(void)
{
	char* str1 ="12345";
	char* str2 = "45223"; 
	IsRotate(str1, str2);

	return 0;
	
}



int IsRotate(char* str1, char* str2)
{
	char* base1 = str1;
	char* base2 = str2;
	int count = 0;
	int str1_count = 0;
	int i;
	
	while(str1)
	{
		str2 = strchr(str2, *str1);
		for (i = 0; i < (int)strlen(str2); ++i)
		{
			if (*str1 == *str2)
			{
				++str1;
				++str2;
				++count;
			}
			else if ('\0' == *str2)
			{
				str2 = base2;
			}
		}
		if (count == (int)strlen(str1))
		{
			printf("yes");
			return 0;
		}
		else
		{
			count = 0;
		}
		++str1_count;
		str1 = base1;
		str2 = base2;
		for (i = 0; i < str1_count; ++i)
		{
			++str1;
		}
	}
		
	if (count == (int)strlen(str1))
	{
			printf("yes");
	}
	else
	{
			printf("no");
	}
		
	return 0;

}

