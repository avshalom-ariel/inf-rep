
#include <ctype.h> /*tolower*/
#include <string.h> /*strlen*/
#include <stdlib.h> /*malloc*/



char* my_strcat(char* dst, char* src)
{
    char* result = dst;
    int i=strlen(dst);
    while(*src != '\0')
    {
        
        dst[i] = *src;
        src++;
        i++;
    
    }
    
    return result;
}



int my_strcasecmp(const char *str1, const char *str2)
{

    int i = 0;
    while(str1[i] == str2[i] && str1[i] != '\0' && str2[i] != '\0')
    {
    
        ++i;    
    
    }
    
    return(tolower(str1[i])-tolower(str2[i]));
}





void my_strcpy(char str_dst[],char str_src[])
{

    int i=0;
    
    while(str_src[i]!='\0')
    {
    
        str_dst[i]=str_src[i];
        ++i;
    
    }

	
}


int my_strncmp(const char *str1, const char *str2, size_t n)
{
    size_t i = 0;
    
    while(i<n && str1[i] == str2[i])
    {
        ++i;
    }
    return(str1[i]-str2[i]);

}



char* my_strstr(char *haystack, char *needle)
{
    
    while(strncmp(haystack, needle, strlen(needle)-1) != 0 )
    {
        haystack++;
        haystack = strchr(haystack, *needle);   
    }   
    
    return haystack;

}


char* my_strdup(char* str)
{
    
    char* dup;
    char* temp;
    dup = (char*)malloc(strlen(str)+1);
    temp = dup;
    while(*str != '\0')
    {
        *dup = *str;
        str++;
        dup++;
    }
    dup[strlen(str)+1] = '\0';
    
    return (temp);
    
}


int my_strncpy(char* src, char* cpy, size_t n)
{
    
    size_t i=0;
    
    while(i<n)
    {
        cpy[i]=src[i];
        ++i;
    }
    return 1;

}




char* my_strchr(char *str, int c)
{
    
    while((*str != c) && (*str != '\0'))
    {
        
        str++;
        
    }
        
    return (str);

}


char* my_strncat(char* dst, char* src, size_t siz)
{
    char* result = dst;
    size_t i=strlen(dst);
    size_t len =strlen(dst);

    while((*src != '\0') && (i<(len+siz)))
    {
        
        dst[i] = *src;
        src++;
        i++;
    
    }
    
    return result;
}


int PalindromeCheck(char* str)
{

    size_t i = 0;
    
    while(i < strlen(str)/2)
    {
        
        if (str[i] != str[strlen(str)-i-1])
        {
            return (-1);
        }
    ++i;
    }
    
    return 0;

}




void WhiteSpaceRemoval(char* str_src, char* result)
{
    
    int src_counter=0;
    int result_counter=0;


    while(str_src[src_counter] != '\0')
    {
        if (str_src[src_counter] == ' ' && str_src[src_counter+1] == ' ')
  
        {
            ++src_counter;
            continue;
        }
        else
        {
            result[result_counter]=str_src[src_counter];
            ++result_counter;
            ++src_counter;
        }
        
    }
    
    if (result[strlen(result)-1] == ' ')
    {
        result[strlen(result)-1] = '\0';
    }
    
    
    if (*result == ' ')
    {
        result++;
    }
    
}


































