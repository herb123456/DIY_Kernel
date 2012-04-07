#include <system.h>


void disableInterrupt() {
    __asm__ __volatile ("cli");
}

void enableInterrupt() {
    __asm__ __volatile ("sti");
}

// Write a byte out to the specified port.
void outb(u16int port, u8int value) {
    __asm__ __volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}

// Write a word out to the specified port.
void outw(u16int port, u16int value) {
    __asm__ __volatile ("outw %1, %0" : : "dN" (port), "a" (value));
}

u8int inb(u16int port) {
    u8int ret;
    __asm__ __volatile("inb %1, %0" : "=a" (ret) : "dN" (port));
    return ret;
}

u16int inw(u16int port) {
    u16int ret;
    __asm__ __volatile ("inw %1, %0" : "=a" (ret) : "dN" (port));
    return ret;
}

void insw(u16int port, void *dst, u32int count) {
      u16int *dp = dst;
	  
	  while(count--) 
			*dp++ = inw(port);
}

void insb(u16int port, void *dst, u32int count) {
      u8int *dp = dst;
	  
	  while(count--) 
			*dp++ = inb(port);
}

void outsw(u16int port, void *src, u32int count) {
      u16int *sp = src;
	  
	  while(count--) 
			outw(port, *sp++);
}

void outsb(u16int port, void *src, u32int count) {
      u8int *sp = src;
	  
	  while(count--) 
			outb(port, *sp++);
}

// Copy len bytes from src to dest.
/**
 * This function will copy memory content from source address to destination
 * address.
 *
 * @param dst the address of destination memory
 * @param src  the address of source memory
 * @param count the copied length
 *
 * @return the address of destination memory
 *
 */
void memcpy(void *dest, const void *src, u32int count) {

	u8int *tmp = (u8int *) dest, *s = (u8int *) src;

	while (count--)
		*tmp++ = *s++;

	//return dest;
}

/**
 * This function will set the content of memory to specified value
 *
 * @param dest the address of source memory
 * @param val the value shall be set in content
 * @param len the copied length
 *
 * @return the address of source memory
 *
 */
void memset(u8int *dest, u8int val, u32int len) {
	u8int *xs = (u8int *) dest;

	while (len--)
		*xs++ = val;

	//return dest;
}

/**
 * This function will move memory content from source address to destination
 * address.
 *
 * @param dest the address of destination memory
 * @param src  the address of source memory
 * @param len the copied length
 *
 * @return the address of destination memory
 *
 */
void* memmove(void *dest, const void *src, u32int len) {
	u8int *tmp = (u8int *) dest, *s = (u8int *) src;

	if (s < tmp && tmp < s + len) 	{
		tmp+=len;
		s+=len;

		while (len--)
			*tmp-- = *s--;
	} 	else	{
		while (len--)
			*tmp++ = *s++;
	}

	return dest;
}

/**
 * memcmp - Compare two areas of memory
 * @param cs: One area of memory
 * @param ct: Another area of memory
 * @param count: The size of the area.
 */
u32int memcmp(const void * cs,const void * ct, u32int count) {
	const u8int *su1, *su2;
	int res = 0;

	for( su1 = cs, su2 = ct; 0 < count; ++su1, ++su2, count--)
		if ((res = *su1 - *su2) != 0)
			break;
	return res;
}
