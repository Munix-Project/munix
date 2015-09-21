
#ifndef KERNEL_INCLUDE_SYSTEM_H_
#define KERNEL_INCLUDE_SYSTEM_H_

#include <task/process.h>
#include <task/task.h>
#include <munix/errno.h>
#include <libc/libc.h>
#include <libc/list.h>
#include <libc/types.h>

#define NTH_BIT(nth) (0x1 << nth)
#define IS_BIT_SET(flag, nth) flag & NTH_BIT(nth)

#define STR(x) #x
#define STRSTR(x) STR(x)

#define asm __asm__
#define volatile __volatile__

#define IRQ_OFF int_disable()
#define IRQ_RES int_resume()
#define IRQ_ON  int_enable()
#define KERNEL_PAUSE   { asm volatile ("hlt"); }
#define KERNEL_FULL_STOP while (1) { KERNEL_PAUSE; }

#define SYSCALL_VECTOR 0x7F
#define SIGNAL_RETURN 0xFFFFDEAF
#define THREAD_RETURN 0xFFFFB00F

void int_disable(void);
void int_resume(void);
void int_enable(void);

int debug_shell_start(void);

extern void * code;
extern void * end;

extern char * boot_arg; /* Argument to pass to init */
extern char * boot_arg_extra; /* Extra data to pass to init */

extern size_t lfind(const char * str, const char accept);
extern size_t rfind(const char * str, const char accept);

extern uintptr_t initial_esp;

/* GDT */
extern void gdt_install(void);
extern void gdt_set_gate(uint8_t num, uint64_t base, uint64_t limit, uint8_t access, uint8_t gran);
extern void set_kernel_stack(uintptr_t stack);

/* IDT */
extern void idt_install(void);
extern void idt_set_gate(uint8_t num, void (*base)(void), uint16_t sel, uint8_t flags);

/* ISR */
enum ISR_IVT {
	ISR_DIVBY0,
	ISR_RESERVED0,
	ISR_NMI,
	ISR_BREAK,
	ISR_OVERFLOW,
	ISR_BOUNDS,
	ISR_INVOPCODE,
	ISR_DEVICEUN,
	ISR_DOUBLEFAULT,
	ISR_COPROC,
	ISR_INVTSS,
	ISR_SEG_FAULT,
	ISR_STACKSEG_FAULT,
	ISR_GENERALPROT,
	ISR_PAGEFAULT,
	ISR_RESERVED1,
	ISR_FPU,
	ISR_ALIGNCHECK,
	ISR_SIMD_FPU,
	ISR_RESERVED2,
	ISR_USR
};
typedef void (*irq_handler_t) (struct regs *);
typedef int (*irq_handler_chain_t) (struct regs *);

extern void isr_install(void);
extern void isr_install_handler(size_t isrs, irq_handler_t);
extern void isr_uninstall_handler(size_t isrs);

/* Registers
 *
 * Note: if the order of these changes, sys/task.S must be changed to use
 * the correct offsets as well.
 */
struct regs {
	unsigned int gs, fs, es, ds;
	unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
	unsigned int int_no, err_code;
	unsigned int eip, cs, eflags, useresp, ss;
};

typedef struct regs regs_t;

/* Interrupt Handlers */
extern void irq_install(void);
extern void irq_install_handler(size_t irq, irq_handler_chain_t);
extern void irq_uninstall_handler(size_t irq);
extern int irq_is_handler_free(size_t irq);
extern void irq_gates(void);
extern void irq_ack(size_t);

/* Panic */
#define HALT_AND_CATCH_FIRE(mesg, regs) halt_and_catch_fire(mesg, __FILE__, __LINE__, regs)
#define assert(statement) ((statement) ? (void)0 : assert_failed(__FILE__, __LINE__, #statement))
void halt_and_catch_fire(char *error_message, const char *file, int line, struct regs * regs);
void assert_failed(const char *file, uint32_t line, const char *desc);
#define assert(statement) ((statement) ? (void)0 : assert_failed(__FILE__, __LINE__, #statement))

/* Timer */
struct timeval {
	uint32_t tv_sec;
	uint32_t tv_usec;
};
extern void timer_install(void);
extern unsigned long timer_ticks;
extern unsigned long timer_subticks;
extern signed long timer_drift;
extern void relative_time(unsigned long seconds, unsigned long subseconds, unsigned long * out_seconds, unsigned long * out_subseconds);

/* CMOS */
extern void get_time(uint16_t * hours, uint16_t * minutes, uint16_t * seconds);
extern void get_date(uint16_t * month, uint16_t * day);
extern uint32_t boot_time;
extern uint32_t read_cmos(void);
extern int gettimeofday(struct timeval * t, void * z);
extern uint32_t now(void);

