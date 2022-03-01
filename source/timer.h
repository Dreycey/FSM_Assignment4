/*
 * timer.h
 *
 *  Created on: Feb 26, 2022
 *      Author: dreyceyalbin
 */

#ifndef TIMER_H_
#define TIMER_H_
#include <stdint.h>

typedef uint32_t ticktime_t;  // time since boot, in sixteenths of a second

void init_systick(void);
ticktime_t now(); // returns time since startup, in sixteenths of a second
void reset_timer(); // resets timer to 0; doesn't affect now() values
ticktime_t get_timer();  // returns ticks since the last call to reset_timer()
void fractional_delay(uint16_t second_fractions);

#endif /* TIMER_H_ */
