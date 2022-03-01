/*
 * stoplight_fsm.c
 *
 *  Created on: Feb 27, 2022
 *      Author: dreyceyalbin
 */
#include <stdint.h>
#include "tsi_module.h"
#include "LEDPWM.h"
#include "MKL25Z4.h"
#include "log.h"
#include "timer.h"


#define TSI_BASELINE (500)



/*
 * Data structures
 */
typedef enum stoplight_state {
	GO_WAIT = 0,
	t_GO2WARNING = 1,
	WARNING_WAIT = 2,
	t_WARNING2STOP = 3,
	STOP_WAIT = 4,
	t_STOP2GO = 5,
	t_CROSS2GO = 6,
	CROSS_WAIT
} stoplight_state;

/*
 * Make a table of States, as defined above
 */

struct States {
	stoplight_state current_state;
	stoplight_state next_state;
	int transition_state;
	RGB_ENTRY color;
	int delay_time;
};

struct States state_table[] =
{
	  {GO_WAIT, t_GO2WARNING, 0, {0x22, 0x96, 0x22}, 5*16},
	  {t_GO2WARNING, WARNING_WAIT, 1, {0xFF, 0xB2, 0x00}, 16},
	  {WARNING_WAIT, t_WARNING2STOP, 0, {0xFF, 0xB2, 0x00}, 5*16},
	  {t_WARNING2STOP, STOP_WAIT, 1, {0x61, 0x1E, 0x3C}, 16},
	  {STOP_WAIT, t_STOP2GO, 0, {0x61, 0x1E, 0x3C}, 5*16},
	  {t_STOP2GO, GO_WAIT, 1, {0x22, 0x96, 0x22}, 16},
	  {t_CROSS2GO, GO_WAIT, 1, {0x22, 0x96, 0x22}, 16},
	  {CROSS_WAIT, t_CROSS2GO, 0, {0x00, 0x10, 0x30}, 16}
};



/*
 * Methods called by active stoplight
 */
volatile uint8_t g_cross_walk = 0;

// read touch sensor by polling
void read_touchsensor(void) {
	LOG("in read sensor \n");
	if (Touch_Scan_LH() > TSI_BASELINE) {
		g_cross_walk = 1;
	} else {
		g_cross_walk = 0;
	}
}

// runs STOPLIGHTS FSM
RGB_ENTRY operate_stoplights(void)
{
	// defines
	static stoplight_state next_state = GO_WAIT;
	static stoplight_state prev_state;
	static uint8_t new_state = 1;
	static RGB_ENTRY current_color;

	/*
	 * Statements
	 */
	if (g_cross_walk == 0) { 	// only run task when NOT in flash mode
		if (new_state) {
			LOG("TRANSITIONING INTO %d STATE \n", state_table[next_state].current_state);
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
			prev_state = next_state;
			next_state = state_table[next_state].next_state;
		    new_state = 1;
		}
	}

	/*
	 * If crosswalk
	 */
	if (g_cross_walk == 1) {
		// blink 250 ms OFF
		RGB_ENTRY off_color = {0, 0, 0};
        for (float i; i < 16; i++) {
			uint16_t percent = (i / 16) * 100;
			turn_on_color(get_transition_color(current_color, off_color, percent));
			fractional_delay(1);
        }
		turn_on_color(off_color);
		fractional_delay(4); // 1/4th of a second; 250 msec

		// blink 750 ms ON
		RGB_ENTRY on_color = {0x00, 0x10, 0x30};
		turn_on_color(on_color);
		fractional_delay(3*4); // 3/4ths of a second; 750 msec

		// update information
		new_state = 1;
		next_state = t_CROSS2GO;
		prev_state = CROSS_WAIT;
	}
	return current_color;
}



