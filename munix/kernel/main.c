/*
 * main.c
 *
 *  Created on: Aug 13, 2015
 *      Author: miguel
 */
#include <multiboot.h>

uintptr_t initial_esp = 0;

int main(struct multiboot *mboot, uint32_t mboot_mag, uintptr_t esp){
	assert(1==1 && "ha");
	return 0;
}
