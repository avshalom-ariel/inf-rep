#include<stdio.h> /*printf*/


#include "ws4.h"



int main(void)
{

    char str1[15] = "first string";
    char str2[] = "abc";
    char str_case_cmp1[] = "A";
    char str_case_cmp2[] = "a";
    char str_src[] = "hey you!";
    char str_cpy[9] = {0};
    const char strcmp1[] = "asDfqwe";
    const char strcmp2[] = "asdfqtyj";
    char* str_haystack = "hey look here";
    char* str_needle = "w";
    char* str_dup = "abcd";
    char str_ncpy[] = "heyou im a string!"; 
    char cpy_str[19] = {0};
    char strchr[] = "Aey one";
    int chrchr = 'y';
    char str_ncat1[115] = "first string";
    char str_ncat2[] = " abc";
    size_t n = 2;
    char* palindrome = "abecddcba";
    char white_space[] = "   hey  you!    come        here     ";
    char after[37] = {0};
    
    
    printf("%s", my_strcat(str1, str2));
    
    printf("%d", my_strcasecmp(str_case_cmp1, str_case_cmp2));	
	
	my_strcpy(str_cpy,str_src);
	
	printf("%s",str_cpy);
	
    printf("%d",my_strncmp(strcmp1, strcmp2, 2));
	
	printf("%s", my_strstr(str_haystack, str_needle));
	
    printf("%s", my_strdup(str_dup));
	
	my_strncpy(str_ncpy, cpy_str, 12);
    
    printf("%s",cpy_str);

	printf("%s", my_strchr(strchr, chrchr));
	
	printf("%s", my_strncat(str_ncat1, str_ncat2, n));
	
	printf("%i", PalindromeCheck(palindrome));
	
	printf("Before: \"%s\"\n", white_space);
    WhiteSpaceRemoval(white_space, after);
    printf("After: \"%s\"\n", after);
	
	return 0;
}
































