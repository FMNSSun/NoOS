/*
  Text Input/Output
*/

#include "ntypes.h"

#ifndef NOOS_H_NTEXTIO
#define NOOS_H_NTEXTIO

extern NUSHORT nkbrd_sid;
extern NUSHORT ntio_last_key;
extern NUSHORT ntio_new_key;
extern NBYTE ntio_text_color;

extern NUSHORT ntio_init();
extern NVALUE ntio_print(NPCHAR text);
extern NCHAR ntio_read_char();
extern NVALUE ntio_set_text_color(NBYTE color);
extern NPCHAR ntio_read_line(NPCHAR buffer,NINT buf_length,NUSHORT echo);
extern NVALUE ntio_keyboard_handler(NCHAR key);

#endif
