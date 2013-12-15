#ifndef __LIBITH_KLDIV_H
#define __LIBITH_KLDIV_H

#include "pmf.h"

double find_q(ith_context cxt);

double kldiv(ith_pmf *, double);

double kldiv2(ith_pmf *);

double kldive(ith_pmf *);

double kldiv10(ith_pmf *);

double kldivfull(ith_pmf *, double, ith_context);

double kldiv2full(ith_pmf *, ith_context);

double kldivefull(ith_pmf *, ith_context);

double kldiv10full(ith_pmf *, ith_context);


#endif
