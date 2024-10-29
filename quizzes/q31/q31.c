
#include <stddef.h> /*size_t*/
#include <string.h> /*strlen strncpy*/
#include <stdlib.h> /*malloc free*/
#include <stdio.h> 	/*printf*/

static void FlipStr(char *str, size_t start, size_t end);
static void SwapChar(char *ch1, char *ch2);
static void FlipWordsInStr(char *str);

int main(void)
{
	char str[] = "I am student";
	
	FlipWordsInStr(str);
	
	printf("%s\n", str);
	
	
	return 0;
}

void FlipWordsInStr(char *str)
{
	size_t len = strlen(str);
	size_t start = 0;
	size_t end = len - 1;
	
	FlipStr(str, start, end);

	end = 0;
	
	while ('\0' != str[end + 1])
	{
		end = start + 1;

		while(' ' != str[end] && '\0' != str[end])
		{
			++end;
		}

		FlipStr(str, start, end - 1);		

		start = end + 1;
	}
	
}

void FlipStr(char *str, size_t start, size_t end)
{
	while (start < end)
	{
		SwapChar(str + start, str + end);
		
		++start;
		--end;
	}
}

void SwapChar(char *ch1, char *ch2)
{
	char temp = *ch1;
	*ch1 = *ch2;
	*ch2 = temp;
}


