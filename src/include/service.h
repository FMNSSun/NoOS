/*
	Services
*/

#include "../nlib/ntypes.h"

#ifndef NOOS_H_SERVICE
#define NOOS_H_SERVICE

#define SRVC_SIZE 2048
struct SRVCEntry {
  NPCHAR name;
  NUSHORT sid;
};

extern NUSHORT srvc_sid;
extern NUINT srvc_index;
extern struct SRVCEntry srvc_entries[];

extern NVALUE srvc_init();
extern NVALUE srvc_dump(NPVALUE none);
extern NUSHORT srvc_register_service(NPCHAR name);
extern NUSHORT srvc_get_id(NPCHAR name);
#endif
