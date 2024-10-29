
#include <stddef.h> /*size_t*/
#include <stdio.h> /*printf*/

int ChecParenthesis(char *str);


typedef struct
{
	size_t size;
	char buffer[30];
} stack_t;


int main(void)
{
	char *str1 = "()))((({{}}{}{[]][][[]";
	char *str2 = "[{}(])";
	char *str3 = "(){{{}}()([])[]}";
	
	printf("should be 0:%d\n", ChecParenthesis(str1));
	printf("should be 0:%d\n", ChecParenthesis(str2));
	printf("should be 1:%d\n", ChecParenthesis(str3));

	return 0;
}


void StackPush(stack_t *stack, char new_element)
{
	stack->buffer[stack->size] = new_element;
	++stack->size;
}

char StackPop(stack_t *stack)
{
	--stack->size;
	return stack->buffer[stack->size];
}

char StackPeak(stack_t *stack)
{
	return stack->buffer[stack->size - 1];
}

int StackIsEmpty(stack_t *stack)
{
	return (0 == stack->size);
}


int ChecParenthesis(char *str) 
{   
    stack_t stack = {0, {0}};
	
	while ('\0' != *str)
	{
		if ('(' == *str || '[' == *str || '{' == *str)
		{
			StackPush(&stack, *str);
		}
		else if (')' == *str)
		{
			if (StackPeak(&stack) == '(')
			{
				StackPop(&stack);
			}
			else
			{
				return 0;
			}
		}
		else if (']' == *str)
		{
			if (StackPeak(&stack) == '[')
			{
				StackPop(&stack);
			}
			else
			{
				return 0;
			}
		}
		else if ('}' == *str)
		{
			if (StackPeak(&stack) == '{')
			{
				StackPop(&stack);
			}
			else
			{
				return 0;
			}
		}
		
		++str;
	}
	
    return StackIsEmpty(&stack);
}


