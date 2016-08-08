#include <stdstack.h>
#include <stddef.h>

void int_stack_ctor(int_stack* s, int* p, size_t l)
{
    s->ptr = p;
    s->length = l;
    s->top = 0;
}

void int_stack_push(int_stack* s, int v)
{
	if(s->top == s->length) return;
	s->ptr[s->top++] = v;
}

int int_stack_pop(int_stack* s)
{
	if(s->top == 0) return 0;
	return s->ptr[--s->top];
}