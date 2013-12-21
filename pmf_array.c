#include "pmf.h"
#include "pmf_array.h"
#include "wchar.h"

typedef struct ith_pmf_array_ {
  void *vals;
  double *freqs;
  int length;
  size_t size;
} ith_pmf_array;

size_t array_unitsize(ith_context cxt);

size_t array_unitsize(ith_context cxt)
{
  switch (cxt.size)
    {
    case BITS:
    case BYTES:
    case CHARS:
      return(sizeof(uint8_t));
    case UINT16:
      return(sizeof(uint16_t));
      break;
    case UINT32:
      return(sizeof(uint32_t));
      break;
    case UINT64:
      return(sizeof(uint64_t));
    case WCHARS:
      return(sizeof(wchar_t));
    default:
      return(0);
    }
}

ith_pmf_array pmf_to_array(ith_pmf *pmf, ith_context cxt)
{
  ith_pmf_array res;
  res.size = unit_arraysize(cxt);
  res.length = pmf->length;
  res.vals = calloc(res.length, res.size);
  res.freqs = calloc(res.length, sizeof(double));
  if ((!(res.vals)) || ((!(res.freqs))))
    {
      free(res.vals);
      free(res.freqs);
    }
  return res;
}

void sort_pmf_array(ith_pmf_array *);

void debug_pmf_array(ith_pmf_array *);

