/*
	Port I/O
*/


#include "../include/pio.h"

inline NBYTE inb(NUINT port)
{
   NBYTE ret;
   asm volatile ("inb %%dx,%%al":"=a" (ret):"d" (port));
   return ret;
}

inline NVALUE outb(NUINT port,NBYTE value)
{
   asm volatile ("outb %%al,%%dx": :"d" (port), "a" (value));
}
