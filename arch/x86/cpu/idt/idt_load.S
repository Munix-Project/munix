/*
 * idt.S
 *
 *  Created on: Aug 13, 2015
 *      Author: miguel
 */
.section .text
.align 4

.global idt_load
.type idt_load, @function

idt_load:
    mov 4(%esp), %eax
    lidt (%eax)
    ret



