

#include<stdio.h> /*printf*/
#include<stdlib.h> /*malloc free*/
#include<string.h> /*strlen*/
#include<assert.h> /*assert*/



#include "ws6.h"


int main(int argc, char **argv, char **envp)
{
    int rows = 5;
    int cols = 5;
    int i = 0;
    int j = 0;
    int *row_sum;
    int** matrix = (int **)malloc(rows * sizeof(int*));
    char str[] = "welcome";
    int arr[10] = {0};
    char* p = "lalala";
    char arr1[10] = "lalala";
    
    
    foo(arr, 10);
    printf("size of str: %ld  '\n'", sizeof(str));
    printf("size of arr: %ld  '\n'", sizeof(arr));
    printf("length of str: %ld  '\n'", strlen(str));
    
    ++p;
    /*++arr1;   error!*/
    /**p = 's'; segmentation fault*/
    /*p[0] = 's'; segmentation fault*/
    arr1[1] = 's'; /*ok*/
    *(arr1 + 1) = 's'; /*ok*/
    1[arr1] = 's'; /*ok*/
    /*printf("size of arr1: %ld  '\n'", sizeof(arr1));
    printf("size of p: %ld  '\n'", sizeof(p));  also gives error*/
    
    for (i = 0; i < rows; i++)
    {
        matrix[i] = (int *)malloc(cols * sizeof(int));
    }
    
/*   matrix = {{5,5,5,5,5},{5,5,5,5,5},{5,5,5,5,5},{5,5,5,5,5},{5,5,5,5,5}};*/
    
    for (i = 0; i < rows; i++) 
    {
        for (j = 0; j < cols; j++) 
        {
            matrix[i][j] = 2;
        }
    }   
    
    row_sum = (int *)malloc(rows * sizeof(int)); 
    
    TwoDimArr(matrix, row_sum, rows, cols);

   
    for (i = 0; i < rows; i++) 
    {
        printf("%d\n",row_sum[i]);
    }
    
    for (i = 0; i < rows; i++)
    {
        free(matrix[i]);
    }
    
    free(matrix);
    
    printf("josephus test:\nexpected: 72, result: %d\n",Josephus(100));
    
    PrintEnvVar();
    
		
	/*basic data types:*/
	printf("size of int:%ld\n",sizeof(int)); 
	printf("size of char:%ld\n",sizeof(char)); 
	printf("size of float:%ld\n",sizeof(float)); 
	printf("size of double:%ld\n",sizeof(double)); 


	/*modifier data types:*/

	printf("size of long:%ld\n",sizeof(long)); 
	printf("size of short:%ld\n",sizeof(short)); 
	/*printf("size of long long:%ld\n",sizeof(long long)); no supported by C90*/
	printf("size of signed:%ld\n",sizeof(signed)); 
	printf("size of unsigned:%ld\n",sizeof(unsigned)); 


		
    
    return 0;
    
}


























   

