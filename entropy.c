#include "pmf.h"
#include "entropy.h"
#include <math.h>

double entropy2(ith_pmf *alph)
{
  double res=0.;
  if (alph->calculated != 0)
    {
      if (alph && alph->head)
	{
	  ith_symbol *search = alph->head;
	  while (search)
	    {
	      res = res - (search->freq * log2(search->freq));
	      search = search->next;
	    }
	}
    }
  return res;
}

double entropy10(ith_pmf *alph)
{
  double res=0.;
  if (alph->calculated != 0)
    {
      if (alph && alph->head)
	{
	  ith_symbol *search = alph->head;
	  while (search)
	    {
	      res = res - (search->freq * log10(search->freq));
	      search = search->next;
	    }
	}
    }
  return res;
}

double entropye(ith_pmf *alph)
{
  double res=0.;
  if (alph->calculated != 0)
    {
      if (alph && alph->head)
	{
	  ith_symbol *search = alph->head;
	  while (search)
	    {
	      res = res - (search->freq * log(search->freq));
	      search = search->next;
	    }
	}
    }
  return res;
}

double entropy(ith_pmf *alph, double base)
{
  double res=0.;
  if (alph->calculated != 0)
    {
      if (alph && alph->head)
	{
	  ith_symbol *search = alph->head;
	  while (search)
	    {
	      res = res - (search->freq * log(search->freq) / log(base));
	      search = search->next;
	    }
	}
    }
  return res;

}

