#ifndef lcd_h
#define lcd_h

   /****************************************************************
	* FILENAME: lcd.h								               *
	* AUTHOR: Dan Kass kassd@msoe.edu    			               *
	* DATE: January 31, 2013						               *
	* CLASS: CE-2811 Basic Temp Lab					               *
	* Provdies: 									               *
	*		Funtion prototypes for the lcd		 	               *
	*		provides output to the lcd				               *
	*		and funtion control to the lcd screen 	               *
	*												               *
	****************************************************************/

#include <inttypes.h>

#define F_CPU	16.00E6
#define UART_BAUD_RATE	9.60E3
#define UBRR_VAL (F_CPU/(UART_BAUD_RATE*16)-1)

#define BS 0x08  //backspace (left)
#define FS 0x09	 //forwardspace (right)
#define LF 0x0a  //line feed
#define FF 0x0c	 //form feed
#define CR 0x0d  //carriage return

#define LIGHTON 0x11  //backlight on
#define LIGHTOFF 0x12  //backlight off

#define DISPLAYOFF 0x15 //display off
#define DISPLAYON 0x16  //default display on

#define ON '1'
#define OFF '0'

/*******************************************************************
*
*	Author: Dan Kass kassd@msoe.edu 
*	Purpose: Initializes the serial communications
*	Parameters: void
*	Returns: void
*	Provides:  This function also initializes the Heartbeat and
*				sound icons into the lcd custom character stops
*				1 and 2 respectivly 
*	
*******************************************************************/
void lcd_init(void);

/*******************************************************************
*
*	Author: Dan Kass kassd@msoe.edu
*	Purpose: Prints a character out to the lcd
*	Parameters: char. The character that is to be printed
*	Returns: void
*	
*******************************************************************/
void lcd_char(char x);

/*******************************************************************
*
*	Author: Dan Kass kassd@msoe.edu
*	Purpose: Prints a string out to the lcd
*	Parameters: char*. The point to the character array for the 
*		string
*	Returns: void
*	
*******************************************************************/
void lcd_string(char *c);

/*******************************************************************
*
*	Author: Dan Kass kassd@msoe.edu
*	Purpose: Puts the lcd curser in the correct x, y corrdinate spot
*	Parameters: uint8_t, uint8_t. row, column
*		(0,0) is the upper left, 0 <= x or y <= 15
*	Returns: void
*	
*******************************************************************/
void lcd_gotoxy(uint8_t x, uint8_t y);

/*******************************************************************
*
*	Author: Dan Kass kassd@msoe.edu
*	Purpose: Clears the lcd and returns the curser to (0,0)
*	Parameters: void
*	Returns: void
*	
*******************************************************************/
void lcd_clear(void);  

/*******************************************************************
*
*	Author: Dan Kass kassd@msoe.edu
*	Purpose: Sends a form feed to the lcd
*	Parameters: void
*	Returns: void
*	
*******************************************************************/
void lcd_ff(void);

/*******************************************************************
*
*	Author: Dan Kass kassd@msoe.edu
*	Purpose: Sends a backspace to the lcd
*	Parameters: void
*	Returns: void
*	
*******************************************************************/
void lcd_left(void);  

/*******************************************************************
*
*	Author: Dan Kass kassd@msoe.edu
*	Purpose: Turns the lcdbacklight on or off
*	Parameters: char. Either "ON" or "OFF" #define 1 and 0
*	Returns: void
*	
*******************************************************************/
void lcd_backlight(char state);
 
/*******************************************************************
*
*	Author: Dan Kass kassd@msoe.edu
*	Purpose: Puts the lcd curser in the correct x, y corrdinate spot
*	Parameters: char. Either "ON" or "OFF" #define 1 and 0
*	Returns: void
*	
*******************************************************************/
void lcd_switch(char state);  

/*******************************************************************
*
*	Author: Dan Kass kassd@msoe.edu
*	Purpose: assigns character array to a custom character spot in
*		the lcd
*	Parameters: uint8_t, char*. 0 to 7 custom character 
*		spot, char pointer to cust character
*	Returns: void
*	
*******************************************************************/
void lcd_define_char(uint8_t num, char *data);
  
/*******************************************************************
*
*	Author: Dan Kass kassd@msoe.edu
*	Purpose: Prints the custom character out to the lcd
*	Parameters: uint8_t. 0 to 7 custom character spot
*	Returns: void
*	
*******************************************************************/
void lcd_custom(uint8_t num); 

#endif
