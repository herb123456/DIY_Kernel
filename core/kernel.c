#include <system.h>

extern u32int end;
u32int end_address = (u32int)&end;


int kernelStart(struct multiboot_info *mboot_ptr){
	 
    
		kprintf("\n\n\n\n\n\n HW init ...\n");
     
		init_descriptor_tables();
		kprintf("\t\t IDT/GDT initialised...\n");
    
		init_sysClock(100);
		kprintf("\t\t CMOS timer initialised to 100hz...\n");
		
		
		u32int memsize = (mboot_ptr->mem_lower + mboot_ptr->mem_upper) * 1024;
		init_heap(end_address + 0x1000, memsize - end_address - 0x1000);
		//kprintf("\t\t end_address: %d \n", end_address);
		kprintf("\t\t Heap initialised...\n");
		
		
		init_keyboard();
		kprintf("\t\t PS/2 keyboard initialised...\n");
		
		init_system_timer();
		kprintf("\t\t timer initialised...\n");
		
		init_application();
		kprintf("\t\t application initialised...\n");
		
		enableInterrupt();
		while(1){}	
		return 0;
}
