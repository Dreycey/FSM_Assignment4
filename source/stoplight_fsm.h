/*
 * stoplight_fsm.h
 *
 *  Created on: Mar 1, 2022
 *      Author: dreyceyalbin
 */

#ifndef STOPLIGHT_FSM_H_
#define STOPLIGHT_FSM_H_


/*
 * stoplight_fsm.c
 *
 *  Created on: Feb 27, 2022
 *      Author: dreyceyalbin
 */

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

// read touch sensor by polling
void read_touchsensor(void);

// runs STOPLIGHTS FSM
RGB_ENTRY operate_stoplights(void);


#endif /* STOPLIGHT_FSM_H_ */
