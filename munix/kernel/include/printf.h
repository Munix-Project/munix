/*
 * printf.h
 *
 *  Created on: Aug 13, 2015
 *      Author: miguel
 */

#ifndef KERNEL_INCLUDE_PRINTF_H_
#define KERNEL_INCLUDE_PRINTF_H_

#include <va_list.h>
#include <fs.h>

extern size_t vasprintf(char * buf, const char *fmt, va_list args);
extern int    sprintf(char *buf, const char *fmt, ...);
extern int    fprintf(fs_node_t * device, char *fmt, ...);
extern void putc(unsigned char c, int x, int y, int attr);

#endif /* KERNEL_INCLUDE_PRINTF_H_ */
