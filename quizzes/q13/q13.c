
#include<stddef.h> /*size_t*/
#include <stdio.h> /*prinf*/
#include <string.h> /*memcpy*/

#define WORD_SIZE sizeof(size_t)


void *MyMemcpy(void *dest, void *src, size_t n)
{
	void *dest_runner = dest;
	void *src_runner = src;
	size_t reminder = 0;
	size_t i = 0;
	
	while(n && (size_t)dest_runner % WORD_SIZE)
	{
		*(char *)dest_runner =*(char *)src_runner;
		--n;
	
		dest_runner = (char *)dest_runner + 1;
		src_runner = (char *)src_runner + 1;
		
	}
	
	
	reminder = n % WORD_SIZE;
	n = n / WORD_SIZE;
	
	for(; i < n; i += WORD_SIZE)
	{
		*(size_t *)dest_runner = *(size_t *)src_runner;
		
		dest_runner = ((size_t *)dest_runner) + 1;
		src_runner = ((size_t *)src_runner) + 1;	

	}
	
	while (reminder)
	{
		*(char *)dest_runner = *(char *)src_runner;
		
		dest_runner = (char *)dest_runner + 1;
		src_runner = (char *)src_runner + 1;
		
		--reminder;
	}
	
	return dest;

}


int main(void)
{
	
	char *str1 = "supermegafragalisticexpialidowshi";
	char str2[30];


	if (((char *)MyMemcpy(str2, str1, 12)) == ((char *)memcpy(str2, str1, 12)))
	{
		printf("test passed!\n");
	}
	

	return 0;
}



