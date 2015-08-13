/*
 * bitset.h
 *
 *  Created on: Aug 13, 2015
 *      Author: miguel
 */

#ifndef KERNEL_INCLUDE_BITSET_H_
#define KERNEL_INCLUDE_BITSET_H_

#include <system.h>

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
