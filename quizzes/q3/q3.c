#include <stdio.h>

void Main(int argc, char *argv[])
{

	int num;
	const int num2 = 6;
	const int num3;
	
	printf("%d", num);
	scanf("%d",num);
	printf("100 divided by %d is %f", num, 100/num);
	
	char ch = 97;
	
	num3 = num2 - 5;
	printf("%f", num3);
	
	num = 4.7;
	(double)num = 4.7;
	
	num = 2 * num++;
	
	return 0;
	
	
	
	
/*	line 1 <stdio.h>
	line 11 &num
	line 12 %f when 100/num is int
	line 17 %f num3 is int
	line 20 (double)num is not lvalue
	line 24 return when main is void
	 
	
	
	
	
*/	
	
