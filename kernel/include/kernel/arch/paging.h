#ifndef _KERNEL_ARCH_PAGING_H
#define _KERNEL_ARCH_PAGING_H

#include <kernel/arch/arch.h>

typedef struct page
{
    unsigned int present    : 1;   // Page present in memory
    unsigned int rw         : 1;   // Read-only if clear, readwrite if set
    unsigned int user       : 1;   // Supervisor level only if clear
    unsigned int accessed   : 1;   // Has the page been accessed since last refresh?
    unsigned int dirty      : 1;   // Has the page been written to since last refresh?
    unsigned int unused     : 7;   // Amalgamation of unused and reserved bits
    unsigned int frame      : 20;  // Frame address (shifted right 12 bits)
} page_t;

typedef struct page_table
{
    page_t pages[1024];
} page_table_t;

typedef struct page_directory
{
    page_table_t *tables[1024];
    unsigned int tablesPhysical[1024];
    unsigned int physicalAddr;
} page_directory_t;

void initialise_paging(unsigned int ram_size);
void switch_page_directory(page_directory_t *new);
page_t *get_page(unsigned int address, int make, page_directory_t *dir);
void page_fault(regs_t* regs);

#endif