#ifndef PROGRAMER_H
#define PROGRAMER_H

typedef void (*func_ptr)();

typedef struct element
{
	void *element;
	func_ptr add;
	func_ptr print;
	func_ptr clean;
} element_t;



void AddInt(int *ptr_int, int num_to_add);
void AddFloat(float *ptr_float, int num_to_add);
void AddString(char **ptr, int num_to_add);
void PrintInt(int *ptr);
void PrintFloat(float *ptr);
void PrintString(char **ptr);
void Clean(char **ptr);
void CleanElem(void *elem);
void DoNothing();

#endif































