#ifndef _KERNEL_ARCH_MULTIBOOT_H
#define _KERNEL_ARCH_MULTIBOOT_H

#define MULTIBOOT_FLAG_MEM		(1<<0)
#define MULTIBOOT_FLAG_BOOT		(1<<1)
#define MULTIBOOT_FLAG_CMD		(1<<2)
#define MULTIBOOT_FLAG_MOD		(1<<3)
#define MULTIBOOT_FLAG_AOUT		(1<<4)
// (1<<5) isn't used in Eppix, because Eppix uses the aout kludge
#define MULTIBOOT_FLAG_MMAP		(1<<6)

// The symbol table for the a.out format
typedef struct multiboot_aout_s
{
	unsigned long tabsize;
	unsigned long strsize;
	unsigned long addr;
	unsigned long reserved;
	
} __attribute__((packed)) multiboot_aout_t;

// The Module structure
typedef struct multiboot_mod_s
{
	void*	mod_start;	// starting address of the module
	void*	mod_end;	// ending address of the module
	char*	string;		// arguments for the module
	unsigned long	reserved;	// 0

} __attribute__((packed)) multiboot_mod_t;

// The memory map. Be careful that the offset 0 is base_addr_low but no size
typedef struct multiboot_memory_map_s
{
	unsigned long size;				// offset to the next structure
	unsigned long base_addr_low;
	unsigned long base_addr_high;
	unsigned long length_low;
	unsigned long length_high;
	unsigned long type;				//  1 is free ram, other is reserved

} __attribute__((packed)) multiboot_memory_map_t;

// The Multiboot information
typedef struct multiboot_header_s
{
	unsigned long			flags;			// this will always be set
											//										a variable is valid if the flag is set
											//										--------------------------------------
	unsigned long			mem_lower;		// KB of conventional memory			MULTIBOOT_FLAG_MEM
	unsigned long			mem_upper;		// KB of extended memory				MULTIBOOT_FLAG_MEM

	unsigned char			boot_device[4]; // +---3---+---2---+---1---+---0---+	MULTIBOOT_FLAG_BOOT
											// | drive | part1 | part2 | part3 |
											// +-------+-------+-------+-------+
	
	char*					cmdline;		// arguments for the kernel				MULTIBOOT_FLAG_CMD

	unsigned long			mods_count;		// number of modules loaded				MULTIBOOT_FLAG_MOD
	multiboot_mod_t* 		mods;			// pointer to the first multiboot_mod_s MULTIBOOT_FLAG_MOD
	
	multiboot_aout_t 		aout_sym;		//										MULTIBOOT_FLAG_AOUT
	
	unsigned long			mmap_length;	// memory map size						MULTIBOOT_FLAG_MMAP
	multiboot_memory_map_t*	mmap;			// memory map address (memory_map_s)	MULTIBOOT_FLAG_MMAP

} __attribute__((packed)) multiboot_header_t;

#endif