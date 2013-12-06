#include "numeric.h"

unsigned long long ith_pmf_sum(ith_numeric_pmf_t *p)
{
  unsigned long long s = 0;
  int i;
  for (i=0; i < p->length; i++)
    {
      s += (p->values)[i];
    }
  return s;
}

double ith_pmf_mean(ith_numeric_pmf_t *p) 
{
  return (ith_pmf_sum(p) / p->length);
}

double ith_pmf_entropy2(ith_numeric_pmf_t *p)
{
  double s = 0.0; /* yes, yes, I know... */
  int i;
  for (i = 1; i < p->length; i++)
    {
      if (p->counts[i] != 0)
	{
	  s += p->freqs[i] * log2(p->freqs[i]);
	}  
    }   
  return -(s);
}

double ith_pmf_entropy10(ith_numeric_pmf_t *p)
{
  double s = 0.0; /* yes, yes, I know... */
  int i;
  for (i = 1; i < p->length; i++)
    {
      if (p->counts[i] != 0)
	{
	  s += p->freqs[i] * log10(p->freqs[i]);
	}  
    }   
  return -(s);
}

double ith_pmf_entropye(ith_numeric_pmf_t *p)
{
  double s = 0.0; /* yes, yes, I know... */
  int i;
  for (i = 1; i < p->length; i++)
    {
      if (p->counts[i] != 0)
	{
	  s += p->freqs[i] * log(p->freqs[i]);
	}  
    }   
  return -(s);
}

double ith_pmf_entropy(ith_numeric_pmf_t *p, double base)
{
  double d = log(base);
  double s = 0.0; /* yes, yes, I know... */
  int i;
  for (i = 1; i < p->length; i++)
    {
      if (p->counts[i] != 0)
	{
	  s += p->freqs[i] * log(p->freqs[i]) / d;
	}  
    }   
  return -(s);
}

