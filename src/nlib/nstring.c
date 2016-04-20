/*
	String functions
*/

#include "nstring.h"

NUINT nstrlen(NPCHAR string) {
  NUINT i=0;
  while(*string){string++;i++;}
  return i;
}


NBYTE nstrcmp(NPCHAR s1,NPCHAR s2) {
  if(nstrlen(s1) != nstrlen(s2)) return 0;
  while((*s1 && *s2)) {
    if(*s1 != *s2) { 
      return 0;
    }
    s1++;s2++;
  }
  return 1;
}
