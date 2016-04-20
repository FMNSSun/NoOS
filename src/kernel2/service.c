/*
	Services
*/

#include "../include/service.h"
#include "../nlib/nstring.h"
#include "../nlib/nmem.h"
#include "../include/mem.h"
#include "../include/video.h"
#include "../nlib/nconv.h"
#include "../include/kernel.h"
#include "../include/rpc.h"

#define DEBUG_LVL_ONE

NUSHORT srvc_sid = 1;
NUINT srvc_index = 0;
struct SRVCEntry srvc_entries[SRVC_SIZE];
struct SRVCEntry entry;

NVALUE srvc_init() {
  entry.sid = 0;
  entry.name = (NPVALUE)0;
  NUSHORT i;
  for(i=0;i<SRVC_SIZE;i++) {
    srvc_entries[i] = entry;
  }
  
  NUSHORT srvc_sid = srvc_register_service("service");
  rpc_register_func("srvc_dump",(NPVALUE)srvc_dump,srvc_sid);
}

NVALUE srvc_dump(NPVALUE none) {
  int i;
  for(i=0;i<SRVC_SIZE;i++) {
    if(srvc_entries[i].sid != 0) {
      vid_print(srvc_entries[i].name,0x0A); vid_print (" at ",0x0A); vid_print(nitoa((int)srvc_entries[i].sid,10),0x0A); vid_print("\r\n",0x0A);
    }
  }
}

NUSHORT srvc_register_service(NPCHAR name) {
#ifdef DEBUG_LVL_ONE
  vid_print("[ SRVC ] srvc_register_service: ",0x0A);
  vid_print(name,0x0A);
  vid_print("\r\n",0x07);
#endif
  struct SRVCEntry entry;
  entry.name = (NPCHAR)mem_alloc(nstrlen(name)+1);
#ifdef DEBUG_LVL_ONE
  vid_print("[ SRVC ] Name of service: ",0x0A);
  vid_print(name,0x0A); char buffer[256];
  vid_print(" ptr = ",0x0A); nultoa((NULONG)(NPVALUE)entry.name,16,buffer); vid_print(buffer,0xf);
  vid_print("\r\n",0x0A);
#endif
  NUSHORT i;
  NUINT len = nstrlen(name)+1;
  for(i=0;i<len;i++) {
    entry.name[i] = name[i];
  }
  entry.sid = srvc_sid;
  srvc_sid++;
  srvc_entries[srvc_index] = entry;
#ifdef DEBUG_LVL_ONE
  vid_print("[ SRVC ] Registered as: ",0x0A);
  vid_print(nitoa((int)srvc_entries[srvc_index].sid,10),0x0A);
  vid_print("\r\n",0x07);
#endif
  srvc_index++;
  return entry.sid;
}

NUSHORT srvc_get_id(NPCHAR name) { 
  NUSHORT i;
  for(i=0;i<SRVC_SIZE;i++) {
    
    if(nstrlen(srvc_entries[i].name) != nstrlen(name)) continue;
    if(nstrcmp(srvc_entries[i].name,name) != 1) continue;
#ifdef DEBUG_LVL_TWO
    vid_print("[ SRVC ] Found as: ",0x0A);
    vid_print(nitoa((int)srvc_entries[i].sid,10),0x0A);
    vid_print("\r\n",0x07);
    vid_print(srvc_entries[i].name,0x08);
    vid_print(" /SRVC\r\n",0x08);
#endif
    return srvc_entries[i].sid;
  }
#ifdef DEBUG_LVL_TWO
  vid_print("[ SRVC ] srvc_get_id could not find this service :(\r\n",0x04);
  vid_print(name,0x4);
#endif
  //kstop();
  return 0;
}
