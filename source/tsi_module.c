/*
 * tsi_module.c
 *
 *  Created on: Feb 23, 2022
 *      Author: dreyceyalbin
 */
#include <MKL25Z4.H>

#define TOUCH_DATA (TSI0->DATA & 0xFFFF)//macro for extracting the count from data register
#define basal_val 500 // the offset used by DEAN


// Defined in header file.
int Touch_Scan_LH(void)
{
	unsigned int scan = 0;
	TSI0->DATA = 	TSI_DATA_TSICH(9u);
	TSI0->DATA |= TSI_DATA_SWTS_MASK; //software trigger to start the scan
	while (!(TSI0->GENCS & TSI_GENCS_EOSF_MASK )) // waiting for the scan to complete 32 times
	;
	scan = TOUCH_DATA;
	TSI0->GENCS |= TSI_GENCS_EOSF_MASK ; //writing one to clear the end of scan flag
	return scan - basal_val;
}

// Defined in header file.
void Touch_Init()
{
	SIM->SCGC5 |= SIM_SCGC5_TSI_MASK; // enabling the clock
	TSI0->GENCS = TSI_GENCS_MODE(0u) | //operating in non-noise mode
								TSI_GENCS_REFCHRG(0u) | //reference oscillator charge and discharge value 500nA
								TSI_GENCS_DVOLT(0u) | //oscillator voltage rails set to default
								TSI_GENCS_EXTCHRG(0u) | //electrode oscillator charge and discharge value 500nA
								TSI_GENCS_PS(0u) |  // frequency clcok divided by one
								TSI_GENCS_NSCN(31u) | //scanning the electrode 32 times
								TSI_GENCS_TSIEN_MASK | //enabling the TSI module
								TSI_GENCS_EOSF_MASK; // writing one to clear the end of scan flag
}
