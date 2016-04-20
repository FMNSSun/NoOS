/*
  Floppy driver
*/

#include "floppy.h"
#include "../include/pio.h"
#include "../include/video.h"

const NPCHAR drive_types[8] = {
  "none",
  "360KB 5,25\"",
  "1.2MB 5.25\"",
  "720KB 3.5\"",
  "1.44MB 3.4\"",
  "2.88MB 3.5\"",
  "unknown",
  "unknown"
};

NVALUE timer_sleep(NUINT times) {
  NUINT i;
  for(i=0;i<1024*1024*+times;i++) asm("nop");
}

NVALUE floppy_detect_drive() {  //only one floppy drive is supported :(
  outb(0x70,0x10);
  unsigned drives = inb(0x71);
  
  vid_print("[ FLOPPY ] Floppy drive 0: ",0x7);
  vid_print(drive_types[drives >> 4],0x7); vid_print("\r\n",0x7);
}

#ifdef _C_WITH_FLOPPY

NVALUE floppy_write_cmd(NINT base, NCHAR cmd) {
  NINT i;
  for(i=0;i<600;i++) {
    timer_sleep(1);
    if(0x80 & inb(base+FLOPPY_MSR)) return (void) outb(base+FLOPPY_FIFO,cmd);
  }
  panic("floppy_write_cmd timed out");
}

NBYTE floppy_read_data(NINT base) {
  NINT i;
  for(i=0;i<600;i++) {
    timer_sleep(1);
    if(0x80 & inb(base+FLOPPY_MSR) return inb(base+FLOPPY_FIFO);
  }
  panic("floppy_read_data timed out");
  return 0;
}

NVALUE floppy_check_interrupt(NINT base, NPINT st0, NPINT cyl) {
  floppy_write_cmd(base, CMD_SENSE_INTERRUPT);
  *st0 = floppy_read_data(base);
  *cyl = floppy_read_data(base);
}

NINT floppy_calibrate(NINT base) {
  NINT i, st0, cyl = -1;
  floppy_motor(base, floppy_motor_on);

  for(i=0;i<10;i++) {
    floppy_write_cmd(base, CMD_RECALIBRATE);
    floppy_write_cmd(base, 0x0);
    
    irq_wait(floppy_irq);
    floppy_check_interrupt(base, &st0, &cyl);

    if(st0 & 0xC0) {
      static NPCHAR status[] = { 0x0, "error","invalid","drive" };
      vid_print("floppy_calibrate: status = ",0x7); vid_print(status[st0 >> 6]); vid_print("\r\n"); continue;
    }

    if(!cyl) {
      floppy_motor(base, floppy_motor_off);
      return 0;
    }
  }
  
  vid_print("floppy_calibrate exhausted\r\n",0x7);
  floppy_motor(base, floppy_motor_off);
  return -1;
}

NINT floppy_reset(NINT base) {
  outb(base+FLOPPY_DOR,0x00);
  outb(base+FLOPPY_DOR,0x0C);
  
  irq_wait(floppy_irq);

  { NINT st0, cyl; floppy_check_interrupt(base,&st0,&cyl); }

  outb(base+FLOPPY_CCR,0x00);

  floppy_write_cmd(base, CMD_SPECIFY);
  floppy_write_cmd(base, 0xDF);
  floppy_write_cmd(base, 0x02);

  if(floppy_calibrate(base)) return -1;
}

volatile NINT floppy_motor_ticks = 0;
volatile NINT floppy_motor_state = 0;

NVALUE floppy_motor(NINT base, NINT onoff) {
  if(onoff) { if(!floppy_motor_state) {
    outb(base+FLOPPY_DOR, 0x1C);
    timer_sleep(60); }
    floppy_motor_state = floppy_motor_on;
  } else
  {
    if(floppy_motor_state == floppy_motor_wain) {
      vid_print("floppy_motor: something is weird!\r\n",0x7);
    }
    floppy_motor_ticks = 300;
    floppy_motor_state = floppy_motor_wait;
  }
}

NINT floppy_seek(NINT base, NUINT clyi, NINT head) {
  NUINT i, st0, cyl =  -1;
  floppy_motor(base,floppy_motor_on);

  for(i=0;i<10;i++) {
    floppy_write_cmd(base, CMD_SEEK);
    floppy_write_cmd(base, head<<2);
    floppy_write_cmd(base, cyli);

    irq_wait(floppy_irq);
    floppy_check_interrupt(base,&st0,&cyl);

    if(st0 & 0xC0) {
      static NPCHAR status[] = { "normal","error","invalid","drive" };
      vid_print("floppy_seek: status = ",0x7); vid_print(status[st0 >> 6],0x7); vid_print("\r\n");
      continue;
    }

    if(cyl == cyli) {
      floppy_motor(base, floppy_motor_off);
      return 0;
    }

    vid_print("floppy_seek exhausted!\r\n");
    floppy_motor(base, floppy_motor_off);
    return -1;
  }
}
 

static const NCHAR floppy_dmabuff[0x4800] __attribute__((aligned(0x8000)));
 
NVALUE floppy_dma_init(floppy_dir dir) {
  union {
    NBYTE b[4];
    NULONG l;
  } a,c;

  a.l = (unsigned) &floppy_dmabuf;
  c.l = (unsigned) 0x4800 - 1;

  if (a.l >> 24) || (c.l >> 16) || ((a.l&0xffff)+c.l)>>16)) {
    panic("floppy_dma_init: buffer is futschikato");
  }
}

#endif
