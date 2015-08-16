/*
 * tss.S
 *
 *  Created on: Aug 13, 2015
 *      Author: miguel
 */
.section .text
.align 4

.global tss_flush
.type tss_flush, @function

tss_flush:
    mov $0x2B, %ax
    ltr %ax
    ret



