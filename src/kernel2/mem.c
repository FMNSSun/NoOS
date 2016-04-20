/*
	Memory Management
*/

#include "../include/kernel.h"
#include "../include/mem.h"
#include "../include/video.h"
#include "../include/rpc.h"
#include "../include/service.h"

#include "../nlib/nconv.h"

#define DEBUG

NADDR mem_mbi;
NUINT mem_average_alloc;
NBIGSIZE mem_allocs;

NVALUE mem_init(NADDR addr) {
  /* Save address */
  mem_mbi = addr;

  /* Set up the first header */
  MMHeader* first_header = (MMHeader*)MEM_BEGIN_ADDR;
  first_header->flag = MEM_USED;
  first_header->length = 4096;
  first_header->next_header = NULL;
  mem_average_alloc = 4096;
  mem_allocs = 1;
}

NVALUE mem_init_srvc() {
  /* Register as service */
  NUSHORT mem_sid = srvc_register_service("memory");
  rpc_register_func("mem_get_average_alloc",(NPVALUE)mem_get_average_alloc,mem_sid);
  rpc_register_func("mem_get_usage",(NPVALUE)mem_get_usage,mem_sid);
  rpc_register_func("mem_get_dead",(NPVALUE)mem_get_dead,mem_sid);
  rpc_register_func("mem_get_allocs",(NPVALUE)mem_get_allocs,mem_sid);
  rpc_register_func("mem_malloc",(NPVALUE)mem_malloc,mem_sid);
  rpc_register_func("mem_mfree",(NPVALUE)mem_mfree,mem_sid);
}

NVALUE mem_malloc(NPMEM_MALLOC mstruct) {
  mstruct->ptr = mem_alloc(mstruct->size);
}

NVALUE mem_mfree(NPVALUE ptr) {
  mem_free(ptr);
}

NVALUE mem_get_average_alloc(NPUINT average_alloc) {
  *average_alloc = mem_average_alloc;
}

NVALUE mem_get_allocs(NPBIGSIZE allocs) {
  *allocs = mem_allocs;
}

NVALUE mem_get_usage(NPBIGSIZE mem_usage) {
  /* Find free space */
  MMHeader* header = (MMHeader*)MEM_BEGIN_ADDR;
  while(1) {
    /* Is this memory region used? */
    if(header->flag == MEM_USED) {
      *mem_usage += header->length;
    }
    /* There is a next header? */
    if(header->next_header != NULL) {
      header = (MMHeader*)header->next_header;
      continue;
    } else { break; }
  }
}

NVALUE mem_get_dead(NPBIGSIZE mem_dead) {
  /* Find free space */
  MMHeader* header = (MMHeader*)MEM_BEGIN_ADDR;
  while(1) {
    /* Is this memory region used? */
    if(header->flag == MEM_UNUSED) {
      *mem_dead += header->length;
    }
    /* There is a next header? */
    if(header->next_header != NULL) {
      header = (MMHeader*)header->next_header;
      continue;
    } else { break; }
  }
}

NVALUE mem_free(NPVALUE ptr) {
  if(mem_allocs == 0)
    panic("Ooops... Memory seems to be corrupted!");
  if(ptr == NULL)
    panic("Ooops... Memory seems to be corrupted!");  

  MMHeader* header = (MMHeader*)(ptr-sizeof(MMHeader));
  header->flag = MEM_UNUSED;
#ifdef DEBUG
  char buffer[256];
  vid_print("[malloc] freeing header: ptr = ",0x2);
  nultoa((NULONG)header + sizeof(MMHeader),16,buffer);
  vid_print(buffer,0x2);
  vid_print(" header = ",0x2);
  nultoa((NULONG)header,16,buffer); vid_print(buffer,0x2);
  vid_print("\r\n",0x2);
#endif
}

NPVALUE mem_alloc(NBIGSIZE size) {
#ifdef DEBUG
  char buffer[256];

  nultoa(size,10,buffer);
  vid_print("[malloc] mem_alloc: NBIGSIZE (0) = ",0x2);
  vid_print(buffer,0x2);
  vid_print("\r\n",0x2);
#endif
  /* Update stats */
  mem_allocs++;
  mem_average_alloc = (mem_average_alloc + size) / 2;

  /* Find free space */
  MMHeader* header = (MMHeader*)MEM_BEGIN_ADDR;
  while(1) {
    /* Is this memory region used? */
    if(header->flag == MEM_USED) {
#ifdef DEBUGn
      vid_print("[malloc] mem_alloc: Header = USED at: ",0x2);
      nultoa((NULONG)header,16,buffer);
      vid_print(buffer,0x2);
      vid_print(" dump = ",0x2); vid_print((char*)header+sizeof(MMHeader),0x2);
      vid_print(" next_header = ",0x2); nultoa((NULONG)header->next_header,16,buffer); vid_print(buffer,0x2);
      vid_print(" len = ",0x2); nultoa((NULONG)header->length,10,buffer); vid_print(buffer,0x2);
      vid_print("\r\n",0x2);
      unsigned int i = 0;
      for(i=0;i < 1024*1024*10;i++) { asm("nop"); asm("nop"); }
#endif
      /* There is a next header? */
      if(header->next_header != NULL) {
        header = (MMHeader*)header->next_header;
        continue;
      }
      else {
        /* So we must create a header */
        return mem_create_header(header,size);
      }
    }
    if(header->flag == MEM_UNUSED) {
      /* Is there enough free space left? */
      if(header->length >= size) {
        header->flag = MEM_USED; //Allocate it!
        char buffer[256];
#ifdef DEBUG
        vid_print("[malloc] reusing header: ptr = ",0x2);
        nultoa((NULONG)header + sizeof(MMHeader),16,buffer);
        vid_print(buffer,0x2);
        vid_print(" header = ",0x2);
        nultoa((NULONG)header,16,buffer); vid_print(buffer,0x2);
        vid_print("\r\n",0x2);
#endif
        return (NPVALUE)((NULONG)header + sizeof(MMHeader));
      }
      /* There is a next header? */
      if(header->next_header != NULL) {
        header = (MMHeader*)header->next_header;
        continue;
      }
      else {
        /* So we must create one */
        return mem_create_header(header,size);
      }
    }
  }
}

NPVALUE mem_create_header(MMHeader* header,NBIGSIZE size) {
  MMHeader* new_header = ((MMHeader*)((NADDR)header + sizeof(MMHeader) + header->length));
  header->next_header = (NADDR)new_header; //Set next header of previous header
  new_header->flag = MEM_USED;
  new_header->length = size;
  new_header->next_header = NULL;
#ifdef DEBUG
  char buffer[256];
  vid_print("[malloc] mem_create_header: ptr = ",0x2);
  nultoa((NULONG)new_header + sizeof(MMHeader),16,buffer);
  vid_print(buffer,0x2);
  vid_print(" header = ",0x2);
  nultoa((NULONG)new_header,16,buffer); vid_print(buffer,0x2);
  vid_print("\r\n",0x2);
#endif
  return (NPVALUE)((NULONG)new_header + sizeof(MMHeader));
}
