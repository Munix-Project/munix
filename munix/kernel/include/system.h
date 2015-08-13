/*
 * system.h
 *
 *  Created on: Aug 13, 2015
 *      Author: miguel
 */

#ifndef KERNEL_INCLUDE_SYSTEM_H_
#define KERNEL_INCLUDE_SYSTEM_H_

#include <types.h>

#define STDOUT_TERM // Output directly to video memory at 0xb8000 or not (undefine it if you don't want any output)

#define STR(x) #x
#define STRSTR(x) STR(x)

#define asm __asm__
#define volatile __volatile__

#define IRQ_OFF int_disable()
#define IRQ_RES int_resume()
#define IRQ_ON  int_enable()
#define PAUSE   { asm volatile ("hlt"); }
#define STOP while (1) { PAUSE; }

#define SYSCALL_VECTOR 0x7F
#define SIGNAL_RETURN 0xFFFFDEAF
#define THREAD_RETURN 0xFFFFB00F

void int_disable(void);
void int_resume(void);
void int_enable(void);

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
extern void isr_install(void);
//XXX extern void isr_install_handler(size_t isrs, irq_handler_t);
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
typedef void (*irq_handler_t) (struct regs *);
typedef int (*irq_handler_chain_t) (struct regs *);

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
extern void timer_install(void);
extern unsigned long timer_ticks;
extern unsigned long timer_subticks;
extern signed long timer_drift;
extern void relative_time(unsigned long seconds, unsigned long subseconds, unsigned long * out_seconds, unsigned long * out_subseconds);

/* Kernel Main */
extern unsigned short *memsetw(unsigned short *dest, unsigned short val, int count);

extern unsigned char inportb(unsigned short _port);
extern void outportb(unsigned short _port, unsigned char _data);
extern unsigned short inports(unsigned short _port);
extern void outports(unsigned short _port, unsigned short _data);
extern unsigned int inportl(unsigned short _port);
extern void outportl(unsigned short _port, unsigned int _data);
extern void outportsm(unsigned short port, unsigned char * data, unsigned long size);
extern void inportsm(unsigned short port, unsigned char * data, unsigned long size);

#endif /* KERNEL_INCLUDE_SYSTEM_H_ */
