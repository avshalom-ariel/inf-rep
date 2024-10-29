#ifndef HEADER
#define HEADER

#include <stddef.h> /*size_t*/

#define WORD sizeof(int)



void *MyMemset(void *dest, int c, size_t num);

void *MyMemcpy(void *dest, void * src, size_t num);

void *MyMemmove(void *dest, const void *src, size_t num) ;

#endif








