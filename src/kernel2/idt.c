/*
	Interrupt Descriptor Table
*/

#include "../include/idt.h"
#include "../include/irqh.h"
#include "../include/isr.h"
#include "../include/handlers.h"
#include "../include/kernel.h"

struct IDTDescr idt[256];
struct IDTPtr   idtptr;

NVALUE idt_setup_descr(NBYTE num, 
                     NUINT offset,
                     NUSHORT selector,
                     NBYTE type_attr) {
  idt[num].offset_1 = (offset & 0xFFFF);
  idt[num].selector = selector;
  idt[num].zero = 0;
  idt[num].type_attr = type_attr;
  idt[num].offset_2 = ((offset >> 16) & 0xFFFF);
}

NVALUE idt_setup_ptr() {
  idtptr.base = (NUINT) &idt;
  idtptr.size = (sizeof(struct IDTDescr)*256) -1;
}

NVALUE idt_load_idt() {
  asm volatile("lidt %0" : "=m" (idtptr));
}

NVALUE idt_set_handlers() {
  idt_setup_descr(32, (NUINT) irq0_asm, 0x08, 0x8E);
  idt_setup_descr(33, (NUINT) irq1_asm, 0x08, 0x8E);
}

NVALUE idt_setup_isr() {
  idt_setup_descr (0, (NUINT) isr0_stub, 0x08, 0x8E);
  idt_setup_descr(1, (NUINT) isr1, 0x08, 0x8E);
  idt_setup_descr(2, (NUINT) isr2, 0x08, 0x8E);
  idt_setup_descr(3, (NUINT) isr3, 0x08, 0x8E);
  idt_setup_descr(4, (NUINT) isr4, 0x08, 0x8E);
  idt_setup_descr(5, (NUINT) isr5, 0x08, 0x8E);
  idt_setup_descr(6, (NUINT) isr6_stub, 0x08, 0x8E);
  idt_setup_descr(7, (NUINT) isr7, 0x08, 0x8E);
  idt_setup_descr(8, (NUINT) isr8, 0x08, 0x8E);
  idt_setup_descr(9, (NUINT) isr9, 0x08, 0x8E);
  idt_setup_descr(10, (NUINT) isr10, 0x08, 0x8E);
  idt_setup_descr(11, (NUINT) isr11, 0x08, 0x8E);
  idt_setup_descr(12, (NUINT) isr12, 0x08, 0x8E);
  idt_setup_descr(13, (NUINT) isr13_stub, 0x08, 0x8E);
  idt_setup_descr(14, (NUINT) isr14, 0x08, 0x8E);
  idt_setup_descr(15, (NUINT) isr15, 0x08, 0x8E);
  idt_setup_descr(16, (NUINT) isr16, 0x08, 0x8E);
  idt_setup_descr(17, (NUINT) isr17, 0x08, 0x8E);
  idt_setup_descr(18, (NUINT) isr18, 0x08, 0x8E);
  idt_setup_descr(19, (NUINT) isr19, 0x08, 0x8E);
  idt_setup_descr(20, (NUINT) isr20, 0x08, 0x8E);
  idt_setup_descr(21, (NUINT) isr21, 0x08, 0x8E);
  idt_setup_descr(22, (NUINT) isr22, 0x08, 0x8E);
  idt_setup_descr(23, (NUINT) isr23, 0x08, 0x8E);
  idt_setup_descr(24, (NUINT) isr24, 0x08, 0x8E);
  idt_setup_descr(25, (NUINT) isr25, 0x08, 0x8E);
  idt_setup_descr(26, (NUINT) isr26, 0x08, 0x8E);
  idt_setup_descr(27, (NUINT) isr27, 0x08, 0x8E);
  idt_setup_descr(28, (NUINT) isr28, 0x08, 0x8E);
  idt_setup_descr(29, (NUINT) isr29, 0x08, 0x8E);
  idt_setup_descr(30, (NUINT) isr30, 0x08, 0x8E);
  idt_setup_descr(31, (NUINT) isr31, 0x08, 0x8E);
  idt_setup_descr(0x81, (NUINT) syscall_handler, 0x08, 0x8E);
}
