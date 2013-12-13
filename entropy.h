#ifndef __LIBITH_ENTROPY_H
#define __LIBITH_ENTROPY_H

#include "alphabet.h"

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

#endif
