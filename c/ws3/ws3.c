
#include <stddef.h>/*size_t*/










void swap (double* num_1 , double* num_2)
{
	*num_1=*num_1+*num_2;
	*num_2=*num_1-*num_2;
	*num_1=*num_1-*num_2;
}
	


void copy_arr(int source_arr[] , int copied_arr[] , int size)
{
    
    int i=0;
    
    for (i=0; i < size ; ++i)
    {
    
        copied_arr[i]=source_arr[i];
    
    }
    
}


void swap_sizet(size_t *siz1 , size_t *siz2)
{

    size_t temp=*siz1;
    *siz1=*siz2;
    *siz2=temp;

}

void swap_size_t_ptr(size_t *ptr1 , size_t *ptr2)
{

    swap_sizet(ptr1 , ptr2);

}






int Strlen(char* str)
{
    
    int count=0;
    
    int i=0;
    
    while(str[i]!='\0')
    {
        ++i;
    }
    return(i);

}


int Strcmp(char* str1, char* str2)
{
    int i=0;
    while(str1[i] == str2[i])
    {
      i++;
    }
    return (*str1-*str2);
}




