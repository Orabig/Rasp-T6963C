  
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "gpio.h" 
#include "lcd_register.h" 
#include "lcd_command.h" 
#include "lcd_controller.h" 


void lprint(char *text);

int main(int argc, char **argv)
{

  // Set up gpi pointer for direct register access
  gpio_setup();
    
  LCD_setup();
  
  LCD_Reverse(0);
  LCD_init(0x0000,0x1000,0);
	
	// MODE SET
	LCD_data( 0x00 );
	LCD_data( 0x00 );
	LCD_command( 0x80 ); 
	
	// DISPLAY MODE
	LCD_command( 0x94 ); // 94 = text only
	                     // 9C = text + graphics

	// Set ADDRESS POINTER


	LCD_command_2D( 0x24 , 0x0000);

	int i;
	
	for (i=0;i<500;i++) {
	LCD_command_1D( 0xC0 , 0x00 ); 
	}
	
	LCD_command_2D( 0x24 , 0x0000);

	
	lprint("* * * * It's alive * * * *");

		LCD_command( 0xB0 );
	for (i=0;i<1024;i++) { 
		LCD_data( i & 0x7F  );
	}
		LCD_command( 0xB2 );

	return 0;		

} // main

void lprint(char *text) {
  while (*text != 0) {
	LCD_command_1D( 0xC0 ,*text - 0x20);
	text++;
  }
}

