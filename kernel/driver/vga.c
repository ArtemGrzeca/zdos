#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <xprintf.h>

#include <kernel/driver/vga.h>
#include <kernel/arch/arch.h>

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

void terminal_initialize(void)
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = make_color(COLOR_LIGHT_GREY, COLOR_BLACK);
	terminal_buffer = VGA_MEMORY;
	xfunc_out = terminal_putuchar;
	for ( size_t y = 0; y < VGA_HEIGHT; y++ )
	{
		for ( size_t x = 0; x < VGA_WIDTH; x++ )
		{
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = make_vgaentry(' ', terminal_color);
		}
	}
}

void terminal_setcolor(uint8_t color)
{
	terminal_color = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = make_vgaentry(c, color);
}

void terminal_putchar(char c)
{
	switch(c)
	{
		case '\n':
			terminal_row++; terminal_column = 0;
		break;
		
		default:
			terminal_putentryat(c, terminal_color, terminal_column++, terminal_row);
		break;
	}
	
	if (terminal_column == VGA_WIDTH ) 
	{
		terminal_column = 0;
		terminal_row++;
	}
	if (terminal_row == VGA_HEIGHT )
	{
		for (size_t y = 0; y < VGA_HEIGHT - 1; y++)
		{
			for (size_t x = 0; x < VGA_WIDTH; x++)
			{
				const size_t index = y * VGA_WIDTH + x;
				terminal_buffer[index] = terminal_buffer[index + VGA_WIDTH];
			}
		}
	}
	terminal_update_cursor();
}

void terminal_putuchar(unsigned char c)
{
	terminal_putchar((char)c);
}

void terminal_write(const char* data, size_t size)
{
	for ( size_t i = 0; i < size; i++ )
		terminal_putchar(data[i]);
}

void terminal_writestring(const char* data)
{
	terminal_write(data, strlen(data));
}

void terminal_update_cursor(void)
{
	unsigned short position = ((unsigned short)terminal_row * VGA_WIDTH) + (unsigned short)terminal_column;
	outportb(0x3D4, 0x0F);
	outportb(0x3D5, (unsigned char)(position & 0xFF));
    outportb(0x3D4, 0x0E);
    outportb(0x3D5, (unsigned char)((position >> 8) & 0xFF));
}

void terminal_set_cursor(int row, int col)
{
	if(col < 0 && (unsigned int)col >= VGA_WIDTH) return;
	if(row < 0 && (unsigned int)row >= VGA_HEIGHT) return;
	terminal_column = (size_t)col;
	terminal_row = (size_t)row;
	terminal_update_cursor();
}
