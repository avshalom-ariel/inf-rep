

#include <string.h> /*strncmp strlen*/


char* my_strstr(char *haystack, char *needle)
{
    
    while(strncmp(haystack, needle, strlen(needle)-1) != 0 )
    {
        haystack++;
        haystack = strchr(haystack, *needle);   
    }   
    
    return haystack;

}

