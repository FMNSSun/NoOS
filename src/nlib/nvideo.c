/*
	Video helpers
*/

#include "nvideo.h"
#include "nsyscalls.h"

NUSHORT nvid_sid = 0;

NUSHORT nvid_init() {
  nvid_sid = syscall_srvc_get_id("video");
  return nvid_sid; 
}

NVALUE nvid_print_text(struct NCOLOREDTEXT text_struct) {
  syscall_rpc_call_func("vid_print",nvid_sid,(NPVALUE)&text_struct);
}

NVALUE nvid_clear_screen() {
  syscall_rpc_call_func("vid_clear_mem",nvid_sid,(NPVALUE)0);
}

NUSHORT nvid_get_height() {
  NUSHORT height = 0;
  syscall_rpc_call_func("vid_get_height",nvid_sid,(NPVALUE)&height);
  return height;
}

NUSHORT nvid_get_width() {
  NUSHORT width = 0;
  syscall_rpc_call_func("vid_get_width",nvid_sid,(NPVALUE)&width);
  return width;
}

NUSHORT nvid_get_row() {
  NUSHORT row = 0;
  syscall_rpc_call_func("vid_get_row",nvid_sid,(NPVALUE)&row);
  return row;
}

NUSHORT nvid_get_column() {
  NUSHORT column = 0;
  syscall_rpc_call_func("vid_get_column",nvid_sid,(NPVALUE)&column);
  return column;
}

NVALUE nvid_set_row(NUSHORT row) {
  syscall_rpc_call_func("vid_set_row",nvid_sid,(NPVALUE)&row);
}

NVALUE nvid_set_column(NUSHORT column) {
  syscall_rpc_call_func("vid_set_column",nvid_sid,(NPVALUE)&column);
}

NADDR nvid_get_ptr() {
  NADDR ptr = 0;
  syscall_rpc_call_func("vid_get_ptr",nvid_sid,(NPVALUE)&ptr);
  return ptr;
}
