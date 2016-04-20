/*
	Syscalls
*/

#include "ntypes.h"

#ifndef NOOS_H_SYSCALLS
#define NOOS_H_SYSCALLS

NUSHORT (*__srvc_get_id)(NPCHAR service);
NUSHORT (*__srvc_register_service)(NPCHAR service);
NVALUE (*__rpc_register_func)(NPCHAR funcname,NPVALUE ptr,NUSHORT pid);
NVALUE (*__rpc_call_func)(NPCHAR name,NUSHORT id,NPVALUE ptr);

#endif
