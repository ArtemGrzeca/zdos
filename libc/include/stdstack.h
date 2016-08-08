#ifndef _STDSTACK_H
#define _STDSTACK_H 1

#include <stddef.h>

typedef struct int_stack_s
{
	int* ptr;
	size_t length;
	size_t top;
} int_stack;

void int_stack_ctor(int_stack* s, int* p, size_t l);
void int_stack_push(int_stack* s, int v);
int int_stack_pop(int_stack* s);

#endif