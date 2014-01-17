  
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#include "lcd_controller.h" 

#define BASE_TEXT            0x0000
#define BASE_GRAPHIC   0x0200


void lprint(char *text);
void lprintln(short cols, char *text);

int main(int argc, char **argv)
{
	// Compute the size of the screen
	// My model is a DG-24128
	int pixelX = 240;
	int pixelY = 128;
	
	int fontSize = 1; // 0=6x8   1=8x8
	
	// Raw computation
	int fontX = fontSize ? 8 : 6;
	int fontY = 8;
	int cols = pixelX / fontX;          // 1E      28
	int rows = pixelY / fontY;

	int textScreenSize = cols * rows;                     // 1E0       280
	int graphicScreenSize = cols * rows * fontY;          // F00      1400 

    LCD_init(BASE_TEXT,BASE_GRAPHIC,fontSize);
	
	// MODE SET
	LCD_mode( MODE_OR ); 
	
	// DISPLAY MODE
	LCD_display_mode( DM_TEXT + DM_GRAPHICS );

	int i;

	// Erase text screen
	LCD_set_address_pointer( BASE_TEXT );
	for (i=0;i<textScreenSize;i++) {
		LCD_data_write_up( 0x00 ); 
	}
	
	// Erase graphic screen
	LCD_set_address_pointer( BASE_GRAPHIC );
	LCD_auto_write_start();
	for (i=0;i<graphicScreenSize;i++) {
		LCD_auto_write( 0x00 ); 
	}
	LCD_auto_write_stop();
	
	LCD_set_address_pointer( BASE_TEXT );

	lprintln(cols,"");
	lprintln(cols,"  Welcome on this DG-24128");
	lprintln(cols,"");
	
	char buffer[256];
	sprintf(buffer,"cols=0x%X",cols);
	lprintln(cols,buffer);
	sprintf(buffer,"rows=0x%X",rows);
	lprintln(cols,buffer);
	sprintf(buffer,"textScreenSize=0x%X",textScreenSize);
	lprintln(cols,buffer);
	sprintf(buffer,"graphicScreenSize=0x%X",graphicScreenSize);
	lprintln(cols,buffer);

	return 0;		

} // main

void lprint(char *text) {
  while (*text != 0) {
	LCD_data_write_up( *text - 0x20 );
	text++;
  }
}
void lprintln(short cols, char *text) {
  LCD_auto_write_start();
  int len = strlen(text);
  while (*text != 0) {
	LCD_auto_write( *text - 0x20 );
	text++;
  }
  len %= cols;
  while (len++<cols) {
	LCD_auto_write( 0 );
  }
  LCD_auto_write_stop();
}

