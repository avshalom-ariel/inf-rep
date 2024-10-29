/*
Author: Avshalom Ariel
Review by: 
Review date:
Status:
*/

#include <stdio.h> 	/*printf*/
#include <stdlib.h> /*malloc free*/
#include <assert.h> /*assert*/

#include "fsm.h" 	/*typedef, function declarations*/

enum is_on
{
	ON,
	OFF
};

struct fsm
{
	enum is_on state;
};

fsm_t *FSMCreate(void)
{
	fsm_t *fsm = (fsm_t *)malloc(sizeof(fsm_t));
	if (NULL == fsm)
	{
		return NULL;
	}
	
	fsm->state = ON;
	
	return fsm;
}


void FSMDestroy(fsm_t *fsm)
{
	assert(fsm);
	
	free(fsm);
}


void FSMInput(fsm_t *fsm, int input)
{
	assert(fsm);
	
	fsm->state = input;
}


void FSMSwitch(fsm_t *fsm)
{
	assert(fsm);
	
	if (ON == fsm->state)
	{
		fsm->state = OFF;
	}
	else
	{
		fsm->state = ON;
	}
}


void FSMPrintState(fsm_t *fsm)
{
	assert(fsm);
	
	if (ON == fsm->state)
	{
		printf("current state is: ON\n");
	}
	else
	{
		printf("current state is: OFF\n");
	}
}


