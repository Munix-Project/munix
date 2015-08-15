/*
 * crash.c
 *
 *  Created on: Aug 13, 2015
 *      Author: miguel
 */

#include <module.h>
#include <printf.h>
#include <mod/shell.h>

DEFINE_SHELL_FUNCTION(crash, "Dereference NULL.") {
	fprintf(tty, "*0x0 = %x\n", *((int *)0x00));
	*((int *)0x0) = 0x42;
	fprintf(tty, "*0x0 = %x\n", *((int *)0x00));
	return 0;
}

DEFINE_SHELL_FUNCTION(assert_false, "assert(0)") {
	assert(0);
	return 0;
}

static int crash_init(void) {
	BIND_SHELL_FUNCTION(crash);
	BIND_SHELL_FUNCTION(assert_false);
	return 0;
}

static int crash_fini(void) {
	return 0;
}

MODULE_DEF(crash, crash_init, crash_fini);
MODULE_DEPENDS(debugshell);

