#ifndef _LIBITH_PMF_H
#define _LIBITH_PMF_H

#include "alphabet.h"

typedef struct ith_pmf_ {
  ith_alphabet_t *alphabet;
  int *counts;
  float *freqs;
} ith_pmf_t;

#endif /* _LIBITH_PMF_H */
