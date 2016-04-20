/*
  Plays sound... (should play sound)
*/

#include "speaker.h"
#include "../include/pio.h"

NVALUE switch_speaker_on() {
  outb(0x61,inb(0x61 | 3));
}

NVALUE switch_speaker_off() {
  outb(0x61,inb(0x61) &~3);
}

NVALUE sound(NUINT freq) {
  NUINT deling;
  deling = 1193180 /freq;
  outb(0x43,0xB6);
  outb(0x42,(unsigned char)deling&0xFF);
  outb(0x42,(unsigned char)(deling >> 8));
  switch_speaker_on();
}
