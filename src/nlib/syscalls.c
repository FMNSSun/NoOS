/*
	Syscalls
*/

#include "syscalls.h"

NUSHORT (*__srvc_get_id)(NPCHAR service) = (NUSHORT(*)(NPCHAR))(0x100000);
NUSHORT (*__srvc_register_service)(NPCHAR service) = (NUSHORT(*)(NPCHAR))(0x100000 + 0x4);
NVALUE (*__rpc_register_func)(NPCHAR funcname,NPVALUE ptr,NUSHORT pid) = (NVALUE(*)(NPCHAR,NPVALUE,NUSHORT))(0x100000 + 0x4 + 0x4);
NVALUE (*__rpc_call_func)(NPCHAR name,NUSHORT id,NPVALUE ptr) = (NVALUE(*)(NPCHAR,NUSHORT,NPVALUE))(0x100000 + 0x4 + 0x4 + 0x4);
