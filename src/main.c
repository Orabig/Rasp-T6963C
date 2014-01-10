//
//  How to access GPIO registers from C-code on the Raspberry-Pi
//  Example program
//  15-January-2012
//  Dom and Gert
//  Revised: 15-Feb-2013



// Access from ARM Running Linux

#define BCM2708_PERI_BASE        0x20000000
#define GPIO_BASE                (BCM2708_PERI_BASE + 0x200000) /* GPIO controller */

// Shift register constants

#define DS_Pin   4
#define SH_Pin   7
#define ST_Pin   17

#define DS   1<<DS_Pin
#define SH   1<<SH_Pin
#define ST   1<<ST_Pin
  
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <time.h>

#define PAGE_SIZE (4*1024)
#define BLOCK_SIZE (4*1024)

int  mem_fd;
void *gpio_map;

// I/O access
volatile unsigned *gpio;


// GPIO setup macros. Always use INP_GPIO(x) before using OUT_GPIO(x) or SET_GPIO_ALT(x,y)
#define INP_GPIO(g) *(gpio+((g)/10)) &= ~(7<<(((g)%10)*3))
#define OUT_GPIO(g) *(gpio+((g)/10)) |=  (1<<(((g)%10)*3))
#define SET_GPIO_ALT(g,a) *(gpio+(((g)/10))) |= (((a)<=3?(a)+4:(a)==4?3:2)<<(((g)%10)*3))

#define GPIO_SET *(gpio+7)  // sets   bits which are 1 ignores bits which are 0
#define GPIO_CLR *(gpio+10) // clears bits which are 1 ignores bits which are 0

#define GPIO_CLK(g) GPIO_SET=g; GPIO_CLR=g // A clock : ___---___

#define GPIO_PUT(g,d) *(gpio+7+(!(d)*3)) = g // sets a value for g. (0 if d==0, else 1)

void setup_io();

void setup_register();

// Shifts a bit into the register (data==0 or 1)
void shift(short bit) {
    // Store the data at the serial input
    GPIO_PUT(DS,bit);
	// Makes a clock signal
	GPIO_CLK(SH);
}

// Send a full byte (8 bits) into the register
void data(short byte) {
  byte &= 255;
  int i;
  for(i=7;i>=0;i--) {
    shift((byte >> i) & 1);
    }
  // Makes a clock signal
  GPIO_CLK(ST);
  }


int main(int argc, char **argv)
{

  // Set up gpi pointer for direct register access
  setup_io();
  setup_register();
  
  int g,rep;
  for (g=0; g<=100; g++) {
	  for (rep=0; rep<256; rep++)
	  {
		data(rep);
		usleep(1000000);
	  }
	}
	
  return 0;

} // main

//
// Set up the data register
//
void setup_register()
{
  // Set GPIO pins 4,17,17 to output
  INP_GPIO(ST_Pin);OUT_GPIO(ST_Pin); // must use INP_GPIO before we can use OUT_GPIO
  INP_GPIO(SH_Pin);OUT_GPIO(SH_Pin);
  INP_GPIO(DS_Pin);OUT_GPIO(DS_Pin);
  
  GPIO_CLR = ST;
  GPIO_CLR = SH;
}

//
// Set up a memory regions to access GPIO
//
void setup_io()
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
