/*
	Video functions
*/

#include "../nlib/ntypes.h"
#include "../nlib/nvideo.h"

#ifndef NOOS_H_VIDEO
#define NOOS_H_VIDEO

extern NPCHAR video_ptr;
extern NUSHORT vid_column;
extern NUSHORT vid_row;
extern NSMALLSIZE vid_t_width;
extern NSMALLSIZE vid_t_height;

extern NVALUE vid_clear_mem();
extern NVALUE vid_print(NPCHAR message,NCHAR color);
extern NVALUE vid_inc_column();
extern NVALUE vid_inc_row();
extern NVALUE vid_scroll();
extern inline NADDR vid_calc_row_start(NUSHORT rowx);
extern NVALUE vid_print(NPCHAR message,NCHAR color);
extern NVALUE vid_init_drv();

extern NVALUE viddrv_print(struct NCOLOREDTEXT* text);
extern NVALUE viddrv_clear_mem(NPVALUE null);
extern NVALUE viddrv_get_height(NPUSHORT height);
extern NVALUE viddrv_get_width(NPUSHORT width);
extern NVALUE viddrv_get_row(NPUSHORT row);
extern NVALUE viddrv_get_column(NPUSHORT column);
extern NVALUE viddrv_set_row(NPUSHORT row);
extern NVALUE viddrv_set_column(NPUSHORT column);
extern NVALUE viddrv_get_ptr(NPADDR addr);


#endif
