/*
 * This file is part of ToaruOS and is released under the terms
 * of the NCSA / University of Illinois License - see LICENSE.md
 * Copyright (C) 2015 Dale Weiler
 *
 */

#ifndef KERNEL_INCLUDE_IOCTL_H_
#define KERNEL_INCLUDE_IOCTL_H_

#include <mod/shell/termios.h>

#define IOCTLDTYPE 0x4F00

#define IOCTL_DTYPE_UNKNOWN -1
#define IOCTL_DTYPE_FILE     1
#define IOCTL_DTYPE_TTY      2

#define IOCTL_PACKETFS_QUEUED 0x5050

#endif /* KERNEL_INCLUDE_IOCTL_H_ */
