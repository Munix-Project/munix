/*
 * main.c
 *
 *  Created on: Aug 13, 2015
 *      Author: miguel
 */

#include <system.h>
#include <multiboot.h>
#include <logging.h>
#include <printf.h>

uintptr_t initial_esp = 0;

const char KERNEL_NAME[] = "Minux";
const char KERNEL_VERSION [] = "0.1";

void kernel_intro(){
	debug_print(NORMAL, "%s version %s", KERNEL_NAME, KERNEL_VERSION);
	debug_print(NORMAL,""); // newline
}

void multiboot_move_stack_location(){

}

void init(struct multiboot *mboot, uint32_t mboot_mag, uintptr_t esp){
	// Prepare initialization:
	log_clrscr();
	kernel_intro();
	debug_print(INFO, "Initializing...");

	// Initialize everything:

	initial_esp = esp;

	// Multiboot:
	debug_print(INFO, "Setting Multiboot header...");
		assert(mboot_mag == MULTIBOOT_EAX_MAGIC && "ERROR: Didn't boot with Multiboot");
		uint32_t mboot_mods_count = 0;
		mboot_mod_t * mboot_mods = NULL;
		mboot_ptr = mboot;

	// HAL:
	debug_print(INFO, "Preparing HAL...");
		// GDT
		debug_print(INFO, "Installing Global Descriptor Table (GDT)...");
		gdt_install();
		// IDT
		debug_print(INFO, "Installing Interrupt Descriptor Table (IDT)...");
		idt_install();
		// ISR
		debug_print(INFO, "Installing Interrupt Service Routines (ISR)...");
		isr_install();
		// IRQ (PIC AND PIT)
		debug_print(INFO, "Installing Interrupt Requests (IRQ) for Programmable Interrupt Controller       (PIC) and Programmable Interval Timer (PIT)...");
		irq_install();

		// Move stack position due to multiboot's modules loaded from grub
		debug_print(INFO, "Checking for grub modules....");
		multiboot_move_stack_location();

		// Paging:

		// Heap:

		debug_print(NORMAL, "");
		debug_print(NOTICE, "System successfully initialized!");
}

int kmain(struct multiboot *mboot, uint32_t mboot_mag, uintptr_t esp){
	init(mboot, mboot_mag, esp);

	for(;;){}
	return 0;
}
