/*
 * This file is part of ToaruOS and is released under the terms
 * of the NCSA / University of Illinois License - see LICENSE.md
 * Copyright (C) 2015 Dale Weiler
 *
 */

#ifndef KERNEL_INCLUDE_ARGS_H_
#define KERNEL_INCLUDE_ARGS_H_

int args_present(char * karg);
char * args_value(char * karg);
void args_parse(char * _arg);

void early_stage_args(void);
void late_stage_args(void);

#endif /* KERNEL_INCLUDE_ARGS_H_ */
