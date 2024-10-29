#include <stdio.h>


size_t MaxCharLUT(size_t *char_LUT);

static size_t char_LUT[256] = {0}; 

void MillionChar(char ch)
{	
	if('0' != ch)
	{
		char_LUT[(int)ch] += 1;
	}
	else
	{
		printf("%ld", MaxCharLUT(char_LUT));
		char_LUT[256] = {0};
	}	
}



size_t MaxCharLUT(size_t *char_LUT)
{
	size_t max = 0;
	size_t i = 11;
	
	for (; i < 256; ++i)
	{
		if(char_LUT[i] > max)
		{
			max = char_LUT[i];
		}
	}
	
	
	return max;

}


int main(void)
{
	MillionChar('A');
	MillionChar('A');
	MillionChar('A');
	MillionChar('B');
	MillionChar('B');
	MillionChar('C');
	MillionChar('D');
	MillionChar('E');
	MillionChar('0');
	
	return 0;
}


