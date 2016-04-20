/*
	Debug
*/

#include "../../elf/elf32.h"
#include "../nlib/ntypes.h"

#ifndef NOOS_H_DEBUG
#define NOOS_H_DEBUG

extern char * elf_get_str(Elf32_Word index);
extern Elf32_Sym * elf_find_sym(dword addr);

extern Elf32_Shdr * symtab; 
extern Elf32_Shdr * strtab;

extern NVALUE debug_init(NADDR addr);
extern NVALUE PrintStackTrace(NUINT MaxFrames);


#endif
