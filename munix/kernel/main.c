/* vim: tabstop=4 shiftwidth=4 noexpandtab
 *
 * The ToAruOS kernel is released under the terms of the
 * University of Illinois / NCSA License.
 *
 * Copyright (C) 2011-2014 Kevin Lange.  All rights reserved.
 * Copyright (C) 2012 Markus Schober
 * Copyright (C) 2014 Lioncash
 *
 *                           Dedicated to the memory of
 *                                Dennis Ritchie
 *                                   1941-2011
 *
 * Developed by: ToAruOS Kernel Development Team
 *               http://github.com/klange/osdev
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal with the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimers.
 *   2. Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimers in the
 *      documentation and/or other materials provided with the distribution.
 *   3. Neither the names of the ToAruOS Kernel Development Team, Kevin Lange,
 *      nor the names of its contributors may be used to endorse
 *      or promote products derived from this Software without specific prior
 *      written permission.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
 * CONTRIBUTORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * WITH THE SOFTWARE.
 */

#include <system.h>
#include <boot.h>
#include <ext2.h>
#include <fs.h>
#include <logging.h>
#include <process.h>
#include <shm.h>
#include <args.h>
#include <module.h>

/* Initial esp value that is loaded right from the beginning and is used for memory */
uintptr_t initial_esp = 0;

/* Module's global variables: */
uint32_t mboot_mods_count = 0;
mboot_mod_t * mboot_mods = NULL;
struct pack_header {
	char     head[4];
	uint32_t region_size;
};

void move_stack_because_modules(struct multiboot *mboot){
	if (mboot_ptr->flags & (1 << 3)) {
			debug_print(NOTICE, "There %s %d module%s starting at 0x%x.", mboot_ptr->mods_count == 1 ? "is" : "are", mboot_ptr->mods_count, mboot_ptr->mods_count == 1 ? "" : "s", mboot_ptr->mods_addr);
			debug_print(NOTICE, "Current kernel heap start point would be 0x%x.", &end);
			if (mboot_ptr->mods_count > 0) {
				uintptr_t last_mod = (uintptr_t)&end;

				mboot_mods = (mboot_mod_t *)mboot_ptr->mods_addr;
				mboot_mods_count = mboot_ptr->mods_count;

				for (uint32_t i = 0; i < mboot_ptr->mods_count; ++i ) {
					mboot_mod_t * mod = &mboot_mods[i];
					uint32_t module_start = mod->mod_start;
					uint32_t module_end   = mod->mod_end;
					if ((uintptr_t)mod + sizeof(mboot_mod_t) > last_mod) {
						/* Just in case some silly person put this *behind* the modules... */
						last_mod = (uintptr_t)mod + sizeof(mboot_mod_t);
					}
					debug_print(NOTICE, "Module %d is at 0x%x:0x%x", i, module_start, module_end);
					if (last_mod < module_end) {
						last_mod = module_end;
					}
				}
				debug_print(NOTICE, "Moving kernel heap start to 0x%x", last_mod);
				kmalloc_startat(last_mod);
			}
		}
}

char* setup_cmdline() {
	char cmdline_buffer[1024], * cmdline;

	size_t len = strlen((char *)mboot_ptr->cmdline) + 1;
	memmove(cmdline_buffer, (char *)mboot_ptr->cmdline, len);

	/* Relocate the command line */
	cmdline = (char *)kmalloc(len);
	memcpy(cmdline, cmdline_buffer, len);
	return cmdline;
}

void setup_cmdline_finalize(char* cmdline) {
	if (cmdline)
		args_parse(cmdline);
}

void load_grub_modules() {
	// Or, in this case (FOR NOW), QEMU's modules ;)
	for (unsigned int i = 0; i < mboot_ptr->mods_count; ++i ) {
		mboot_mod_t * mod = &mboot_mods[i];
		uint32_t module_start = mod->mod_start;
		uint32_t module_end = mod->mod_end;
		size_t   module_size = module_end - module_start;

		int check_result = module_quickcheck((void *)module_start);
		if (check_result == 1) {
			debug_print(NOTICE, "Loading a module: 0x%x:0x%x", module_start, module_end);
			module_data_t * mod_info = (module_data_t *)module_load_direct((void *)(module_start), module_size);
			if (mod_info) {
				debug_print(NOTICE, "Loaded: %s", mod_info->mod_info->name);
			}
		} else if (check_result == 2) {
			/* Mod pack */
			debug_print(NOTICE, "Loading modpack. %x", module_start);
			struct pack_header * pack_header = (struct pack_header *)module_start;
			while (pack_header->region_size) {
				void * start = (void *)((uintptr_t)pack_header + 4096);
				int result = module_quickcheck(start);
				if (result != 1) {
					debug_print(WARNING, "Not actually a module?! %x", start);
				}
				module_data_t * mod_info = (module_data_t *)module_load_direct(start, pack_header->region_size);
				if (mod_info) {
					debug_print(NOTICE, "Loaded: %s", mod_info->mod_info->name);
				}
				pack_header = (struct pack_header *)((uintptr_t)start + pack_header->region_size);
			}
			debug_print(NOTICE, "Done with modpack.");
		} else {
			debug_print(NOTICE, "Loading initrd: 0x%x:0x%x", module_start, module_end);
			initrd_mount(module_start, module_size);
		}
	}
}

