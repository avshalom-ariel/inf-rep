#ifndef __WS14_H__ 
#define __WS14_H__



#define ENDIAN_CHECK2 (*(short *)"\0\xff" & 0xff) ? printf("Big endian\n") : printf("Little endian\n"); 


int MyAtoi(char str[], int base);
void MyItoa(char str[], int num, int base);
size_t Pow(size_t base, int exp);
void AtoiTest(char* str);
void EndianCheck(void);


static char LUT[36] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E',
					   'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S',
					   'T','U', 'V', 'W', 'X', 'Y', 'Z'};

void DoubleParallelArray(char *arr1, char *arr2, char *arr3, size_t size1, size_t size2, size_t size3);


#endif
