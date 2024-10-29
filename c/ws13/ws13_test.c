#include "header.h"
#include<stdio.h> /*printf*/
#include<string.h> /*stdcpy*/



int main(void)
{
	char src[20];
	char dest[20];
	char *unaligned_ptr;
	char *aligned_ptr = src;
	
	strcpy(src, "abcdefghijk");
	
	++aligned_ptr;
	unaligned_ptr = aligned_ptr;
	
	printf("before memset source is: %s\n", src);	
	
	printf("offset of src is: %ld\n", (long int)src % WORD);
	printf("offset of unaligned_ptr is: %ld\n", (long int)unaligned_ptr % WORD);
	
	MyMemset(unaligned_ptr, 'h', 5);
	
	printf("after memset source is: %s\n", unaligned_ptr);	

	printf("before memcpy:\nsource is: %s\ndest is:%s\n", src, dest);	
	
	MyMemcpy(dest, src, 8);
	
	printf("after memcpy:\nsource is: %s\ndest is:%s\n", src, dest);	

	printf("before memmove:\nsource is: %s\ndest is:%s\n", src, dest);	
	
	printf("offset of src is: %ld\n", (long int)src % WORD);
	printf("offset of unaligned_ptr is: %ld\n", (long int)(src + 4) % WORD);
	
	MyMemmove(src, src + 4, 4);
	
	printf("after memmove:\nsource is: %s\ndest is:%s\n", src, dest);	
	return 0;
}


