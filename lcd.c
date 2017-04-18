   /****************************************************************
	* FILENAME: lcd.c								               *
	* AUTHOR: Dan Kass kassd@msoe.edu    			               *
	* DATE: January 31, 2013						               *
	* CLASS: CE-2811 Basic Temp Lab					               *
	* Provdies: 									               *
	*		Funtion for the lcd					 	               *
	*		provides output to the lcd				               *
	*		and funtion control to the lcd screen 	               *
	*												               *
	****************************************************************/

#include <avr/io.h>
#include <inttypes.h>
#include <util/delay.h>

#include "lcd.h"

/*******************************************************************
*
*	Author: Dan Kass kassd@msoe.edu 
*	Purpose: Initializes the serial communications
*	Parameters: void
*	Returns: void
*	
*******************************************************************/
void lcd_init(void)
{
	//sets up the usart
	UBRRH = 0;
	UBRRL = UBRR_VAL; 	// 9600 baud
	UCSRB = (1<<TXEN);	// Enable Tx 
	
	//turns on the lcd and the backlight
	lcd_char(DISPLAYON);
	lcd_char(LIGHTON);

	_delay_ms(125);
	//inits the Heart shape, Music note, and degree sybmol
	lcd_sound_icon();
	lcd_degree_icon();
	lcd_heartbeat_icon();
}

/*******************************************************************
*
*	Author: Dan Kass kassd@msoe.edu
*	Purpose: Prints a character out to the lcd
*	Parameters: char. The character that is to be printed
*	Returns: void
*	
*******************************************************************/	
void lcd_char(char x)
{
		while(!(UCSRA&(1<<UDRE)));	// Wait for UDR empty
		_delay_ms(25);
		UDR = x;					// Send char
}

/*******************************************************************
*
*	Author: Dan Kass kassd@msoe.edu
*	Purpose: Prints a string out to the lcd
*	Parameters: char. The point to the character array for the 
*		string
*	Returns: void
*	
*******************************************************************/
void lcd_string(char *c)
{
	for(int i=0; c[i] != 0; i++)
	{
		lcd_char(c[i]);
	}
	lcd_char(CR);
	lcd_char(LF);
}

 /*******************************************************************
*
*	Author: Dan Kass kassd@msoe.edu
*	Purpose: Puts the lcd curser in the correct x, y corrdinate spot
*	Parameters: uint8_t, uint8_t. row, column
*		(0,0) is the upper left, 0 <= x or y <= 15
*	Returns: void
*	
*******************************************************************/
void lcd_gotoxy(uint8_t x, uint8_t y)
{
	uint8_t output = 128; //cursor at line 0 position 0
	//makes sure the x and y corridnates fit within the lcd screen
	if((x <= 1) && (y <= 15))
	{
		//0 line is 128 + y for each position
		//1 line is 148 + y for each position
		output += (x*20) + y;
	}
	lcd_char(output);
}

/*******************************************************************
*
*	Author: Dan Kass kassd@msoe.edu
*	Purpose: Clears the lcd and returns the curser to (0,0)
*	Parameters: void
*	Returns: void
*	
*******************************************************************/
void lcd_clear(void)
{
	lcd_ff();
}

/*******************************************************************
*
*	Author: Dan Kass kassd@msoe.edu
*	Purpose: Sends a form feed to the lcd
*	Parameters: void
*	Returns: void
*	
*******************************************************************/
void lcd_ff(void)
{
	lcd_char(FF);
	_delay_ms(25);
}

/*******************************************************************
*
*	Author: Dan Kass kassd@msoe.edu
*	Purpose: Sends a backspace to the lcd
*	Parameters: void
*	Returns: void
*	
*******************************************************************/
void lcd_left(void)
{
	lcd_char(BS);
}

/*******************************************************************
*
*	Author: Dan Kass kassd@msoe.edu
*	Purpose: Turns the lcdbacklight on or off
*	Parameters: char. Either "ON" or "OFF" #define 1 and 0
*	Returns: void
*	
*******************************************************************/
void lcd_backlight(char state)
{
	// sets the light to ON as default
	uint8_t backlight = LIGHTON;
	if ( state == '0' )
	{
		// sets the light to off
		backlight = LIGHTOFF;
	}
	lcd_char(backlight);
}
 
/*******************************************************************
*
*	Author: Dan Kass kassd@msoe.edu
*	Purpose: Puts the lcd curser in the correct x, y corrdinate spot
*	Parameters: char. Either "ON" or "OFF" #define 1 and 0
*	Returns: void
*	
*******************************************************************/
void lcd_switch(char state)
{
	// sets the power to OFF as default
	uint8_t power = DISPLAYOFF;
	if ( state == '1' )
	{
		//turns the back light on then turns on the display
		lcd_backlight(ON);
		// sets the display on cursor on and character blink
		power = DISPLAYON;
	}
	else
	{
		//When the Display goes off the back light will also go off.
		lcd_backlight(OFF);
	}
	lcd_char(power);
}

/*******************************************************************
*
*	Author: Dan Kass kassd@msoe.edu
*	Purpose: assigns character array to a custom character spot in
*		the lcd
*	Parameters: uint8_t, char*.0 to 7 custom character 
*		spot,char pointer to custom character
*	Returns: void
*	
*******************************************************************/
void lcd_define_char(uint8_t num, char *data)
{
	lcd_char(num+247);
	for(int i=0; i < 8; i++)
	{
		lcd_char(data[i]);
	}
	_delay_ms(250); //so the initalization can end
}
  
/*******************************************************************
*
*	Author: Dan Kass kassd@msoe.edu
*	Purpose: Prints the custom character out to the lcd
*	Parameters: uint8_t. 0 to 7 custom character spot
*	Returns: void
*	
*******************************************************************/
void lcd_custom(uint8_t num)
{
	if(num <= 8)
	//num works becasue the custom chars codes are 0-7
	//and will be stored in the same style
	lcd_char(num-1);
}

/******************************************************************
*
*	Author: Dan Kass kassd@msoe.edu
*	Purpose: sets the custom character heartbeat to lcd's custom 1
*				spot
*	Parameters: none
*	Returns: void
*
*******************************************************************/
void lcd_heartbeat_icon(void)
{
	char custom[] = {0b00000000,
					 0b00001010,
	                 0b00011111,
					 0b00011111,
					 0b00001110,
					 0b00001110,
					 0b00000100,
					 0b00000000};
   	char *ptr = custom;
	lcd_define_char(1, ptr);
}
/******************************************************************
*
*	Author: Dan Kass kassd@msoe.edu
*	Purpose: sets the custom character music note to lcd's custom 2
*				spot
*	Parameters: none
*	Returns: void
*
*******************************************************************/
void lcd_sound_icon(void)
{
	char custom[] = {0b00000011,
					 0b00000101,
	                 0b00001001,
					 0b00010001,
					 0b00010000,
					 0b00010000,
					 0b00010000,
					 0b00000000};
	char *ptr = custom;
	lcd_define_char(2, ptr);
}

/******************************************************************
*
*	Author: Dan Kass kassd@msoe.edu
*	Purpose: sets the custom character degree symbol to lcd's custom 
*			3 spot
*	Parameters: none
*	Returns: void
*
*******************************************************************/
void lcd_degree_icon(void)
{
	char custom[] = {0b00000000,
					 0b00000110,
	                 0b00001001,
					 0b00001001,
					 0b00000110,
					 0b00000000,
					 0b00000000,
					 0b00000000};
	char *ptr = custom;
	lcd_define_char(3, ptr);
}
