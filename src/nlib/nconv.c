/*
	Conversions
*/

#include "nconv.h"

NPCHAR nitoa(NINT val, NINT base){
  if(val == 0) {
   static NCHAR b[2] = {0};
   b[0] = '0'; b[1] = 0x00;
   return &b[0];
  }
  static NCHAR buf[32] = {0};
  NINT i = 30;
  for(; val && i ; --i, val /= base)
    buf[i] = "0123456789abcdef"[val % base];
  return &buf[i+1];	
}

NPCHAR nultoa(NULONG value, NUINT radix, NPCHAR string)
{
  NPCHAR dst;
  NCHAR digits[32];
  NINT i, n;
  
  dst = string;
  if (radix < 2 || radix > 36)
    {
      *dst = 0;
      return string;
    }
  i = 0;
  do
    {
      n = value % radix;
      digits[i++] = (n < 10 ? (char)n+'0' : (char)n-10+'a');
      value /= radix;
    } while (value != 0);
  while (i > 0)
    *dst++ = digits[--i];
  *dst = 0;
  return string;
}
