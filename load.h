#ifndef __ITH_LOAD_H
#define __ITH_LOAD_H
#include <stdio.h>
#include <wchar.h>
#include <wctype.h>

#include "bits.h"
#include "pmf.h"

typedef enum entropy_base_ {
  BINARY,
  NATURAL,
  DECIMAL,
  CUSTOM
} entropy_base;

typedef enum entropy_alphabet_ {
  BITS,
  BYTES,
  UINT16,
  UINT32,
  UINT64,
  CHARS,
  WORDS
} entropy_alphabet;

typedef struct entropy_context_ {
  entropy_alphabet alphabet;
  entropy_base base;
  int ignore_punctuation;
  int ignore_case;
} entropy_context;

ith_pmf *load_from_file(int fflag, char *fval, entropy_context cxt);

void *add_sample_from_file(ith_pmf *pmf, int fflag, char *fval, entropy_context cxt);

int next_word(FILE *fp, wchar_t *buff, int len);

#endif
