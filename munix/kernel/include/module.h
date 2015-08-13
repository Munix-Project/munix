/*
 * module.h
 *
 *  Created on: Aug 13, 2015
 *      Author: miguel
 */

#ifndef KERNEL_INCLUDE_MODULE_H_
#define KERNEL_INCLUDE_MODULE_H_


typedef struct {
    char * name;
    int (* initialize)(void);
    int (* finalize)(void);
} module_defs;

typedef struct {
    module_defs * mod_info;
    void * bin_data;
    // xxx hashmap_t * symbols;
    uintptr_t end;
    size_t deps_length;
    char * deps;
} module_data_t;

void (* symbol_find(const char * name))(void);

extern int module_quickcheck(void * blob);
extern void * module_load_direct(void * blob, size_t size);
extern void * module_load(char * filename);
extern void module_unload(char * name);
extern void modules_install(void);

#define MODULE_DEF(n,init,fini) \
        module_defs module_info_ ## n = { \
            .name       = #n, \
            .initialize = &init, \
            .finalize   = &fini \
        }

//xxx extern hashmap_t * modules_get_list(void);
//xxx extern hashmap_t * modules_get_symbols(void);

#define MODULE_DEPENDS(n) \
    static char _mod_dependency_ ## n [] __attribute__((section("moddeps"), used)) = #n

#endif /* KERNEL_INCLUDE_MODULE_H_ */
