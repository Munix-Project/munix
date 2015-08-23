/*
 * This file is part of ToaruOS and is released under the terms
 * of the NCSA / University of Illinois License - see LICENSE.md
 * Copyright (C) 2015 Dale Weiler
 *
 */

#ifndef KERNEL_INCLUDE_PRINTF_H_
#define KERNEL_INCLUDE_PRINTF_H_

#include <fs/fs.h>
#include <libc/va_list.h>

extern size_t vasprintf(char * buf, const char *fmt, va_list args);
extern int    sprintf(char *buf, const char *fmt, ...);
extern int    fprintf(fs_node_t * device, char *fmt, ...);
extern void putc(unsigned char c, int x, int y, int attr);

#endif /* KERNEL_INCLUDE_PRINTF_H_ */
