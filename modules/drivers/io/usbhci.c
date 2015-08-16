/*
 * usbhci.c
 *
 *  Created on: Aug 13, 2015
 *      Author: miguel
 */

#include <module.h>
#include <pci.h>
#include <printf.h>
#include <logging.h>
#include <mod/shell.h>

static uint32_t hub_device = 0;

static void find_usb_device(uint32_t device, uint16_t vendorid, uint16_t deviceid, void * extra) {
	if (pci_find_type(device) == 0xc03) {
		int prog_if = (int)pci_read_field(device, PCI_PROG_IF, 1);
		if (prog_if == 0) {
			*((uint32_t *)extra)= device;
		}
	}
}

DEFINE_SHELL_FUNCTION(usb, "Enumerate USB devices (UHCI)") {

	pci_scan(&find_usb_device, -1, &hub_device);

	if (!hub_device) {
		fprintf(tty, "Failed to locate a UHCI controller.\n");
		return 1;
	}

	fprintf(tty, "Located UHCI controller: %2x:%2x.%d\n",
			(int)pci_extract_bus (hub_device),
			(int)pci_extract_slot(hub_device),
			(int)pci_extract_func(hub_device));

	return 0;
}

static int install(void) {
	BIND_SHELL_FUNCTION(usb);
	return 0;
}

static int uninstall(void) {
	return 0;
}

MODULE_DEF(usbuhci, install, uninstall);
MODULE_DEPENDS(debugshell);


