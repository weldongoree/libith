#ifndef _LIBITH_ALPHABET_H
#define _LIBITH_ALPHABET_H

typedef struct ith_symbol_ {
  void * data;
  int length;
  struct ith_symbol_ *next;
} ith_symbol_t;

typedef struct ith_alphabet_ {
  int length;
  char *name;
} ith_alphabet_t;

bool contains_symbol(ith_alphabet_t *, ith_symbol_t *);

int add_symbol(ith_alphabet_t *, ith_symbol_t *);



#endif /* _LIBITH_ALPHABET_H */
