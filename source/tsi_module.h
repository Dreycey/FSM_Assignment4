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
 * ERROR CODES:
 *     1. N/A
 */
void init_tsi_touch_sensor();

/*
 * Touch_Scan_LH
 *
 * Description:
 * 	   This function scans the touch sensor for new input
 *
 * Input:
 * 	   The difference from the basal value.
 * ERROR CODES:
 *     1. N/A
 */
int scan_touch_sensor(void);
