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


#include "system.h"
#include "alt_types.h"
#include "sys/alt_stdio.h"

#include "altera_avalon_timer_regs.h"
#include "altera_avalon_pio_regs.h"
#include "altera_avalon_timer.h"
#include <errno.h>

#include "nios2.h"


#define TRUE 1
#define FALSE 0

#define SEC 2
#define MIN 3
#define HR 4

#ifndef __ALT_IRQ_H__
#define __ALT_IRQ_H__

/*
 * Number of available interrupts in internal interrupt controller.
 */
#define ALT_NIRQ NIOS2_NIRQ

/*
 * Used by alt_irq_disable_all() and alt_irq_enable_all().
 */
typedef int alt_irq_context;

/* ISR Prototype */
#ifdef ALT_ENHANCED_INTERRUPT_API_PRESENT
typedef void (*alt_isr_func)(void* isr_context);
#else
typedef void (*alt_isr_func)(void* isr_context, alt_u32 id);
#endif

/*
 * alt_irq_disable_all()
 *
 * This routine inhibits all interrupts by negating the status register PIE
 * bit. It returns the previous contents of the CPU status register (IRQ
 * context) which can be used to restore the status register PIE bit to its
 * state before this routine was called.
 */
static ALT_INLINE alt_irq_context ALT_ALWAYS_INLINE
       alt_irq_disable_all (void)
{
  alt_irq_context context;

  NIOS2_READ_STATUS (context);

  NIOS2_WRITE_STATUS (context & ~NIOS2_STATUS_PIE_MSK);

  return context;
}

/*
 * alt_irq_enable_all()
 *
 * Enable all interrupts that were previously disabled by alt_irq_disable_all()
 *
 * This routine accepts a context to restore the CPU status register PIE bit
 * to the state prior to a call to alt_irq_disable_all().

 * In the case of nested calls to alt_irq_disable_all()/alt_irq_enable_all(),
 * this means that alt_irq_enable_all() does not necessarily re-enable
 * interrupts.
 *
 * This routine will perform a read-modify-write sequence to restore only
 * status.PIE if the processor is configured with options that add additional
 * writeable status register bits. These include the MMU, MPU, the enhanced
 * interrupt controller port, and shadow registers. Otherwise, as a performance
 * enhancement, status is overwritten with the prior context.
 */
static ALT_INLINE void ALT_ALWAYS_INLINE
       alt_irq_enable_all (alt_irq_context context)
{
#if (NIOS2_NUM_OF_SHADOW_REG_SETS > 0) || (defined NIOS2_EIC_PRESENT) || \
    (defined NIOS2_MMU_PRESENT) || (defined NIOS2_MPU_PRESENT)
  alt_irq_context status;

  NIOS2_READ_STATUS (status);

  status &= ~NIOS2_STATUS_PIE_MSK;
  status |= (context & NIOS2_STATUS_PIE_MSK);

  NIOS2_WRITE_STATUS (status);
#else
  NIOS2_WRITE_STATUS (context);
#endif
}

/*
 * The function alt_irq_init() is defined within the auto-generated file
 * alt_sys_init.c. This function calls the initilization macros for all
 * interrupt controllers in the system at config time, before any other
 * non-interrupt controller driver is initialized.
 *
 * The "base" parameter is ignored and only present for backwards-compatibility.
 * It is recommended that NULL is passed in for the "base" parameter.
 */
extern void alt_irq_init (const void* base);

/*
 * alt_irq_cpu_enable_interrupts() enables the CPU to start taking interrupts.
 */
static ALT_INLINE void ALT_ALWAYS_INLINE
       alt_irq_cpu_enable_interrupts (void)
{
    NIOS2_WRITE_STATUS(NIOS2_STATUS_PIE_MSK
#if defined(NIOS2_EIC_PRESENT) && (NIOS2_NUM_OF_SHADOW_REG_SETS > 0)
    | NIOS2_STATUS_RSIE_MSK
#endif
      );
}

#ifndef __ALT_LEGACY_IRQ_H__
#define __ALT_LEGACY_IRQ_H__

/*
 * This file provides prototypes and inline implementations of certain routines
 * used by the legacy interrupt API. Do not include this in your driver or
 * application source files, use "sys/alt_irq.h" instead to access the proper
 * public API.
 */
#ifndef NIOS2_EIC_PRESENT

/*
 * alt_irq_register() can be used to register an interrupt handler. If the
 * function is succesful, then the requested interrupt will be enabled upon
 * return.
 */

