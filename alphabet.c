#include "alphabet.h"
#include <string.h>

int ith_symbol_equals(ith_symbol_t *a, ith_symbol_t *b) {
  if (a->size != b->size) {
    return 0;
  }
  if (memcmp(a->data, b->data, a->size)) {
    return (int) a->size;
  }
  return 0;
}

int ith_contains_symbol(ith_alphabet_t *alph, ith_symbol_t *symb)
{
  int idx=0;
  ith_symbol_t *search = alph->head;
  do
    {
      ++idx;
      if ith_symbol_equals(search, symb) {
	  return idx;
	}
    }
  while (search->next);
  return 0;
}

int ith_add_symbol(ith_alphabet_t *alph, ith_symbol_t *symb) {
  if (alph->length == 0) {
    alph->head = symb;
    alph->length = 1;
    return 1;
  }
  if (ith_contains_symbol(alph, symb)) {
    /* no-op */
    return 0;
  }
  ith_symbol_t *search = alph->head;
  while (search->next) {
    search = search->next;
  }
  search->next = symb;
  return ++(alph->length);
}
