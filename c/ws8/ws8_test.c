


#include "ws8.h"



struct print_me 
{
  int num;
  void (*Print)(int);
};




int main(void) 
{
  int i;
  struct print_me arr[10] = {0};
  
  for (i = 0; i < 10; ++i)
  {
  		arr[i].num = i;
  		arr[i].Print = &Print;
  		
  		(arr[i].Print)(arr[i].num);
  }
  
  loggit();
  
  return 0;
  
} 



