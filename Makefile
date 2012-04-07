# Makefile for JamesM's kernel tutorials.
# The C and C++ rules are already setup by default.
# The only one that needs changing is the assembler 
# rule, as we use nasm instead of GNU as.

#Assembler
AA = nasm
AFLAGS =-f elf

# C Compiler
CC = gcc
CFLAGS = -O2 -DDEBUG -Wall -std=c99 -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include -Wno-system-headers

# Linker
LD = ld
LDFLAGS =-T link.ld

	
COBJS =  	hw/isr.o \
			hw/descriptor_tables.o \
			hw/clock.o \
			lib/stdio.o \
			lib/stdlib.o  \
			lib/string.o  \
			lib/list.o	\
			core/heap.o	\
			core/timer.o	\
			core/task.o	\
			core/stack.o	\
			core/kernel.o \
			dev/keyboard.o 	\
			apps/timer_test.o
	
AOBJS =  	core/loader.o hw/interrupt.o hw/gdt.o


kernel.elf: $(AOBJS) $(COBJS) 
	$(LD) $(LDFLAGS) -o $@ $^
	objcopy.exe -O elf32-i386 kernel.elf kernel.elf
	cp -a kernel.elf /cygdrive/a/boot/kernel.elf
        
$(COBJS):%.o:%.c
	 $(CC) -c $(CFLAGS) $< -o $@
	 
$(AOBJS):%.o:%.asm
	$(AA) $(AFLAGS) $< -o $@

clean:
	-rm hw/*.o \
		lib/*.o \
		core/*.o \
		dev/*.o \
		kernel.elf


	