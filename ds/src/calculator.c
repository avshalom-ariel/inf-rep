/*****************************
Code by: Avshalom Ariel
Date: 24/06/2024
Review by: Shahar Marom
Review date: 30/06/2024
Status: Approved
*****************************/

#include <math.h>    	/* pow */
#include <stdlib.h>  	/* strtod */
#include <ctype.h> 		/* isdigit */
#include <assert.h>  	/* assert */

#include "stack.h"		/*e_status_t*/
#include "calculator.h"	/*typedefs, function declarations*/

#define NUM_OF_STATES 2
#define ASCII_SIZE 256
#define MAX_OPRATOR_CHAR 95
#define STACK_SIZE 50
#define DUMMY '#'
#define EXECUTION_SUCCEED 0
#define DIVDED_BY_ZERO -1

typedef const char *(*handler_t)(e_status_t *, const char *);
typedef double (*operation_t)(double, double);

typedef enum state
{
	WATING_FOR_NUM,
	WATING_FOR_OPERATOR
} e_state_t;

typedef enum pritorty
{
	FOURTH_PRIORITY,
	THIRD_PRIORITY,
	SECOND_PRIORITY,
	FIRST_PRIORITY
} e_pritorty_t;

typedef struct transion
{
	handler_t handler;
	e_state_t next_state;
} transion_t;


typedef struct operator
{
	e_pritorty_t priorty;
	operation_t operation;
} operator_t;

typedef struct 
{
	stack_t *operators;
	stack_t *operands;
}stacks_t;

static stacks_t stacks = {NULL, NULL};

static operator_t operator_lut_g[MAX_OPRATOR_CHAR] = {0};
static transion_t fsm_lut_g[NUM_OF_STATES][ASCII_SIZE] = {0};

static const char *DigitHandler(e_status_t *status, const char *str);
static const char *InvalidHandler(e_status_t *status, const char *str);
static const char *WhiteSpaceHandler(e_status_t *status, const char *str);
static const char *OpenParenHandler(e_status_t *status, const char *str);
static const char *CloseParenHandler(e_status_t *status, const char *str);       
static const char *NullTerminatorHandler(e_status_t *status, const char *str);
static const char *OperationHandler(e_status_t *status, const char *str);
static const char *PowerHandler(e_status_t *status, const char *str);

static int Execution(const char operation, e_status_t *status);
static e_status_t ResultExecution(e_status_t *status, double *result);

static double Plus(double num1, double num2);
static double Minus(double num1, double num2);
static double Multi(double num1, double num2);
static double Dvide(double num1, double num2);
static double Pow(double num1, double num2);

static void DestroyStacks(void);
static int InitStacks(void);
static void InitLut(void);


/************************************************/
/*		 	   	  API Function   	  			*/
/************************************************/


e_status_t Calculate(const char *expresion, double *result)
{
	e_status_t status = RUNNING;
	e_state_t current_state = WATING_FOR_NUM;
	char runner = DUMMY;
	
	if (0 != InitStacks())
	{
		*result = 0;
		return CALC_MEMORY_ERROR;
	}
	
	InitLut();
	StackPush(stacks.operators, &runner);
	
	while (RUNNING == status)
	{
		runner = *expresion;
		expresion = (fsm_lut_g[current_state][(int)*expresion].handler)(&status, expresion);
		current_state = fsm_lut_g[current_state][(int)runner].next_state;
	}
	
	return ResultExecution(&status, result);
}


/************************************************/
/*		 	   	  Handlers   	  				*/
/************************************************/


static const char *OperationHandler(e_status_t *status, const char *str)
{
	char operator_peek = *(char *)StackPeek(stacks.operators);
	
	while (operator_lut_g[(int)operator_peek].priorty >= operator_lut_g[(int)*str].priorty)
	{	
		Execution(operator_peek, status);
		operator_peek = *(char *)StackPeek(stacks.operators);	
	}
	
	StackPush(stacks.operators, (char *)str);
	
	return (str + 1);
}

static const char *InvalidHandler(e_status_t *status, const char *str)
{	
	*status = CALC_SYNTAX_ERROR;
	
	return str;
}

static const char *WhiteSpaceHandler(e_status_t *status, const char *str)
{
	(void)status;
	
	return (str + 1);
}

static const char *PowerHandler(e_status_t *status, const char *str)
{
	StackPush(stacks.operators, (char *)str);
	
	(void)status;
	
	return (str + 1);
}

