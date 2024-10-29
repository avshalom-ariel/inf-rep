#ifndef __CALCULATOR_H__
#define __CALCULATOR_H__

typedef enum
{
	CALC_SUCCESS,
	CALC_MATH_ERROR,
	CALC_SYNTAX_ERROR,
	CALC_MEMORY_ERROR,
	RUNNING
} e_status_t;


/*
Description: Calculate the expresion recieved as input.
Input: String expresion to be calculated, a double pointer to recieve the result.
Return: Enum represent the status of calculation.
Time complexity: O(n)
Space complexity: O(n)
*/
e_status_t Calculate(const char *expresion, double *result);

/* Can proccess:
    -Decimal point
    -Unaric operators
    -Power (support as well: fractional powers, and negative powers)
    -Parentheses
    -White spaces
*/

#endif /*__CALCULATOR_H__*/
