#ifndef __STRING_H__
#define __STRING_H__

int strcmp(u8int *str1, u8int *str2);
u8int *strcpy(u8int *dest, const u8int *src, u32int n);
u32int strlen(const u8int *s);
u8int *strcat(u8int * dest, const u8int * src);
//int putc(char c);
void puts(char *c);

#endif
