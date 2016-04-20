#include "keyboard.h"
#include "../include/kernel.h"
#include "../include/video.h"
#include "../include/service.h"
#include "../include/rpc.h"
#include "../include/pio.h"

NUSHORT kbd_sid = 0;
NBYTE last_scancode;
NBYTE new_key = 0;
NPVALUE registered = NULL;

NBYTE keys[0xFF];

NVALUE kbd_init_layout() {
  vid_print("[ KEYBOARD ] Keyboard layout: U.S\r\n",0x07);

  /*
    Numbers
  */
  keys[0x02] = '1'; keys[0x03] = '2'; keys[0x04] = '3';
  keys[0x05] = '4'; keys[0x06] = '5'; keys[0x06] = '5';
  keys[0x07] = '6'; keys[0x08] = '7'; keys[0x09] = '8';
  keys[0x0A] = '9'; keys[0x0B] = '0';

  /*
    First row
  */
  keys[0x10] = 'q'; keys[0x11] = 'w'; keys[0x12] = 'e';
  keys[0x13] = 'r'; keys[0x14] = 't'; keys[0x15] = 'y';
  keys[0x16] = 'u'; keys[0x17] = 'i'; keys[0x18] = 'o';
  keys[0x19] = 'p';

  /*
   Second row
  */
  keys[0x1E] = 'a'; keys[0x1F] = 's'; keys[0x20] = 'd';
  keys[0x21] = 'f'; keys[0x22] = 'g'; keys[0x23] = 'h';
  keys[0x24] = 'j'; keys[0x25] = 'k'; keys[0x26] = 'l'; 

  /*
   Third row
  */
  keys[0x2C] = 'z'; keys[0x2D] = 'x'; keys[0x2E] = 'c';
  keys[0x2F] = 'v'; keys[0x30] = 'b'; keys[0x31] = 'n';
  keys[0x32] = 'm';

  /*
   Special characters
  */
  keys[0x39] = ' '; keys[0x1C] = '\n'; keys[0x01] = '\r';
}

NVALUE kbd_init() {
  kbd_init_layout();
  /*
    Tell the kernel: "I'm the Keyboard driver"
  */
  kbd_sid = srvc_register_service("keyboard");
  /*
    Ok, now we have to tell the kernel we have some function for him
  */
  rpc_register_func("kbd_handler",(NPVALUE)kbd_handler,kbd_sid);
  rpc_register_func("kbd_register",(NPVALUE)kbd_register,kbd_sid);


  /*
    Now, beg for peace
  */
}


NVALUE kbd_handler(NPVALUE ptr) {
  NBYTE scancode = inb(0x60);
  last_scancode = scancode;
  new_key = 1;
  if(registered == NULL) return;
  NVALUE (*p)(NCHAR);
  p = registered;
  (*p)(kbd_convert(last_scancode));
}

NVALUE kbd_register(NPVALUE ptr) {
  registered = ptr;
}

NBYTE kbd_convert(NBYTE scancode) {
  return keys[scancode];
}


