  
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "lcd_controller.h" 


void lprint(char *text);

int main(int argc, char **argv)
{

//  LCD_Reverse(0);

    LCD_init(0x0000,0x1000,0);
	
	// MODE SET
	LCD_mode( MODE_OR ); 
	
	// DISPLAY MODE
	LCD_display_mode( DM_TEXT /* + DM_GRAPHICS */ );

	// Set ADDRESS POINTER
	LCD_set_address_pointer( 0x0000 );

	int i;
	
	for (i=0;i<500;i++) {
		LCD_data_write_up( 0x00 ); 
	}
	
	LCD_set_address_pointer( 0x0000 );

	
	lprint("* * * * It's alive * * * *");

	LCD_auto_write_start();
	for (i=0;i<1024;i++) { 
		LCD_auto_write( i & 0x7F  );
	}
	LCD_auto_write_stop();

	return 0;		

} // main

void lprint(char *text) {
  while (*text != 0) {
	LCD_data_write_up( *text - 0x20 );
	text++;
  }
}

