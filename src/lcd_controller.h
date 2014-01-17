#define MODE_OR     0x00
#define MODE_EXOR   0x01
#define MODE_AND    0x03
#define MODE_TEXT_ONLY 0x04
#define MODE_CG_RAM 0x08

#define DM_GRAPHICS     0x08
#define DM_TEXT         0x04
#define DM_CURSOR       0x02
#define DM_CURSOR_BLINK 0x01

void LCD_init(int textStart, int graphicStart, short fontSize);
void LCD_mode(int mode);
void LCD_display_mode(int dm);
void LCD_set_offset_register( int offset );
void LCD_set_cursor_pointer( int pointer );
void LCD_set_address_pointer( int address );

void LCD_data_write( short data );
void LCD_data_write_up( short data );
void LCD_data_write_down( short data );

void LCD_auto_write_start();
void LCD_auto_write(short data);
void LCD_auto_write_stop();

void LCD_set_bit(short bit, short set);

void lprint(char *text);