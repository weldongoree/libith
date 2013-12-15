#ifndef __LIBITH_PMF_ARRAY_H
#define __LIBITH_PMF_ARRAY_H

typedef struct ith_pmf_array_ {
  double *freqs;
  int length;
} ith_pmf_array;

ith_pmf_array pmf_to_array(ith_pmf *);

#endif /* __LIBITH_PMF_ARRAY_H */
