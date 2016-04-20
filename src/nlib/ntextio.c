/*
  Text Input/Output
*/

#include "ntextio.h"
#include "nsyscalls.h"
#include "nvideo.h"

NUSHORT nkbrd_sid;
NUSHORT ntio_last_key = 0;
NUSHORT ntio_new_key = 0;
NBYTE ntio_text_color = 0x7;

NUSHORT ntio_init() {
  nkbrd_sid = syscall_srvc_get_id("keyboard");
  syscall_rpc_call_func("kbd_register",nkbrd_sid,(NPVALUE)ntio_keyboard_handler);
  return nkbrd_sid;
}

NVALUE ntio_set_text_color(NBYTE color) {
  ntio_text_color = color;
}

NVALUE ntio_print(NPCHAR text) {
  struct NCOLOREDTEXT text_struct;
  text_struct.text = text;
  text_struct.color = ntio_text_color;
  nvid_print_text(text_struct);
}

NCHAR ntio_read_char() {
  while(ntio_new_key == 0) {
    asm volatile ("nop");
  }
  ntio_new_key = 0; return ntio_last_key;
}

NPCHAR ntio_read_line(NPCHAR buffer,NINT buf_length,NUSHORT echo) {
  NINT index = 0;
  while(index < (buf_length-2)) {
    NCHAR key;
    while(1) { 
      key = ntio_read_char();
      if(key != 0) break;
    }
    if(key == '\n') break;
    buffer[index] = key;
    index++;
    if(echo == 1) {
      struct NCOLOREDTEXT text_struct;
      NCHAR output[2]; output[1] = '\0'; output[0] = key;
      text_struct.text = (NPVALUE)&output; text_struct.color = 0x7;
      nvid_print_text(text_struct);
    }
  }
  buffer[index] = '\0';
  return buffer;
}

NVALUE ntio_keyboard_handler(NCHAR key) {
  ntio_last_key = key;
  ntio_new_key = 1;
}
