/*
 * system.h - SOPC Builder system and BSP software package information
 *
 * Machine generated for CPU 'CPU' in SOPC Builder design 'system'
 * SOPC Builder design path: ../../system.sopcinfo
 *
 * Generated: Sun Nov 01 01:53:59 CST 2020
 */

/*
 * DO NOT MODIFY THIS FILE
 *
 * Changing this file will have subtle consequences
 * which will almost certainly lead to a nonfunctioning
 * system. If you do modify this file, be aware that your
 * changes will be overwritten and lost when this file
 * is generated again.
 *
 * DO NOT MODIFY THIS FILE
 */

/*
 * License Agreement
 *
 * Copyright (c) 2008
 * Altera Corporation, San Jose, California, USA.
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * This agreement shall be governed in all respects by the laws of the State
 * of California and by the laws of the United States of America.
 */

#ifndef __SYSTEM_H_
#define __SYSTEM_H_

/* Include definitions from linker script generator */
#include "linker.h"


/*
 * ALARM configuration
 *
 */

#define ALARM_BASE 0x4060
#define ALARM_BIT_CLEARING_EDGE_REGISTER 0
#define ALARM_BIT_MODIFYING_OUTPUT_REGISTER 0
#define ALARM_CAPTURE 0
#define ALARM_DATA_WIDTH 1
#define ALARM_DO_TEST_BENCH_WIRING 0
#define ALARM_DRIVEN_SIM_VALUE 0
#define ALARM_EDGE_TYPE "NONE"
#define ALARM_FREQ 50000000
#define ALARM_HAS_IN 0
#define ALARM_HAS_OUT 1
#define ALARM_HAS_TRI 0
#define ALARM_IRQ -1
#define ALARM_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ALARM_IRQ_TYPE "NONE"
#define ALARM_NAME "/dev/ALARM"
#define ALARM_RESET_VALUE 0
#define ALARM_SPAN 16
#define ALARM_TYPE "altera_avalon_pio"
#define ALT_MODULE_CLASS_ALARM altera_avalon_pio


/*
 * BTN_DOWN configuration
 *
 */

#define ALT_MODULE_CLASS_BTN_DOWN altera_avalon_pio
#define BTN_DOWN_BASE 0x4090
#define BTN_DOWN_BIT_CLEARING_EDGE_REGISTER 0
#define BTN_DOWN_BIT_MODIFYING_OUTPUT_REGISTER 0
#define BTN_DOWN_CAPTURE 0
#define BTN_DOWN_DATA_WIDTH 1
#define BTN_DOWN_DO_TEST_BENCH_WIRING 1
#define BTN_DOWN_DRIVEN_SIM_VALUE 0
#define BTN_DOWN_EDGE_TYPE "NONE"
#define BTN_DOWN_FREQ 50000000
#define BTN_DOWN_HAS_IN 1
#define BTN_DOWN_HAS_OUT 0
#define BTN_DOWN_HAS_TRI 0
#define BTN_DOWN_IRQ 3
#define BTN_DOWN_IRQ_INTERRUPT_CONTROLLER_ID 0
#define BTN_DOWN_IRQ_TYPE "LEVEL"
#define BTN_DOWN_NAME "/dev/BTN_DOWN"
#define BTN_DOWN_RESET_VALUE 0
#define BTN_DOWN_SPAN 16
#define BTN_DOWN_TYPE "altera_avalon_pio"


/*
 * BTN_SET_ALARM configuration
 *
 */

