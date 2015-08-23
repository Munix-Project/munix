/*
 * This file is part of ToaruOS and is released under the terms
 * of the NCSA / University of Illinois License - see LICENSE.md
 * Copyright (C) 2015 Dale Weiler
 *
 */

#include <libc/printf.h>
#include <mod/module.h>
#include <mod/shell/shell.h>

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


