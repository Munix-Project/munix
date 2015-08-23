/*
 * This file is part of ToaruOS and is released under the terms
 * of the NCSA / University of Illinois License - see LICENSE.md
 * Copyright (C) 2015 Dale Weiler
 *
 */

.section .text
.align 4

.global tss_flush
.type tss_flush, @function

tss_flush:
    mov $0x2B, %ax
    ltr %ax
    ret



