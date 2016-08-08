#include <stdlib.h>
#include <stdstack.h>

char itoa_alphabet[36] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
int itoa_stack_array[12];

char* itoa(int value, char* str, int base)
{
	if(base < 2 || base > 36) { return 0; }
	int_stack s; int_stack_ctor(&s, itoa_stack_array, 12); int_stack_push(&s, -1);
	for(; value != 0; value /= base) int_stack_push(&s, (int)itoa_alphabet[value % base]);
	int i = 0; if(value < 0) str[i++] = '-'; for(int c = int_stack_pop(&s); c != -1;  c = int_stack_pop(&s)) str[i++] = (char)c; 
	str[i] = '\0'; return str;
}