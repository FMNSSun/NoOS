global irq0_asm		;visible for linker
global irq1_asm
extern handler_pit  	
extern handler_keyboard

irq0_asm:
  pusha
  call handler_pit	;call handler
  popa
  iret			;exit with iret

irq1_asm:
  pusha
  call handler_keyboard ;call handler
  popa
  iret			;exit with iret
