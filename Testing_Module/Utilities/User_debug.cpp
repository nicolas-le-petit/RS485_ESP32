/**
	Standard debug utils
	Port source for Arduino Style
	DungTT
    29/07/2020
**/
#include "Arduino.h"
#include <stdarg.h>
#include <stdio.h>

#define UART_DEBUG Serial

void user_debug_init(int baud_rate)
{
	UART_DEBUG.begin(baud_rate);
	UART_DEBUG.println("UART Debug is ready!");
	UART_DEBUG.print("Baud rate: ");
	UART_DEBUG.println(baud_rate);
}

static  uint8_t  buffer[256];
static void uart_printf(const char *fmt, ...)
{
	uint32_t len;
	va_list vArgs;
	va_start(vArgs, fmt);
	len = vsprintf((char *)&buffer[0], (char const *)fmt, vArgs);
	va_end(vArgs);
	UART_DEBUG.write(buffer, len);
}
// Du`.. fat hien ra chan ly :D
static void uart_vprintf(const char *fmt, va_list vArgs)
{
	uint32_t len;
	len = vsprintf((char *)&buffer[0], (char const *)fmt, vArgs);
	UART_DEBUG.write(buffer, len);
}

/* ############### Actual debug redirect ################# */
#define __debug_printf(fmt, ...) uart_printf(fmt, __VA_ARGS__)
#define __debug_vprintf(fmt, vArgs) uart_vprintf(fmt, vArgs)

/* ------------------- MAIN DEBUG I/O -------------- */
void user_debug_print(int level, const char* module, int line, const char* fmt, ...)
{
//   osSemaphoreWait(dbgSem_id , osWaitForever);
	
  	if (level == 1)
		{
			uart_printf("[ERROR]");
		}
  	else if (level == 2){
			uart_printf("[WARN]");
		}
		
 	// __debug_printf("%d@%s: ", line, module);
  	__debug_printf("->%s: ", module);
	
	va_list     vArgs;		    
	va_start(vArgs, fmt);
	__debug_vprintf((char const *)fmt, vArgs);
	va_end(vArgs);
}

void dbg_error(const char* module, int line, int ret)
{
//   osSemaphoreWait(dbgSem_id , osWaitForever);
  __debug_printf("[RC] Module %s - Line %d : Error %d\n", module, line, ret);
//   osSemaphoreRelease(dbgSem_id);
}

void user_debug_print_exact(const char* fmt, ...)
{
//   osSemaphoreWait(dbgSem_id , osWaitForever);

	va_list     vArgs;		    
	va_start(vArgs, fmt);
	__debug_vprintf((char const *)fmt, vArgs);
	va_end(vArgs);
	
//   osSemaphoreRelease(dbgSem_id);
}

