/*
	Helpers for flags
*/

#include "nflag.h"

NBYTE NCHECK_FLAG(NULONG value,NULONG flag) {
  if((value & (1 << flag)) == (1 << flag)) return 1;
  return 0;
}
