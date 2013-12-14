#ifndef __LIBITH_PMF_H
#define __LIBITH_PMF_H
#include <stdlib.h>

typedef enum ith_base_ {
  BINARY,
  NATURAL,
  DECIMAL,
  CUSTOM
} ith_base;

typedef enum ith_alphabet_ {
  BITS,
  BYTES,
  UINT16,
  UINT32,
  UINT64,
  CHARS,
  WORDS,
  WCHARS,
  WWORDS
} ith_alphabet;

typedef struct ith_context_ {
  ith_alphabet alphabet;
  ith_base base;
  int ignore_punctuation;
  int ignore_case;
} ith_context;

void print_ith_context(ith_context ctx);

typedef struct ith_symbol_ {
  void * data;
  size_t size;
  struct ith_symbol_ *next;
  unsigned long long count;
  double freq;
} ith_symbol;

typedef struct ith_pmf_ {
  int length;
  ith_symbol *head;
  int calculated;
} ith_pmf;

int ith_symbol_equals(ith_symbol *, ith_symbol *);

size_t get_data_size(ith_symbol *);

void * get_data(ith_symbol *);

ith_pmf * new_pmf();

ith_symbol * new_symbol(void *, size_t);

void destroy_symbol(ith_symbol *);

void destroy_pmf(ith_pmf *);

unsigned long long pmf_sum(ith_pmf *);

void calculate_frequencies(ith_pmf *);

unsigned long long ith_add_data(ith_pmf *alph, void *data, size_t size);

void load_data(ith_symbol *, void *, size_t);

double entropy2(ith_pmf *);

double entropy10(ith_pmf *);

double entropye(ith_pmf *);

double entropy(ith_pmf *, double);

void print_ith_pmf(ith_pmf *, ith_context);

#endif /* __LIBITH_PMF_H */