__asm__( "\n\t.globl alt_irq_entry" );

__asm__( "\n\t.globl alt_irq_handler" );

/*
 * The header, alt_irq_table.h contains a table describing which function
 * handles each interrupt.
 */

#ifndef __ALT_IRQ_TABLE_H__
#define __ALT_IRQ_TABLE_H__

/*
 * Definition of a table describing each interrupt handler. The index into
 * the array is the interrupt id associated with the handler.
 *
 * When an interrupt occurs, the associated handler is called with
 * the argument stored in the context member.
 *
 * The table is physically created in alt_irq_handler.c
 */
extern struct ALT_IRQ_HANDLER
{
#ifdef ALT_ENHANCED_INTERRUPT_API_PRESENT
  void (*handler)(void*);
#else
  void (*handler)(void*, alt_u32);
#endif
  void *context;
} alt_irq[ALT_NIRQ];

#endif

/*
 * alt_irq_register() can be used to register an interrupt handler. If the
 * function is succesful, then the requested interrupt will be enabled upon
 * return.
 */
int alt_irq_register (alt_u32 id,
					 void*   context,
					 alt_isr_func handler);

/*
 * alt_irq_disable() disables the individual interrupt indicated by "id".
 */
static ALT_INLINE int ALT_ALWAYS_INLINE alt_irq_disable (alt_u32 id)
{
  alt_irq_context  status;
  extern volatile alt_u32 alt_irq_active;

  status = alt_irq_disable_all ();

  alt_irq_active &= ~(1 << id);
  NIOS2_WRITE_IENABLE (alt_irq_active);

  alt_irq_enable_all(status);

  return 0;
}

/*
 * alt_irq_enable() enables the individual interrupt indicated by "id".
 */
static ALT_INLINE int ALT_ALWAYS_INLINE alt_irq_enable (alt_u32 id)
{
  alt_irq_context  status;
  extern volatile alt_u32 alt_irq_active;

  status = alt_irq_disable_all ();

  alt_irq_active |= (1 << id);
  NIOS2_WRITE_IENABLE (alt_irq_active);

  alt_irq_enable_all(status);

  return 0;
}

/*
 * alt_irq_handler() is called to register an interrupt handler. If the
 * function is succesful, then the requested interrupt will be enabled upon
 * return. Registering a NULL handler will disable the interrupt.
 *
 * The return value is 0 if the interrupt handler was registered and the
 * interrupt was enabled, otherwise it is negative.
 */
int alt_irq_register (alt_u32 id,
                      void* context,
                      alt_isr_func handler)
{
  int rc = -EINVAL;
  alt_irq_context status;

  if (id < ALT_NIRQ)
  {
    /*
     * interrupts are disabled while the handler tables are updated to ensure
     * that an interrupt doesn't occur while the tables are in an inconsistant
     * state.
     */

    status = alt_irq_disable_all ();

    alt_irq[id].handler = handler;
    alt_irq[id].context = context;

    rc = (handler) ? alt_irq_enable (id): alt_irq_disable (id);

    alt_irq_enable_all(status);
  }
  return rc;
}

#endif /* NIOS2_EIC_PRESENT */

#endif /* __ALT_LEGACY_IRQ_H__ */

/*
 * alt_irq_pending() returns a bit list of the current pending interrupts.
 * This is used by alt_irq_handler() to determine which registered interrupt
 * handlers should be called.
 *
 * This routine is only available for the Nios II internal interrupt
 * controller.
 */
#ifndef NIOS2_EIC_PRESENT
static ALT_INLINE alt_u32 ALT_ALWAYS_INLINE alt_irq_pending (void)
{
  alt_u32 active;

  NIOS2_READ_IPENDING (active);

  return active;
}
#endif

#endif /* __ALT_IRQ_H__ */


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
volatile unsigned char *swc_sel = (unsigned char*) SWC_SEL_BASE;
volatile unsigned char *swc_alarm = (unsigned char*) SWC_ALARM_BASE;

// Pointer to interact with the alarm sound
volatile unsigned char *alarm_ptr = (unsigned char*) ALARM_BASE;

//Timer pointer
volatile unsigned char *timer_base_ptr = (unsigned char *) TIMER_BASE;

