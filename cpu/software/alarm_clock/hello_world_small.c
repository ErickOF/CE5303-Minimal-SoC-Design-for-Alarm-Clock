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

/*
 * alt_irq.h is the Nios II specific implementation of the interrupt controller
 * interface.
 *
 * Nios II includes optional support for an external interrupt controller.
 * When an external controller is present, the "Enhanced" interrupt API
 * must be used to manage individual interrupts. The enhanced API also
 * supports the processor's internal interrupt controller. Certain API
 * members are accessible from either the "legacy" or "enhanced" interrpt
 * API.
 *
 * Regardless of which API is in use, this file should be included by
 * application code and device drivers that register ISRs or manage interrpts.
 */

/*
 * This file provides prototypes and inline implementations of certain routines
 * used by the legacy interrupt API. Do not include this in your driver or
 * application source files, use "sys/alt_irq.h" instead to access the proper
 * public API.
 */

/*
 * The following protypes and routines are supported by both
 * the enhanced and legacy interrupt APIs
 */

#include "system.h"
#include "alt_types.h"
#include "sys/alt_stdio.h"

#include "altera_avalon_timer_regs.h"
#include "altera_avalon_pio_regs.h"
#include "altera_avalon_timer.h"
#include "priv/alt_legacy_irq.h"
#include "sys/alt_irq.h"
#include <errno.h>

#include "nios2.h"


#define TRUE 1
#define FALSE 0

#define SEC 2
#define MIN 3
#define HR 4


// Pointers to interact with the displays
volatile unsigned char *h1_ptr = (unsigned char*) H1_BASE;
volatile unsigned char *h0_ptr = (unsigned char*) H0_BASE;
volatile unsigned char *m1_ptr = (unsigned char*) M1_BASE;
volatile unsigned char *m0_ptr = (unsigned char*) M0_BASE;
volatile unsigned char *s1_ptr = (unsigned char*) S1_BASE;
volatile unsigned char *s0_ptr = (unsigned char*) S0_BASE;

// Pointers to interact with the buttons
volatile unsigned char *set_clock = (unsigned char*) BTN_SET_BASE;
volatile unsigned char *up_ptr = (unsigned char*) BTN_UP_BASE;
volatile unsigned char *down_ptr = (unsigned char*) BTN_DOWN_BASE;
//volatile unsigned char *right_ptr = (unsigned char*) BTN_RIGHT_BASE;
//volatile unsigned char *left_ptr = (unsigned char*) BTN_LEFT_BASE;
volatile unsigned char *swc_sel = (unsigned char*) SWC_SEL_BASE;
volatile unsigned char *swc_alarm = (unsigned char*) SWC_ALARM_BASE;

// Pointer to interact with the alarm sound
volatile unsigned char *alarm_ptr = (unsigned char*) ALARM_BASE;

//Timer pointer
volatile unsigned char *timer_base_ptr = (unsigned char *) TIMER_BASE;

// Current alarm hour
unsigned short alarm[3] = {5, 0, 0};
// Current hour
unsigned short hour[3] = {0, 0, 0};
// To activate and deactivate the Alarm
short is_activated = FALSE;
unsigned char irqtimer_stall = FALSE;
unsigned char first = TRUE;
//unsigned char all_botons_en = FALSE;
unsigned char ud_buttons_en = FALSE;
unsigned char up_pressed = FALSE;
unsigned char down_pressed = FALSE;
unsigned char set_pressed = FALSE;
unsigned char button_pressed = FALSE;


/**
 * Handler for alarm set button interrupt.
 */
static void btn_set_respond(void* context, alt_u32 id) {

	up_pressed = FALSE;
//	down_pressed = FALSE;
	//logica del boton set_alarm.
	unsigned int *button_action = (unsigned int*) context;
	*button_action =  IORD_ALTERA_AVALON_PIO_EDGE_CAP(BTN_SET_BASE);

	/* Acknowledge interrupt by clearing edge capture register */
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(BTN_SET_BASE, *button_action);

	if (!set_pressed) {
		alt_putstr("Button set\n");
		set_pressed = TRUE;
		if (irqtimer_stall) {
			irqtimer_stall = FALSE;

			alt_irq_enable(TIMER_IRQ);
		} else {
			irqtimer_stall = TRUE;

			alt_irq_disable(TIMER_IRQ);
		}
	} else {
		alt_putstr("Button already set\n");
	}
}

