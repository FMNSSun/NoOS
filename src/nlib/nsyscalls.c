/*
	Syscalls
*/

#include "nsyscalls.h"

NVALUE syscall_ksysinfo() {
  struct SYSCALL_PARAMS p;
  p.ebx = 0;
  p.ecx = 0;
  p.edx = 0;
  syscall_generic(0,p);
}

NVALUE syscall_ksysstop() {
  struct SYSCALL_PARAMS p;
  p.ebx = 0;
  p.ecx = 0;
  p.edx = 0;
  syscall_generic(1,p);
}

NVALUE syscall_ksysprint(NPCHAR message) {
  struct SYSCALL_PARAMS p;
  p.ebx = (NULONG)message;
  p.ecx = 0;
  p.edx = 0;
  syscall_generic(2,p);
}

NVALUE syscall_ksysreboot() {
  struct SYSCALL_PARAMS p;
  p.ebx = 0;
  p.ecx = 0;
  p.edx = 0;
  syscall_generic(3,p);
}

NUSHORT syscall_srvc_register_service(NPCHAR service_name) {
  struct SYSCALL_PARAMS p;
  p.ebx = (NULONG)service_name;
  p.ecx = 0;
  p.edx = 0;
  return (NUSHORT)syscall_generic(4,p);
}

NUSHORT syscall_srvc_get_id(NPCHAR service_name) {
  struct SYSCALL_PARAMS p;
  p.ebx = (NULONG)service_name;
  p.ecx = 0;
  p.edx = 0;
  return (NUSHORT)syscall_generic(5,p);
}

NVALUE syscall_rpc_register_func(NPCHAR funcname,NPVALUE ptr,NUSHORT pid) {
  struct SYSCALL_PARAMS p;
  p.ebx = (NULONG)funcname;
  p.ecx = (NULONG)ptr;
  p.edx = (NULONG)pid;
  syscall_generic(6,p);
}

NVALUE syscall_rpc_call_func(NPCHAR name,NUSHORT id,NPVALUE ptr) {
  struct SYSCALL_PARAMS p;
  p.ebx = (NULONG)name;
  p.ecx = (NULONG)id;
  p.edx = (NULONG)ptr;
  syscall_generic(7,p);
}

NULONG syscall_generic(NULONG number,struct SYSCALL_PARAMS p) {
  NULONG returnvalue;
  asm volatile("int $0x81" : "=a"(returnvalue) : "a"(number),"b"(p.ebx),"c"(p.ecx),"d"(p.edx));
  return returnvalue;
}
