/*
	Interrupt Descriptor Table
*/

#include "../nlib/ntypes.h"

#ifndef NOOS_H_IDT
#define NOOS_H_IDT

struct IDTDescr {
 NUSHORT offset_1; // offset bits 0..15
 NUSHORT selector; // a code segment selector in GDT or LDT
 NBYTE zero;      // unused, set to 0
 NBYTE type_attr; // type and attributes, see below
 NUSHORT offset_2; // offset bits 16..31
} __attribute__((packed));

struct IDTPtr {
 NUSHORT size;
 NUINT base;
} __attribute__((packed));

extern NVALUE isr0_stub();
extern NVALUE isr6_stub();
extern NVALUE isr13_stub();

extern NVALUE syscall_handler();

extern NVALUE idt_setup_descr(NBYTE num, 
                     NUINT offset,
                     NUSHORT selector,
                     NBYTE type_attr);

extern NVALUE idt_setup_ptr();
extern NVALUE idt_load_idt();
extern NVALUE idt_setup_isr();
extern NVALUE idt_set_handlers();

extern struct IDTDescr idt[];
extern struct IDTPtr idtptr;
#endif
