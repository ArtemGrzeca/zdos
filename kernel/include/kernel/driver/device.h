#ifndef _KERNEL_DRIVER_DEVICE_H
#define _KERNEL_DRIVER_DEVICE_H

#include <kernel/system/system.h>

#define NULL_DEVICE 0
#define CHAR_DEVICE 1
#define BLOCK_DEVICE 2
#define PSEUDO_DEVICE 3

typedef struct device_s
{
    char type;
    void* device;
} device_t;

typedef struct char_device_s
{
    void (*initialize)(void);
    void (*destory)(void);
    void (*irq_header)(regs_t r);
    void (*send)(char*);
    char* (*recive)(void);
} char_device_t;

typedef struct block_device_s
{
    void (*initialize)(void);
    void (*destory)(void);
    void (*irq_header)(regs_t r);
    void (*send)(block_t*);
    block_t* (*recive)(void);
} block_device_t;

typedef struct pseudo_device_s
{
    void (*initialize)(void);
    void (*destory)(void);
    void (*irq_header)(regs_t r);
    void (*send)(void*);
    void* (*recive)(void);
} pseudo_device_t;

typedef struct block_s
{
	unsigned int magic;
	unsigned int size;
	void* data;
} block_t;

#endif
