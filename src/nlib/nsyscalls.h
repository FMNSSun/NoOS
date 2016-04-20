/*
	Syscalls
*/

#include "ntypes.h"

#ifndef NOOS_H_NSYSCALLS
#define NOOS_H_NSYSCALLS

struct SYSCALL_PARAMS {
  NULONG ebx;
  NULONG ecx;
  NULONG edx;
};

extern NULONG syscall_generic(NULONG number,struct SYSCALL_PARAMS p);
extern NVALUE syscall_ksysinfo();
extern NVALUE syscall_ksysstop();
extern NVALUE syscall_ksysprint(NPCHAR message);
extern NVALUE syscall_ksysreboot();

extern NUSHORT syscall_srvc_register_service(NPCHAR service_name);
extern NUSHORT syscall_srvc_get_id(NPCHAR service_name);
extern NVALUE syscall_rpc_register_func(NPCHAR funcname,NPVALUE ptr,NUSHORT pid);
extern NVALUE syscall_rpc_call_func(NPCHAR name,NUSHORT id,NPVALUE ptr);


#endif
