//
//  GPIO registers access on the Raspberry-Pi
//  Based from Example program
//  15-January-2012
//  Dom and Gert
//  Revised: 15-Feb-2013



void gpio_setup();
void gpio_output_pin(int pin);
void gpio_input_pin(int pin);

// Warning : the following function takes a shifted pin argument.
// i.e. : gpio_set(1 << 6) to set the 6th pin !
void gpio_set(int pin);
void gpio_clr(int pin);
void gpio_put(int pin,short value);

