/*
	Global Descriptor Table
*/

#include "../nlib/ntypes.h"


#ifndef NOOS_H_GDT
#define NOOS_H_GDT



#define GDT_SIZE 6

#define GDT_CODESEG 0x0A
#define GDT_DATASEG 0x02
#define GDT_TSS 0x09
#define GDT_PRESENT 0x80
#define GDT_SEGMENT 0x10

#define SYS_CODE_SEL 0x08
#define SYS_DATA_SEL 0x10
#define USER_CODE_SEL 0x18
#define USER_DATA_SEL 0x20
#define TSS_SEL 0x28

extern NVALUE init_gdt(NVALUE);
extern NVALUE gdt_set_descriptor(NINT segment, NULONG size, NULONG base, NBYTE access, NINT dpl);
extern NVALUE gdt_set_descriptor_byte_granularity(NINT segment, NULONG size, NULONG base, NBYTE access, NINT dpl);

#endif