void init_kernel(struct multiboot *mboot, uint32_t mboot_magic, uintptr_t esp){
	/* Check if multiboot is set */
	assert(mboot_magic == MULTIBOOT_EAX_MAGIC && "Didn't boot with multiboot, not sure how we got here.");

	/* Set up critical boot time global variables: */
	initial_esp = esp;
	mboot_ptr = mboot;

	/* Initialize core modules */
	gdt_install(); /* Global Descriptor Table	 	(GDT) 	*/
	idt_install(); /* Interrupt Descriptor Table 	(IDT) 	*/
	isr_install(); /* Interrupt Service Requests 	(ISR) 	*/
	irq_install(); /* Hardware Interrupt Requests 	(IRQ)	*/

	/* Move the stack's position due to the fact GRUB/QEMU might load some modules into RAM */
	move_stack_because_modules(mboot);

	/* Set up paging: */
	paging_install(mboot_ptr->mem_upper + mboot_ptr->mem_lower);
	paging_parse(); /* Check how it is */
	paging_finalize(); /* Looking good! Finish him! */

	/* Setup command line that is used for initialization during launching of QEMU */
	char * cmdline = setup_cmdline();

	/* Install Kernel Heap! (by setting the heap_end variable to the already set placement_pointer) */
	heap_install();

	/* Now the heap is ready, you can parse the command line provided during QEMU's launch */
	setup_cmdline_finalize(cmdline);

	/* Now that the memory and paging is set up, install the most abstract features of this kernel! */
	vfs_install();		/* Virtual File System! 			*/
	tasking_install();  /* Multi-tasking! 					*/
	timer_install();    /* PIT driver 						*/
	fpu_install();      /* FPU/SSE 							*/
	syscalls_install(); /* Install the system calls vector 	*/
	shm_install();      /* Install shared memory 			*/
	modules_install();  /* Modules! 						*/

	/* Load modules from bootloader */
	debug_print(NOTICE, "%d modules to load", mboot_mods_count);
	load_grub_modules();

	/*
	 * We're still running? Surprising! All that's left is prepare ourselves for creating basic devices and mounting root,
	 * then we'll be on our way to userpace on /bin/init!
	 */

	/* Map /dev to a device mapper so we can set root there (and also other devices) */
	map_vfs_directory("/dev");

	/* Grab start arguments provided by QEMU/GRUB: (if it's QEMU then the argument is in --append="..." while launching the script) */

	/* Use QEMU's arguments for setting root here: */
	if (args_present("root"))
		vfs_mount_type("ext2", args_value("root"), "/"); /* Use the good ol' ext2 :) We might use more in the future (MIGHT!...) */

	/* And here for the argument 'start': */
	if (args_present("start")) {
		/* Grab what start argument you passed on, you better not screw up this on QEMU launch script my good sir... */
		char * c = args_value("start");
		if (!c) {
			/* Really? Did you just pass on start= ? Just that? Why are you even trying to run this kernel then? */
			debug_print(WARNING, "Expected an argument to kernel option `start`. Ignoring.");
		} else {
			/* Good! You did it! */
			debug_print(NOTICE, "Got start argument: %s", c);
			boot_arg = strdup(c); /* We're passing this variable for initialization of the OS */
		}
	}

	/*
	 * At this point, root should be set up somewhere, preferably on /dev/hda,
	 * if not, you dun' goof'd on the --append='...' argument on QEMU, better fix it son.
	 */
	if (!fs_root) {
		debug_print(CRITICAL, "No root filesystem is mounted. Skipping init.");
		map_vfs_directory("/");
		switch_task(0);
	}

	debug_print(NOTICE, "System Successfully Initialized!");
	debug_print(NORMAL,""); // new line
	// Yes! All is done and well! Congratulations!
}

int count_argc(char* argv[]){
	int argc = 0;
	while (argv[argc]) argc++;
	return argc;
}

/*
 * multiboot i386 (pc) kernel entry point run by 'kernel_boot.S' on start
 */
int kmain(struct multiboot *mboot, uint32_t mboot_magic, uintptr_t esp) {
	/* Initialize the system completely! */
	init_kernel(mboot, mboot_magic, esp);

	/* Prepare to run /bin/init */
	char * argv[] = {
		"/bin/init", /* Init program */
		boot_arg 	 /* Pass in the parsed arguments */
	};

	/* Run init / OS! */
	system(argv[0], count_argc(argv), argv);

	/* The OS exited... That's weird... Are you sure you wanted to do that? */
	return 0;
}