static const char *OpenParenHandler(e_status_t *status, const char *str)
{
	StackPush(stacks.operators, (char *)str);
	
	(void)status;
	
	return (str + 1);
}

static const char *CloseParenHandler(e_status_t *status, const char *str) 
{
	char operator_peek = *(char *)StackPeek(stacks.operators);
	int operation_res = 0;
	
	while (DUMMY != operator_peek && '(' != operator_peek)
	{
		operation_res = Execution(operator_peek, status);
		
		if (DIVDED_BY_ZERO == operation_res)
		{
			return str;
		}
		
		operator_peek = *(char *)StackPeek(stacks.operators);
	}
	
	if (DUMMY == operator_peek)
	{
		*status = CALC_SYNTAX_ERROR;
		return str;
	}
	
	StackPop(stacks.operators);
	
	return (str + 1);
}

static const char *NullTerminatorHandler(e_status_t *status, const char *str)
{
	char operator_peek = *(char *)StackPeek(stacks.operators);
	int operation_res = 0;
	
	while (DUMMY != operator_peek && '(' != operator_peek)
	{
		
		operation_res = Execution(operator_peek, status);
		
		if (DIVDED_BY_ZERO == operation_res)
		{
			return str;
		}
		
		operator_peek = *(char *)StackPeek(stacks.operators);
	}
	
	if ('(' == operator_peek)
	{
		*status = CALC_SYNTAX_ERROR;
		return str;
	}
	
	*status = CALC_SUCCESS;
	
	return str;
}

static const char *DigitHandler(e_status_t *status, const char *str)
{
	const char *end_scan = NULL;
	double holder = strtod(str, (char **)&end_scan);
	
	if (('+' ==  *str || '-' ==  *str) && !isdigit(*(str + 1)))
	{
		*status = CALC_SYNTAX_ERROR;
		return str;
	}
	
	StackPush(stacks.operands, &holder);
	
	(void)status;
	
	return end_scan;
}


/************************************************/
/*		 	   	  Operations   	  				*/
/************************************************/


static double Plus(double num1, double num2)
{
	return (num1 + num2);
}

static double Minus(double num1, double num2)
{
	return (num1 - num2);
}

static double Multi(double num1, double num2)
{
	return (num1 * num2);
}

static double Dvide(double num1, double num2)
{
	return (num1 / num2);
}

static double Pow(double num1, double num2)
{
	return pow(num1, num2);
}


/************************************************/
/*		 	   	  Executions   	  				*/
/************************************************/


static int Execution(const char operation, e_status_t *status)
{
	double num1 = 0;
	double num2 = 0;
	double result = 0;
	
	num2 = *(double *)StackPeek(stacks.operands);
	StackPop(stacks.operands);
			
	num1 = *(double *)StackPeek(stacks.operands);
	StackPop(stacks.operands);
			
	if ( 0 == num2 && '/' == operation)
	{
		*status = CALC_MATH_ERROR;
		return DIVDED_BY_ZERO;
	}
			
	result = (operator_lut_g[(int)operation].operation)(num1, num2);
	StackPop(stacks.operators);
			
	StackPush(stacks.operands, &result);
	
	return EXECUTION_SUCCEED;
}

e_status_t ResultExecution(e_status_t *status, double *result)
{
	if (CALC_SUCCESS == *status) 
	{
		*result = *(double *)StackPeek(stacks.operands);	
	}
	else
	{
		*result = 0;
	}
	
	DestroyStacks();
	
	return *status;
}


/************************************************/
/*		 	 	  Initializers   				*/
/************************************************/


