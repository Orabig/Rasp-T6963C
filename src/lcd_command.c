//
// Low level access function to the LCD
//




// LCD Control constants
#define FNT_Pin   15   // Font select
#define REV_Pin   14  // Reverse
#define CD_Pin   18  //  Command_\Data
#define CE_Pin   23  //   \Chip_Enable

#define FNT   1<<FNT_Pin
#define REV   1<<REV_Pin
#define CD   1<<CD_Pin
#define CE   1<<CE_Pin
  
#include <unistd.h>

#include "gpio.h" 
#include "lcd_register.h" 



// LCD Control constants
#define FNT_Pin   15   // Font select
#define REV_Pin   14  // Reverse
#define CD_Pin   18  //  Command_\Data
#define CE_Pin   23  //   \Chip_Enable

#define FNT   1<<FNT_Pin
#define REV   1<<REV_Pin
#define CD   1<<CD_Pin
#define CE   1<<CE_Pin


//
// Set up the LCD
//
void LCD_setup()
{
  reg_setup();
  // Set useful GPIO pins to output
  gpio_output_pin(REV_Pin);
  gpio_output_pin(FNT_Pin);
  gpio_output_pin(CD_Pin);
  gpio_output_pin(CE_Pin);
  
  gpio_set( CE );
}

void LCD_command(short command) {
  reg_data(command);
  gpio_set( CD );

  gpio_clr( CE );
  usleep(1); // ! Important
  gpio_set( CE );
}

void LCD_data(short data) {
  reg_data(data);
  gpio_clr( CD );

  gpio_clr( CE );
  usleep(1); // ! Important
  gpio_set( CE );
}

void LCD_command_1D(short command, short data) {
  LCD_data(data);
  LCD_command(command);
}

void LCD_command_2D(short command, int data) {
  LCD_data(data & 0xFF);
  LCD_data((data >> 8) & 0xFF);
  LCD_command(command);
}

void LCD_Reverse(short rev) {
  if (rev) {
	gpio_clr( REV ); 
	} else {
	gpio_set( REV ); 
	}
}

void LCD_FontSelect(short high) {
  if (high) {
	gpio_clr( FNT ); 
	} else {
	gpio_set( FNT ); 
	}
}

