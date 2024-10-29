#include <stdio.h> /* sizeof printf */
#include <stdlib.h> /* malloc */
#include <string.h> /* strcpy */
#include "programer.h" /*AddInt AddFloat AddString AddElem PrintInt PrintFloat PrintString PrintElem Clean CleanElem DoNothing*/
#include "user.h" /*PrintAll AddAll CleanAll*/


int main(void)
{
	element_t arr[4];
	char *str_element = NULL;
	int first_int_element = 11;
	float float_element = 77.777;
	int second_int_element = 44;
	
	int num_to_add = 55;
	
	element_t first_element;
	element_t second_element; 
	element_t third_element;
	element_t fourth_element;
	
	str_element = (char*)malloc(15);
	
	if (NULL == str_element)
	{
		printf("error in str_element malloc\n");
		return -1;
	}
	
	strcpy(str_element, "string element");
	
	
	first_element.element =  &first_int_element;
	first_element.add =  AddInt;
	first_element.print =  PrintInt;
	first_element.clean =  DoNothing;
	
	second_element.element = &float_element;
	second_element.add = AddFloat;
	second_element.print = PrintFloat;
	second_element.clean = DoNothing;
	
	third_element.element = &str_element;
	third_element.add = AddString;
	third_element.print = PrintString;
	third_element.clean = Clean;
	
	fourth_element.element = &second_int_element;
	fourth_element.add = AddInt;
	fourth_element.print = PrintInt;
	fourth_element.clean = DoNothing;

	arr[0] = first_element;
	arr[1] = second_element;
	arr[2] = third_element;
	arr[3] = fourth_element;
	
	printf("Print all on initial array gives:\n");
	PrintAll(arr, 4);
	
	AddAll(arr, 4, num_to_add);
	
	printf("Print all after adding %d to array gives:\n", num_to_add);
	PrintAll(arr, 4);
	
	CleanAll(arr, 4);
	
	return 0;
}












































