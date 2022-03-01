/*
 * UART.h
 *
 *  Created on: Feb 25, 2022
 *      Author: dreyceyalbin
 *
 *  Description:
 *      From Dean
 *      URL: https://github.com/alexander-g-dean/ESF/blob/master/NXP/Misc/Touch%20Sense/TSI/src/UART.c
 */
#ifndef UART_H
#define UART_H

#include <stdint.h>
#include <MKL25Z4.H>


#define UART_OVERSAMPLE_RATE 	(16)
#define SYS_CLOCK							(48e6)

void Init_UART0(uint32_t baud_rate);
void UART0_Transmit_Poll(uint8_t data);
uint8_t UART0_Receive_Poll(void);

void Send_String_Poll(uint8_t * str);
#endif
