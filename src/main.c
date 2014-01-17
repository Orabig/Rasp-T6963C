  
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#include "lcd_controller.h" 
#include "lcd_screen.h" 
#include "lcd_graphics.h" 


int main(int argc, char **argv)
{
	// Compute the size of the screen
	// My model is a DG-24128
	int pixelX = 240;
	int pixelY = 128;
	
	int fontSize = 1; // 0=6x8   1=8x8
	
	LCD_screen_init(pixelX,pixelY, fontSize);
	
	// MODE SET
	LCD_mode( MODE_OR ); 
	
	// DISPLAY MODE
	LCD_display_mode( DM_TEXT + DM_GRAPHICS );

	int i;

	// Erase text screen
	LCD_set_address_pointer( LCD_getBaseText() );
	for (i=0;i<LCD_getTextScreenSize();i++) {
		LCD_data_write_up( 0x00 ); 
	}
	
	// Erase graphic screen
	LCD_set_address_pointer( LCD_getBaseGraphic() );
	LCD_auto_write_start();
	for (i=0;i<LCD_getGraphicScreenSize();i++) {
		LCD_auto_write( 0x00 ); 
	}
	LCD_auto_write_stop();
	LCD_set_address_pointer( LCD_getBaseText() );

	lprintln("");
	lprintln("  Welcome on this DG-24128");
	lprintln("");
	lprintln("");
	
	char buffer[256];
	sprintf(buffer,"cols=0x%X",(unsigned int)LCD_getCols());
	lprintln(buffer);
	sprintf(buffer,"rows=0x%X",(unsigned int)LCD_getRows());
	lprintln(buffer);
	sprintf(buffer,"getTextScreenSize=0x%X",LCD_getTextScreenSize());
	lprintln(buffer);
	sprintf(buffer,"getGraphicScreenSize=0x%X",LCD_getGraphicScreenSize());
	lprintln(buffer);

    LCD_Circle(50,100,20);	
	LCD_Rectangle(10,3,210,18);
	LCD_Line(100,100,210,80);
	return 0;		

} // main

