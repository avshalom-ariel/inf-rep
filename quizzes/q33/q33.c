
#include <stdio.h> /*printf*/

static int Atoi(const char *str);

int main(void)
{
	char *str1 = "1335";
	char *str2 = "-1528";
	char *str3 = "0";

	int result1 = 1335;
	int result2 = -1528;
	int result3 = 0;
	
	if (result1 != Atoi(str1))
	{
		printf("test1 failed!\n");
	}
	else if (result2 != Atoi(str2))
	{
		printf("test2 failed!\n");
	}
	else if (result3 != Atoi(str3))
	{
		printf("test3 failed!\n");
	}
	else
	{
		printf("all tests passed!\n");
	}


	return 0;
}


int Atoi(const char *str)
{
	int result = 0;
	char *runner = (char *)str;
	int sign = 1;
	
	if ('-' == *runner)
	{
		sign = -1;
		++runner;
	}
	
	while ('\0' != *runner)
	{
		result *= 10;
		result += (int)(*runner - '0');
	
		++runner;
	}
	
	result *= sign;
	
	return result;
}


