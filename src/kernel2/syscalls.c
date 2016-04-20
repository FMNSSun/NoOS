/*
  Syscalls
*/

#include "../include/syscalls.h"

#include "../include/video.h"
#include "../include/kernel.h"
#include "../include/service.h"
#include "../include/rpc.h"

NULONG ksysinfo() {
  vid_print("NoOS v. 0.8.0\r\n",0x8);
  vid_print("\t\tNoOS (c) Roman Muentener\r\n",0x1);

  return 0;
}

NULONG ksysstop() {
  vid_print("NoOS has been stopped by request\r\n",0x4);
  kstop();

  return 0;
}

NULONG ksysprint(NPCHAR message) {
  vid_print(message,0x7);

  return 0;
}

NULONG ksysreboot() {
  kreboot();

  return 0;
}

NUSHORT ksyssrvcregisterservice(NPCHAR service_name) {
  return srvc_register_service(service_name);
}

NUSHORT ksyssrvcgetid(NPCHAR service_name) {
  return srvc_get_id(service_name);
}

NULONG ksysrpcregisterfunc(NPCHAR funcname,NPVALUE ptr,NUSHORT pid) {
  rpc_register_func(funcname,ptr,pid);

  return 0;
}

NULONG ksysrpccallfunc(NPCHAR name,NUSHORT id,NPVALUE ptr) {
  rpc_call_func(name,id,ptr);

  return 0;
}
