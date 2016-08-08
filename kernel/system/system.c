#include <xprintf.h>

#include <kernel/driver/timer.h>
#include <kernel/system/system.h>

void sys_panic(const char *file, unsigned int line, const char *desc)
{
    char buffer[256];
	bootlog("KERNEL PANIC.");
	xsprintf(buffer, "In file %s at file %d.", file, line); bootlog(buffer);
	xsprintf(buffer, "Description: %s", desc); bootlog(buffer);
	for(;;);
}

void sys_panic_assert(const char *file, unsigned int line, const char *desc)
{
    char buffer[256];
	bootlog("KERNEL PANIC. ASSERTION-FAILED.");
	xsprintf(buffer, "In file %s at file %d.", file, line); bootlog(buffer);
	xsprintf(buffer, "Description: %s", desc); bootlog(buffer);
	for(;;);
}

void bootlog(char* str)
{
	int s = timer_ticks / 1000; int t = timer_ticks % 100;
	xprintf("[%8d.%03d] %s\n", s, t, str);
}