

#include "fsm.h" /*function declaration*/

enum is_on
{
	ON,
	OFF
};


int main(void)
{
	fsm_t *fsm = FSMCreate();
	
	FSMPrintState(fsm);
	
	FSMSwitch(fsm);
	
	FSMPrintState(fsm);
	
	FSMSwitch(fsm);
	FSMSwitch(fsm);
	
	FSMPrintState(fsm);
	
	FSMSwitch(fsm);
	
	FSMPrintState(fsm);
	
	FSMInput(fsm, 1);
	
	FSMDestroy(fsm);
	
	return 0;
}














