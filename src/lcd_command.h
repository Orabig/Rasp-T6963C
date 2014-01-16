
void LCD_setup();
void LCD_data(short data);
void LCD_command(short command);

// Sends a command with a 1-byte data parameter
void LCD_command_1D(short command,short data);

// Sends a command with a 2-bytes data parameter
void LCD_command_2D(short command,int data);

void LCD_Reverse(short rev);
void LCD_FontSelect(short high);
