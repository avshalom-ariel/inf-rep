

#include <stdio.h>/*printf*/
#include <assert.h> /*assert*/
#include <stdlib.h> /*malloc free*/
#include <ctype.h> /*tolower*/
#include <string.h> /*strlen*/


void TwoDimArr(int* matrix[], int result[], int row, int col)
{
    int i = 0;
    int j = 0;
    
    for(i = 0; i < row; i++)
    {

        for (j = 0; j < col; j++)
        {
            result[i] += matrix[i][j];
        }

    }
}




void foo(int a[], int size)
{
    int i = 0;
    
    for(i = 0; i<size; ++i)
    {
        a[i] = i * 2;
    }
    printf("size of a: %ld  '\n'", sizeof(a));
}
  





int Josephus(int n)
{
    int result;
    int* arr = (int *)malloc(n * sizeof(int));

    int* surviver = (int *)malloc(n * sizeof(int));

    int i = 0;
    int j = 0;
    
    assert(arr);
    assert(surviver);

    
    for( i = 0; i < n; i++)
    {
        arr[i] = i;
    }
    
    while(n != 1)
    {
        if(n%2 == 0)
        {
            for(i = 0, j = 0; i < n; i += 2, ++j )
            {
                surviver[j] = arr[i];
            }
        }
        else
        {
            for(i = 2, j = 0; j < n/2; i += 2, ++j )
            {
                surviver[j] = arr[i];
            }
        }
        
        for(i = 0; i < n/2; ++i)
        {
            arr[i] = surviver[i];
        }
        
        n = n/2;    
    }
    
    result = surviver[0];
    
    free(arr);
    free(surviver);
    
    return (result); 
}


void StrLow(char* str)
{
	size_t i;
	size_t len;
	
	len = strlen(str);
	
	for (i = 0; i < len ; ++i)
	{
		str[i] = tolower(str[i]);
	}
}



void PrintEnvVar(void) 
{
    
    extern char **environ;
    
    int count = 0;
    char **env = environ;
    char **buffer = (char **)malloc((count + 1) * sizeof(char *));
    int i = 0;
    int j = 0;
    
    while (*env != NULL) 
    {
        count++;
        env++;
    }
    
    if (buffer == NULL) 
    {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    

    env = environ;
    
    while (*env != NULL) 
    {
        
        buffer[i] = (*env); 
        
        if (buffer[i] == NULL) 
        {
            printf("Memory allocation failed in line 50 \n");
            exit(EXIT_FAILURE);
        }
        
        i++;
        env++;
    }
    
    buffer[i] = NULL; 
    i = 0;
    
    while (i < count) 
    {
        
        StrLow(buffer[i]);
        ++i;
        
    }

    for (j = 0; j < count; j++) 
    {
        printf("%s\n", buffer[j]);
    }
    

    for (j = 0; j < count; j++) 
    {
        free(buffer[j]);
    }
    free(buffer);
}






















