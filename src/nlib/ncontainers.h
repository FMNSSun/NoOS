/*
  Containers for NLIB
*/

#include "ntypes.h"

#ifndef NOOS_H_NCONTAINERS
#define NOOS_H_NCONTAINERS

struct NDICTIONARY {
  struct NDICTIONARY_ENTRY* first_entry;
  NULONG entry_count;
}; typedef struct NDICTIONARY NDICTIONARY; typedef struct NDICTIONARY* NPDICTIONARY;

struct NDICTIONARY_ENTRY {
  NPCHAR key;
  NPVALUE value;
  struct NDICTONARY_ENTRY* next_entry;
}; typedef struct NDICTIONARY_ENTRY NDICTIONARY_ENTRY; typedef struct NDICTIONARY_ENTRY* NPDICTIONARY_ENTRY;

#endif

