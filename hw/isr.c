#include <system.h>

isr_t interrupt_handlers[256];

void fault_handler(u8int);


/* This is a simple string array. It contains the message that
*  corresponds to each and every exception. We get the correct
*  message by accessing like:
*  exception_message[interrupt_number] */
char *exception_messages[] =
{
	"Division By Zero",
	"Debug",
	"Non Maskable Interrupt",
	"Breakpoint",
	"Into Detected Overflow",

	"Out of Bounds",
	"Invalid Opcode",
	"No Coprocessor",
	"Double Fault",
	"Coprocessor Segment Overrun",

	"Bad TSS",
	"Segment Not Present",
	"Stack Fault",
	"General Protection Fault",
	"Page Fault",
	
	"Unknown Interrupt",
	"Coprocessor Fault",
	"Alignment Check",
	"Machine Check",
	"Reserved",

	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",

	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",

	"Reserved",
	"Reserved"
};



void register_interrupt_handler(u8int n, isr_t handler) {
    interrupt_handlers[n] = handler;
}

// This gets called from our ASM interrupt handler stub.
void isr_handler(registers_t* regs)
{
    u8int int_no = regs->int_no & 0xFF;
    //kprintf(" INT:0x%x \n",int_no);
    if (interrupt_handlers[int_no] != 0)
    {
        isr_t handler = interrupt_handlers[int_no];
        handler(regs);
        return;
    }
    else
    {
        fault_handler(int_no);
    }
}



/**
 * @brief exception handler ISR: just show msg, enter infinite loop
 *
 * All of our Exception handling Interrupt Service Routines will
 * point to this function. This will tell us what exception has
 * happened! Right now, we simply halt the system by hitting an
 * endless loop. All ISRs disable interrupts while they are being
 * serviced as a 'locking' mechanism to prevent an IRQ from
 * happening and messing up kernel data structures 
 */
void fault_handler(u8int int_no) {
	if (int_no < 32) {
		kprintf(exception_messages[int_no]);
		kprintf(" Exception. System Halted!\n");
		for (;;);
	}
}



// This gets called from our ASM interrupt handler stub.
void irq_handler(registers_t* regs)
{   
    // Send an EOI (end of interrupt) signal to the PICs.
    // If this interrupt involved the slave.
    if (regs->int_no >= 40)
    {
        // Send reset signal to slave.
        outb(0xA0, 0x20);
    }
    // Send reset signal to master.
    outb(0x20, 0x20);

   //kprintf(" INT:0x%x \n",regs->int_no);

    if (interrupt_handlers[regs->int_no] != 0)
    {   
        isr_t handler = interrupt_handlers[regs->int_no];
        handler(regs);
    }
}
