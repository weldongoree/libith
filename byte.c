#include "numeric.h"
#include <stdlib.h>

ith_numeric_pmf_t *new_byte_pmf(void)
{
  ith_numeric_pmf_t *pmf = malloc(sizeof(ith_numeric_mpf_t));
  if (!pmf) 
    {
      return 0;
    }
  pmf->values = malloc(256 * sizeof(long long));
  if (!(pmf->values))
    { 
      return 0;
    }
  pmf->counts = calloc(256 * sizeof(unsigned long long));
  if (!(pmf->counts))
    {
      return 0;
    }
  pmf->freqs = calloc(256 * sizeof(double));
  if (!(pmf->freqs))
    {
      return 0;
    }
  int i;
  for (i = 0; i < 256; i++)
    {
      pmf->values[i] = (long long) i;
    }
  p->length = 256;
}
