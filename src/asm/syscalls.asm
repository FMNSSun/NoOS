extern ksysinfo
extern ksysstop
extern ksysprint
extern ksysreboot
extern ksyssrvcregisterservice
extern ksyssrvcgetid
extern ksysrpcregisterfunc
extern ksysrpccallfunc
global syscall_handler

syscall_handler:
  cmp eax, 0
  je syscall_0
  cmp eax, 1
  je syscall_1
  cmp eax, 2
  je syscall_2
  cmp eax, 3
  je syscall_3
  cmp eax, 4
  je syscall_4
  cmp eax, 5
  je syscall_5
  cmp eax, 6
  je syscall_6
  cmp eax, 7
  je syscall_7
  iret

  syscall_0:
    call ksysinfo
    iret

  syscall_1:
    call ksysstop
    iret

  syscall_2:
    push ebx
    call ksysprint
    add esp, 4
    iret

  syscall_3:
    call ksysreboot
    iret

  syscall_4:
    push ebx
    call ksyssrvcregisterservice
    add esp, 4
    iret

  syscall_5:
    push ebx
    call ksyssrvcgetid
    add esp, 4
    iret

  syscall_6:
    push edx
    push ecx
    push ebx
    call ksysrpcregisterfunc
    add esp, 12
    iret

  syscall_7:
    push edx
    push ecx
    push ebx
    call ksysrpccallfunc
    add esp, 12
    iret