/**
 * Handler for button up interrupt.
 */
static void btn_up_respond(void* context, alt_u32 id){
	//logica del boton up.

	unsigned int *button_action = (unsigned int*) context;
	*button_action =  IORD_ALTERA_AVALON_PIO_EDGE_CAP(BTN_UP_BASE);

	/* Acknowledge interrupt by clearing edge capture register */
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(BTN_UP_BASE, *button_action);

	if (!up_pressed) {
		alt_putstr("Button up\n");
		up_pressed = TRUE;
	} else {
		alt_putstr("Button already set up\n");
	}
}

/**
 * Handler for button down interrupt.
 */
static void btn_down_respond(void* context, alt_u32 id) {
	//logica del boton down.

	unsigned int *button_action = (unsigned int*) context;
	*button_action =  IORD_ALTERA_AVALON_PIO_EDGE_CAP(BTN_DOWN_BASE);

	/* Acknowledge interrupt by clearing edge capture register */
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(BTN_DOWN_BASE, *button_action);

	if (!down_pressed) {
		alt_putstr("Button up\n");
		down_pressed = TRUE;

	} else {
		alt_putstr("Button already set up\n");
	}
}

/**
 * Handler for button right interrupt.
 */
//static void* btn_right_respond(void* context, alt_u32 id){
//	//logica del boton down.
//	alt_printf("Button right\n");
//
//	unsigned int *button_action = (unsigned int*) context;
//	*button_action =  IORD_ALTERA_AVALON_PIO_EDGE_CAP(BTN_RIGHT_BASE);
//
//	/* Acknowledge interrupt by clearing edge capture register */
//	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(BTN_RIGHT_BASE, *button_action);
//}

/**
 * Handler for button right interrupt.
 */
//static void* btn_left_respond(void* context, alt_u32 id){
//	//logica del boton down.
//	alt_printf("Button left\n");
//
//	unsigned int *button_action = (unsigned int*) context;
//	*button_action =  IORD_ALTERA_AVALON_PIO_EDGE_CAP(BTN_LEFT_BASE);
//
//	/* Acknowledge interrupt by clearing edge capture register */
//	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(BTN_LEFT_BASE, *button_action);
//}


/**
 * Buttons init.
 */
static void buttons_init(void){

	//Set alarm button:
	IOWR_ALTERA_AVALON_PIO_IRQ_MASK(BTN_SET_BASE, 0xf);
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(BTN_SET_BASE, 0x0);
	alt_irq_register(BTN_SET_IRQ, BTN_SET_BASE, btn_set_respond);

	//Up button:
	IOWR_ALTERA_AVALON_PIO_IRQ_MASK(BTN_UP_BASE, 0xf);
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(BTN_UP_BASE, 0x0);
	alt_irq_register(BTN_UP_IRQ, BTN_UP_BASE, btn_up_respond);

	//Down button:
//	IOWR_ALTERA_AVALON_PIO_IRQ_MASK(BTN_DOWN_BASE, 0xf);
//	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(BTN_DOWN_BASE, 0x0);
//	alt_irq_register(BTN_DOWN_IRQ, BTN_DOWN_BASE, btn_down_respond);

//	//Right button:
//	IOWR_ALTERA_AVALON_PIO_IRQ_MASK(BTN_RIGHT_BASE, 0xf);
//	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(BTN_RIGHT_BASE, 0x0);
//	alt_irq_register(BTN_RIGHT_IRQ, BTN_RIGHT_BASE, btn_right_respond);
//
//
//	//Left button:
//	IOWR_ALTERA_AVALON_PIO_IRQ_MASK(BTN_LEFT_BASE, 0xf);
//	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(BTN_LEFT_BASE, 0x0);
//	alt_irq_register(BTN_LEFT_IRQ, BTN_LEFT_BASE, btn_left_respond);

}

/**
 * Set values to the correct output.
 */
int set_value(unsigned short value, volatile unsigned char* seg1, volatile unsigned char* seg0)
{
	*seg1 = (unsigned char) value / 10;
	*seg0 = (unsigned char) value % 10;

	return 0;
}

