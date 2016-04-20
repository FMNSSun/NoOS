#include "../include/handlers.h"
#include "../include/video.h"
#include "../include/kernel.h"
#include "../include/service.h"
#include "../include/rpc.h"
#include "../include/pio.h"

NVALUE handler_pit() {
  //vid_print("[handlers.c] handler_pit\r\n",0x3);
  ack_handler();
}

NVALUE handler_keyboard() {
  NUSHORT id = srvc_get_id("keyboard");
  NPVALUE buf = (NPVALUE)0;
  rpc_call_func("kbd_handler",id,buf);
  ack_handler();
}

NVALUE ack_handler() {
  //outb(0xA0,0x20);
  outb(0x20,0x20);
}
