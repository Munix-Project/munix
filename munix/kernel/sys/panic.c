/*
 * panic.c
 *
 *  Created on: Aug 13, 2015
 *      Author: miguel
 */

#include <system.h>
#include <logging.h>
#include <printf.h>

void halt_and_catch_fire(char * error_message, const char * file, int line, struct regs * regs) {
	IRQ_OFF;
	debug_print(CRITICAL, "Kernel Panic!");
	debug_print(NORMAL,""); // New line
	debug_print(ERROR, "HACF: %s", error_message);
	// xxx debug_print(ERROR, "Proc: %d", getpid());
	debug_print(ERROR, "File: %s", file);
	debug_print(ERROR, "Line: %d", line);
	if (regs) {
		debug_print(ERROR, "Registers at interrupt:");
		debug_print(ERROR, "eax=0x%x ebx=0x%x", regs->eax, regs->ebx);
		debug_print(ERROR, "ecx=0x%x edx=0x%x", regs->ecx, regs->edx);
		debug_print(ERROR, "esp=0x%x ebp=0x%x", regs->esp, regs->ebp);
		debug_print(ERROR, "Error code: 0x%x",  regs->err_code);
		debug_print(ERROR, "EFLAGS:     0x%x",  regs->eflags);
		debug_print(ERROR, "User ESP:   0x%x",  regs->useresp);
		debug_print(ERROR, "eip=0x%x",          regs->eip);
	}
	debug_print(ERROR, "This process has been descheduled.");

	// temporary:
	PAUSE;
}

void assert_failed(const char *file, uint32_t line, const char *desc){
	IRQ_OFF;
	log_clrscr();
	log_reset();
	debug_print(INSANE, "Kernel Assertion Failed: %s", desc);
	debug_print(INSANE, "File: %s", file);
	debug_print(INSANE, "Line: %d", line);
	debug_print(INSANE, "System Halted!");

	// This is our life now:
	while (1) {
		IRQ_OFF;
		PAUSE;
	}
}
