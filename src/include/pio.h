/*
	Port I/O
*/

#include "../nlib/ntypes.h"

#ifndef NOOS_H_PIO
#define NOOS_H_PIO
extern inline NBYTE inb(NUINT port);
extern inline NVALUE outb(NUINT port,NBYTE value);
#endif
