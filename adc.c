/********************************************
 *	Filename: adc.c							*
 *	Author:   Dan Kass kassd@msoe.edu		*
 *	Date:	  1/31/13						*
 *	Provides:								*
 *		This is the driver for Analong to	*
 *		digital conversion					*
 ********************************************/

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>
#include <util/delay.h>
#include "adc.h"

/********************************
 *	Initalces the Analog to 	*
 *		digital conversion		*
 ********************************/
void adc_init(void)
{
	setADMUX(0b01100000);

	//ADEN ADSC ADATE ADIF ADIE ADPS2 ADPS1 ADPS0
	setADCSRA(0b11011111);

	DDRB = 0xFF;
}

/********************************
 *	returns the ADCH			*
 ********************************/
int getADCH(void)
{
	return ADCH;
}

/********************************
 *	returns the ADCL			*
 ********************************/
int getADCL(void)
{
	return ADCL;
}

/********************************
 *	set the ADMUX value		*
 *	   ADC Multiplexer Selection*
 *	   Register					* 
 ********************************/
void setADMUX(uint8_t mux)
{
	ADMUX = mux;
}

/********************************
 *	set the ADCSRA				*
 *	   ADC Control and Status 	*
 *	   Register					*
 ********************************/
void setADCSRA(uint8_t sra)
{
	ADCSRA = sra;
}

/********************************
 *	function that starts the 	*
 *		conversion				*
 ********************************/
void adc_start_convert(void)
{
	uint8_t temp = ADCSRA;
	temp = temp | (1<<ADSC);
	ADCSRA = temp;
	
	while (ADCSRA & (1<<ADSC));
	
}

/********************************
 *	ISR							*
 *		for the ADC				*
 ********************************/
 ISR(ADC_vect)
 {
	adc_done = 1;
	analog = ADCH;
	
	//43 is the number that is equivlant to 84 
	//degrees 
	if(analog >= 43)
	{
		PORTB = 0xFF;
	}
	else
	{
		PORTB = 0x00;
	}
 }


