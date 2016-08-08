#ifndef _KERNEL_ARCH_ARCH_H
#define _KERNEL_ARCH_ARCH_H

#ifdef _i386
typedef struct regs_s
{
    unsigned int gs, fs, es, ds;
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
    unsigned int int_no, err_code;
    unsigned int eip, cs, eflags, useresp, ss;
} regs_t;
#endif // _i386

unsigned char inportb (unsigned short _port);
void outportb (unsigned short _port, unsigned char _data);
void sti(void);
void cli(void);

#endif
