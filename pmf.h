#ifndef _LIBITH_PMF_H
#define _LIBITH_PMF_H

#include "alphabet.h"

typedef struct ith_pmf_ {
  ith_alphabet_t *alphabet;
  unsigned long *counts;
  double *freqs;
  int freqed;
} ith_pmf_t;

int load_alphabet(ith_pmf_t *, ith_alphabet_t *);

/* int compute_counts(ith_pmf_t *); */

void compute_freqs(ith_pmf_t *);

double compute_entropy(ith_pmf_t *);

unsigned long long alphabet_sum(ith_pmf_t *);

#endif /* _LIBITH_PMF_H */
