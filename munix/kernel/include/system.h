/*
 * system.h
 *
 *  Created on: Aug 13, 2015
 *      Author: miguel
 */

#ifndef KERNEL_INCLUDE_SYSTEM_H_
#define KERNEL_INCLUDE_SYSTEM_H_

#include <types.h>

void assert_failed(const char *file, uint32_t line, const char *desc);
#define assert(statement) ((statement) ? (void)0 : assert_failed(__FILE__, __LINE__, #statement))

#endif /* KERNEL_INCLUDE_SYSTEM_H_ */
