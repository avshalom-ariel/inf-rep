#include <stdio.h> /* printf */
#include <string.h> /* strcmp */


#define RED "\x1B[0;31m"
#define GREEN "\x1B[0;32m"
#define WHITE "\x1B[1;37m"

size_t g_num_of_tests = 0;
size_t g_num_of_failed_tests = 0;

typedef struct student
{
	char *name;
	int grade_avg;
} student_t;

void Test(void)
{
	if (!g_num_of_failed_tests)
	{
		printf("%sAll Tests Passed!%s\n", GREEN, WHITE);
	}
	else
	{
		printf("%s%ld Tests Failed out of %ld Tests%s\n", RED,
		       g_num_of_failed_tests, g_num_of_tests, WHITE);
	}
}
void TestSizeT(char *test_name, char *file, int line,
               size_t expected_val, size_t result_val)
{
	++g_num_of_tests;
	
	if (expected_val != result_val)
	{
		++g_num_of_failed_tests;
		
		printf("%s%s Failed%s in %s:%d\n", RED, test_name, WHITE, file, line);
		printf("Expected value is: %ld ", expected_val);
		printf("%sAcutal value is: %ld%s\n", RED, result_val, WHITE);
	}
	
}

void TestString(char *test_name, char *file, int line,
                char* expected_val, char* result_val)
{
	++g_num_of_tests;
	
	if (!strcmp(expected_val, result_val))
	{
		++g_num_of_failed_tests;
		
		printf("%s%s Failed%s in %s:%d\n", RED, test_name, WHITE, file, line);
		printf("Expected value is: %s ", expected_val);
		printf("%sAcutal value is: %s%s\n", RED, result_val, WHITE);
	}
	
}

void TestInt(char *test_name, char *file, int line,
             int expected_val, int result_val)
{
	++g_num_of_tests;
	
	if (expected_val != result_val)
	{
		++g_num_of_failed_tests;
		
		printf("%s%s Failed%s in %s:%d\n", RED, test_name, WHITE, file, line);
		printf("Expected value is: %d ", expected_val);
		printf("%sAcutal value is: %d%s\n", RED, result_val, WHITE);
	}
	
}

void TestFloat(char *test_name, char *file, int line,
               float expected_val, float result_val)
{
	++g_num_of_tests;
	
	if (expected_val != result_val)
	{
		++g_num_of_failed_tests;
		
		printf("%s%s Failed%s in %s:%d\n", RED, test_name, WHITE, file, line);
		printf("Expected value is: %f ", expected_val);
		printf("%sAcutal value is: %f%s\n", RED, result_val, WHITE);
	}
	
}

void TestDouble(char *test_name, char *file, int line,
               	double expected_val, double result_val)
{
	++g_num_of_tests;
	
	if (expected_val != result_val)
	{
		++g_num_of_failed_tests;
		
		printf("%s%s Failed%s in %s:%d\n", RED, test_name, WHITE, file, line);
		printf("Expected value is: %f ", expected_val);
		printf("%sAcutal value is: %f%s\n", RED, result_val, WHITE);
	}
	
}

void TestStudentT(char *test_name, char *file, int line, student_t *expected_val, student_t *result_val)
{
	g_num_of_tests += 2;
	
	if (expected_val -> grade_avg != result_val -> grade_avg)
	{
		++g_num_of_failed_tests;
		
		printf("%s%s Failed%s in %s:%d\n", RED, test_name, WHITE, file, line);
		printf("Expected grade average value is: %d ", expected_val -> grade_avg);
		printf("%sAcutal grade average value is: %d%s\n", RED,
		       result_val -> grade_avg, WHITE);
	}
	else if (!strcmp(expected_val -> name, result_val -> name))
	{
		++g_num_of_failed_tests;
		
		printf("%s%s Failed%s in %s:%d\n", RED, test_name, WHITE, file, line);
		printf("Expected name value is: %s ", expected_val -> name);
		printf("%sAcutal name value is: %s%s\n", RED, result_val -> name, WHITE);
	}
}


