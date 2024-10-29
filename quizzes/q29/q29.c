
#include <stdio.h> /*printf*/
#include <string.h> /*strcpy*/

#define STRING_SIZE 50

static void Swap(char *x, char *y);
static void PermutationPrint(char *str);
static void permute(char *str, int l, int r);

int main(void)
{
	char str1[] = "ABC";
	char str2[] = "1234";
	
	
	PermutationPrint(str1);
	printf("\n");
	PermutationPrint(str2);
	printf("\n");
	
	return 0;
}

void PermutationPrint(char *str)
{
    int len = strlen(str);
    permute(str, 0, len - 1);
}

void permute(char *str, int left, int right) 
{
    int i = 0;
    
    if (left == right) 
    {
        printf("%s\n", str);
    } 
    else 
    {
        for (i = left; i <= right; ++i) 
        {
            Swap((str + left), (str + i)); 
            permute(str, left + 1, right);    
            Swap((str + left), (str + i)); /* Undo the swap to restore the original string*/
        }
    }
}

void Swap(char *x, char *y)
{
    char temp;
    temp = *x;
    *x = *y;
    *y = temp;
}


