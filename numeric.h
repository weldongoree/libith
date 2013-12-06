#ifndef _LIBITH_NUMERIC_H
#define _LIBITH_NUMERIC_H

typedef struct ith_numeric_pmf_ 
{
  long long *values;
  unsigned long long *counts;
  double *freqs;
  int length;
} ith_numeric_pmf_t;

unsigned long long ith_pmf_sum(ith_numeric_pmf_t *);

double ith_pmf_mean(ith_numeric_pmf_t *);

double ith_pmf_entropy2(ith_numeric_pmf_t *);

double ith_pmf_entropy10(ith_numeric_pmf_t *);

double ith_pmf_entropye(ith_numeric_pmf_t *);

double ith_pmf_entropy(ith_numeric_pmf_t *, double)

#endif /* _LIBITH_NUMERIC_H */