static void InitLut(void)
{
	size_t i = 0;
	size_t j = 0;
	
	if (NULL != fsm_lut_g[i][j].handler)
	{
		return;
	}
	
	for (; i < NUM_OF_STATES; ++i)
	{
		for (j = 0; j < ASCII_SIZE; ++j)
		{
			fsm_lut_g[i][j].handler = &InvalidHandler;
			fsm_lut_g[i][j].next_state = i;
		}
	}
	
	fsm_lut_g[WATING_FOR_OPERATOR]['\0'].handler = &NullTerminatorHandler;
	fsm_lut_g[WATING_FOR_OPERATOR]['\0'].next_state = WATING_FOR_OPERATOR;
	
	fsm_lut_g[WATING_FOR_NUM]['\n'].handler = &WhiteSpaceHandler;
	fsm_lut_g[WATING_FOR_NUM]['\n'].next_state = WATING_FOR_NUM;
	
	fsm_lut_g[WATING_FOR_OPERATOR]['\n'].handler = &WhiteSpaceHandler;
	fsm_lut_g[WATING_FOR_OPERATOR]['\n'].next_state = WATING_FOR_OPERATOR;
	
	fsm_lut_g[WATING_FOR_NUM][' '].handler = &WhiteSpaceHandler;
	fsm_lut_g[WATING_FOR_NUM][' '].next_state = WATING_FOR_NUM;
	
	fsm_lut_g[WATING_FOR_OPERATOR][' '].handler = &WhiteSpaceHandler;
	fsm_lut_g[WATING_FOR_OPERATOR][' '].next_state = WATING_FOR_OPERATOR;
	
	fsm_lut_g[WATING_FOR_NUM]['+'].handler = &DigitHandler;
	fsm_lut_g[WATING_FOR_NUM]['+'].next_state = WATING_FOR_OPERATOR;
	
	fsm_lut_g[WATING_FOR_NUM]['-'].handler = &DigitHandler;
	fsm_lut_g[WATING_FOR_NUM]['-'].next_state = WATING_FOR_OPERATOR;
	
	for (i = '0'; i <= '9'; ++i)
	{
		fsm_lut_g[WATING_FOR_NUM][i].handler = &DigitHandler;
		fsm_lut_g[WATING_FOR_NUM][i].next_state = WATING_FOR_OPERATOR;
	}
		
	fsm_lut_g[WATING_FOR_OPERATOR]['+'].handler = &OperationHandler;
	fsm_lut_g[WATING_FOR_OPERATOR]['+'].next_state = WATING_FOR_NUM;
	
	fsm_lut_g[WATING_FOR_OPERATOR]['-'].handler = &OperationHandler;
	fsm_lut_g[WATING_FOR_OPERATOR]['-'].next_state = WATING_FOR_NUM;
	
	fsm_lut_g[WATING_FOR_OPERATOR]['*'].handler = &OperationHandler;
	fsm_lut_g[WATING_FOR_OPERATOR]['*'].next_state = WATING_FOR_NUM;	
	
	fsm_lut_g[WATING_FOR_OPERATOR]['/'].handler = &OperationHandler;
	fsm_lut_g[WATING_FOR_OPERATOR]['/'].next_state = WATING_FOR_NUM;	
	
	fsm_lut_g[WATING_FOR_OPERATOR]['^'].handler = &PowerHandler;
	fsm_lut_g[WATING_FOR_OPERATOR]['^'].next_state = WATING_FOR_NUM;
	
	fsm_lut_g[WATING_FOR_NUM]['('].handler = &OpenParenHandler;
	fsm_lut_g[WATING_FOR_NUM]['('].next_state = WATING_FOR_NUM;
	
	fsm_lut_g[WATING_FOR_OPERATOR][')'].handler = &CloseParenHandler;
	fsm_lut_g[WATING_FOR_OPERATOR][')'].next_state = WATING_FOR_OPERATOR;	
	
	
	operator_lut_g['+'].operation = &Plus;
	operator_lut_g['+'].priorty = THIRD_PRIORITY;
	operator_lut_g['-'].operation = &Minus;
	operator_lut_g['-'].priorty = THIRD_PRIORITY;
	operator_lut_g['*'].operation = &Multi;
	operator_lut_g['*'].priorty = SECOND_PRIORITY;
	operator_lut_g['/'].operation = &Dvide;
	operator_lut_g['/'].priorty = SECOND_PRIORITY;
	operator_lut_g['^'].operation = &Pow;
	operator_lut_g['^'].priorty = FIRST_PRIORITY;
	operator_lut_g['('].operation = NULL;
	operator_lut_g['('].priorty = FOURTH_PRIORITY;
	operator_lut_g[DUMMY].operation = NULL;
	operator_lut_g[DUMMY].priorty = FOURTH_PRIORITY;
}

int InitStacks(void) 
{
	
	stacks.operators = StackCreate(STACK_SIZE, sizeof(char));
	if (!stacks.operators) 
	{
		return CALC_MEMORY_ERROR;
	}

	stacks.operands = StackCreate(STACK_SIZE, sizeof(double));
	if (!stacks.operands) 
	{
		StackDestroy(stacks.operators);
		return CALC_MEMORY_ERROR;
	}

	return CALC_SUCCESS;
}

void DestroyStacks(void) 
{
	StackDestroy(stacks.operators);
	StackDestroy(stacks.operands);
}


