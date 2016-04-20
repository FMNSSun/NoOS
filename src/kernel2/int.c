/*
	Interrupts
*/

#include "../include/int.h"


NVALUE int_enable() {
  asm volatile ("sti");
}

NVALUE int_disable() {
  asm volatile ("cli");
}
