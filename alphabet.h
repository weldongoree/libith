#ifndef _LIBITH_ALPHABET_H
#define _LIBITH_ALPHABET_H

#include <stddef.h>

typedef struct ith_symbol_ {
  void * data;
  size_t size;
  struct ith_symbol_ *next;
} ith_symbol_t;

typedef struct ith_alphabet_ {
  int length;
  char *name;
  ith_symbol_t *head;
} ith_alphabet_t;

int ith_contains_symbol(ith_alphabet_t *, ith_symbol_t *);

int ith_add_symbol(ith_alphabet_t *, ith_symbol_t *);

ith_symbol_t * ith_retrieve_nth(int, ith_alphabet_t *);

int ith_symbol_equals(ith_symbol_t *, ith_symbol_t*);

#endif /* _LIBITH_ALPHABET_H */
