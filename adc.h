/********************************************
 *	Filename: adc.h							*
 *	Author:   Dan Kass kassd@msoe.edu		*
 *	Date:	  1/31/13						*
 *	Provides:								*
 *		This is the driver for Analong to	*
 *		digital conversion					*
 ********************************************/

#ifndef adc_h
#define adc_h

#include <stdio.h>
#include <avr/interrupt.h>
#include <inttypes.h>

volatile uint8_t adc_done;
volatile uint16_t analog;

/********************************
 *	Initalces the Analog to 	*
 *		digital conversion		*
 ********************************/
	void adc_init(void);

/********************************
 *	returns the ADCH			*
 *		Only need for 8-bit 	*
 *		precision				*
 ********************************/
	int getADCH(void);

/********************************
 *	returns the ADCL			*
 *		Read this first for 	*
 *		bits of precision		*
 ********************************/
	int getADCL(void);

/********************************
 *	set the ADMUX value			*
 *	   ADC Multiplexer Selection*
 *	   Register					* 
 ********************************/
	void setADMUX(uint8_t mux);

/********************************
 *	set the ADCSRA				*
 *	   ADC Control and Status 	*
 *	   Register					*
 ********************************/
	void setADCSRA(uint8_t sra);

/********************************
 *	function that starts the 	*
 *		conversion				*
 ********************************/
	void adc_start_convert(void);

#endif
