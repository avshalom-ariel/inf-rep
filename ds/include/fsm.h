#ifndef __FSM_H__
#define __FSM_H__

typedef struct fsm fsm_t;

fsm_t *FSMCreate(void);
void FSMDestroy(fsm_t *fsm);
void FSMInput(fsm_t *fsm, int input);
void FSMSwitch(fsm_t *fsm);
void FSMPrintState(fsm_t *fsm);

#endif /*__FSM_H__*/
