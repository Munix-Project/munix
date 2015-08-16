/*
 * signal.h
 *
 *  Created on: Aug 13, 2015
 *      Author: miguel
 */

#ifndef KERNEL_INCLUDE_SIGNAL_H_
#define KERNEL_INCLUDE_SIGNAL_H_

#include "libc/types.h"
void return_from_signal_handler(void);
void fix_signal_stacks(void);

#include "task/signal_defs.h"

#endif /* KERNEL_INCLUDE_SIGNAL_H_ */
