/*
	Interrupt Service Routines
*/

#include "../include/isr.h"
#include "../include/video.h"
#include "../include/kernel.h"
#include "../nlib/nconv.h"
#include "../include/debug.h"

NVALUE print_sf(NADDR esp) {
  struct stack_frame * sf = (struct stack_frame *)esp;
  char buffer[400];

  
  vid_print(" Register dump: \r\n",0x7);
  nultoa(sf->eip,16,buffer);
  vid_print("  EIP = ",0x7);
  vid_print(buffer,0x7);vid_print(",",0x7);
  nultoa(sf->interrupt,16,buffer);
  vid_print("  INT = ",0x7);
  vid_print(buffer,0x7);vid_print(",",0x7);
  nultoa(sf->error,16,buffer);
  vid_print("  ERR = ",0x7);
  vid_print(buffer,0x7);vid_print("\r\n",0x7);

  nultoa(sf->gs,16,buffer);
  vid_print("  GS = ",0x7);
  vid_print(buffer,0x7);vid_print(",",0x7);
  nultoa(sf->fs,16,buffer);
  vid_print("  FS = ",0x7);
  vid_print(buffer,0x7);vid_print(",",0x7);
  nultoa(sf->es,16,buffer);
  vid_print("  ES = ",0x7);
  vid_print(buffer,0x7);vid_print(",",0x7);
  nultoa(sf->ds,16,buffer);
  vid_print("  DS = ",0x7);
  vid_print(buffer,0x7);vid_print("\r\n",0x7);

  nultoa(sf->eax,16,buffer);
  vid_print("  EAX = ",0x7);
  vid_print(buffer,0x7);vid_print(",",0x7);
  nultoa(sf->ebx,16,buffer);
  vid_print("  EBX = ",0x7);
  vid_print(buffer,0x7);vid_print(",",0x7);
  nultoa(sf->ecx,16,buffer);
  vid_print("  ECX = ",0x7);
  vid_print(buffer,0x7);vid_print(",",0x7);
  nultoa(sf->edx,16,buffer);
  vid_print("  EDX = ",0x7);
  vid_print(buffer,0x7);vid_print("\r\n",0x7);

  nultoa(sf->edi,16,buffer);
  vid_print("  EDI = ",0x7);
  vid_print(buffer,0x7);vid_print(",",0x7);
  nultoa(sf->esi,16,buffer);
  vid_print("  ESI = ",0x7);
  vid_print(buffer,0x7);vid_print("\r\n",0x7);

  nultoa(sf->ss,16,buffer);
  vid_print("  SS = ",0x7);
  vid_print(buffer,0x7);vid_print(",",0x7);
  nultoa(sf->cs,16,buffer);
  vid_print("  CS = ",0x7);
  vid_print(buffer,0x7);vid_print("\r\n",0x7);

  nultoa(sf->_esp,16,buffer);
  vid_print("  >>",0x7);
  vid_print(buffer,0x7);vid_print("\r\n",0x7);
  nultoa(esp,16,buffer);
  vid_print(" Stack frame located at: ",0x7);
  vid_print(buffer,0x7);vid_print("\r\n",0x7);
  /* Ultra test */
  vid_print("Error caused in: ",0x8);
  Elf32_Sym* symbol = elf_find_sym((dword)sf->eip);
  char* name = elf_get_str(symbol->st_name);
  vid_print(name,0x6);
  PrintStackTrace(7);
}

NVALUE isr0(NADDR esp) {
  vid_print("\r\n[ ISR ] Division By Zero Exception\r\n",0xC);
  print_sf(esp);
  kstop();
}

NVALUE isr1() {
  vid_print("[ ISR ] Debug Exception",0xC);
  kstop();
}

NVALUE isr2() {
  vid_print("[ ISR ] No Maskable Interrupt Exception",0xC);
  kstop();
}

NVALUE isr3() {
  vid_print("[ ISR ] Breakpoint Exception",0xC);
  kstop();
}

NVALUE isr4() {
  vid_print("[ ISR ] Into Detected Overflow Exception",0xC);
  kstop();
}

NVALUE isr5() {
  vid_print("[ ISR ] Out Of Bounds Exception",0xC);
  kstop();
}

NVALUE isr6(NADDR esp) {
  vid_print("[ ISR ] Invalid Opcode Exception",0xC);
  print_sf(esp);
  kstop();
}

NVALUE isr7() {
  vid_print("[ ISR ] No Coproccesor Exception",0xC);
  kstop();
}

NVALUE isr8() {
  vid_print("[ ISR ] Double Fault Exception",0xC);
  kstop();
}

NVALUE isr9() {
  vid_print("[ ISR ] Coprocessor Segment Overrun Exception",0xc);
  kstop();
}

NVALUE isr10() {
  vid_print("[ ISR ] Bad TSS Exception",0xC);
  kstop();
}

NVALUE isr11() {
  vid_print("[ ISR ] Segment Not Present Exception",0xC);
  kstop();
}


NVALUE isr12() {
  vid_print("[ ISR ] Stack Fault Exception",0xC);
  kstop();
}

NVALUE isr13(NADDR esp) {
  vid_print("[ ISR ] General Protection Fault Exception",0xC);
  print_sf(esp);
  kstop();
}

NVALUE isr14() {
  vid_print("[ ISR ] Page Fault Exception",0xC);
  kstop();
}

NVALUE isr15() {
  vid_print("[ ISR ] Unknown Interrupt Exception",0xC);
  kstop();
}

NVALUE isr16() {
  vid_print("[ ISR ] Coprocessor Fault Exception",0xC);
  kstop();
}

NVALUE isr17() {
  vid_print("[ ISR ] Alignment Check Exception",0xC);
  kstop();
}

NVALUE isr18() {
  vid_print("[ ISR ] Machine Check Exception",0xC);
  kstop();
}

NVALUE isr19() {
  vid_print("[ ISR ] Unknown Exception",0xC);
  kstop();
}

NVALUE isr20() {
  vid_print("[ ISR ] Unknown Exception",0xC);
  kstop();
}

NVALUE isr21() {
  vid_print("[ ISR ] Unknown Exception",0xC);
  kstop();
}

NVALUE isr22() {
  vid_print("[ ISR ] Unknown Exception",0xC);
  kstop();
}

NVALUE isr23() {
  vid_print("[ ISR ] Unknown Exception",0xC);
  kstop();
}

NVALUE isr24() {
  vid_print("[ ISR ] Unknown Exception",0xC);
  kstop();
}

NVALUE isr25() {
  vid_print("[ ISR ] Unknown Exception",0xC);
  kstop();
}

NVALUE isr26() {
  vid_print("[ ISR ] Unknown Exception",0xC);
  kstop();
}

NVALUE isr27() {
  vid_print("[ ISR ] Unknown Exception",0xC);
  kstop();
}

NVALUE isr28() {
  vid_print("[ ISR ] Unknown Exception",0xC);
  kstop();
}

NVALUE isr29() {
  vid_print("[ ISR ] Unknown Exception",0xC);
  kstop();
}

NVALUE isr30() {
  vid_print("[ ISR ] Unknown Exception",0xC);
  kstop();
}

NVALUE isr31() {
  vid_print("[ ISR ] Unknown Exception",0xC);
  kstop();
}
