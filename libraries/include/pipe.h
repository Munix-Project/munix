/*
 * pipe.h
 *
 *  Created on: Aug 13, 2015
 *      Author: miguel
 */

#ifndef KERNEL_INCLUDE_PIPE_H_
#define KERNEL_INCLUDE_PIPE_H_

#include <types.h>

typedef struct _pipe_device {
	uint8_t * buffer;
	size_t write_ptr;
	size_t read_ptr;
	size_t size;
	size_t refcount;
	volatile int lock_read[2];
	volatile int lock_write[2];
	list_t * wait_queue_readers;
	list_t * wait_queue_writers;
	int dead;
} pipe_device_t;

fs_node_t * make_pipe(size_t size);
int pipe_size(fs_node_t * node);
int pipe_unsize(fs_node_t * node);

#endif /* KERNEL_INCLUDE_PIPE_H_ */