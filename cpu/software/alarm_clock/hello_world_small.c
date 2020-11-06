/* 
 * "Small Hello World" example. 
 * 
 * This example prints 'Hello from Nios II' to the STDOUT stream. It runs on
 * the Nios II 'standard', 'full_featured', 'fast', and 'low_cost' example 
 * designs. It requires a STDOUT  device in your system's hardware. 
 *
 * The purpose of this example is to demonstrate the smallest possible Hello 
 * World application, using the Nios II HAL library.  The memory footprint
 * of this hosted application is ~332 bytes by default using the standard 
 * reference design.  For a more fully featured Hello World application
 * example, see the example titled "Hello World".
 *
 * The memory footprint of this example has been reduced by making the
 * following changes to the normal "Hello World" example.
 * Check in the Nios II Software Developers Manual for a more complete 
 * description.
 * 
 * In the SW Application project (small_hello_world):
 *
 *  - In the C/C++ Build page
 * 
 *    - Set the Optimization Level to -Os
 * 
 * In System Library project (small_hello_world_syslib):
 *  - In the C/C++ Build page
 * 
 *    - Set the Optimization Level to -Os
 * 
 *    - Define the preprocessor option ALT_NO_INSTRUCTION_EMULATION 
 *      This removes software exception handling, which means that you cannot 
 *      run code compiled for Nios II cpu with a hardware multiplier on a core 
 *      without a the multiply unit. Check the Nios II Software Developers 
 *      Manual for more details.
 *
 *  - In the System Library page:
 *    - Set Periodic system timer and Timestamp timer to none
 *      This prevents the automatic inclusion of the timer driver.
 *
 *    - Set Max file descriptors to 4
 *      This reduces the size of the file handle pool.
 *
 *    - Check Main function does not exit
 *    - Uncheck Clean exit (flush buffers)
 *      This removes the unneeded call to exit when main returns, since it
 *      won't.
 *
 *    - Check Don't use C++
 *      This builds without the C++ support code.
 *
 *    - Check Small C library
 *      This uses a reduced functionality C library, which lacks  
 *      support for buffering, file IO, floating point and getch(), etc. 
 *      Check the Nios II Software Developers Manual for a complete list.
 *
 *    - Check Reduced device drivers
 *      This uses reduced functionality drivers if they're available. For the
 *      standard design this means you get polled UART and JTAG UART drivers,
 *      no support for the LCD driver and you lose the ability to program 
 *      CFI compliant flash devices.
 *
 *    - Check Access device drivers directly
 *      This bypasses the device file system to access device drivers directly.
 *      This eliminates the space required for the device file system services.
 *      It also provides a HAL version of libc services that access the drivers
 *      directly, further reducing space. Only a limited number of libc
 *      functions are available in this configuration.
 *
 *    - Use ALT versions of stdio routines:
 *
 *           Function                  Description
 *        ===============  =====================================
 *        alt_printf       Only supports %s, %x, and %c ( < 1 Kbyte)
 *        alt_putstr       Smaller overhead than puts with direct drivers
 *                         Note this function doesn't add a newline.
 *        alt_putchar      Smaller overhead than putchar with direct drivers
 *        alt_getchar      Smaller overhead than getchar with direct drivers
 *
 */

#include <system.h>
#include <alt_types.h>
#include <sys/alt_stdio.h>

#define true 1
#define false 0


// Pointers to interact with the displays
volatile unsigned char *h1_ptr = (unsigned char*) H1_BASE;
volatile unsigned char *h0_ptr = (unsigned char*) H0_BASE;
volatile unsigned char *m1_ptr = (unsigned char*) M1_BASE;
volatile unsigned char *m0_ptr = (unsigned char*) M0_BASE;
volatile unsigned char *s1_ptr = (unsigned char*) S1_BASE;
volatile unsigned char *s0_ptr = (unsigned char*) S0_BASE;

// Pointers to interact with the buttons
volatile unsigned char *set_alarm_ptr = (unsigned char*) BTN_SET_ALARM_BASE;
volatile unsigned char *set_clock_ptr = (unsigned char*) BTN_SET_CLOCK_BASE;
volatile unsigned char *up_ptr = (unsigned char*) BTN_UP_BASE;
volatile unsigned char *down_ptr = (unsigned char*) BTN_DOWN_BASE;

// Pointer to interact with the alarm sound
volatile unsigned char *alarm_ptr = (unsigned char*) ALARM_BASE;

// Current alarm hour
unsigned short alarm[3] = {5, 0, 0};
// Current hour
unsigned short hour[3] = {0, 0, 0};
// To activate and deactivate the Alarm
short is_activated = false;

//Timer pointer


/**
 * Update the value of a specific display
 */
void add_second()
{
	// Add a second
	hour[0]++;

	if (hour[0] == 60)
	{
		hour[0] = 0;
		hour[1]++;

		if (hour[1] == 60)
		{
			hour[1] = 0;
			hour[2]++;

			if (hour[2] == 24)
			{
				hour[2] = 0;
			}
		}
	}
}

void display_hour()
{
	alt_printf("%x %x : %x %x : %x %x\n", *h1_ptr, *h0_ptr, *m1_ptr, *m0_ptr,
									   *s1_ptr, *s0_ptr);
}

void init_values()
{
	// Init all pointer in zero
	*h1_ptr = 0;
	*h0_ptr = 0;
	*m1_ptr = 0;
	*m0_ptr = 0;
	*s1_ptr = 0;
	*s0_ptr = 0;

	// Alarm doesn't sound
	*alarm_ptr = 0;
}

/**
 *
 */
void set_value(unsigned short value, volatile unsigned char* seg1, volatile unsigned char* seg0)
{
	*seg1 = (unsigned char) value / 10;
	*seg0 = (unsigned char) value % 10;
}

int main()
{ 
  alt_putstr("Welcome to the Alarm Clock\n");

  init_values();

  while (true)
  {
	  // Timer interrupt
	  add_second();

	  set_value(hour[0], s1_ptr, s0_ptr);
	  set_value(hour[1], m1_ptr, m0_ptr);
	  set_value(hour[2], h1_ptr, h0_ptr);

	  display_hour();
  }

  return 0;
}
