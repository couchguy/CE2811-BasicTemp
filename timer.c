/********************************************
 *	Filename: timer.c						*
 *	Author:   Dan Kass kassd@msoe.edu		*
 *	Date:	  2/7/13						*
 *	Provides:								*
 *		This is the driver for the timer	*
 ********************************************/

#include "timer.h"
#include <avr/interrupt.h>
#include <inttypes.h>
#include <util/delay.h>

volatile uint8_t count = 0;
/****************************
 * Initalizes the time for  *
 *	quater second intervals *
 ****************************/
void timer_init(void)
{
	//FOC0 WGM00 COM01 COM00 WGM01 CS02 CS01 CS00
	TCCR0 = 0b00000101;
	TCNT0 = 0;  //Initial Counter Value
	OCR0 = 255; //Count too
	TIMSK = (1<<OCIE0); //timer compare match
}

ISR(TIMER0_COMP_vect)
{
	//it takes 15 times for the counter to go through
	//255 to be about a quarter of a second
	if( count  == 15)
	{
		timer = 1;
		//starts the ADC conversion every
		//1/4 of second
	
	while (ADCSRA & (1<<ADSC));
		count =0;
	}
	else
	{
		count++;
	}
}