// Current alarm hour
unsigned short alarm[3] = {0, 0, 0};
// Current hour
unsigned short hour[3] = {0, 0, 0};
// To activate and deactivate the Alarm
short is_activated = FALSE;
short time_unit_sel = SEC;
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
	down_pressed = FALSE;
	*alarm_ptr = (unsigned char) 0;

	//logica del boton set_alarm.
	unsigned int *button_action = (unsigned int*) context;
	*button_action =  IORD_ALTERA_AVALON_PIO_EDGE_CAP(BTN_SET_BASE);

	/* Acknowledge interrupt by clearing edge capture register */
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(BTN_SET_BASE, *button_action);

	if (!set_pressed) {
		alt_putstr("Button set\n");
		set_pressed = TRUE;
		if (irqtimer_stall) {
			switch(time_unit_sel)
			{
			case SEC:
				time_unit_sel = MIN;
				break;
			case MIN:
				time_unit_sel = HR;
				break;
			case HR:
				time_unit_sel = SEC;
				irqtimer_stall = FALSE;
				alt_irq_enable(TIMER_IRQ);
				break;
			}
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
		alt_putstr("Button down\n");
		down_pressed = TRUE;

	} else {
		alt_putstr("Button already set down\n");
	}
}

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
	IOWR_ALTERA_AVALON_PIO_IRQ_MASK(BTN_DOWN_BASE, 0xf);
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(BTN_DOWN_BASE, 0x0);
	alt_irq_register(BTN_DOWN_IRQ, BTN_DOWN_BASE, btn_down_respond);
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

	set_pressed = FALSE;
	ud_buttons_en = FALSE;

	alt_irq_disable(BTN_UP_IRQ);
	alt_irq_disable(BTN_DOWN_IRQ);

	/* Acknowledge interrupt by clearing status register */
	IOWR_ALTERA_AVALON_TIMER_STATUS(TIMER_BASE, 0x0);

	add_second();

	if (*swc_alarm == 1 && hour[2] == alarm [2] && hour[1] == alarm[1]) {
		*alarm_ptr = (unsigned char) 1;
	} else {
		*alarm_ptr = (unsigned char) 0;
	}

	set_value(hour[0], s1_ptr, s0_ptr);
	set_value(hour[1], m1_ptr, m0_ptr);
	set_value(hour[2], h1_ptr, h0_ptr);

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

		alt_printf("Changing %s\n", *swc_sel == 0 ? "Time" : "Alarm");

		if (up_pressed) {
			if (*swc_sel == 0) {
				if (time_unit_sel == HR) {
					if (hour[2]<23)
						hour[2]++;
					else
						hour[2] = 0;
				} else {
					if (hour[time_unit_sel-2] < 59)
						hour[time_unit_sel-2]++;
					else
						hour[time_unit_sel-2] = 0;
				}
				set_value(hour[0], s1_ptr, s0_ptr);
				set_value(hour[1], m1_ptr, m0_ptr);
				set_value(hour[2], h1_ptr, h0_ptr);
			} else {
				if (time_unit_sel == HR) {
					if (alarm[2]<23)
						alarm[2]++;
					else
						alarm[2] = 0;
				} else if (time_unit_sel == MIN ) {
					if (alarm[1] < 59)
						alarm[1]++;
					else
						alarm[1] = 0;
				} else {
					alt_putstr("Can't set an alarm for seconds\n");
				}
				alt_printf("Alarm setted > %x : %x : %x \n", alarm[2], alarm[1], alarm[0]);
			}
		} else if (down_pressed) {
			if (*swc_sel == 0) {
				if (time_unit_sel == HR) {
					if (hour[2]>0)
						hour[2]--;
					else
						hour[2] = 23;
				} else {
					if (hour[time_unit_sel-2] > 0)
						hour[time_unit_sel-2]--;
					else
						hour[time_unit_sel-2] = 59;
				}
				set_value(hour[0], s1_ptr, s0_ptr);
				set_value(hour[1], m1_ptr, m0_ptr);
				set_value(hour[2], h1_ptr, h0_ptr);
			} else {
				if (time_unit_sel == HR) {
					if (alarm[2] > 0)
						alarm[2]--;
					else
						alarm[2] = 23;
				} else if (time_unit_sel == MIN ) {
					if (alarm[1] > 0)
						alarm[1]--;
					else
						alarm[1] = 59;
				} else {
					alt_putstr("Can't set an alarm for seconds\n");
				}
				alt_printf("Alarm setted > %x : %x : %x \n", alarm[2], alarm[1], alarm[0]);
			}
		}

		up_pressed = FALSE;
		down_pressed = FALSE;
		set_pressed = FALSE;
		button_pressed = FALSE;

		display_hour();
	}

	return 0;
}

