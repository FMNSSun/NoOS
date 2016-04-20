/*
	Memory functions
*/

#include "nmem.h"
#include "nsyscalls.h"

NUSHORT nmem_sid = 0;

NVALUE nmem_init() {
  nmem_sid = syscall_srvc_get_id("memory");
}

NPVALUE nmemalloc(NBIGSIZE size) {
  NMEM_MALLOC mstruct;
  mstruct.size = size;
  syscall_rpc_call_func("mem_malloc",nmem_sid,&mstruct);
  return mstruct.ptr;
}

NVALUE nmemfree(NPVALUE ptr) {
  syscall_rpc_call_func("mem_mfree",nmem_sid,ptr);
}

NVALUE nmemset(NPVALUE ptr, NBYTE val, NBIGSIZE size) {
  NPBYTE mptr = (NPBYTE)ptr;
  NINT i = 0;
  for(;i<size;i++) {
    *mptr = val;
    mptr++;
  }
}

NVALUE nmemcpy(NPVALUE src, NPVALUE dst, NBIGSIZE size) {
  NBIGSIZE i;
  NPBYTE p1 = (NPBYTE)src;
  NPBYTE p2 = (NPBYTE)dst;
  for(i=0;i<size;i++) {
    *p2 = *p1;
    p1++;
    p2++;
  }
}

NVALUE nmemmv(NPVALUE src, NPVALUE dst, NBIGSIZE size) {
  nmemcpy(src,dst,size);
  nmemset(src,0,size);
}
