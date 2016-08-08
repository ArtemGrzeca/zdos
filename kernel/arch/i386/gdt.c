#include <kernel/arch/gdt.h>

struct gdt_entry gdt[5];
struct gdt_ptr gp;

void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran)
{
    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;

    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].granularity = ((limit >> 16) & 0x0F);

    gdt[num].granularity |= (gran & 0xF0);
    gdt[num].access = access;
}

void gdt_install()
{
    gp.limit = (sizeof(struct gdt_entry) * 3) - 1;
    gp.base = (int)&gdt;

    gdt_set_gate(0, 0, 0x00000000, 0x00, 0x00); //Null segment
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);	//Kernel code segment
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);	//Kernel data segment
	gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); //User code segment
	gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); //User data segment

	asm("lgdtl (gp)"); //Setting gdt
    asm("movw $0x10, %ax\n \
        movw %ax, %ds\n \
        movw %ax, %es\n \
        movw %ax, %fs\n \
        movw %ax, %gs\n \
        ljmp $0x08, $next\n \
        next:\n");
}
