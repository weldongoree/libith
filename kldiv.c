#include "kldiv.h"
#include <math.h>
#include <stdio.h>

/* TODO: add functions that look at the whole possible alphabet, not just the
   actual sample */

double find_q(ith_context cxt)
{
  double q;
	  switch (cxt.alphabet)
	    {
	    case BITS:
	      q = 1. / (double) ITH_MAX_BIT;
	      break;
	    case BYTES:
	      q = 1. / (double) ITH_MAX_BYTE;
	      break;
	    case UINT16:
	      q = 1. / (double) ITH_MAX_UINT16;
	      break;
	    case UINT32:
	      q = 1. / (double) ITH_MAX_UINT32;
	      break;
	    case UINT64:
	      q = 1. / (double) ITH_MAX_UINT64;
	      break;
	    default:
	      printf("Full alphabet coverage requires numeric alphabet");
	      q = 1.;
	      break;
	    }
	  return(q);
}

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

double kldivfull(ith_pmf *pmf, double base, ith_context cxt)
{
  double res=0.;
  double q = 0.;
  double div;
  if (pmf->calculated != 0)
    {
      q = find_q(cxt);
      if (pmf && pmf->head)
	{
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

double kldiv2full(ith_pmf *pmf, ith_context cxt)
{
  double res=0.;
  double q = 0.;
  double div;

  if (pmf->calculated != 0)
    {
      if (pmf && pmf->head)
	{
	  q = find_q(cxt);
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

double kldivefull(ith_pmf *pmf, ith_context cxt)
{
  double res=0.;
  double q = 0.;
  double div;

  if (pmf->calculated != 0)
    {
      if (pmf && pmf->head)
	{
	  q = find_q(cxt);
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

double kldiv10full(ith_pmf *pmf, ith_context cxt)
{
  double res=0.;
  double q = 0.;
  double div;

  if (pmf->calculated != 0)
    {
      if (pmf && pmf->head)
	{
	  q = find_q(cxt);
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
