global isr0_stub
extern isr0
global isr6_stub
extern isr6
global isr13_stub
extern isr13


isr0_stub:
  push dword 0
  push dword 0
  jmp isr_common

isr6_stub:
  push dword 6
  push dword 0
  jmp isr_common

isr13_stub:
  push dword 13
  push dword 0
  jmp isr_common

isr_common:
  pusha
  push ds
  push es
  push fs
  push gs


  push esp
  call isr0

  pop gs
  pop fs
  pop es
  pop ds

  popa

  add esp,8
  iret
