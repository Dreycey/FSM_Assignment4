/*
 * Code used  from Dean Alexander
 *
 * Note that he used channel 10, where as
 * here channel 9 is being used.
 *
 *
 * URL: https://github.com/alexander-g-dean/ESF/blob/master/NXP/Misc/Touch%20Sense/TSI/src/main.c
 */



/*
 * Touch_Init
 *
 * Description:
 * 	   This function intializes the touch sensor
 *
 * Input:
 * 	   N/A - void
 */
void Touch_Init();

/*
 * Touch_Scan_LH
 *
 * Description:
 * 	   This function scans the touch sensor for new input
 *
 * Input:
 * 	   The difference from the basal value.
 */
int Touch_Scan_LH(void);
