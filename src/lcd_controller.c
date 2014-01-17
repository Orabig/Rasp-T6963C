  
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "gpio.h" 
#include "lcd_register.h" 
#include "lcd_command.h" 

/*
* Initialize the LCD screen with the given parameters
* textStart : The start address of the text memory
* graphicStart : The startAddress of the graphic memory
* fontSize : 0 for 6x8 characters, 1 for 8x8 characters
*/
void LCD_init(int textStart, int graphicStart, short fontSize) {
	// Set up gpi pointer for direct register access
	gpio_setup();
	LCD_setup();

	LCD_FontSelect( fontSize );

	int lineGap = fontSize ? 0x1E : 0x28;  

	// Set text Home Address
	LCD_command_2D( 0x40, textStart );

	// Set text area
	LCD_command_2D( 0x41, lineGap );

	// Set graphic Home Address
	LCD_command_2D( 0x42, graphicStart );

	// Set Graphic area
	LCD_command_2D( 0x43, lineGap );  
}

/*
* Set mode for the LCD screen
*/
void LCD_mode(int mode) {
	LCD_command( 0x80 + mode );
}

void LCD_display_mode(int dm) {
	LCD_command( 0x90 + dm );
}

void LCD_set_offset_register( int offset ) {
	LCD_command_2D( 0x22 , offset);
}

void LCD_set_cursor_pointer( int pointer ) {
	LCD_command_2D( 0x21 , pointer);
}

void LCD_set_address_pointer( int address ) {
	LCD_command_2D( 0x24 , address);
}

void LCD_data_write( short data ) {
	LCD_command_1D( 0xC4 , data );
}

void LCD_data_write_up( short data ) {
	LCD_command_1D( 0xC0 , data );
}

void LCD_data_write_down( short data ) {
	LCD_command_1D( 0xC2 , data );
}

void LCD_auto_write_start() {
	LCD_command( 0xB0 );
}

void LCD_auto_write(short data) {
	LCD_data( data );
}

void LCD_auto_write_stop() {
	LCD_command( 0xB2 );
}

void lprint(char *text) {
  while (*text != 0) {
	LCD_data_write_up( *text - 0x20 );
	text++;
  }
}
