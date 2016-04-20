/*
	Video functions
*/

#include "../include/video.h"
#include "../nlib/nmem.h"
#include "../include/rpc.h"
#include "../include/service.h"


NPCHAR video_ptr = (NPCHAR)0xB8000;
NUSHORT vid_t_width = 80;
NUSHORT vid_t_height = 25;
NUSHORT vid_row = 0;
NUSHORT vid_column = 0;

NVALUE vid_init_drv() {
  NUSHORT vid_sid = srvc_register_service("video");
  rpc_register_func("vid_print",(NPVALUE)viddrv_print,vid_sid);
  rpc_register_func("vid_clear_mem",(NPVALUE)viddrv_clear_mem,vid_sid);
  rpc_register_func("vid_get_height",(NPVALUE)viddrv_get_height,vid_sid);
  rpc_register_func("vid_get_width",(NPVALUE)viddrv_get_width,vid_sid);
  rpc_register_func("vid_get_row",(NPVALUE)viddrv_get_row,vid_sid);
  rpc_register_func("vid_get_column",(NPVALUE)viddrv_get_column,vid_sid);
  rpc_register_func("vid_set_row",(NPVALUE)viddrv_set_row,vid_sid);
  rpc_register_func("vid_set_column",(NPVALUE)viddrv_set_column,vid_sid);
  rpc_register_func("vid_get_ptr",(NPVALUE)viddrv_get_ptr,vid_sid);
  vid_print("[ VIDEO ] Registered functions for RPC\r\n",0x7);
}

NVALUE viddrv_print(struct NCOLOREDTEXT* text) {
  /* Wrap driver handler */
  vid_print(text->text,text->color);
}

NVALUE viddrv_clear_mem(NPVALUE null) { vid_clear_mem(); }

NVALUE viddrv_get_height(NPUSHORT height) {
  *height = vid_t_height;
}

NVALUE viddrv_get_width(NPUSHORT width) {
  *width = vid_t_width;
}

NVALUE viddrv_get_row(NPUSHORT row) {
  *row = vid_row;
}

NVALUE viddrv_get_column(NPUSHORT column) {
  *column = vid_column;
}

NVALUE viddrv_set_row(NPUSHORT row) {
  vid_row = *row;
}

NVALUE viddrv_set_column(NPUSHORT column) {
  vid_column = *column;
}

NVALUE viddrv_get_ptr(NPADDR addr) {
  *addr = (NADDR)video_ptr;
}

NVALUE vid_clear_mem() {
  NPCHAR video = video_ptr;
  for(video+=4000; video !=video_ptr; video--)
    *video=0;
}

NVALUE vid_print(NPCHAR message,NCHAR color) {
  NADDR base_ptr;
  NPCHAR vidmem;

  while(*message) {
    base_ptr = ((vid_row*160)+(vid_column*2));
    vidmem = (video_ptr + base_ptr);
    if(*message == 0x0A) { vid_column = 0; vid_inc_row(); message++; continue; }
    if(*message == 0x0D) { vid_inc_column(); message++; continue; }
    if(*message == 0x09) { NUSHORT i; for(i=0;i<4;i++) vid_inc_column(); message++; continue; }
    *vidmem = *message;
    vidmem++;
    *vidmem = color;
    message++;
    vid_inc_column();
  }
}

NVALUE vid_inc_column() {
  vid_column++;
  if(vid_column >= vid_t_width) {
    vid_inc_row();
    vid_column = 0;
  }
}

NVALUE vid_inc_row() {
  vid_row++;
  if(vid_row > (vid_t_height-1)) { vid_row = (vid_t_height-1); vid_column = 0; vid_scroll(); }
}

NVALUE vid_scroll() {
  NUINT i;
  for(i=1;i<vid_t_height;i++) {
    nmemcpy((NPVALUE)vid_calc_row_start(i),(NPVALUE)vid_calc_row_start(i-1),vid_t_width*2);
  }
  NPCHAR last_row = (NPCHAR)vid_calc_row_start(vid_t_height-1);
  for(i=0;i<(vid_t_width*2);i++) {
    *last_row = 0x00;
    last_row++;
  }
}

inline NADDR vid_calc_row_start(NUSHORT rowx) {
  return (NADDR)(video_ptr + (rowx*(vid_t_width*2)));
}
