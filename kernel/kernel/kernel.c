#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <xprintf.h>

#include <kernel/arch/gdt.h>
#include <kernel/arch/idt.h>
#include <kernel/arch/isr.h>
#include <kernel/arch/irq.h>
#include <kernel/arch/cpuid.h>
#include <kernel/arch/paging.h>
#include <kernel/arch/kheap.h>
#include <kernel/arch/multiboot.h>
#include <kernel/driver/timer.h>
#include <kernel/driver/vga.h>
#include <kernel/system/system.h>

extern unsigned int kernel_end;
extern unsigned int kernel_base;

char buffer[128];
char buffer_CPU_name[128] = "CPU: ";

void kernel_early(unsigned int bootmagic, multiboot_header_t* header)
{
	gdt_install();
	idt_install();
	isr_install();
	irq_install();
	
	//Basic hardware. If something fails here, System fails at all. Later it will be mounted in devfs
	terminal_initialize();
	timer_install();
	keyboard_install();
	
	//Basic informations
	sti();
	bootlog("Inializing zDOS..");
	xsprintf(buffer, "zDos: kernel_base: 0x%08x kernel_end: 0x%08x", &kernel_base, &kernel_end); bootlog(buffer);
	if(bootmagic != 0x2BADB002) PANIC("zDos was loaded with not supported loader.");
	bootlog("Basic subsystem loaded initialized");
	
	//System info
	unsigned int ram_size = ((unsigned int)header->mem_upper + 2048)*1024;
	if(ram_size < 0x1000000) PANIC("zDos need at least 16MB of memory");
	xsprintf(buffer, "RAM: %d MB", ram_size / 0x100000); bootlog(buffer);
	cpuid_brand(buffer, sizeof(buffer)); strcat(buffer_CPU_name, buffer); bootlog(buffer_CPU_name);
	
	//Paging initialize
	initialise_paging(ram_size);
	bootlog("Paging initialized");
}

void kernel_main(void)
{
	for(;;);
}
