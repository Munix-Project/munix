/*
 * user.c
 *
 *  Created on: Aug 15, 2015
 *      Author: miguel
 */
#include <munix/system.h>

/*
 * Enter ring 3 and jump to `location`.
 *
 * @param location Address to jump to in user space
 * @param argc     Argument count
 * @param argv     Argument pointers
 * @param stack    Userspace stack address
 */
extern void enter_userspace(uintptr_t location, uintptr_t stack);

void enter_user_jmp(uintptr_t location, int argc, char ** argv, uintptr_t stack) {
	IRQ_OFF;
	set_kernel_stack(current_process->image.stack);

	PUSH(stack, uintptr_t, (uintptr_t)argv);
	PUSH(stack, int, argc);
	enter_userspace(location, stack);
}


