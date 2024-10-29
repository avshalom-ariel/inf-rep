
#include <stdio.h>	/*printf*/
#include <time.h>	/*time_t, time*/

#include "sum_of_div.h"

time_t g_start_time;
time_t g_end_time;

int main(void)
{
	int num_to_check = 1000000000;

	g_start_time = time(NULL);

	printf("sum of divisor: %ld\n", SumOfDiv(num_to_check));

	g_end_time = time(NULL);

	printf("performence without threads: %ld\n", g_end_time - g_start_time);

	g_start_time = time(NULL);

	printf("sum of divisor: %ld\n", SumOfDivThreads(num_to_check));

	g_end_time = time(NULL);

	printf("performence with threads: %ld\n", g_end_time - g_start_time);

	return 0;
}


