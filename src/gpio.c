//
//  GPIO registers access on the Raspberry-Pi
//  Based from Example program
//  15-January-2012
//  Dom and Gert
//  Revised: 15-Feb-2013


#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#include "gpio.h"


// Access from ARM Running Linux

#define BCM2708_PERI_BASE        0x20000000
#define GPIO_BASE                (BCM2708_PERI_BASE + 0x200000) /* GPIO controller */
#define BLOCK_SIZE (4*1024)

int  mem_fd;
void *gpio_map;

// I/O access
volatile unsigned *gpio;


// GPIO setup macros. Always use INP_GPIO(x) before using OUT_GPIO(x)
#define INP_GPIO(g) *(gpio+((g)/10)) &= ~(7<<(((g)%10)*3))
#define OUT_GPIO(g) *(gpio+((g)/10)) |=  (1<<(((g)%10)*3))

#define GPIO_SET *(gpio+7)  // sets   bits which are 1 ignores bits which are 0
#define GPIO_CLR *(gpio+10) // clears bits which are 1 ignores bits which are 0
#define GPIO_PUT(g,d) *(gpio+7+(!(d)*3)) = g // sets a value for g. (0 if d==0, else 1)


	
void gpio_output_pin(int pin) {
	INP_GPIO(pin);
	OUT_GPIO(pin); // must use INP_GPIO before we can use OUT_GPIO
	}
	
void gpio_input_pin(int pin) {
	INP_GPIO(pin);
	}

// Turn GPIO output to 1
inline void gpio_set(int pin) {
	GPIO_SET = pin;
	}

// Turn GPIO output to 0
inline void gpio_clr(int pin) {
	GPIO_CLR = pin;
	}

// Turn GPIO output to given value
inline void gpio_put(int pin, short value) {
	*(gpio+7+(!(value & 1)*3)) = pin;
	}	

//
// Set up a memory regions to access GPIO
//
void gpio_setup()
{
   /* open /dev/mem */
   if ((mem_fd = open("/dev/mem", O_RDWR|O_SYNC) ) < 0) {
      printf("can't open /dev/mem \n");
      exit(-1);
   }

   /* mmap GPIO */
   gpio_map = mmap(
      NULL,             //Any adddress in our space will do
      BLOCK_SIZE,       //Map length
      PROT_READ|PROT_WRITE,// Enable reading & writting to mapped memory
      MAP_SHARED,       //Shared with other processes
      mem_fd,           //File to map
      GPIO_BASE         //Offset to GPIO peripheral
   );

   close(mem_fd); //No need to keep mem_fd open after mmap

   if (gpio_map == MAP_FAILED) {
      printf("mmap error %d\n", (int)gpio_map);//errno also set!
      exit(-1);
   }

   // Always use volatile pointer!
   gpio = (volatile unsigned *)gpio_map;

} // setup_io
