#include "pmf.h"
#include "pmf_array.h"
#include "wchar.h"

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
  ith_symbol *search;
  ith_pmf_array res;
  int i = 0;
  if (!(pmf->calculated))
    {
      return NULL;
    }
  res.size = unit_arraysize(cxt);
  res.length = pmf->length;
  res.vals = calloc(res.length, res.size);
  res.freqs = calloc(res.length, sizeof(double));
  if ((!(res.vals)) || ((!(res.freqs))))
    {
      free(res.vals);
      free(res.freqs);
    }
  
  search = pmf->head;
  while (search)
    {
      switch (cxt.size)
	{
	case BITS:
	case BYTES:
	case CHARS:
	  (res.vals)[i] = (uint8_t) *(search->data);
	  break;
	case UINT16:
	  (res.vals)[i] = (uint16_t) *(search->data);
	  break;
	case UINT32:
	  (res.vals)[i] = (uint32_t) *(search->data);
	  break;
	case UINT64:
	  (res.vals)[i] = (uint64_t) *(search->data);
	  break;
	case WCHARS:
	  (res.vals)[i] = (wchar_t) *(search->data);
	  break;
	default:
	  return NULL;
	}
      i++;
      search = search->next;
    }

  return res;
}

void sort_pmf_array(ith_pmf_array *);

void debug_pmf_array(ith_pmf_array *);

