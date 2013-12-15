#include "kldiv.h"
#include <math.h>

/* TODO: add functions that look at the whole possible alphabet, not just the
   actual sample */

double kldiv(ith_pmf *pmf, double base)
{
  double res=0.;
  double q = 0.;
  double div;
  if (pmf->calculated != 0)
    {
      if (pmf && pmf->head)
	{
	  q = 1. / pmf->length;
	  ith_symbol *search = pmf->head;
	  while (search)
	    {
	      div = search->freq / q;
	      res = res + (search->freq * log(div) / log(base));
	      search = search->next;
	    }
	}
    }
  return res;
}

double kldiv2(ith_pmf *pmf)
{
  double res=0.;
  double q = 0.;
  double div;

  if (pmf->calculated != 0)
    {
      if (pmf && pmf->head)
	{
	  q = 1. / pmf->length;
	  ith_symbol *search = pmf->head;
	  while (search)
	    {
	      div = search->freq / q;
	      res = res + (search->freq * log2(div));
	      search = search->next;
	    }
	}
    }
  return res;
}

double kldive(ith_pmf *pmf)
{
  double res=0.;
  double q = 0.;
  double div;

  if (pmf->calculated != 0)
    {
      if (pmf && pmf->head)
	{
	  q = 1. / pmf->length;
	  ith_symbol *search = pmf->head;
	  while (search)
	    {
	      div = search->freq / q;
	      res = res + (search->freq * log(div));
	      search = search->next;
	    }
	}
    }
  return res;
}

double kldiv10(ith_pmf *pmf)
{
  double res=0.;
  double q = 0.;
  double div;

  if (pmf->calculated != 0)
    {
      if (pmf && pmf->head)
	{
	  q = 1. / pmf->length;
	  ith_symbol *search = pmf->head;
	  while (search)
	    {
	      div = search->freq / q;
	      res = res + (search->freq * log10(div));
	      search = search->next;
	    }
	}
    }
  return res;
}

