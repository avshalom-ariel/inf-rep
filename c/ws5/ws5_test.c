
#include<stdio.h> /*printf*/
#include<stdlib.h> /*malloc free*/

#include "ws5.h"


int main(void)
{
    int* ptr_stuck = (int*) malloc(sizeof(int)*11);
    int ten_ptr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int out_of_bound = ten_ptr[11];
    char* str_haystack = "hey look here";
    char* str_needle = "w";
    
    printf("%s\n", my_strstr(str_haystack, str_needle));
    
    while(5 == 5)
    {
    }
    
    
    
    
    free(ptr_stuck);

}














