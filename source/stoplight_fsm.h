/*
 * stoplight_fsm.h
 *
 *  Created on: Mar 1, 2022
 *      Author: dreyceyalbin
 */

#ifndef STOPLIGHT_FSM_H_
#define STOPLIGHT_FSM_H_


/*
 * Data structures
 */
typedef enum stoplight_state {
	GO_WAIT,
	t_GO2WARNING,
	WARNING_WAIT,
	t_WARNING2STOP,
	STOP_WAIT,
	t_STOP2GO,
	t_CROSS2GO
} stoplight_state;




/*
 * Methods called by active stoplight
 */

/*
 * Function:
 *     ead_touchsensor
 * Description:
 *     This function reads the touch sensor (TSI) on the KL25Z
 * INPUT:
 *     1. N/A - void
 *
 * OUTPUT:
 *     1. N/A - void
 * NOTE:
 *     -- updates a global variable used by the state machine:
 *         'g_cross_walk'
 *         g_cross_walk = 0 IF not being touched
 *         g_cross_walk = 1 IF touched
 */
void read_touchsensor(void);

/*
 * Function:
 *     operate_stoplights(void)
 * Description:
 *     This function implements the finite state machine.
 *
 *     It works by using a table of states that defines the next state, as
 *     well as context about each state, such as color and the associated enum
 *     number with the state.
 * INPUT:
 *     1. N/A - void
 *
 * OUTPUT:
 *     1. RGB_ENTRY - allows for updating a color outside the scope of the FSM
 * NOTES:
 *     **several static variables** are used for keeping track of states:
 *     1. next_state - initialized to GO, this keeps track of the current state.
 *     2. prev_state - keeps track of the last state for transitions.
 *     3. new_state - an indicator that allows for looping until time runs out per state
 *     4. current_color - this doesn't have to be static, but defined as such for flexible design.
 */
RGB_ENTRY operate_stoplights(void);


#endif /* STOPLIGHT_FSM_H_ */
