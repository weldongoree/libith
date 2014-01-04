#ifndef __LIBITH_PMF_ARRAY_H
#define __LIBITH_PMF_ARRAY_H

#include "pmf.h"

typedef struct ith_pmf_array_ {
  void *vals;
  double *freqs;
  int length;
  size_t size;
} ith_pmf_array;

ith_pmf_array pmf_to_array(ith_pmf *, ith_context);

void sort_pmf_array(ith_pmf_array *);

void debug_pmf_array(ith_pmf_array *);

#endif /* __LIBITH_PMF_ARRAY_H */
