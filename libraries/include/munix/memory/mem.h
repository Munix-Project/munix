
#ifndef KERNEL_INCLUDE_MEM_H_
#define KERNEL_INCLUDE_MEM_H_

#include <libc/types.h>

extern uintptr_t heap_end;

extern void set_frame(uintptr_t frame_addr);
extern void clear_frame(uintptr_t frame_addr);
extern uint32_t test_frame(uintptr_t frame_addr);
extern uint32_t first_frame(void);

extern uintptr_t map_to_physical(uintptr_t virtual);

#endif /* KERNEL_INCLUDE_MEM_H_ */
