/*
	Kernel header
*/

#include "../nlib/ntypes.h"

#ifndef NOOS_H_KERNEL
#define NOOS_H_KERNEL

extern inline NVALUE kstop();
extern NVALUE panic(NPCHAR message);
extern NVALUE kprint(NPCHAR message);
extern inline NVALUE kwait();
extern inline NVALUE kreboot();

#endif
