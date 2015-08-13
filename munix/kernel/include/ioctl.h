/*
 * ioctl.h
 *
 *  Created on: Aug 13, 2015
 *      Author: miguel
 */

#ifndef KERNEL_INCLUDE_IOCTL_H_
#define KERNEL_INCLUDE_IOCTL_H_

//xxx #include <termios.h>

#define IOCTLDTYPE 0x4F00

#define IOCTL_DTYPE_UNKNOWN -1
#define IOCTL_DTYPE_FILE     1
#define IOCTL_DTYPE_TTY      2

#define IOCTL_PACKETFS_QUEUED 0x5050

#endif /* KERNEL_INCLUDE_IOCTL_H_ */