/* Floating Point Unit */
extern void switch_fpu(void);
extern void fpu_install(void);

/* Memory Management */
extern uintptr_t placement_pointer;
extern void kmalloc_startat(uintptr_t address);
extern uintptr_t kmalloc_real(size_t size, int align, uintptr_t * phys);
extern uintptr_t kmalloc(size_t size);
extern uintptr_t kvmalloc(size_t size);
extern uintptr_t kmalloc_p(size_t size, uintptr_t * phys);
extern uintptr_t kvmalloc_p(size_t size, uintptr_t * phys);
extern void *sbrk(uintptr_t increment);
/* klmalloc */
void * __attribute__ ((malloc)) malloc(size_t size);
void * __attribute__ ((malloc)) realloc(void *ptr, size_t size);
void * __attribute__ ((malloc)) calloc(size_t nmemb, size_t size);
void * __attribute__ ((malloc)) valloc(size_t size);
void free(void *ptr);

// Page types moved to task.h
extern page_directory_t *kernel_directory;
extern page_directory_t *current_directory;

extern void paging_install(uint32_t memsize);
extern void paging_parse();
extern void paging_prestart(void);
extern void paging_finalize(void);
extern void paging_mark_system(uint64_t addr);
extern void switch_page_directory(page_directory_t * new);
extern void invalidate_page_tables(void);
extern void invalidate_tables_at(uintptr_t addr);
extern page_t *get_page(uintptr_t address, int make, page_directory_t * dir);
extern void page_fault(struct regs *r);
extern void dma_frame(page_t * page, int, int, uintptr_t);
extern void debug_print_directory(page_directory_t *);

void heap_install(void);

void alloc_frame(page_t *page, int is_kernel, int is_writeable);
void free_frame(page_t *page);
uintptr_t memory_use(void);
uintptr_t memory_total(void);

/* spin.c */
typedef volatile int spin_lock_t[2];
extern void spin_init(spin_lock_t lock);
extern void spin_lock(spin_lock_t lock);
extern void spin_unlock(spin_lock_t lock);

extern void return_to_userspace(void);

/* Kernel Main */
extern unsigned short *memsetw(unsigned short *dest, unsigned short val, int count);
extern uint32_t krand(void);
extern uint8_t startswith(const char * str, const char * accept);

extern unsigned char inportb(unsigned short _port);
extern void outportb(unsigned short _port, unsigned char _data);
extern unsigned short inports(unsigned short _port);
extern void outports(unsigned short _port, unsigned short _data);
extern unsigned int inportl(unsigned short _port);
extern void outportl(unsigned short _port, unsigned int _data);
extern void outportsm(unsigned short port, unsigned char * data, unsigned long size);
extern void inportsm(unsigned short port, unsigned char * data, unsigned long size);

/* wakeup queue */
extern int wakeup_queue(list_t * queue);
extern int wakeup_queue_interrupted(list_t * queue);
extern int sleep_on(list_t * queue);

/* Signal */
typedef struct {
	uint32_t  signum;
	uintptr_t handler;
	regs_t registers_before;
} signal_t;
extern void handle_signal(process_t *, signal_t *);
extern int send_signal(pid_t process, uint32_t signal);

#define USER_STACK_BOTTOM 0xAFF00000
#define USER_STACK_TOP    0xB0000000
#define SHM_START         0xB0000000

/* Tasking */
#define PUSH(stack, type, item) stack -= sizeof(type); \
							*((type *) stack) = item
extern uintptr_t read_eip(void);
extern void copy_page_physical(uint32_t, uint32_t);
extern page_directory_t * clone_directory(page_directory_t * src);
extern page_table_t * clone_table(page_table_t * src, uintptr_t * physAddr);
extern void move_stack(void *new_stack_start, size_t size);
extern void kexit(int retval);
extern void task_exit(int retval);
extern uint32_t next_pid;

extern void tasking_install(void);
extern void switch_task(uint8_t reschedule);
extern void switch_next(void);
extern uint32_t fork(void);
extern uint32_t clone(uintptr_t new_stack, uintptr_t thread_func, uintptr_t arg);
extern uint32_t getpid(void);
extern void enter_user_jmp(uintptr_t location, int argc, char ** argv, uintptr_t stack);

/* System Calls */
extern void syscalls_install(void);

extern void validate(void * ptr);
extern int validate_safe(void * ptr);

extern fs_node_t * initrd_mount(uintptr_t, size_t);

extern int system(char * path, int argc, char ** argv);

#endif /* KERNEL_INCLUDE_SYSTEM_H_ */
