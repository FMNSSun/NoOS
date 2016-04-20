global loader ; loader für Linker sichtbar machen
extern main   ; main-Funktion des C-Kernels
 
FLAGS    equ 0
MAGIC    equ 0x1BADB002       ; Magicnumber - Erkennungsmerkmal für GRUB
CHECKSUM equ -(MAGIC + FLAGS) ; Checksum
 
section .text
align 4
MultiBootHeader:
  dd MAGIC       ; Magic number
  dd FLAGS       ; Flags
  dd CHECKSUM    ; Checksum
 
loader:
  mov esp,0x600000 ; Stack an die 6MB-Grenze platzieren  ;STACK OVERFLOOOOOOOW MIT 0x400000
  push dword ebx         ; Multiboot Magicnumber auf den Stack legen
  push dword eax         ; Adresse der Multiboot-Structure auf den Stack legen
  call main        ; main-Funktion des C-Kernels aufrufen
 
  cli ; falls der Kernel bis hier her kommt, CPU anhalten
  hlt
;0x001001f4
;0x1004a8
;0x1001ef
