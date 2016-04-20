/*
	Remote Procedure Call
*/

#include "../nlib/ntypes.h"

#ifndef NOOS_H_RPC
#define NOOS_H_RPC

#define RPC_SIZE 10000

struct RPCFuncEntry {
  NPCHAR func;
  NPVALUE ptr;
  NUSHORT pid;
} __attribute__((packed));

extern struct RPCFuncEntry rpc_entries[];

extern NVALUE rpc_init();
extern NVALUE rpc_register_func(NPCHAR funcname,NPVALUE ptr,NUSHORT pid);
extern NVALUE rpc_call_func(NPCHAR name,NUSHORT id,NPVALUE ptr);
extern NVALUE rpc_dump(NPVALUE ptr);
extern NVALUE rpc_init_srvc();

#endif
