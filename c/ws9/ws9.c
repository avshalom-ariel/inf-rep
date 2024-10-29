

#include <stdio.h> /*printf*/






/*ex1*/
long Pow2(unsigned int x, unsigned int y)
{
	return(x<<y);
}



/*ex2*/ 
int Pow2CheckWithLoop(unsigned int n)
{
	unsigned int i;
	
	i = 1;
	
	while(i < 8 * sizeof(unsigned int ))
	{
		if ((1 << i) == (int)n)
		{
			return 1;
		}
		++i;
	}
	
	return 0;

}



/*ex2*/ 
int Pow2CheckWithoutLoop(unsigned int n)
{
	
	if ((n & (n - 1)) == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}

}



/*ex3*/

int add1( int n)
{
    return (-(~n)); 
}




int ThreeBytePrint(unsigned int* arr, int size)
{
	int i;
	int count;
	unsigned int val;
	
	for(i = 0; i < size; ++i)
	{
		count =0;
		val = arr[i];
		
		while(arr[i])
		{	
			count += arr[i] & 1;
			arr[i] >>= 1;
			/*printf("%d", arr[i]);*/
		}
		if(count == 3)
		{
			printf("%d\n", val);
		}
	}
	
	return 0;
}




unsigned char ByteMirrorLoop(unsigned char byte) 
{
    unsigned char mirrored_byte = 0;
    long unsigned int i;
    
    for (i = 0; i < 8 * sizeof(byte); i++) 
    {
        mirrored_byte <<= 1; 
        mirrored_byte |= (byte & 1); 
        byte >>= 1; 
    }
    
    return mirrored_byte;
}



unsigned char ByteMirror(unsigned char byte) 
{
   byte = (byte & 0xF0) >> 4 | (byte & 0x0F) << 4;
   byte = (byte & 0xCC) >> 2 | (byte & 0x33) << 2;
   byte= (byte & 0xAA) >> 1 | (byte & 0x55) << 1;
   return byte;
}



int True1(unsigned char num)
{
	return (34 == (34 & num));
}



int True2(unsigned char num)
{
	return (0 != (34 & num));
}



int Swap3_5(unsigned char num)
{	
    unsigned char bit3;
    unsigned char bit5;
    
    bit3 = 4 & num;
    bit5 = 16 & num;
    
    bit3 <<= 2;
    bit5  >>= 2;
    
    num = num & (~20);
    num = num + bit3 + bit5;
    
    return num;
    
}



unsigned int CloseDiv16(unsigned int num)
{
	unsigned int first_bit;

	first_bit = 1;
	
	while(num)
	{
		num >>= 1;
		first_bit <<= 1;
	}
	
	
	
	return (first_bit >> 1);
	
}



void Swap(unsigned int* x, unsigned int* y)
{
	if(x != y)
	{
		*x = *x ^ *y;
		*y = *x ^ *y;
		*x = *x ^ *y;
	}
}


void BitPrint(float num)
{
	unsigned int *ptr = (unsigned int *)&num;

    unsigned int binary = *ptr;

	int i = 0;
	
	
    printf("Binary representation of %f is: ", num);
    for (i = sizeof(float) * 8 - 1; i >= 0; i--) {

        printf("%d", (binary >> i) & 1);

        if (i % 4 == 0)
            printf(" ");
    }
    printf("\n");
}


int BitCountLoop(unsigned int num)
{
	int count;
	
	count = 0;
	
	while(num)
	{
		if(1 & num)
		{
			++count;
		}
		num >>= 1;
	}
	
	return count;
}



int BitCount(unsigned int num)
{

    num = num - ((num >> 1) & 0x55555555);
    num = (num & 0x33333333) + ((num >> 2) & 0x33333333);
    num = (((num + (num >> 4)) & 0xF0F0F0F) * 0x1010101) >> 24;
    

    
    return (num );
}


void DoubleBitCount(double d)
{
 unsigned long *double_as_int = (unsigned long *)&d;
 int i;

 for (i=0; i<=63; i++)
   {
    if (i==1)
      printf(" "); 
    if (i==12)
      printf(" "); 

    if ((*double_as_int >> (63-i)) & 1)
      printf("1");
    else
      printf("0");
   }
 printf("\n");
}




void FloateBitCount(float f)
{
 unsigned long *float_as_int = (unsigned long *)&f;
 int i;

 for (i=0; i<=31; i++)
   {
    if (i==1)
      printf(" "); 
    if (i==5)
      printf(" "); 

    if ((*float_as_int >> (31-i)) & 1)
      printf("1");
    else
      printf("0");
   }
   printf("\n");
}