/**
 * Update the value of a specific display
 */
void add_second()
{
//	if (sel == 0) {
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

/**
 * Handler for timer interrupt.
 */
static void timer_respond(void* context){

	/* Acknowledge interrupt by clearing status register */
	IOWR_ALTERA_AVALON_TIMER_STATUS(TIMER_BASE, 0x0);

	//	IOWR_ALTERA_AVALON_TIMER_STATUS(timer_base_ptr, 0x0);
//	clock_pressed = FALSE;
	set_pressed = FALSE;
	ud_buttons_en = FALSE;

	alt_irq_disable(BTN_UP_IRQ);
	alt_irq_disable(BTN_DOWN_IRQ);

	add_second();

	set_value(hour[0], s1_ptr, s0_ptr);
	set_value(hour[1], m1_ptr, m0_ptr);
	set_value(hour[2], h1_ptr, h0_ptr);

//	alt_irq_disable(BTN_UP_IRQ);
//	alt_irq_disable(BTN_DOWN_IRQ);

	display_hour();
}

/**
 * Timer init
 */
static void timer_init(void){
	//Start the values for the timer interrupt.
	IOWR_ALTERA_AVALON_TIMER_CONTROL(timer_base_ptr, ALTERA_AVALON_TIMER_CONTROL_ITO_MSK
	        | ALTERA_AVALON_TIMER_CONTROL_START_MSK);
	//Init the handler for the timer interrupt.
	alt_irq_register(TIMER_IRQ, TIMER_BASE /*timer_base_ptr*/, timer_respond);
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

int main()
{ 
	alt_putstr("Welcome to the Alarm Clock\n");

	if (first) {
		init_values();
		first = FALSE;
	}

	buttons_init();

	alt_irq_disable(BTN_UP_IRQ);
	alt_irq_disable(BTN_DOWN_IRQ);

	// Timer interrupt
	timer_init();

	while (TRUE)
	{

		if (!ud_buttons_en && set_pressed) {
			alt_irq_enable(BTN_UP_IRQ);
			alt_irq_enable(BTN_DOWN_IRQ);
			ud_buttons_en = TRUE;
		}

//		changevariable (*swc_sel, 1);
		if (up_pressed) {
			if (*swc_sel == 0) {
				if (hour[1]<60)
					hour[1]++;
				else
					hour[1] = 0;
			} else {
				if (alarm[1]<60)
					alarm[1]++;
				else
					alarm[1] = 0;
			}
		}

		//		if (down_pressed){
		//			if (hour[pos]>0)
		//				hour[pos]--;
		//			else
		//				hour[pos] = 59;
		//		}
//			}
		//		if (down_pressed){
		//			if (alarm[pos]>0)
		//				alarm[pos]--;
		//			else
		//				alarm[pos] = 59;
		//		}
//			}

//		alt_printf("Changing %s\n", *swc_sel == 0 ? "Time" : "Alarm");
//
//			if (up_pressed) {
//				if (this_sel == 0) {
//					if (hour[1]<60)
//						hour[1]++;
//					else
//						hour[1] = 0;
//		//				set_value(hour[1], m1_ptr, m0_ptr);
//		//				alt_putstr("Hour changed\n");
//				} else {
//					if (alarm[1]<60)
//						alarm[1]++;
//					else
//						alarm[1] = 0;
//				}
//			}
//
//			if (down_pressed) {
//				if (this_sel == 0) {
//					if (hour[1]>0)
//						hour[1]--;
//					else
//						hour[1] = 59;
//				}
//	//				set_value(hour[1], m1_ptr, m0_ptr);
//	//				alt_putstr("Hour changed\n");
//			}

//			if (this_sel == 0) {
//
//
//				if (down_pressed) {
//					if (hour[1]>0)
//						hour[1]--;
//					else
//						hour[1] = 59;
//	//				set_value(hour[1], m1_ptr, m0_ptr);
//	//				alt_putstr("Hour changed\n");
//				}
//			} else {
//				alarm[1] = 0;
//			}

		up_pressed = FALSE;
		down_pressed = FALSE;
		set_pressed = FALSE;
		button_pressed = FALSE;

		display_hour();
	}

	return 0;
}

