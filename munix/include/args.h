/*
 * args.h
 *
 *  Created on: Aug 13, 2015
 *      Author: miguel
 */

#ifndef KERNEL_INCLUDE_ARGS_H_
#define KERNEL_INCLUDE_ARGS_H_

int args_present(char * karg);
char * args_value(char * karg);
void args_parse(char * _arg);

void early_stage_args(void);
void late_stage_args(void);

#endif /* KERNEL_INCLUDE_ARGS_H_ */
