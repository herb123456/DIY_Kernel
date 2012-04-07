// common.h -- Defines typedefs and some global functions.
//             From JamesM's kernel development tutorials.

#ifndef __STDLIB_H__
#define __STDLIB_H__

void disableInterrupt();
void enableInterrupt();
void outb(u16int port, u8int value);
void outw(u16int port, u16int value);
u8int inb(u16int port);
u16int inw(u16int port);
void insw(u16int port, void *dst, u32int count);
void insb(u16int port, void *dst, u32int count);
void outsw(u16int port, void *src, u32int count);
void outsb(u16int port, void *src, u32int count);
void memcpy(void *dest, const void *src, u32int len);
void memset(u8int *dest, u8int val, u32int len);
void* memmove(void *dest, const void *src, u32int len);
u32int memcmp(const void * cs,const void * ct, u32int count);


#endif 
