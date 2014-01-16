  
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
