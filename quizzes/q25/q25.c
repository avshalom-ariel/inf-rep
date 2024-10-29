#include <stdio.h> /*printf*/


void foo()
{
	int *pi = NULL;
	int a = 1, b = 2, c = 3;
	const char *c_str = "abcd";
	char *p_str = (char *)c_str;
	char arr_str[] = "abcd";
	const char ch = 0;
	short *ps = NULL;

	printf("%s\n", c_str + 1);
	printf("%lu\n", sizeof(c_str));
	printf("%s\n", arr_str + 1);
	printf("%lu\n", sizeof(arr_str));
	printf("%s\n", p_str);
	printf("%lu\n", sizeof(p_str));
	
	printf("%lu\n", sizeof(*ps));
	printf("%lu\n", sizeof(*pi));

	pi = &c;
	*pi = a;
	b = *pi;

	/*c_str[2] = '0';*/
	printf("%s\n", c_str);
	*(arr_str + 1) = '0';
	printf("%s\n", arr_str);
	/*++arr_str;*/
	printf("%s\n", arr_str);

	p_str = (char*)&c + 3;
	*p_str = '1';
	printf("%d\n", c);

	pi = (int*)&ch;
	*pi = 0;
	
	printf("%d\n", *pi);

	
	(void)b;
}


int main(void)
{
	foo();
	
	return 0;	
}






