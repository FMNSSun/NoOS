/*
  Syscalls
*/

#include "../nlib/ntypes.h"

#ifndef NOOS_H_SYSCALLS
#define NOOS_H_SYSCALLS

extern NULONG ksysinfo();
extern NULONG ksysstop();
extern NULONG ksysprint(NPCHAR message);
extern NULONG ksysreboot();
extern NUSHORT ksyssrvcregisterservice(NPCHAR service_name);
extern NUSHORT ksyssrvcgetid(NPCHAR service_name);
extern NULONG ksysrpcregisterfunc(NPCHAR funcname,NPVALUE ptr,NUSHORT pid);
extern NULONG ksysrpccallfunc(NPCHAR name,NUSHORT id,NPVALUE ptr);

#endif
