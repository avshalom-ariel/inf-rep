
#include <stdio.h>
#include <unistd.h>

int main(void)
{
	size_t i = 0;
	
	for (; i < 3; ++i)
	{
		printf("im running!\n");
		
		sleep(5);
	}

	return 0;
}
