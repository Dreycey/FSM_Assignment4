/*
 * LEDPWM.c
 *
 *  Created on: Feb 25, 2022
 *      Author: dreyceyalbin
 */

#include "LEDPWM.h"
#include "MKL25Z4.h"
#define gpio_mask(x) (1UL << (x))

// Defined in Header file
void init_blue_leds_pwm(uint16_t period){
	// Enable clock to port D and B
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK | SIM_SCGC5_PORTB_MASK;

	/*
	 * Set Alternative MUX
	 */
	// SET RED MUX [ALT 3]
	PORTB->PCR[RED_PCR] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[RED_PCR] |= PORT_PCR_MUX(3);
	// SET GREEN MUX [ALT 3]
	PORTB->PCR[GREEN_PCR] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[GREEN_PCR] |= PORT_PCR_MUX(3);
	// SET BLUE MUX [ALT 4]
	PORTD->PCR[BLUE_LED_POS] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[BLUE_LED_POS] |= PORT_PCR_MUX(4);

	/*
	 * TPM Settings (clock)
	 */
	// Configure TPM [Blue-TPM0; Green-TPM2; Red-TPM2]
	SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK | SIM_SCGC6_TPM2_MASK;
	//set clock source for tpm: 48 MHz
	SIM->SOPT2 |= (SIM_SOPT2_TPMSRC(1) | SIM_SOPT2_PLLFLLSEL_MASK);
	//load the counter and mod
	TPM0->MOD = period-1;
	TPM2->MOD = period-1;
	//set TPM count direction to up with a divide by 2 prescaler
	TPM0->SC =  TPM_SC_PS(1);
	TPM2->SC =  TPM_SC_PS(1);
	// Continue operation in debug mode
	TPM0->CONF |= TPM_CONF_DBGMODE(3);
	TPM2->CONF |= TPM_CONF_DBGMODE(3);

	/*
	 * Channel settings
	 * Order for all: R, G, B
	 */
	// Set channels to edge-aligned low-true PWM
	TPM2->CONTROLS[0].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;
	TPM2->CONTROLS[1].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;
	TPM0->CONTROLS[1].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;
	// Set initial duty cycle
	TPM2->CONTROLS[0].CnV = 0;
	TPM2->CONTROLS[1].CnV = 0;
	TPM0->CONTROLS[1].CnV = 0;
	// Start TPM
	TPM2->SC |= TPM_SC_CMOD(1);
	TPM2->SC |= TPM_SC_CMOD(1);
	TPM0->SC |= TPM_SC_CMOD(1);
}

// Defined in Header file
void turn_on_color(RGB_ENTRY color) {
	TPM2->CONTROLS[0].CnV = color.R;
	TPM2->CONTROLS[1].CnV = color.G;
	TPM0->CONTROLS[1].CnV = color.B;
}

// Defined in Header file
RGB_ENTRY get_transition_color(RGB_ENTRY color1, RGB_ENTRY color2, uint16_t percent){
	RGB_ENTRY transition_color;
	transition_color.R = color1.R + percent*(color2.R - color1.R)/100;
	transition_color.G = color1.G + percent*(color2.G - color1.G)/100;
	transition_color.B = color1.B + percent*(color2.B - color1.B)/100;
    return transition_color;
}
