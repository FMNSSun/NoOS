/*
  Floppy driver
*/

#include "../nlib/ntypes.h"


//The registers
enum floppy_registers {
  FLOPPY_DOR  = 2,            //digital output register
  FLOPPY_MSR  = 4,            //master status register (read-only)
  FLOPPY_FIFO = 5,            //FIFO, DMA
  FLOPPY_CCR  = 7             //configuration control register (write-only) 
};

//The commands
enum floppy_commands {
  CMD_SPECIFY         = 3,
  CMD_WRITE_DATA      = 5,
  CMD_READ_DATA       = 6,
  CMD_RECALIBRATE     = 7,
  CMD_SENSE_INTERRUPT = 8,
  CMD_SEEK            = 15 
};

enum { floppy_motor_off = 0, floppy_motor_on, floppy_motor_wait };

typedef enum {
  floppy_dir_read = 1,
  floppy_dir_write = 2
} floppy_dir;


extern NVALUE floppy_detect_drive();
