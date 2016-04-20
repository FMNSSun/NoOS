/*
	Memory management
*/

#include "../nlib/ntypes.h"
#include "../nlib/nmem.h"

#ifndef NOOS_H_MEM
#define NOOS_H_MEM

#define MEM_BEGIN_ADDR (0x600000 + 0xF)
#define MEM_USED '?'
#define MEM_UNUSED '!'


struct _MMHeader {
  NBYTE flag;
  NBIGSIZE length;
  NADDR next_header;
};

typedef struct _MMHeader MMHeader;

//Stats
extern NUINT mem_average_alloc;
extern NBIGSIZE mem_allocs;

extern NPVALUE mem_create_header(MMHeader* header,NBIGSIZE size);
extern NPVALUE mem_alloc(NBIGSIZE size);
extern NVALUE mem_free(NPVALUE ptr);
extern NVALUE mem_init(NADDR addr);
extern NVALUE mem_get_average_alloc(NPUINT average_alloc);
extern NVALUE mem_init_srvc();
extern NVALUE mem_get_usage(NPBIGSIZE mem_usage);
extern NVALUE mem_get_dead(NPBIGSIZE mem_dead);
extern NVALUE mem_get_allocs(NPBIGSIZE allocs);
extern NVALUE mem_malloc(NPMEM_MALLOC mstruct);
extern NVALUE mem_mfree(NPVALUE ptr);

#endif
