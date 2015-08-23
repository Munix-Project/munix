/*
 * This file is part of ToaruOS and is released under the terms
 * of the NCSA / University of Illinois License - see LICENSE.md
 * Copyright (C) 2015 Dale Weiler
 *
 */

#ifndef KERNEL_INCLUDE_SIGNAL_H_
#define KERNEL_INCLUDE_SIGNAL_H_

#include "libc/types.h"
void return_from_signal_handler(void);
void fix_signal_stacks(void);

#include "task/signal_defs.h"

#endif /* KERNEL_INCLUDE_SIGNAL_H_ */
