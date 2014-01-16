//
// This file controls the register used to send a byte to the LCD via a 74HC595 chip
//
  
#include "gpio.h" 

#include "lcd_register.h" 

// GPIO Pins used by the data register :

// Data Serial
#define DS_Pin   4
// Shift Clock
#define SH_Pin   7
// Storage Clock
#define ST_Pin   17

#define DS   1<<DS_Pin
#define SH   1<<SH_Pin
#define ST   1<<ST_Pin

// Shifts a bit into the register (data==0 or 1)
void reg_shift(short bit) {
    // Store the data at the serial input
    gpio_put(DS,bit);
	// Makes a clock signal
	gpio_set(SH); 
	gpio_clr(SH);
}

// Send a full byte (8 bits) into the register
void reg_data(short byte) {
	byte &= 255;
	int i;
	for(i=7;i>=0;i--) {
		reg_shift((byte >> i) & 1);
	}
	// Makes a clock signal
	gpio_set(ST); 
	gpio_clr(ST);
  }

//
// Set up the data register
//
void reg_setup()
{
  // Set GPIO pins to output
  gpio_output_pin(ST_Pin);
  gpio_output_pin(SH_Pin);
  gpio_output_pin(DS_Pin);
  
  gpio_clr( ST );
  gpio_clr( SH );
}

