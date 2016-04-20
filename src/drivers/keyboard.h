/*
	Keyboard driver
*/

#include "../nlib/ntypes.h"

#ifndef NOOS_H_KEYBOARD
#define NOOS_H_KEYBOARD

extern NVALUE kbd_init();
extern NVALUE kbd_handler(NPVALUE ptr);
extern NBYTE last_scancode;
extern NBYTE keys[];
extern NBYTE kbd_convert(NBYTE scancode);
extern NVALUE kbd_register(NPVALUE ptr);

#endif
