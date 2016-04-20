/*
	Debug
*/

#include "../include/debug.h"
#include "../include/multiboot.h"
#include "../include/video.h"
#include "../include/kernel.h"
#include "../nlib/nconv.h"

Elf32_Shdr * symtab = 0; 
Elf32_Shdr * strtab = 0;

NVALUE PrintStackTrace(NUINT MaxFrames) {
  NPUINT ebp = &MaxFrames - 2;
  NUINT frame;
  NCHAR buffer[400];
    vid_print("\r\nStack trace:\r\n",0x5);
    for(frame = 0; frame < MaxFrames; ++frame)
    {
        NUINT eip = ebp[1];
        if(eip == 0)
            // No caller on stack
            break;
        // Unwind to previous stack frame
        ebp = (NUINT*)(ebp[0]);
        //NUINT * arguments = &ebp[2];
        Elf32_Sym* symbol = elf_find_sym((dword)eip);
        NPCHAR name = elf_get_str(symbol->st_name);
        nultoa(eip,16,buffer);
        vid_print(buffer,0x2);vid_print("\t\t",0x2);
        if(symbol != 0) vid_print(name,0x6);
        else vid_print(" [unknown] ",0x6);
        vid_print("\r\n",0x7);
  }

}

NVALUE debug_init(NADDR addr) {
  multiboot_info_t *mbi;
  mbi = (multiboot_info_t*) addr;
  Elf32_Shdr * elfshdr = (Elf32_Shdr *) mbi->u.elf_sec.addr;
  NINT i;
  /* Symbol Table and String Table lookup */
  for (i = 0; i < mbi->u.elf_sec.num; i++) {
    if (elfshdr[i].sh_type == SHT_SYMTAB) {
        symtab = &elfshdr[i];
        strtab = &elfshdr[symtab->sh_link];
        break;
    }
  }
}


Elf32_Sym * elf_find_sym(dword addr)
{
    Elf32_Sym * sym;
    int i;

    if(symtab == 0)
    {
        return 0;
    }

    sym = (Elf32_Sym *)symtab->sh_addr;

    for(i = 0; i < symtab->sh_size / sizeof(Elf32_Sym); i++)
    {
        if(addr >= (dword)sym[i].st_value && addr < (dword)sym[i].st_value + sym[i].st_size)
        {
            return sym + i;
        }
    }

    return 0;
}


NPCHAR elf_get_str(Elf32_Word index)
{
    if(strtab == 0)
    {
        return "";
    }

    return (NPCHAR)strtab->sh_addr + index;
}
