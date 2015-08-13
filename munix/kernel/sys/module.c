/*
 * module.c
 *
 *  Created on: Aug 13, 2015
 *      Author: miguel
 */
#include <system.h>
#include <libc.h>
#include <module.h>

#define SYMBOLTABLE_HASHMAP_SIZE 10
#define MODULE_HASHMAP_SIZE 10

//xxx static hashmap_t * symboltable = NULL;
//xxx static hashmap_t * modules = NULL;

extern char kernel_symbols_start[];
extern char kernel_symbols_end[];

typedef struct {
	uintptr_t addr;
	char name[];
} kernel_symbol_t;

/* Cannot use symboltable here because symbol_find is used during initialization
 * of IRQs and ISRs.
 */
void (* symbol_find(const char * name))(void) {
	kernel_symbol_t * k = (kernel_symbol_t *)&kernel_symbols_start;

	while ((uintptr_t)k < (uintptr_t)&kernel_symbols_end) {
		if (strcmp(k->name, name)) {
			k = (kernel_symbol_t *)((uintptr_t)k + sizeof *k + strlen(k->name) + 1);
			continue;
		}
		return (void (*)(void))k->addr;
	}

	return NULL;
}
