#ifndef _KERNEL_SYSTEM_H
#define _KERNEL_SYSTEM_H

#define PANIC(msg) sys_panic(__FILE__, __LINE__, msg);
#define ASSERT(b) ((b) ? (void)0 : sys_panic_assert(__FILE__, __LINE__, #b))

void sys_panic(const char *file, unsigned int line, const char *desc);
void sys_panic_assert(const char *file, unsigned int line, const char *desc);
void bootlog(char* str);

#endif
