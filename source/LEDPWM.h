/*
 * LEDPWM.h
 *
 *  Created on: Feb 25, 2022
 *      Author: dreyceyalbin
 */

#ifndef LEDPWM_H_
#define LEDPWM_H_

#include "MKL25Z4.h"
#define PWM_PERIOD (255)
#define FULL_ON (PWM_PERIOD-1)
#define FULL_OFF (0)
#define RED_LED_POS (18)		// on port B
#define GREEN_LED_POS (19)	// on port B
#define BLUE_LED_POS (1)		// on port D
#define RED_PCR (18)		// on port B
#define GREEN_PCR (19)	// on port B
#define BLUE_PCR (1)		// on port D

/*
 * RBG_ENTRY
 *
 * Description:
 *     This structure is used to hold the int values for
 *     Red, Green and Blue
 *     Values - 1-255 expected; 256 is error
 */
typedef struct {
	uint8_t R, G, B;
} RGB_ENTRY;

/*
 * Function:
 *     turn_on_color(RGB_ENTRY color)
 * Description:
 *     This function turns on internal LED lights to a certain value
 *     based on the input RGB_ENTRY values.
 * INPUT:
 *     RGB_ENTRY struct [defined as struct with uint8_t R, G, B;]
 *
 * OUTPUT:
 *     void
 *     -- TPM2 and TPM0 of KL25z to change lights.
 */
void turn_on_color(RGB_ENTRY color);

/*
 * Function:
 *     Init_Blue_LED_PWM(uint16_t period)
 * Description:
 *     This function initializes the PWM system for the LEDs on the KL25Z.
 * INPUT:
 *     Period for the MOD of the PWM.
 * OUTPUT:
 *     void
 *     -- PWM LED system is ready
 */
void Init_Blue_LED_PWM(uint16_t period);

/*
 * Function:
 *     get_transition_color
 * Description:
 *     This function returns a transition color based on two inputs and
 *     a percent of transition (percent being 0-100).
 * INPUT:
 *     1.color1 - an RGB_ENTRY that is current
 *     2.color2 - an RGB_ENTRY that is the next state
 *     3.percent - a percent value 0-100 representing how far along in transition
 * OUTPUT:
 *     RGB_ENTRY
 *     -- a color struct with new values
 */
RGB_ENTRY get_transition_color(RGB_ENTRY color1, RGB_ENTRY color2, uint16_t percent);

#endif /* LEDPWM_H_ */
