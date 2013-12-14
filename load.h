#ifndef __ITH_LOAD_H
#define __ITH_LOAD_H
#include <stdio.h>
#include <wchar.h>
#include <wctype.h>
#include <ctype.h>
#include "bits.h"
#include "pmf.h"

ith_pmf *load_from_file(int fflag, char *fval, ith_context cxt);

void *add_sample_from_file(ith_pmf *pmf, int fflag, char *fval, ith_context cxt);

int next_word(FILE *fp, char *buff, int len);
int next_wword(FILE *fp, wchar_t *buff, int len);
#endif
