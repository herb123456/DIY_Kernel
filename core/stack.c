#include "system.h"

void *init_stack(void *stack_addr, void *entry, void *parameter){
	u32int *stk;
	stk = (void *)stack_addr;
	
	*(--stk) = (u32int)parameter;
	*(--stk) = (u32int)entry;
	
	*(--stk) = (u32int)0xFF;
	*(--stk) = (u32int)0xFF;
	
	*(--stk) = (u32int)0x0;
	*(--stk) = (u32int)0x0;
	*(--stk) = (u32int)0x0;
	*(--stk) = (u32int)0x0;
	*(--stk) = (u32int)0x0;
	*(--stk) = (u32int)0x0;
	*(--stk) = (u32int)0x0;
	*(--stk) = (u32int)0x0;
	
	*(--stk) = (u32int)0x00000010;
	*(--stk) = (u32int)0x00000010;
	*(--stk) = (u32int)0x00000010;
	*(--stk) = (u32int)0x00000010;
	
	return (void *)stk;

}