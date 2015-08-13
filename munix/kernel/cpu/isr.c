/*
 * isr.c
 *
 *  Created on: Aug 13, 2015
 *      Author: miguel
 */
#include <system.h>
#include <logging.h>
//xxx #include <module.h>
#include <printf.h>

/* The count is treated as is when setting up IDT gates. However there is an
 * additional ISR for the system call vector which is handled explicitly since
 * it's mapped at a different address.
 */
#define ISR_COUNT 32

// Declared in isr.S:
void _isr0();
void _isr1();
void _isr2();
void _isr3();
void _isr4();
void _isr5();
void _isr6();
void _isr7();
void _isr8();
void _isr9();
void _isr10();
void _isr11();
void _isr12();
void _isr13();
void _isr14();
void _isr15();
void _isr16();
void _isr17();
void _isr18();
void _isr19();
void _isr20();
void _isr21();
void _isr22();
void _isr23();
void _isr24();
void _isr25();
void _isr26();
void _isr27();
void _isr28();
void _isr29();
void _isr30();
void _isr31();

static struct {
	size_t index;
	void (*stub)(void);
} isrs[32 + 1] __attribute__((used));

static irq_handler_t isr_routines[256] = { 0 };

void isr_install_handler(size_t isrs, irq_handler_t handler) {
	isr_routines[isrs] = handler;
}

void isr_uninstall_handler(size_t isrs) {
	isr_routines[isrs] = 0;
}

void isr_install(void) {
	/*xxx char buffer[16];
	for (int i = 0; i < ISR_COUNT; i++) {
		sprintf(buffer, "_isr%d", i);
		isrs[i].index = i;
		isrs[i].stub = symbol_find(buffer);
	}
	isrs[ISR_COUNT].index = SYSCALL_VECTOR;
	isrs[ISR_COUNT].stub = symbol_find("_isr127");

	for (int i = 0; i < ISR_COUNT + 1; i++) {
		idt_set_gate(isrs[i].index, isrs[i].stub, 0x08, 0x8E);
	}*/

	idt_set_gate(0, _isr0, 0x08, 0x8E);
	idt_set_gate(1, _isr1, 0x08, 0x8E);
	idt_set_gate(2, _isr2, 0x08, 0x8E);
	idt_set_gate(3, _isr3, 0x08, 0x8E);
	idt_set_gate(4, _isr4, 0x08, 0x8E);
	idt_set_gate(5, _isr5, 0x08, 0x8E);
	idt_set_gate(6, _isr6, 0x08, 0x8E);
	idt_set_gate(7, _isr7, 0x08, 0x8E);
	idt_set_gate(8, _isr8, 0x08, 0x8E);
	idt_set_gate(9, _isr9, 0x08, 0x8E);
	idt_set_gate(10, _isr10, 0x08, 0x8E);
	idt_set_gate(11, _isr11, 0x08, 0x8E);
	idt_set_gate(12, _isr12, 0x08, 0x8E);
	idt_set_gate(13, _isr13, 0x08, 0x8E);
	idt_set_gate(14, _isr14, 0x08, 0x8E);
	idt_set_gate(15, _isr15, 0x08, 0x8E);
	idt_set_gate(16, _isr16, 0x08, 0x8E);
	idt_set_gate(17, _isr17, 0x08, 0x8E);
	idt_set_gate(18, _isr18, 0x08, 0x8E);
	idt_set_gate(19, _isr19, 0x08, 0x8E);
	idt_set_gate(20, _isr20, 0x08, 0x8E);
	idt_set_gate(21, _isr21, 0x08, 0x8E);
	idt_set_gate(22, _isr22, 0x08, 0x8E);
	idt_set_gate(23, _isr23, 0x08, 0x8E);
	idt_set_gate(24, _isr24, 0x08, 0x8E);
	idt_set_gate(25, _isr25, 0x08, 0x8E);
	idt_set_gate(26, _isr26, 0x08, 0x8E);
	idt_set_gate(27, _isr27, 0x08, 0x8E);
	idt_set_gate(28, _isr28, 0x08, 0x8E);
	idt_set_gate(29, _isr29, 0x08, 0x8E);
	idt_set_gate(30, _isr30, 0x08, 0x8E);
	idt_set_gate(31, _isr31, 0x08, 0x8E);
}

static const char *exception_messages[32] = {
	"Division by zero",
	"Debug",
	"Non-maskable interrupt",
	"Breakpoint",
	"Detected overflow",
	"Out-of-bounds",
	"Invalid opcode",
	"No coprocessor",
	"Double fault",
	"Coprocessor segment overrun",
	"Bad TSS",
	"Segment not present",
	"Stack fault",
	"General protection fault",
	"Page fault",
	"Unknown interrupt",
	"Coprocessor fault",
	"Alignment check",
	"Machine check",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved"
};

void fault_handler(struct regs * r) {
	irq_handler_t handler = isr_routines[r->int_no];
	if (handler) {
		handler(r);
	} else {
		log_clrscr();
		log_reset();
		debug_print(CRITICAL, "Unhandled exception: [%d] %s", r->int_no, exception_messages[r->int_no]);

		HALT_AND_CATCH_FIRE("Process caused an unhandled exception", r);
		STOP;
	}
}



