



#ifndef __WS8_H__
#define __WS8_H__

void Print(int num);


#define MAX_LENGTH 300 



int loggit(void);

int Cmp_rmv (char* str);
int Cmp_cnt (char* str);
int Cmp_ext (char* str);

enum results 
{
  RESULT
}; 

enum results Invoke_rmv(char* fname);
enum results Invoke_cnt(char* fname);
enum results Invoke_ext(char* fname);


#endif


