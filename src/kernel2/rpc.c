/*
	Remote Procedure Call
*/

#include "../include/rpc.h"
#include "../include/mem.h"
#include "../nlib/nstring.h"
#include "../include/kernel.h"
#include "../include/video.h"
#include "../include/service.h"
#include "../nlib/nconv.h"

#define DEBUG

struct RPCFuncEntry rpc_entries[RPC_SIZE];
struct RPCFuncEntry entry;
NUINT rpc_index = 0;


NVALUE rpc_init() {
  entry.ptr = (NPVALUE)0;
  entry.pid = 0;
  entry.func = (NPVALUE)0;
  NUINT i;
  for(i=0;i<RPC_SIZE;i++) {
    rpc_entries[i] = entry;
  }
}

NVALUE rpc_init_srvc() {
  NUSHORT rpc_sid = srvc_register_service("rpc");
  rpc_register_func("rpc_dump",&rpc_dump,rpc_sid);
}

NVALUE rpc_dump(NPVALUE ptr) {
  NUINT i;
  for(i=0;i<RPC_SIZE;i++) {
    if(rpc_entries[i].pid == 0) continue;
    vid_print(rpc_entries[i].func,0x03); vid_print(" with id ",0x03);
    vid_print(nitoa((NINT)rpc_entries[i].pid,10),0x03); vid_print("\r\n",0x03);
  }
}


NVALUE rpc_register_func(NPCHAR funcname,NPVALUE ptr,NUSHORT pid) {
  struct RPCFuncEntry entry;
  entry.func = (NPCHAR)mem_alloc(nstrlen(funcname)+1);
  NUINT i;
  NUINT len = nstrlen(funcname)+1;
#ifdef DEBUG
  vid_print("[ RPC ] rpc_register_func: ",0x03);
  vid_print(funcname,0x07);
  vid_print("\r\n",0x07);
#endif
  for(i=0;i<len;i++) {
    entry.func[i] = funcname[i];
  }
  entry.ptr = ptr;
  entry.pid = pid;
  rpc_entries[rpc_index] = entry;
  rpc_index++;
}

NVALUE rpc_call_func(NPCHAR name,NUSHORT id,NPVALUE ptr) {
  NUINT i;
  for(i=0;i<RPC_SIZE;i++) {
    if(rpc_entries[i].pid != id) continue;
    if(nstrlen(name) != nstrlen(rpc_entries[i].func)) continue;
    if(nstrcmp(name,rpc_entries[i].func) != 1) continue;
    NVALUE (*p)(NPVALUE);
    p = rpc_entries[i].ptr;
    (*p)(ptr);
    return;
  }
#ifdef DEBUG
  vid_print("[ RPC ] Call to not registered function: ",0x03);
  vid_print(name,0x03);vid_print("\r\n",0x03);
#endif
}
