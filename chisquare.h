#ifndef __LIBITH_CHISQUARE_H
#define __LIBITH_CHISQUARE_H
#include "pmf.h"

typedef struct chisquare_result_ {
  double chisquare;
  long long degrees;
} chisquare_result;

chisquare_result chisquare(ith_pmf *);

chisquare_result chisquarefull(ith_pmf *, ith_context cxt);

#endif
