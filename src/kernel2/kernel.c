/*
	Noos (c) Roman Muentener
	************************
  Kernel2
*/

#include "../include/kernel.h"
#include "../include/multiboot.h"
#include "../include/mem.h"
#include "../include/video.h"
#include "../include/pic.h"
#include "../include/pio.h"
#include "../include/idt.h"
#include "../include/gdt.h"
#include "../include/rpc.h"
#include "../include/service.h"
#include "../include/debug.h"
#include "../include/syscalls.h"

#include "../drivers/keyboard.h"
#include "../drivers/floppy.h"
#include "../drivers/speaker.h"

#include "../nlib/ntypes.h"
#include "../nlib/nconv.h"
#include "../nlib/nflag.h"
#include "../nlib/nmem.h"

#include "../apps/nash.h"

int main(NULONG magic,NADDR addr) {

  //Clear screen
  vid_clear_mem();

  /*
    Multiboot stuff
  */
  

  /* Am I booted by a Multiboot-compliant boot loader? */
  if (magic != MULTIBOOT_BOOTLOADER_MAGIC)
   panic("NoOS was not booted by a Multiboot-compliant boot loader. MAGIC_VALUE is not correct");

  multiboot_info_t *mbi;
  /* Set MBI to the address of the Multiboot information structure. */
  mbi = (multiboot_info_t *) addr;


  /* Are mem_* valid? */
  if (NCHECK_FLAG(mbi->flags,0) == 0)
    panic("NoOS detected that flag 0 in the mbi is not set. MBI_FLAGS are not correct");

  if (NCHECK_FLAG(mbi->flags,5) == 0)
    panic("NoOS detected that flog 5 in the mbi is not set. MBI_FLAGS are not correct");

  /* Init debug */
  debug_init(addr);
/*
  vid_print("Error caused in: ",0x8);
  Elf32_Sym* symbol = elf_find_sym((dword)0x1001ef);
  char* name = elf_get_str(symbol->st_name);
  vid_print(name,0x6);vid_print("\r\n",0x06); kstop();
*/
  kprint("Kernel loaded\r\n");
  kprint("Setting up IDT...\r\n");

  idt_setup_ptr();
  nmemset(&idt, 0, sizeof(struct IDTDescr)*256);
  idt_load_idt();
  idt_setup_isr();

  kprint("Creating Handlers...\r\n");

  idt_set_handlers();

  kprint("Remapping PIC...\r\n");

  pic_remap();

  kprint("Initializing GDT...\r\n");

  init_gdt();

  kprint("Initializing Memory Manager...\r\n");

  mem_init(addr);

  kprint("Setting up RPC...\r\n");

  rpc_init();

  kprint("Setting up Services..\r\n");

  srvc_init();

  kprint("Initializing Keyboard driver...\r\n");

  kbd_init();

  kprint("Initializing Video driver...\r\n");

  vid_init_drv();

  kprint("Initializing Floppy driver...\r\n");

  floppy_detect_drive();

  kprint("Initializing Memory Manager [[SERVICE]]...\r\n");

  mem_init_srvc();

  kprint("Initializing RPC [[SERVICE]]...\r\n");

  rpc_init_srvc();

  kprint("Enabling interrupts...\r\n");

 
  asm("sti");

  nash_start();

  while(1) asm("hlt");
}


NVALUE kprint(NPCHAR message) {
  vid_print("[NoOS] ",0x05);
  vid_print(message,0x02);
}

inline NVALUE kwait() {
  asm volatile ("nop");
  asm volatile ("nop");
  asm volatile ("nop");
}

inline NVALUE kstop() {
  asm volatile ("cli"); 
  asm volatile ("hlt");
}

NVALUE panic(NPCHAR message) {
  vid_print(message,0x04);
  kstop();
}

inline NVALUE kreboot()
{
    NBYTE good = 0x02;
    while ((good & 0x02) != 0)
        good = inb(0x64);
    outb(0x64, 0xFE);
    kstop();
}
