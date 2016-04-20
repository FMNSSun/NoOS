/*
	Global Descriptor Table
*/

#include "../include/gdt.h"


typedef struct {
  NUSHORT size;
  NUSHORT base;
  NBYTE base2;
  NBYTE access;
  NBYTE size2;
  NBYTE base3;
} segment_descriptor;

segment_descriptor gdt[GDT_SIZE];


NVALUE init_gdt()
{
  gdt_set_descriptor(1, 0x000FFFFF, 0x00000000, GDT_SEGMENT | GDT_PRESENT | GDT_CODESEG, 0);
  gdt_set_descriptor(2, 0x000FFFFF, 0x00000000, GDT_SEGMENT | GDT_PRESENT | GDT_DATASEG, 0);
  struct {
    NUSHORT size;
    NULONG base;
  }  __attribute__((packed)) gdt_ptr = {
    .size  = GDT_SIZE*8 - 1,
    .base  = (NULONG)gdt,
  };

  __asm__("lgdtl %0\n\t"
    "ljmpl $0x08, $1f\n\t"
    "1:\n\t"
    "mov $0x10, %%eax\n\t"
    "mov %%eax, %%ds\n\t"
    "mov %%eax, %%es\n\t"
    "mov %%eax, %%fs\n\t"
    "mov %%eax, %%gs\n\t"
    "mov %%eax, %%ss\n\t" : : "m" (gdt_ptr) : "eax");
}


NVALUE gdt_set_descriptor(NINT segment, NULONG size, NULONG base, NBYTE access, NINT dpl)
{
  gdt[segment].size   = size & 0xFFFF;
  gdt[segment].size2  = ((size >> 16) & 0x0F) | 0xC0;
  gdt[segment].base   = base & 0xFFFF;
  gdt[segment].base2  = (base >> 16) & 0xFF;
  gdt[segment].base3  = ((base >> 24) & 0xFF);
  gdt[segment].access = access | ((dpl & 3) << 5);
}


NVALUE gdt_set_descriptor_byte_granularity(NINT segment, NULONG size, NULONG base, NBYTE access, NINT dpl)
{
  gdt_set_descriptor(segment, size, base, access, dpl);
  gdt[segment].size2  = ((size >> 16) & 0x0F) | 0x40;
}