#define ALT_MODULE_CLASS_BTN_SET_ALARM altera_avalon_pio
#define BTN_SET_ALARM_BASE 0x4070
#define BTN_SET_ALARM_BIT_CLEARING_EDGE_REGISTER 0
#define BTN_SET_ALARM_BIT_MODIFYING_OUTPUT_REGISTER 0
#define BTN_SET_ALARM_CAPTURE 0
#define BTN_SET_ALARM_DATA_WIDTH 1
#define BTN_SET_ALARM_DO_TEST_BENCH_WIRING 1
#define BTN_SET_ALARM_DRIVEN_SIM_VALUE 0
#define BTN_SET_ALARM_EDGE_TYPE "NONE"
#define BTN_SET_ALARM_FREQ 50000000
#define BTN_SET_ALARM_HAS_IN 1
#define BTN_SET_ALARM_HAS_OUT 0
#define BTN_SET_ALARM_HAS_TRI 0
#define BTN_SET_ALARM_IRQ 1
#define BTN_SET_ALARM_IRQ_INTERRUPT_CONTROLLER_ID 0
#define BTN_SET_ALARM_IRQ_TYPE "LEVEL"
#define BTN_SET_ALARM_NAME "/dev/BTN_SET_ALARM"
#define BTN_SET_ALARM_RESET_VALUE 0
#define BTN_SET_ALARM_SPAN 16
#define BTN_SET_ALARM_TYPE "altera_avalon_pio"


/*
 * BTN_UP configuration
 *
 */

#define ALT_MODULE_CLASS_BTN_UP altera_avalon_pio
#define BTN_UP_BASE 0x4080
#define BTN_UP_BIT_CLEARING_EDGE_REGISTER 0
#define BTN_UP_BIT_MODIFYING_OUTPUT_REGISTER 0
#define BTN_UP_CAPTURE 0
#define BTN_UP_DATA_WIDTH 1
#define BTN_UP_DO_TEST_BENCH_WIRING 1
#define BTN_UP_DRIVEN_SIM_VALUE 0
#define BTN_UP_EDGE_TYPE "NONE"
#define BTN_UP_FREQ 50000000
#define BTN_UP_HAS_IN 1
#define BTN_UP_HAS_OUT 0
#define BTN_UP_HAS_TRI 0
#define BTN_UP_IRQ 2
#define BTN_UP_IRQ_INTERRUPT_CONTROLLER_ID 0
#define BTN_UP_IRQ_TYPE "LEVEL"
#define BTN_UP_NAME "/dev/BTN_UP"
#define BTN_UP_RESET_VALUE 0
#define BTN_UP_SPAN 16
#define BTN_UP_TYPE "altera_avalon_pio"


/*
 * CPU configuration
 *
 */

#define ALT_CPU_ARCHITECTURE "altera_nios2_gen2"
#define ALT_CPU_BIG_ENDIAN 0
#define ALT_CPU_BREAK_ADDR 0x00002820
#define ALT_CPU_CPU_ARCH_NIOS2_R1
#define ALT_CPU_CPU_FREQ 50000000u
#define ALT_CPU_CPU_ID_SIZE 1
#define ALT_CPU_CPU_ID_VALUE 0x00000000
#define ALT_CPU_CPU_IMPLEMENTATION "tiny"
#define ALT_CPU_DATA_ADDR_WIDTH 0xf
#define ALT_CPU_DCACHE_LINE_SIZE 0
#define ALT_CPU_DCACHE_LINE_SIZE_LOG2 0
#define ALT_CPU_DCACHE_SIZE 0
#define ALT_CPU_EXCEPTION_ADDR 0x00001020
#define ALT_CPU_FLASH_ACCELERATOR_LINES 0
#define ALT_CPU_FLASH_ACCELERATOR_LINE_SIZE 0
#define ALT_CPU_FLUSHDA_SUPPORTED
#define ALT_CPU_FREQ 50000000
#define ALT_CPU_HARDWARE_DIVIDE_PRESENT 0
#define ALT_CPU_HARDWARE_MULTIPLY_PRESENT 0
#define ALT_CPU_HARDWARE_MULX_PRESENT 0
#define ALT_CPU_HAS_DEBUG_CORE 1
#define ALT_CPU_HAS_DEBUG_STUB
#define ALT_CPU_HAS_ILLEGAL_INSTRUCTION_EXCEPTION
#define ALT_CPU_HAS_JMPI_INSTRUCTION
#define ALT_CPU_ICACHE_LINE_SIZE 0
#define ALT_CPU_ICACHE_LINE_SIZE_LOG2 0
#define ALT_CPU_ICACHE_SIZE 0
#define ALT_CPU_INST_ADDR_WIDTH 0xf
#define ALT_CPU_NAME "CPU"
#define ALT_CPU_OCI_VERSION 1
#define ALT_CPU_RESET_ADDR 0x00001000


