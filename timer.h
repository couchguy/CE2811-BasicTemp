/********************************************
 *	Filename: timer.h						*
 *	Author:   Dan Kass kassd@msoe.edu		*
 *	Date:	  2/7/13						*
 *	Provides:								*
 *		This is the driver for the timer	*
 ********************************************/

#ifndef timer_h
#define timer_h

#include <avr/interrupt.h>
#include <inttypes.h>

volatile uint8_t timer;

/****************************
 * Initalizes the time for  *
 *	quater second intervals *
 ****************************/
void timer_init(void);


#endif
