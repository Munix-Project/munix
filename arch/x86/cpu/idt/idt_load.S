/*
 * This file is part of ToaruOS and is released under the terms
 * of the NCSA / University of Illinois License - see LICENSE.md
 * Copyright (C) 2015 Dale Weiler
 *
 */
.section .text
.align 4

.global idt_load
.type idt_load, @function

idt_load:
    mov 4(%esp), %eax
    lidt (%eax)
    ret