/*
 * CPU configuration (with legacy prefix - don't use these anymore)
 *
 */

#define NIOS2_BIG_ENDIAN 0
#define NIOS2_BREAK_ADDR 0x00002820
#define NIOS2_CPU_ARCH_NIOS2_R1
#define NIOS2_CPU_FREQ 50000000u
#define NIOS2_CPU_ID_SIZE 1
#define NIOS2_CPU_ID_VALUE 0x00000000
#define NIOS2_CPU_IMPLEMENTATION "tiny"
#define NIOS2_DATA_ADDR_WIDTH 0xf
#define NIOS2_DCACHE_LINE_SIZE 0
#define NIOS2_DCACHE_LINE_SIZE_LOG2 0
#define NIOS2_DCACHE_SIZE 0
#define NIOS2_EXCEPTION_ADDR 0x00001020
#define NIOS2_FLASH_ACCELERATOR_LINES 0
#define NIOS2_FLASH_ACCELERATOR_LINE_SIZE 0
#define NIOS2_FLUSHDA_SUPPORTED
#define NIOS2_HARDWARE_DIVIDE_PRESENT 0
#define NIOS2_HARDWARE_MULTIPLY_PRESENT 0
#define NIOS2_HARDWARE_MULX_PRESENT 0
#define NIOS2_HAS_DEBUG_CORE 1
#define NIOS2_HAS_DEBUG_STUB
#define NIOS2_HAS_ILLEGAL_INSTRUCTION_EXCEPTION
#define NIOS2_HAS_JMPI_INSTRUCTION
#define NIOS2_ICACHE_LINE_SIZE 0
#define NIOS2_ICACHE_LINE_SIZE_LOG2 0
#define NIOS2_ICACHE_SIZE 0
#define NIOS2_INST_ADDR_WIDTH 0xf
#define NIOS2_OCI_VERSION 1
#define NIOS2_RESET_ADDR 0x00001000


/*
 * Define for each module class mastered by the CPU
 *
 */

#define __ALTERA_AVALON_JTAG_UART
#define __ALTERA_AVALON_ONCHIP_MEMORY2
#define __ALTERA_AVALON_PIO
#define __ALTERA_NIOS2_GEN2


/*
 * H0 configuration
 *
 */

#define ALT_MODULE_CLASS_H0 altera_avalon_pio
#define H0_BASE 0x4010
#define H0_BIT_CLEARING_EDGE_REGISTER 0
#define H0_BIT_MODIFYING_OUTPUT_REGISTER 0
#define H0_CAPTURE 0
#define H0_DATA_WIDTH 4
#define H0_DO_TEST_BENCH_WIRING 0
#define H0_DRIVEN_SIM_VALUE 0
#define H0_EDGE_TYPE "NONE"
#define H0_FREQ 50000000
#define H0_HAS_IN 0
#define H0_HAS_OUT 1
#define H0_HAS_TRI 0
#define H0_IRQ -1
#define H0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define H0_IRQ_TYPE "NONE"
#define H0_NAME "/dev/H0"
#define H0_RESET_VALUE 0
#define H0_SPAN 16
#define H0_TYPE "altera_avalon_pio"


/*
 * H1 configuration
 *
 */

#define ALT_MODULE_CLASS_H1 altera_avalon_pio
#define H1_BASE 0x4000
#define H1_BIT_CLEARING_EDGE_REGISTER 0
#define H1_BIT_MODIFYING_OUTPUT_REGISTER 0
#define H1_CAPTURE 0
#define H1_DATA_WIDTH 4
#define H1_DO_TEST_BENCH_WIRING 0
#define H1_DRIVEN_SIM_VALUE 0
#define H1_EDGE_TYPE "NONE"
#define H1_FREQ 50000000
#define H1_HAS_IN 0
#define H1_HAS_OUT 1
#define H1_HAS_TRI 0
#define H1_IRQ -1
#define H1_IRQ_INTERRUPT_CONTROLLER_ID -1
#define H1_IRQ_TYPE "NONE"
#define H1_NAME "/dev/H1"
#define H1_RESET_VALUE 0
#define H1_SPAN 16
#define H1_TYPE "altera_avalon_pio"


