/*
 * initrd.c
 *
 *  Created on: Aug 13, 2015
 *      Author: miguel
 */

#include <system.h>
#include <logging.h>
#include <module.h>
#include <fs.h>
#include <printf.h>

static uint32_t read_initrd(fs_node_t *node, uint32_t offset, uint32_t size, uint8_t *buffer);
static uint32_t write_initrd(fs_node_t *node, uint32_t offset, uint32_t size, uint8_t *buffer);
static void     open_initrd(fs_node_t *node, unsigned int flags);
static void     close_initrd(fs_node_t *node);

static uint32_t read_initrd(fs_node_t *node, uint32_t offset, uint32_t size, uint8_t *buffer) {

	if (offset > node->length) {
		return 0;
	}

	if (offset + size > node->length) {
		unsigned int i = node->length - offset;
		size = i;
	}

	memcpy(buffer, (void *)(node->inode + offset), size);

	return size;
}

static uint32_t write_initrd(fs_node_t *node, uint32_t offset, uint32_t size, uint8_t *buffer) {
	if (offset > node->length) {
		return 0;
	}

	if (offset + size > node->length) {
		unsigned int i = node->length - offset;
		size = i;
	}

	memcpy((void *)(node->inode + offset), buffer, size);
	return size;
}

static void open_initrd(fs_node_t * node, unsigned int flags) {
	return;
}

static void close_initrd(fs_node_t * node) {
	return;
}

static fs_node_t * initrd_device_create(int device_number, uintptr_t location, size_t size) {
	fs_node_t * fnode = malloc(sizeof(fs_node_t));
	memset(fnode, 0x00, sizeof(fs_node_t));
	fnode->inode = location;
	sprintf(fnode->name, "ram%d", device_number);
	fnode->uid = 0;
	fnode->gid = 0;
	fnode->length  = size;
	fnode->flags   = FS_BLOCKDEVICE;
	fnode->read    = read_initrd;
	fnode->write   = write_initrd;
	fnode->open    = open_initrd;
	fnode->close   = close_initrd;
	return fnode;
}

static int last_device_number = 0;
fs_node_t * initrd_mount(uintptr_t location, size_t size) {
	fs_node_t * initrd = initrd_device_create(last_device_number, location, size);
	if (initrd) {
		char tmp[64];
		sprintf(tmp, "/dev/%s", initrd->name);
		vfs_mount(tmp, initrd);
		last_device_number += 1;
		return initrd;
	}

	return NULL;
}


