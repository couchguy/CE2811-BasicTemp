/********************************************
 *	Filename: basicTemp.c					*
 *	Author:   Dan Kass kassd@msoe.edu		*
 *	Date:	  1/31/13						*
 *	Provides:								*
 *		This is the main function for the 	*
 *		Analong Digital Converter to read	*
 *		the temperature						*
 ********************************************/

#include "adc.h"
#include "lcd.h"
#include "timer.h"
#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>
#include <util/delay.h>
#include <avr/interrupt.h>

FILE lcd_stream = FDEV_SETUP_STREAM(lcd_char, NULL, _FDEV_SETUP_WRITE);

int main(void)
{

 uint8_t tempurature = 0;
 uint8_t maxtemp =0;
 uint8_t heartmon = 0;
 timer = 0;
 adc_done = 0;
 analog = 0;

 //Initalization
 adc_init();
 lcd_init();
 timer_init();


 //setup printf
 stdout = &lcd_stream;

 //sets portb data direction register
 DDRB = 0xFF;

 //
 lcd_clear();
 lcd_gotoxy(0,7);
 lcd_custom(1);
 _delay_ms(250);
 lcd_clear();
 _delay_ms(250);
 lcd_clear();
 lcd_gotoxy(0,7);
 lcd_custom(1);
 _delay_ms(250);
 lcd_clear();
 _delay_ms(250);

 sei();
 while(1)
 {

	if(timer)
	{
		//just telling main that
		//the timer hit a 1/4 of a
		//second and that adc has started
		timer = 0;
		adc_start_convert();
		if(heartmon)
		{
			lcd_gotoxy(1,15);
			lcd_custom(1); //heart
			heartmon = 0;
		}
		else
		{
			lcd_gotoxy(1,15);
			printf(" ");
			heartmon = 1;
		}
	}
	
	if(adc_done)
	{
		adc_done = 0;
		lcd_gotoxy(0,0);
		
		tempurature = ((analog*5.0)/256)*100;	

		printf("T=%2d F  MAX=%2d F",tempurature, maxtemp);
		lcd_gotoxy(0,4);
		lcd_custom(3); //degree symbol
		lcd_gotoxy(0,14);
		lcd_custom(3); //degree symbol

		lcd_gotoxy(1,14);
		lcd_custom(2); //music note
		
	}
	if(tempurature > maxtemp)
	{
		//alert for 1ms when new max temp
		PORTB = 0xFF;
		_delay_ms(1);
		PORTB = 0x00;
		
		//sets the new max temp 4
		//degrees higher
		maxtemp = tempurature +4;
		lcd_clear();
		printf("New Max Temp!!!!");
		_delay_ms(1000);
		//lcd_clear();
	}

 }
return 0;
}