/*
 * M0 configuration
 *
 */

#define ALT_MODULE_CLASS_M0 altera_avalon_pio
#define M0_BASE 0x4030
#define M0_BIT_CLEARING_EDGE_REGISTER 0
#define M0_BIT_MODIFYING_OUTPUT_REGISTER 0
#define M0_CAPTURE 0
#define M0_DATA_WIDTH 4
#define M0_DO_TEST_BENCH_WIRING 0
#define M0_DRIVEN_SIM_VALUE 0
#define M0_EDGE_TYPE "NONE"
#define M0_FREQ 50000000
#define M0_HAS_IN 0
#define M0_HAS_OUT 1
#define M0_HAS_TRI 0
#define M0_IRQ -1
#define M0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define M0_IRQ_TYPE "NONE"
#define M0_NAME "/dev/M0"
#define M0_RESET_VALUE 0
#define M0_SPAN 16
#define M0_TYPE "altera_avalon_pio"


/*
 * M1 configuration
 *
 */

#define ALT_MODULE_CLASS_M1 altera_avalon_pio
#define M1_BASE 0x4020
#define M1_BIT_CLEARING_EDGE_REGISTER 0
#define M1_BIT_MODIFYING_OUTPUT_REGISTER 0
#define M1_CAPTURE 0
#define M1_DATA_WIDTH 4
#define M1_DO_TEST_BENCH_WIRING 0
#define M1_DRIVEN_SIM_VALUE 0
#define M1_EDGE_TYPE "NONE"
#define M1_FREQ 50000000
#define M1_HAS_IN 0
#define M1_HAS_OUT 1
#define M1_HAS_TRI 0
#define M1_IRQ -1
#define M1_IRQ_INTERRUPT_CONTROLLER_ID -1
#define M1_IRQ_TYPE "NONE"
#define M1_NAME "/dev/M1"
#define M1_RESET_VALUE 0
#define M1_SPAN 16
#define M1_TYPE "altera_avalon_pio"


/*
 * RAM configuration
 *
 */

#define ALT_MODULE_CLASS_RAM altera_avalon_onchip_memory2
#define RAM_ALLOW_IN_SYSTEM_MEMORY_CONTENT_EDITOR 0
#define RAM_ALLOW_MRAM_SIM_CONTENTS_ONLY_FILE 0
#define RAM_BASE 0x1000
#define RAM_CONTENTS_INFO ""
#define RAM_DUAL_PORT 0
#define RAM_GUI_RAM_BLOCK_TYPE "AUTO"
#define RAM_INIT_CONTENTS_FILE "system_RAM"
#define RAM_INIT_MEM_CONTENT 1
#define RAM_INSTANCE_ID "NONE"
#define RAM_IRQ -1
#define RAM_IRQ_INTERRUPT_CONTROLLER_ID -1
#define RAM_NAME "/dev/RAM"
#define RAM_NON_DEFAULT_INIT_FILE_ENABLED 0
#define RAM_RAM_BLOCK_TYPE "AUTO"
#define RAM_READ_DURING_WRITE_MODE "DONT_CARE"
#define RAM_SINGLE_CLOCK_OP 0
#define RAM_SIZE_MULTIPLE 1
#define RAM_SIZE_VALUE 4096
#define RAM_SPAN 4096
#define RAM_TYPE "altera_avalon_onchip_memory2"
#define RAM_WRITABLE 1


/*
 * S0 configuration
 *
 */

