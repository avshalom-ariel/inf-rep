#ifndef __WS4_H__
#define __WS4_H__


char* my_strcat(char* dst, char* src);
int my_strcasecmp(const char *str1, const char *str2);
int my_strcpy(char str_dst[],char str_src[]);
int my_strncmp(const char *str1, const char *str2, size_t n);
char* my_strstr(char *haystack, char *needle);
char* my_strdup(char* str);
int my_strncpy(char* src, char* cpy, size_t n);
char* my_strchr(char *str, int c);
char* my_strncat(char* dst, char* src, size_t siz);
int PalindromeCheck(char* str);
void WhiteSpaceRemoval(char* str_src, char* result);



#endif

