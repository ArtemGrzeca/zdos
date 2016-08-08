#include <string.h>

#include <kernel/driver/kb.h>
#include <kernel/system/system.h>
#include <kernel/arch/irq.h>

char kbdus[128] =
{
    0,  
	27, //ESC
	'1', 
	'2', 
	'3', 
	'4', 
	'5', 
	'6', 
	'7', 
	'8',
	'9', 
	'0', 
	'-', 
	'=', 
	'\b', //Backspace
    '\t', //Tab
    'q', 
	'w', 
	'e', 
	'r',
    't', 
	'y', 
	'u', 
	'i', 
	'o', 
	'p', 
	'[', 
	']', 
	'\r', //Enter
	0, //Control
    'a', 
	's', 
	'd', 
	'f', 
	'g', 
	'h', 
	'j', 
	'k', 
	'l', 
	';',
	'\'',
	'`',
	0, //Left shift
	'\\',
	'z', 
	'x', 
	'c', 
	'v', 
	'b', 
	'n',
	'm', 
	',', 
	'.', 
	'/',  
	0, //Right shift
	'*',
    0, //Alt
	' ', //Spacebar
    0,	//Caps lock
    0, //F1
    0, //F2
	0, //F3  
	0, //F4  
	0, //F5  
	0, //F6  
	0, //F7 
	0, //F8 
	0, //F9
    0, //F10
    0, //Num lock
    0, //Scroll lock
    0, //Home key
    0, //Up arrow
    0, //Page up
	'-',
    0, //Left arrow
    0,
    0, //Right arrow
	'+',
    0, //End key
    0, //Down arrow
    0, //Page down
    0, //Insert key
    0, //Delete key
    0,   
	0,   
	0,
    0, //F11
    0, //F12
    0, //All other keys
};	

size_t keyboard_buffer_size;
char keyboard_buffer[256];

void keyboard_handler(regs_t* r)
{
	unsigned char scancode;
    scancode = inportb(0x60);
    if (scancode & 0x80)
    {
        //to do
    }
    else
    {
		if(keyboard_buffer_size == 256) { for(size_t i = 0; i < 254; i++) keyboard_buffer[i] = keyboard_buffer[i+1]; keyboard_buffer_size--; }
		keyboard_buffer[++keyboard_buffer_size] = kbdus[scancode];
    }
}

void keyboard_install()
{
	keyboard_buffer_size = 0;
	memset(&keyboard_buffer, 0, sizeof(char) * 256);
	irq_install_handler(1, keyboard_handler);
}