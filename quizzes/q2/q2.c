#include<stdio.h>
#include <ctype.h>
#include <string.h>

void reverse(char str[]);

void TF();


int main(void)
{

	/*TF(120);*/
	
	char* str = "HelLoo wORLd";
	
	printf("%s\n", str);


	reverse(str);


	return 0;
	
}


void TF(int num)
{
    int i = 1;
    while(i<num + 1)
    {
        if(i%3 == 0)
        {
            printf("%c",'T');
        }
        else if(i%5 == 0)
        { 
            printf("%c", 'F');
        }
        else/*if(i%3 != 0 && i%5 != 0)*/
        {
            printf("%d", i);
        }
        ++i;
        
    }

}



void reverse(char str[])
{
	int l=strlen(str);
	char rev[l];
	int i = 0;
	int p = 0;
	
	for(i = l-1; i >= 0; --i)
	{
		rev[p++]=tolower(str[i]);
	}
	
	printf("%s",rev);
}














