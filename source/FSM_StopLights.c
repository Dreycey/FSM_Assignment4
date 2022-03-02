
/**
 * @file    Assignment4_FSM_Buffahiti.c
 * @brief   Application entry point.
 *
 * Description:
 *
 *     Primary file for running stop lights
 *     for the people of Buffahiti.
 */
#include <stdio.h>
#include "board.h"
#include "MKL25Z4.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "fsl_debug_console.h"
#include "tsi_module.h"
#include "log.h"
#include "LEDPWM.h"
#include "timer.h"
#include "stoplight_fsm.h"

/*
 * Function:
 *     stoplight_activate(void)
 * Description:
 *     This function is responsible for the embedded while loop that
 *     controls the finite state machine for the traffic lights.
 * INPUT:
 *     1.N/A - void
 * OUTPUT:
 *     1. N/A - void
 * ERROR CODES:
 *     1. N/A
 * NOTES:
 *     - each pass it runs through the FSM and reads the touch sensor.
 *       This allows for flexible design as other sensors may be read.
 */
void stoplight_activate(void) {
	LOG("The main loop is starting \n\r");
	while (1) {
		operate_stoplights();
		read_touchsensor();
	}
}

/*
 * MAIN
 */
int main(void) {
	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();
	#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
	    BOARD_InitDebugConsole();
	#endif
    /* Init board hardware. */

    // Initialize TSI, PWM, and systick
	init_tsi_touch_sensor();
	init_blue_leds_pwm(PWM_PERIOD);
	init_systick();

	// run Finite State Machine
	stoplight_activate();
    return 0;
}