#define ALT_MODULE_CLASS_S0 altera_avalon_pio
#define S0_BASE 0x4050
#define S0_BIT_CLEARING_EDGE_REGISTER 0
#define S0_BIT_MODIFYING_OUTPUT_REGISTER 0
#define S0_CAPTURE 0
#define S0_DATA_WIDTH 4
#define S0_DO_TEST_BENCH_WIRING 0
#define S0_DRIVEN_SIM_VALUE 0
#define S0_EDGE_TYPE "NONE"
#define S0_FREQ 50000000
#define S0_HAS_IN 0
#define S0_HAS_OUT 1
#define S0_HAS_TRI 0
#define S0_IRQ -1
#define S0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define S0_IRQ_TYPE "NONE"
#define S0_NAME "/dev/S0"
#define S0_RESET_VALUE 0
#define S0_SPAN 16
#define S0_TYPE "altera_avalon_pio"


/*
 * S1 configuration
 *
 */

#define ALT_MODULE_CLASS_S1 altera_avalon_pio
#define S1_BASE 0x4040
#define S1_BIT_CLEARING_EDGE_REGISTER 0
#define S1_BIT_MODIFYING_OUTPUT_REGISTER 0
#define S1_CAPTURE 0
#define S1_DATA_WIDTH 4
#define S1_DO_TEST_BENCH_WIRING 0
#define S1_DRIVEN_SIM_VALUE 0
#define S1_EDGE_TYPE "NONE"
#define S1_FREQ 50000000
#define S1_HAS_IN 0
#define S1_HAS_OUT 1
#define S1_HAS_TRI 0
#define S1_IRQ -1
#define S1_IRQ_INTERRUPT_CONTROLLER_ID -1
#define S1_IRQ_TYPE "NONE"
#define S1_NAME "/dev/S1"
#define S1_RESET_VALUE 0
#define S1_SPAN 16
#define S1_TYPE "altera_avalon_pio"


/*
 * System configuration
 *
 */

#define ALT_DEVICE_FAMILY "Cyclone V"
#define ALT_ENHANCED_INTERRUPT_API_PRESENT
#define ALT_IRQ_BASE NULL
#define ALT_LOG_PORT "/dev/null"
#define ALT_LOG_PORT_BASE 0x0
#define ALT_LOG_PORT_DEV null
#define ALT_LOG_PORT_TYPE ""
#define ALT_NUM_EXTERNAL_INTERRUPT_CONTROLLERS 0
#define ALT_NUM_INTERNAL_INTERRUPT_CONTROLLERS 1
#define ALT_NUM_INTERRUPT_CONTROLLERS 1
#define ALT_STDERR "/dev/UART"
#define ALT_STDERR_BASE 0x3148
#define ALT_STDERR_DEV UART
#define ALT_STDERR_IS_JTAG_UART
#define ALT_STDERR_PRESENT
#define ALT_STDERR_TYPE "altera_avalon_jtag_uart"
#define ALT_STDIN "/dev/UART"
#define ALT_STDIN_BASE 0x3148
#define ALT_STDIN_DEV UART
#define ALT_STDIN_IS_JTAG_UART
#define ALT_STDIN_PRESENT
#define ALT_STDIN_TYPE "altera_avalon_jtag_uart"
#define ALT_STDOUT "/dev/UART"
#define ALT_STDOUT_BASE 0x3148
#define ALT_STDOUT_DEV UART
#define ALT_STDOUT_IS_JTAG_UART
#define ALT_STDOUT_PRESENT
#define ALT_STDOUT_TYPE "altera_avalon_jtag_uart"
#define ALT_SYSTEM_NAME "system"


/*
 * UART configuration
 *
 */

#define ALT_MODULE_CLASS_UART altera_avalon_jtag_uart
#define UART_BASE 0x3148
#define UART_IRQ 0
#define UART_IRQ_INTERRUPT_CONTROLLER_ID 0
#define UART_NAME "/dev/UART"
#define UART_READ_DEPTH 64
#define UART_READ_THRESHOLD 8
#define UART_SPAN 8
#define UART_TYPE "altera_avalon_jtag_uart"
#define UART_WRITE_DEPTH 64
#define UART_WRITE_THRESHOLD 8


/*
 * hal configuration
 *
 */

#define ALT_INCLUDE_INSTRUCTION_RELATED_EXCEPTION_API
#define ALT_MAX_FD 4
#define ALT_SYS_CLK none
#define ALT_TIMESTAMP_CLK none

#endif /* __SYSTEM_H_ */
