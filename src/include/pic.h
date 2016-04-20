/*
	Programmable Interrupt Controller
*/

#include "../nlib/ntypes.h"

#ifndef NOOS_H_PIC
#define NOOS_H_PIC

#define PIC1_PORT1 0x20
#define PIC1_PORT2  0x21
#define PIC2_PORT1  0xA0
#define PIC2_PORT2  0xA1
//00010001b
#define ICW1 17
#define ICW2_PIC1 0x20
#define ICW2_PIC2 0x28
//00000100b
#define ICW3 4
#define ICW3_IRQ 0x02
//00000001b
#define ICW4 1

extern NVALUE pic_remap();
#endif
