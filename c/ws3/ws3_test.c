

#include<stdio.h>/*printf*/
#include<stdlib.h>/*malloc free*/


#include "ws3.h"



int main(void)
{

	
	
	int arr[] = {1 , 2 , 3 , 4 , 5};
    int i = 0;
    int size = sizeof(arr) / sizeof(arr[0]);
    int copied_arr[5] = {0};
    size_t siz1 = 10;
    size_t siz2 = 20;
    size_t *ptr1 = &siz1;
    static int s_i = 7;
    int *ptr = &i;
    int *ptr2 = (int *)malloc(sizeof(int));
    char* str1 = "hey12343";
    char* str2 = "hey2";
    
    printf("the length of the string is :%d \n",Strlen(str1));
    
    printf("the difference between strings is:%d \n",Strcmp(str1,str2));
    
    
    copy_arr(arr , copied_arr , size);
    
    printf("copied array:");
    for (i=0; i < size; ++i)
    {
        
        printf("%d" , copied_arr[i]);   
        
    }
    
    printf("first array:");
    for (i=0; i < size; ++i)
    {
        
        printf("%d" , arr[i]);   
        
    }
	
	i = 7;
	
    free(ptr2);        

    printf("the adress of s_i is %ls\n.", &s_i);
    printf("the adress of i is %ls\n.", &i);
    printf("the adress of ptr is %ls\n.", &ptr);
    printf("the adress of ptr2 is %p\n.", &ptr2);
    
    if(ptr)
    {
        int **ptr3 = &ptr;
                
        printf("the adress of ptr3 is %p\n.", &ptr3);
        
    }
    free(ptr2); 
    
    
    
    printf("before swap size_t: siz1 = %zu , siz2 = %zu", siz1, siz2);
    swap_sizet(&siz1,&siz2);
    printf("after swap size_t: siz1 = %zu , siz2 = %zu", siz1, siz2);
    
    printf("before swap_ptr size_t: ptr1 = %p , ptr2 = %p", ptr1, ptr2);
    swap_size_t_ptr(&ptr1,&ptr2);
    printf("after swap_ptr size_t: ptr1 = %p , ptr2 = %p", ptr1, ptr2);

    
    
       
	
    return 0;
}

