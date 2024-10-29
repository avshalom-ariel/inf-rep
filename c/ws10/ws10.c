
#include "ws10.h" /*g_s*/




int Foo(void)
{
	++g_s;
	
	return 0;
}




char* my_strchr(char *str, int c)
{
    
    while((*str != c) && (*str != '\0'))
    {
        
        str++;
        
    }
        
    return (str);

}




int my_strcpy(char str_dst[],char str_src[])
{

    int i=0;
    
    while(str_src[i]!='\0')
    {
    
        str_dst[i]=str_src[i];
        ++i;
    
    }
    
    return 0;
}

