/*
	Interrupt Service Routine
*/

#include "../nlib/ntypes.h"


#ifndef NOOS_H_ISR
#define NOOS_H_ISR

struct stack_frame
{
    NULONG gs, fs, es, ds;
    NULONG edi, esi, ebp, _esp, ebx, edx, ecx, eax;
    NULONG interrupt, error;
    NULONG eip, cs, eflags, esp, ss;
};



NVALUE print_sf(NADDR esp);

NVALUE isr0(NADDR esp);
NVALUE isr1();
NVALUE isr2();
NVALUE isr3();
NVALUE isr4();
NVALUE isr5();
NVALUE isr6(NADDR esp);
NVALUE isr7();
NVALUE isr8();
NVALUE isr9();
NVALUE isr10();
NVALUE isr11();
NVALUE isr12();
NVALUE isr13();
NVALUE isr14();
NVALUE isr15();
NVALUE isr16();
NVALUE isr17();
NVALUE isr18();
NVALUE isr19();
NVALUE isr20();
NVALUE isr21();
NVALUE isr22();
NVALUE isr23();
NVALUE isr24();
NVALUE isr25();
NVALUE isr26();
NVALUE isr27();
NVALUE isr28();
NVALUE isr29();
NVALUE isr30();
NVALUE isr31();
#endif
