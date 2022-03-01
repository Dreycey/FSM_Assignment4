/*
 * timer.c
 *
 *  Created on: Feb 26, 2022
 *      Author: dreyceyalbin
 */
#define F_SYS_CLK (48000000L)
#include "timer.h"
#include "log.h"
#include "MKL25Z4.h"
#include "core_cm0plus.h"
#define LOAD_TICKS ((F_SYS_CLK / 16) / 16) //Alternative clock, 1/16 seconds




volatile ticktime_t temp_time = 0;
volatile ticktime_t startup_time = 0;

void init_systick(void) {
	// SysTick is defined in core_cm0.h
	SysTick->LOAD = (LOAD_TICKS) - 1; //ISR every 1/16 seconds
	// Set interrupt priority
	NVIC_SetPriority(SysTick_IRQn, 3);
	// Force load of reload value
	SysTick->VAL = 0;
	// Enable interrupt, enable SysTick timer
	SysTick->CTRL =  SysTick_CTRL_TICKINT_Msk |
			         SysTick_CTRL_ENABLE_Msk;
}

/* Based off Dean Listing 7.2 */
void SysTick_Handler(void) {
	startup_time++;
	temp_time++;
}

ticktime_t now() {
	return startup_time;
}

void reset_timer() {
	LOG("TIME RESET \n");
	temp_time = 0;
}

ticktime_t get_timer() {
	return temp_time;
}

void fractional_delay(uint16_t second_fractions)
{
	reset_timer();
	while(temp_time <= (ticktime_t)second_fractions)
	{
	}
}
