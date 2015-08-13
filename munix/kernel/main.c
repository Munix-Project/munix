/*
 * main.c
 *
 *  Created on: Aug 13, 2015
 *      Author: miguel
 */

#include <system.h>
#include <multiboot.h>
#include <fs.h>
//xxx #include <ext2.h>
#include <logging.h>
#include <process.h>
#include <shm.h>
#include <args.h>
#include <module.h>

uintptr_t initial_esp = 0;

uint32_t mboot_mods_count;
struct pack_header {
	char     head[4];
	uint32_t region_size;
};
fs_node_t * ramdisk_mount(uintptr_t, size_t);

const char KERNEL_NAME[] = "Minux";
const char KERNEL_VERSION [] = "0.1";

void kernel_intro(){
	debug_print(NORMAL, "%s version %s", KERNEL_NAME, KERNEL_VERSION);
	debug_print(NORMAL,""); // newline
}

void init(struct multiboot *mboot, uint32_t mboot_mag, uintptr_t esp){
	extern char * cmdline;

	// Prepare initialization:
	log_clrscr();
	kernel_intro();
	debug_print(INFO, "Initializing...");

	// Initialize everything:

	initial_esp = esp;

	// Multiboot:
	debug_print(INFO, "Setting Multiboot header...");
		assert(mboot_mag == MULTIBOOT_EAX_MAGIC && "ERROR: Didn't boot with Multiboot");
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
		debug_print(INFO, "Checking for grub modules...");
		if (mboot_ptr->flags & (1 << 3)) {
			mboot_mods_count = mboot_ptr->mods_count;

			debug_print(NOTICE, "There %s %d module%s starting at 0x%x.", mboot_mods_count == 1 ? "is" : "are", mboot_mods_count, mboot_mods_count == 1 ? "" : "s", mboot_ptr->mods_addr);
			debug_print(NOTICE, "Current kernel heap start point would be 0x%x.", &end);
			if (mboot_ptr->mods_count > 0) {
				uintptr_t last_mod = (uintptr_t)&end;
				uint32_t i;
				mboot_mods = (mboot_mod_t *)mboot_ptr->mods_addr;
				for (i = 0; i < mboot_ptr->mods_count; ++i ) {
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

		// Paging:
		debug_print(INFO, "Installing paging...");
		paging_install(mboot_ptr->mem_upper + mboot_ptr->mem_lower);
		if (mboot_ptr->flags & (1 << 6)) {
			debug_print(NOTICE, "Parsing memory map.");
			mboot_memmap_t * mmap = (void *)mboot_ptr->mmap_addr;
			while ((uintptr_t)mmap < mboot_ptr->mmap_addr + mboot_ptr->mmap_length) {
				if (mmap->type == 2) {
					for (unsigned long long int i = 0; i < mmap->length; i += 0x1000) {
						if (mmap->base_addr + i > 0xFFFFFFFF) break;
						debug_print(INFO, "Marking 0x%x", (uint32_t)(mmap->base_addr + i));
						paging_mark_system((mmap->base_addr + i) & 0xFFFFF000);
					}
				}
				mmap = (mboot_memmap_t *) ((uintptr_t)mmap + mmap->size + sizeof(uintptr_t));
			}
		}
		paging_finalize();

		{
			char cmdline_[1024];

			size_t len = strlen((char *)mboot_ptr->cmdline);
			memmove(cmdline_, (char *)mboot_ptr->cmdline, len + 1);

			/* Relocate the command line */
			cmdline = (char *)kmalloc(len + 1);
			memcpy(cmdline, cmdline_, len + 1);
		}

		// Heap:
		debug_print(INFO, "Setting up the heap memory...");
		heap_install();     /* Kernel heap */

		if (cmdline) {
			args_parse(cmdline);
		}

		// VFS:
		debug_print(INFO, "Installing Virtual File System...");
		vfs_install();

		// Tasking:
		debug_print(INFO, "Installing Multitasking...");
		tasking_install();

		// Timer:
		debug_print(INFO, "Installing System Timer...");
		timer_install();

		// FPU:
		debug_print(INFO, "Installing Floating Point Unit (FPU)...");
		fpu_install();

		// System calls:
		debug_print(INFO, "Preparing System API...");
		syscalls_install();

		// Shared memory:
		debug_print(INFO, "Setting up shared memory...");
		shm_install();

		// Shared memory:
		debug_print(INFO, "Installing modules...");
		modules_install();

		// Load modules:
		/* Load modules from bootloader */
		debug_print(NOTICE, "%d modules to load", mboot_mods_count);

		for (unsigned int i = 0; i < mboot_mods_count; ++i ) {
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
				debug_print(NOTICE, "Loading ramdisk: 0x%x:0x%x", module_start, module_end);
				ramdisk_mount(module_start, module_size);
			}
		}

		/* Map /dev to a device mapper */
		map_vfs_directory("/dev");

		if (args_present("root")) {
			vfs_mount_type("ext2", args_value("root"), "/");
		}

		if (args_present("start")) {
			char * c = args_value("start");
			if (!c) {
				debug_print(WARNING, "Expected an argument to kernel option `start`. Ignoring.");
			} else {
				debug_print(NOTICE, "Got start argument: %s", c);
				boot_arg = strdup(c);
			}
		}

		if (!fs_root) {
			debug_print(CRITICAL, "No root filesystem is mounted. Skipping init.");
			map_vfs_directory("/");
			switch_task(0);
		}

		debug_print(NORMAL, "");
		debug_print(NOTICE, "System successfully initialized!");
}

int kmain(struct multiboot *mboot, uint32_t mboot_mag, uintptr_t esp){
	init(mboot, mboot_mag, esp);

	/* Prepare to run /bin/init */
	char * argv[] = {
		"/bin/init",
		boot_arg,
		NULL
	};
	int argc = 0;
	while (argv[argc]) {
		argc++;
	}

	system(argv[0], argc, argv); /* Run init */

	return 0;
}
