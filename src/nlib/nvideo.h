/*
	Video helpers
*/

#include "ntypes.h"

#ifndef NOOS_H_NVIDEO
#define NOOS_H_NVIDEO

extern NUSHORT nvid_sid;

struct NCOLOREDTEXT {
  NPCHAR text;
  NBYTE color;
} __attribute__ ((packed));

extern NUSHORT nvid_init();
extern NVALUE nvid_clear_screen();
extern NUSHORT nvid_get_height();
extern NUSHORT nvid_get_width();
extern NUSHORT nvid_get_row();
extern NUSHORT nvid_get_column();
extern NVALUE nvid_set_row(NUSHORT row);
extern NVALUE nvid_set_column(NUSHORT column);
extern NADDR nvid_get_ptr();
extern NVALUE nvid_print_text(struct NCOLOREDTEXT text_struct);

#endif
