
#include <stdio.h>

#include "ws7.h"

int system(const char *command);




int main(void)
{
	typedef long int lint;

	typedef void (*myfunc)(int);

	typedef int (*arr)[];
	
	char key = 0;
	int i = 0;
	function func_arr[256] = {0};

	system("stty -icanon -echo");
	key ='B'; 
	
	while(key != 27)
	{
		scanf("%c", &key);
		if (key == 'A')
		{
			printf("A is pressed\n" );
		}
		else if (key == 'T')
		{
			printf("T is pressed\n" );
		}
		printf("%c", key);
	}
	
	system("stty icanon echo");
		
    printf("finished\n");
	
	
	system("stty -icanon -echo");
	key ='B'; 
	
	while(key != 27)
	{
		scanf("%c", &key);
		switch (key)
		{
			case 'A':
			printf("A is pressed\n" );
			break;
			
			
			case 'T':
			printf("T is pressed\n" );
			break;
		}
	}
	
	system("stty icanon echo");
		
    printf("finished\n");
	

	for (i = 0; i < 256; ++i)
	{
		func_arr[i] = nullf;
	}
	
	func_arr['A'] = prnt_A;
	func_arr['T'] = prnt_T;
	
	system("stty -icanon -echo");
	key ='B'; 
	
	while(key != 27)
	{
		scanf("%c", &key);
		(func_arr[(int)key])();
	}
	
	system("stty icanon echo");
		
    printf("finished\n");






	return 0;
}
