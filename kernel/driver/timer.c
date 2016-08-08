#include <kernel/driver/timer.h>
#include <kernel/system/system.h>
#include <kernel/arch/irq.h>

unsigned int timer_ticks = 0;

void timer_handler(regs_t* r)
{
	timer_ticks++;
}

void timer_wait(int ticks)
{
    unsigned long eticks;

    eticks = timer_ticks + ticks;
    while(timer_ticks < eticks);
}

void timer_install()
{
    //Set timer to 1000Hz
	int divisor = 1193180 / 1000;
    outportb(0x43, 0x36);
    outportb(0x40, divisor & 0xFF);
    outportb(0x40, divisor >> 8);
	
	//Installs 'timer_handler' to IRQ0
    irq_install_handler(0, timer_handler);
}