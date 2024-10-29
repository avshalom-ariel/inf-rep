
#include <stddef.h> 		/*NULL*/
#include <stdio.h> 			/*printf*/
#include <stdlib.h> 		/*malloc free*/

#include "calculator.h" 	/*calculate, e_status_t*/
#include "test_utility.h" 	/*test functions*/

static int checker = 0;

static void CalculateTalTest(void);
static void CalculateTest(void);

int main(void)
{
	CalculateTalTest();
	CalculateTest();
	
	Test();

	return 0;
}


void CalculateTalTest(void)
{
	char str[100] = "7+8";
	char str2[100] = "8+8*3+-2^5";
	char str3[100] = "8+8*3-2^";
	char str4[100] = "2/0";
	char str5[100] = "8++8*((3-2)*5)";
	char str6[100] = "3-2)5";
	char str7[100] = "(3-2)5+ 5(4+4+4";
	char str8[100] = "4-3-2-1\n";
	char str9[100] = "4^3^2^1\n";
	
	double expected_result = 15;
	double expected_result2 = 0;
	double expected_result3 = 0;
	double expected_result4 = 0;
	double expected_result5 = 48;
	double expected_result6 = 0;
	double expected_result7 = 0;
	double expected_result8 = -2;
	double expected_result9 = 262144;
	
	double *my_result = (double *)malloc(sizeof(double));
	double *my_result2 = (double *)malloc(sizeof(double));
	double *my_result3 = (double *)malloc(sizeof(double));
	double *my_result4 = (double *)malloc(sizeof(double));
	double *my_result5 = (double *)malloc(sizeof(double));
	double *my_result6 = (double *)malloc(sizeof(double));
	double *my_result7 = (double *)malloc(sizeof(double));
	double *my_result8 = (double *)malloc(sizeof(double));
	double *my_result9 = (double *)malloc(sizeof(double));
	
	TestInt("CalculateTest", __FILE__, __LINE__, 1, 
			CALC_SUCCESS == Calculate(str, my_result));
	TestInt("CalculateTest", __FILE__, __LINE__, 1, 
			CALC_SUCCESS == Calculate(str2, my_result2));
	TestInt("CalculateTest", __FILE__, __LINE__, 1, 
			CALC_SYNTAX_ERROR == Calculate(str3, my_result3));
	TestInt("CalculateTest", __FILE__, __LINE__, 1, 
			CALC_MATH_ERROR == Calculate(str4, my_result4));
	TestInt("CalculateTest", __FILE__, __LINE__, 1, 
			CALC_SUCCESS == Calculate(str5, my_result5));
	TestInt("CalculateTest", __FILE__, __LINE__, 1, 
			CALC_SYNTAX_ERROR == Calculate(str6, my_result6));
	TestInt("CalculateTest", __FILE__, __LINE__, 1, 
			CALC_SYNTAX_ERROR == Calculate(str7, my_result7));
	TestInt("CalculateTest", __FILE__, __LINE__, 1, 
			CALC_SUCCESS == Calculate(str8, my_result8));
	TestInt("CalculateTest", __FILE__, __LINE__, 1, 
			CALC_SUCCESS == Calculate(str9, my_result9));
	
	TestDouble("CalculateTest", __FILE__, __LINE__, expected_result, *my_result);
	TestDouble("CalculateTest", __FILE__, __LINE__, expected_result2, *my_result2);
	TestDouble("CalculateTest", __FILE__, __LINE__, expected_result3, *my_result3);
	TestDouble("CalculateTest", __FILE__, __LINE__, expected_result4, *my_result4);
	TestDouble("CalculateTest", __FILE__, __LINE__, expected_result5, *my_result5);
	TestDouble("CalculateTest", __FILE__, __LINE__, expected_result6, *my_result6);
	TestDouble("CalculateTest", __FILE__, __LINE__, expected_result7, *my_result7);
	TestDouble("CalculateTest", __FILE__, __LINE__, expected_result8, *my_result8);
	TestDouble("CalculateTest", __FILE__, __LINE__, expected_result9, *my_result9);	
	
	free(my_result);
	free(my_result2);
	free(my_result3);
	free(my_result4);
	free(my_result5);
	free(my_result6);
	free(my_result7);
	free(my_result8);
	free(my_result9);
}


void CalculateTest(void)
{
	const char *str[] = {"    7+8",  "8+8*3+-2^5", "8+8*3-2^", "2/0",
						"8++8*((3-2)*5)", "4^3^2^1\n", "(3-2)*5+ 5*(4+4+4", 
						"4-3-2-1\n", "1+1", "3-2)*5", "2+1+2^3^2 * 1", "1-2-3", 
						"2^0", "4^3^2^1 + 1 - 1\n", "2^1", "(2+3)*4", 
						"2*(3+4*2)/2", "5/2", "5.5*2", "-2+3", "3+-2", "4/2+2", 
						"(2+3)*(4-1)", "10/(5-5)", "((2+3)*4)", "7++8", 
						"8+8*3+-2^5", "8+8*3-2^", "2/0", "8++8*((3-2)*5)", 
						"3-2)*5", "10/2/2/1", "2 * 1^2^3 + 4" , "4^(3^(2^(1)))", 
						"1 2 + 3", "1--1", "5 * (1-1)", " 5 *   (1-1) / 8", 
						"10/2/1^1^2^3^4 + 1", "(1-2) * (5)", "7.2393 * 1", 
						"Hello", "4 % 2", "9 * -9", " 05 + 01", "5* 2/0+3+1",
						"5 - 2.1.1", "(3+3+3)", "8*(5-5-5-5)*2", "3/((4+2*3)"};
							
	size_t size = sizeof(str) / sizeof(str[0]);
	size_t i = 0;
	e_status_t status = 0;
	const double results[] = {15, 0, 0, 0, 48, 262144, 0, -2, 2, 0, 515, -4, 1, 
								262144, 2, 20, 11, 2.5, 11, 1, 1, 4, 15, 0, 20, 
								15, 0, 0, 0, 48, 0, 2.5, 6, 262144, 0, 2, 0, 0, 
								6, -5, 7.2393, 0, 0, -81, 6, 0, 0, 9, -160, 0};
								
	const double statuses[] = {CALC_SUCCESS, 0, 2, 1, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0, 
								0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 2, 1, 0, 2, 0, 
								0, 0, 2, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 1, 2, 0, 
								0, 2};
	double result = 0;
	
 	for (i = 0; i < size; ++i)
 	{
 		result = 0;
 		status = Calculate(str[i], &result);
 		if(status == statuses[i] && results[i] == result)
		{
			printf("Test %.2ld passed\n", i+1);
		}
		else
		{
			++checker;
/*			printf("result is:%ld\n", result);*/
			printf("Test %ld failed\n", i+1);
		}
 	}
	
	if(0 == checker)
	{
		printf("\nALL TESTS PASSED!\n");
	}
}


