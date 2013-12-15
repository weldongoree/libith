#ifndef ITH_H
#define ITH_H

#define ITH_MAX_BIT 2ULL
#define ITH_MAX_BYTE 0xFFULL
#define ITH_MAX_UINT16 0xFFFFULL
#define ITH_MAX_UINT32 0xFFFFFFFFULL
#define ITH_MAX_UINT64 0xFFFFFFFFFFFFFFFFULL

typedef struct bytebits_ {
  uint8_t bits[8];
} bytebits;

bytebits explode_byte(uint8_t);

#endif
#ifndef __LIBITH_CHISQUARE_H
#define __LIBITH_CHISQUARE_H
#include "pmf.h"

typedef struct chisquare_result_ {
  double chisquare;
  long long degrees;
} chisquare_result;

chisquare_result chisquare(ith_pmf *);

chisquare_result chisquarefull(ith_pmf *, ith_context cxt);

double find_q(ith_context cxt);

double kldiv(ith_pmf *, double);

double kldiv2(ith_pmf *);

double kldive(ith_pmf *);

double kldiv10(ith_pmf *);

double kldivfull(ith_pmf *, double, ith_context);

double kldiv2full(ith_pmf *, ith_context);

double kldivefull(ith_pmf *, ith_context);

double kldiv10full(ith_pmf *, ith_context);

ith_pmf *load_from_file(int fflag, char *fval, ith_context cxt);

void *add_sample_from_file(ith_pmf *pmf, int fflag, char *fval, ith_context cxt);

int next_word(FILE *fp, char *buff, int len);
int next_wword(FILE *fp, wchar_t *buff, int len);

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
  unsigned long long length;
  ith_symbol *head;
  int calculated;
} ith_pmf;

unsigned long long missing_coverage(ith_pmf *, ith_context);

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

#endif /* ITH_H */
