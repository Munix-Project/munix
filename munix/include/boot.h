/*
 * boot.h
 *
 *  Created on: Aug 13, 2015
 *      Author: miguel
 */

#ifndef KERNEL_INCLUDE_BOOT_H_
#define KERNEL_INCLUDE_BOOT_H_

/*
 * Boot Information Types
 * Used in the kernel boot process to determine
 * how we booted and where we can get BIOS
 * information from that bootloader.
 *
 */
#include <system.h>

/*
 * Multiboot
 * A format managed by GNU and used in GRUB.
 * Also supported natively by QEMU and a few
 * other emulators.
 */
#include <multiboot.h>

#endif /* KERNEL_INCLUDE_BOOT_H_ */
