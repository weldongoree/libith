#include "pmf.h"
#include <stdlib.h>

int load_alphabet(ith_pmf_t *p, ith_alphabet_t *a) {
  p->alphabet = a;
  p->counts = malloc(a->length * sizeof(int));
  if (!(p->counts))
    {
      return 0;
    }
  p->freqs = malloc(a->length * sizeof(float));
  if (!(p->freqs))
    {
      return 0;
    }
  return a->length;
}

int compute_counts(ith_pmf_t *p) {
  
}
