/*
 * ringbuffer.h
 *
 *  Created on: Aug 13, 2015
 *      Author: miguel
 */

#ifndef KERNEL_INCLUDE_RINGBUFFER_H_
#define KERNEL_INCLUDE_RINGBUFFER_H_


typedef struct {
	unsigned char * buffer;
	size_t write_ptr;
	size_t read_ptr;
	size_t size;
	volatile int lock[2];
	list_t * wait_queue_readers;
	list_t * wait_queue_writers;
	int internal_stop;
} ring_buffer_t;

size_t ring_buffer_unread(ring_buffer_t * ring_buffer);
size_t ring_buffer_size(fs_node_t * node);
size_t ring_buffer_available(ring_buffer_t * ring_buffer);
size_t ring_buffer_read(ring_buffer_t * ring_buffer, size_t size, uint8_t * buffer);
size_t ring_buffer_write(ring_buffer_t * ring_buffer, size_t size, uint8_t * buffer);

ring_buffer_t * ring_buffer_create(size_t size);
void ring_buffer_destroy(ring_buffer_t * ring_buffer);
void ring_buffer_interrupt(ring_buffer_t * ring_buffer);


#endif /* KERNEL_INCLUDE_RINGBUFFER_H_ */