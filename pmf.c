#include "pmf.h"
#include <stdlib.h>

int load_alphabet(ith_pmf_t *p, ith_alphabet_t *a) {
  p->alphabet = a;
  p->counts = malloc(a->length * sizeof(int));
  if (!(p->counts))
    {
      return 0;
    }
  p->freqs = malloc(a->length * sizeof(double));
  if (!(p->freqs))
    {
      return 0;
    }
  return a->length;
}

unsigned long long alphabet_sum(ith_pmf_t *p) {
  unsigned long long sum = 0;
  int i;
  for (i = 0; i < p->alphabet->length; i++) 
    {
      sum += (unsigned long long) p->counts[i];
    }
  return sum;
}


void compute_freqs(ith_pmf_t *p) {
  double sum = (double) alphabet_sum(p);
  int i;
  for (i=0; i < p->alphabet->length; i++)
    {
      p->freqs[i] = p->counts[i] / sum;
    }
  p->freqed=1;
}

double compute_entropy2(ith_pmf_t *p) 
{
  double entropy = 0; /* this needs to be done better; don't initialize a double to zero...  */
  int i;
  for (i=0; i < p->alphabet->count; i++)
    {
      entropy += p->freqs[i] * log2(p->freqs[i]);
    }
  entropy = -entropy;
}

double compute_entropy10(ith_pmf_t *p) 
{
  double entropy = 0; /* this needs to be done better; don't initialize a double to zero...  */
  int i;
  for (i=0; i < p->alphabet->count; i++)
    {
      entropy += p->freqs[i] * log10(p->freqs[i]);
    }
  entropy = -entropy;
}

double compute_entropye(ith_pmf_t *p) 
{
  double entropy = 0; /* this needs to be done better; don't initialize a double to zero...  */
  int i;
  for (i=0; i < p->alphabet->count; i++)
    {
      entropy += p->freqs[i] * log(p->freqs[i]);
    }
  entropy = -entropy;
}

/* NB these next few make little sense for textual alphabets... */

double pmf_mean(ith_pmf_t *p) 
{
  
}
