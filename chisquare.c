#include <math.h>
#include <stdio.h>

#include "chisquare.h"
#include "pmf.h"
#include "kldiv.h"

chisquare_result chisquare(ith_pmf *pmf)
{
  chisquare_result chisq;
  double res = 0.;
  double e = 1. / (double) pmf->length;
  double obs = 0.;
  ith_symbol *search;
  long long len;
  len = pmf->length;
  if (pmf && pmf->head)
    {
      if (!(pmf->calculated))
	{
	  calculate_frequencies(pmf);
	}
      search = pmf->head;
      while (search)
	{
	  obs = (search->freq) - e;	  
	  res += pow(obs, 2.) / e;
	  search = search->next;
	}	      
    }
  chisq.chisquare = res;
chisq.degrees = len - 1;
return chisq;  
}

chisquare_result chisquarefull(ith_pmf *pmf, ith_context cxt)
{
  chisquare_result chisq;
  double res = 0.;
  double e = find_q(cxt);
  double obs = 0.;
  ith_symbol *search;
  long long len;
  len = pmf->length;
  if (pmf && pmf->head)
    {
      if (!(pmf->calculated))
	{
	  calculate_frequencies(pmf);
	}
      search = pmf->head;
      while (search)
	{
	  obs = (search->freq) - e;	  
	  res += pow(obs, 2.) / e;
	  search = search->next;
	}	      
    }
  chisq.chisquare = res;
  chisq.degrees = len - 1;
  return chisq;  
}

