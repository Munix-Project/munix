/*
 * This file is part of ToaruOS and is released under the terms
 * of the NCSA / University of Illinois License - see LICENSE.md
 * Copyright (C) 2015 Dale Weiler
 *
 */

#ifndef KERNEL_INCLUDE_BITSET_H_
#define KERNEL_INCLUDE_BITSET_H_

#include <munix/system.h>

typedef struct {
	unsigned char *data;
	size_t size;
} bitset_t;

void bitset_init(bitset_t *set, size_t size);
void bitset_free(bitset_t *set);
void bitset_set(bitset_t *set, size_t bit);
void bitset_clear(bitset_t *set, size_t bit);
int bitset_test(bitset_t *set, size_t bit);
/* Find first unset bit */
int bitset_ffub(bitset_t *set);


#endif /* KERNEL_INCLUDE_BITSET_H_ */
