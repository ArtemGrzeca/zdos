#ifndef _KERNEL_DRIVER_KB_H
#define _KERNEL_DRIVER_KB_H

#include <kernel/arch/arch.h>

extern char kbdus[128];
extern size_t keyboard_buffer_size;
extern char keyboard_buffer[256];

void keyboard_handler(regs_t* r);
void keyboard_install();

#endif