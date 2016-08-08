#ifndef _KERNEL_DRIVER_TIMER_H
#define _KERNEL_DRIVER_TIMER_H

#include <kernel/arch/arch.h>

extern unsigned int timer_ticks;

void timer_handler(regs_t* r);
void timer_wait(int ticks);
void timer_install();

#endif
