/*
	Memory functions
*/

#include "ntypes.h"

#ifndef NOOS_H_NMEM
#define NOOS_H_NMEM

extern NUSHORT nmem_sid;

extern NVALUE nmem_init();
extern NVALUE nmemset(NPVALUE ptr, NBYTE val, NBIGSIZE size);
extern NVALUE nmemcpy(NPVALUE src, NPVALUE dst, NBIGSIZE size);
extern NVALUE nmemmv(NPVALUE src, NPVALUE dst, NBIGSIZE size);
extern NPVALUE nmemalloc(NBIGSIZE size);
extern NVALUE nmemfree(NPVALUE ptr);

struct NMEM_MALLOC {
  NBIGSIZE size;
  NPVALUE ptr;
}; typedef struct NMEM_MALLOC NMEM_MALLOC; typedef struct NMEM_MALLOC* NPMEM_MALLOC;

#endif
