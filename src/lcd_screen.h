void LCD_screen_compute(int pX, int pY, int font);
void LCD_screen_init(int pX, int pY, int font);

int LCD_getRows();
int LCD_getCols();
int LCD_getBaseText();
int LCD_getBaseGraphic();
int LCD_getTextScreenSize();
int LCD_getGraphicScreenSize();

void lprintln(char *text);