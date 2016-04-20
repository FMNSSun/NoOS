/*
	Programmable Interrupt Controller
*/

#include "../include/pic.h"
#include "../include/pio.h"
#include "../include/kernel.h"

NVALUE pic_remap() {


  //Send ICW1
  outb(PIC1_PORT1,ICW1);
  kwait();
  outb(PIC2_PORT1,ICW1);
  kwait();

  //Send ICW2 which are the numbers of the interrupts afaik :)
  outb(PIC1_PORT2,ICW2_PIC1);
  kwait();
  outb(PIC2_PORT2,ICW2_PIC2);
  kwait();

  //Send ICW3 (Slave at IRQ 2)
  outb(PIC1_PORT2,ICW3);
  kwait();
  outb(PIC2_PORT2,ICW3_IRQ);
  kwait();

  //Finally, Send ICW4 (EOI or so)
  outb(PIC1_PORT2,ICW4);
  kwait();
  outb(PIC2_PORT2,ICW4);
  kwait();
}
