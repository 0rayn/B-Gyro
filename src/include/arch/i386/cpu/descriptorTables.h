#pragma once
#include "klibc/types.h"


void	initDescriptorTables();

/*--------------------------- GDT ---------------------------*/
# define GDT_ENTRIES 7
# define GDT_BASEADDR 0x00000800

// gdt entry structure:
typedef	struct gdtEntry{
	uint16_t	lowLimit;			// 0-15 bits of the limit
	uint16_t	lowBase;			// 0-15 bits of the base
	uint8_t		middleBase;		// 16-23 bits of the base
	/*
		|7|6 5|4|3|2 |1 |0|
		|P|DPL|S|E|DC|RW|A|
		Access Byte: learn more https://wiki.osdev.org/Global_Descriptor_Table#Segment_Descriptor
	*/
	uint8_t		accessByte;		// access bytes
	/*
		|3|2 |1|0       |
		|G|DB|L|Reserved|
		*G* -> when this set to 1 the limit got multiplayed by 0x1000 (to get 4Gb)
	*/
	uint8_t	flags:4;
	uint8_t highLimit:4;
	uint8_t	highBase;			// 24-31 bits of the base
}__attribute__ ((packed)) _gdtEntry; // __attribute__((packed)) prevents the compiler from optimizing the structure

typedef	struct	gdtPtr{
	uint16_t	limit;	// size of the GDT
	uint32_t	base;	//	start of the GDT
}__attribute__ ((packed)) _gdtPtr;

void	initGDT();

/*----------------------------------------------------------*/

/*--------------------------- PIC ---------------------------*/

# define MASTER_CTRL	0x20
# define MASTER_DATA	0x21
# define SLAVE_CTRL		0xA0
# define SLAVE_DATA		0xA1
# define PIC_EOI		0x20

void	picRemap(uint8_t masterOffset, uint8_t slaveOffset);

/*-----------------------------------------------------------*/

/*--------------------------- IDT ---------------------------*/

#define USED_HANDLERS 48

typedef enum {
	TIMER_IRQ = 0,
	KEYBOARD_IRQ = 1,
}e_IRQs;

typedef struct idtEntry{
	uint16_t	isrLow;	// The lower 16 bits of the ISR's address
	uint16_t	kernelCS;	// The GDT segment selector that the CPU will load into CS before calling the ISR
	uint8_t		always0;	// Set to zero
	uint8_t		attributes;	// Type and attributes
	uint16_t	isrHigh;	// The higher 16 bits of the ISR's address
} __attribute__((packed)) _idtEntry;

typedef struct idtPtr{
	uint16_t	limit;
	uint32_t	base;		// address of the first element in the idtEntries array
}__attribute__((packed)) _idtPtr;

//to do: re-check this :)
typedef struct registers{
	// R https://www.eecg.utoronto.ca/~amza/www.mindsec.com/files/x86regs.html
	uint32_t	ds;	// data segment selector
	uint32_t	edi, esi, ebp, esp, ebx, edx, ecx, eax; // pushed by pusha R https://pdos.csail.mit.edu/6.828/2005/readings/i386/PUSHA.htm
	uint32_t	InterruptNbr, errCode;	// interrupt index and error code
	uint32_t	eip, cs, eflags, useresp, ss; // pushed by the cpu automatically
} _registers;

void	initIDT();

void	setIRQHandler(e_IRQs irq, void (*handler)(_registers r));
void	clearIRQHandler(e_IRQs irq);


// CPU exceptions ISRs
extern	void	isr0();
extern	void	isr1();
extern	void	isr2();
extern	void	isr3();
extern	void	isr4();
extern	void	isr5();
extern	void	isr6();
extern	void	isr7();
extern	void	isr8();
extern	void	isr9();
extern	void	isr10();
extern	void	isr11();
extern	void	isr12();
extern	void	isr13();
extern	void	isr14();
extern	void	isr15();
extern	void	isr16();
extern	void	isr17();
extern	void	isr18();
extern	void	isr19();
extern	void	isr20();
extern	void	isr21();
extern	void	isr22();
extern	void	isr23();
extern	void	isr24();
extern	void	isr25();
extern	void	isr26();
extern	void	isr27();
extern	void	isr28();
extern	void	isr29();
extern	void	isr30();
extern	void	isr31();
// IRQs
extern	void	irq0();
extern	void	irq1();
extern	void	irq2();
extern	void	irq3();
extern	void	irq4();
extern	void	irq5();
extern	void	irq6();
extern	void	irq7();
extern	void	irq8();
extern	void	irq9();
extern	void	irq10();
extern	void	irq11();
extern	void	irq12();
extern	void	irq13();
extern	void	irq14();
extern	void	irq15();