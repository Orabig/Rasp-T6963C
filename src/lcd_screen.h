void LCD_screen_compute(int pX, int pY, int font);
void LCD_screen_init(int pX, int pY, int font);

short LCD_getRows();
short LCD_getCols();
unsigned int LCD_getBaseText();
unsigned int LCD_getBaseGraphic();
unsigned int LCD_getTextScreenSize();
unsigned int LCD_getGraphicScreenSize();

void lprintln(char *text);
void LCD_SetPixel(unsigned char x,unsigned char y, short color);