/*
 * stoplight_fsm.c
 *
 *  Created on: Feb 27, 2022
 *      Author: dreyceyalbin
 *
 *  Description:
 *      This file contains the implementation-specific information
 *      for the design of the Buffahiti Traffic Light (PES Assignment 4).
 *      Specifically, the methods and structures defined are used for
 *      creating a modular finite-state-machine.
 */
#include <stdint.h>
#include "tsi_module.h"
#include "LEDPWM.h"
#include "MKL25Z4.h"
#include "log.h"
#include "timer.h"
#define TSI_BASELINE (500)


/*
 * stoplight_state
 *
 * Each state is defined by a particular number
 * in the following Enum.
 */
typedef enum stoplight_state {
	GO_WAIT = 0,
	t_GO2WARNING = 1,
	WARNING_WAIT = 2,
	t_WARNING2STOP = 3,
	STOP_WAIT = 4,
	t_STOP2GO = 5,
	t_CROSS2GO = 6,
	CROSS_WAIT = 7
} stoplight_state;

/*
 * States
 *
 * States can be used as data structures, with
 * the following information per state.
 */

struct States {
	stoplight_state current_state;
	stoplight_state next_state;
	int transition_state;
	RGB_ENTRY color;
	int delay_time;
};

/*
 * state_table
 *
 * For this particular FSM, we define the following
 * table for each state, containing information on
 * delay times, next state, and the state's color.
 */

#ifdef DEBUG
struct States state_table[] =
{
	  {GO_WAIT, t_GO2WARNING, 0, {0x22, 0x96, 0x22}, 5*16},
	  {t_GO2WARNING, WARNING_WAIT, 1, {0xFF, 0xB2, 0x00}, 16},
	  {WARNING_WAIT, t_WARNING2STOP, 0, {0xFF, 0xB2, 0x00}, 3*16},
	  {t_WARNING2STOP, STOP_WAIT, 1, {0x61, 0x1E, 0x3C}, 16},
	  {STOP_WAIT, t_STOP2GO, 0, {0x61, 0x1E, 0x3C}, 5*16},
	  {t_STOP2GO, GO_WAIT, 1, {0x22, 0x96, 0x22}, 16},
	  {t_CROSS2GO, GO_WAIT, 1, {0x22, 0x96, 0x22}, 16},
	  {CROSS_WAIT, t_CROSS2GO, 0, {0x00, 0x10, 0x30}, 16}
};
#else
struct States state_table[] =
{
	  {GO_WAIT, t_GO2WARNING, 0, {0x22, 0x96, 0x22}, 20*16},
	  {t_GO2WARNING, WARNING_WAIT, 1, {0xFF, 0xB2, 0x00}, 16},
	  {WARNING_WAIT, t_WARNING2STOP, 0, {0xFF, 0xB2, 0x00}, 5*16},
	  {t_WARNING2STOP, STOP_WAIT, 1, {0x61, 0x1E, 0x3C}, 16},
	  {STOP_WAIT, t_STOP2GO, 0, {0x61, 0x1E, 0x3C}, 20*16},
	  {t_STOP2GO, GO_WAIT, 1, {0x22, 0x96, 0x22}, 16},
	  {t_CROSS2GO, GO_WAIT, 1, {0x22, 0x96, 0x22}, 16},
	  {CROSS_WAIT, t_CROSS2GO, 0, {0x00, 0x10, 0x30}, 16}
};
#endif


/*
 * global to inidicate CROSSWALK/button press
 */
volatile uint8_t g_cross_walk = 0;

// defined in H file
void read_touchsensor(void) {
	if (Touch_Scan_LH() > TSI_BASELINE) {
		LOG("Button press detected \n\r");
		LOG("Time since startup - %d \n\r", now());
		g_cross_walk = 1;
	} else {
		g_cross_walk = 0;
	}
}

// defined in H file - this is the finite state machine
RGB_ENTRY operate_stoplights(void)
{
	// defines
	static stoplight_state next_state = GO_WAIT;
	static stoplight_state prev_state;
	static uint8_t new_state = 1;
	static RGB_ENTRY current_color;
	// parameters
	int number_of_seconds = 10; // loop CROSSWALK FOR 10 seconds
	/*
	 * Statements
	 */
	if (g_cross_walk == 0) { 	// only run task when NOT in flash mode
		if (new_state) {
			reset_timer();
			new_state = 0;
		}
		// get color
		if (state_table[next_state].transition_state == 1) {
			RGB_ENTRY out_color = state_table[prev_state].color;
			RGB_ENTRY in_color = state_table[next_state].color;
			uint16_t percent = ((float)get_timer() / (float)state_table[next_state].delay_time) * 100;
			current_color = get_transition_color(out_color, in_color, percent);
		} else {
			current_color = state_table[next_state].color;
		};
		turn_on_color(current_color);
		if (get_timer() >= state_table[next_state].delay_time) {
			LOG("TRANSITIONING FROM %d STATE \n\r", state_table[next_state].current_state);
			LOG("TRANSITIONING INTO %d STATE \n\r", state_table[next_state].next_state);
			LOG("Time since startup - %d \n", now());
			prev_state = next_state;
			next_state = state_table[next_state].next_state;
		    new_state = 1;
		}
	}

	/*
	 * If crosswalk
	 */
	if (g_cross_walk == 1) {
		// Define colors
		RGB_ENTRY off_color = {0, 0, 0};
		RGB_ENTRY on_color = {0x00, 0x10, 0x30};

		// transition to off.
        for (float i; i < 16; i++) {
			uint16_t percent = (i / 16) * 100;
			turn_on_color(get_transition_color(current_color, off_color, percent));
			fractional_delay(1);
        }
		turn_on_color(off_color);
		fractional_delay(4); // 1/4th of a second; 250 msec

		// loop N-1 times
		for (int j=1; j < number_of_seconds; j++) {
			turn_on_color(on_color);
			fractional_delay(3*4); // 3/4ths of a second; 750 msec
			turn_on_color(off_color);
			fractional_delay(4); // 1/4ths of a second; 250 msec
		}

		// blink 750 ms ON
		turn_on_color(on_color);
		fractional_delay(3*4); // 3/4ths of a second; 750 msec

		// update information
		new_state = 1;
		next_state = t_CROSS2GO;
		prev_state = CROSS_WAIT;
	}
	return current_color;
}
