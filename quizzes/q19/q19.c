
#include <stdio.h>

double Sqrt(double num);

int main(void)
{
	double x = 4;
	double y = 16;
	double z = 3.5 * 3.5;
	
	printf("sqrt of 4 is: %f\n", Sqrt(x));
	printf("sqrt of 16 is: %f\n", Sqrt(y));
	printf("sqrt of 3.5*3.5 is: %f\n", Sqrt(z));
		
	return 0;
}


double Sqrt(double num)
{
	double eps = 0.00001;
	double guess = num / 2.0;
	
	if(num < 0)
	{
		return -1;
	}
	
	while((guess * guess - num > eps ) || (num - guess * guess > eps))
	{
		guess = (guess + (num / guess)) / 2.0;
	}
	
	return guess;
}


