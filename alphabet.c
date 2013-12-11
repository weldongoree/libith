#include "alphabet.h"
#include <string.h>

int ith_symbol_equals(ith_symbol *a, ith_symbol *b) {
  if (a->size != b->size) {
    return 0;
  }
  if (memcmp(a->data, b->data, a->size)) {
    return (int) a->size;
  }
  return 0;
}

int ith_contains_symbol(ith_alphabet *alph, ith_symbol *symb)
{
  int idx=0;
  ith_symbol *search = alph->head;
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

int ith_add_symbol(ith_alphabet *alph, ith_symbol *symb) {
  if (alph->length == 0) {
    alph->head = symb;
    alph->length = 1;
    return 1;
  }

  ith_symbol *search = alph->head;
  while (search)
    {
      if ith_symbol_equals(search, symb)
			    {
			      search->count += 1;
			      alph->length++;
			      return alph->length;
			    }
      else if (!search->next)
	{
	  search->next = symb;
	  symb.count = 1;
	  alph->length++;
	  return alph->length;
	}
      else
	{
	  search = search->next;
	}
    }
  /* should not reach here */
  return -1;
}

int ith_remove_symbol(ith_alphabet *alph, ith_symbol *symb) {
  if (alph->length == 0) {
    return 0;
  }
  ith_symbol *search = alph->head;
  while (search) {
    

  }

}
