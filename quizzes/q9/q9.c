#include <stdio.h>

#define MAX2(a,b) (a < b) ? b : a
#define MAX3(a,b,c) MAX2(a, MAX2(b,c))
#define TO_LOWER(a) (a > 90) ? (a = a) : (a = a + 32)
#define OFFSET(s, f) (size_t)&(((s *)0)->f) 



struct my_struct 
{
	char ch1;
	int num;
	char ch2;
	char ch3;
	long num_long;
};



struct s 
{
	int num;
	char ch1;
	int *ptr;
	char ch2;
};



typedef struct
{
	int num;
	char ch1;
} s1;


union u
{
	int num;
	char ch1;
} u1;




int main(void)
{
	int a = 1;
	int b = 2;
	int c = 3;
	char ch1 = 'A';
	char ch2 = 'a';
	

	
	
	
	
	
	 
	printf("%d\n", MAX3(a,b,c));
	
	printf("%c\n", TO_LOWER(ch1));
	
	printf("%c\n", TO_LOWER(ch2));
	
	printf( "%ld\n", OFFSET(struct my_struct, ch1));
	
	printf("%ld\n", sizeof(struct s));
	
	printf( "%ld\n", OFFSET(struct s, ch2));
	
	printf("%ld\n", sizeof(union u));
	
	return 0;
}
