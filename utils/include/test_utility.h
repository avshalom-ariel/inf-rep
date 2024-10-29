#ifndef __TEST_UTILITY_H__
#define __TEST_UTILITY_H__

#include <stddef.h>

typedef struct student student_t;

void Test(void);
void TestSizeT(char *test_name, char *file, int line,
               size_t expected_val, size_t result_val);
void TestString(char *test_name, char *file, int line,
                char* expected_val, char* result_val);
void TestInt(char *test_name, char *file, int line,
             int expected_val, int result_val);
void TestFloat(char *test_name, char *file, int line,
               float expected_val, float result_val);
void TestDouble(char *test_name, char *file, int line,
               	double expected_val, double result_val);
void TestStudentT(char *test_name, char *file, int line, student_t *expected_val, 
				  student_t *result_val);























#endif /* __TEST_UTILITY_H__ */
