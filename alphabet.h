#include <stddef.h>

typedef struct ith_symbol_ {
  void * data;
  size_t size;
  struct ith_symbol_ *next;
  long long count;
  double freq;
} ith_symbol;

typedef struct ith_alphabet_ {
  int length;
  char *name;
  ith_symbol *head;
  int calculated;
} ith_alphabet;

int ith_contains_symbol(ith_alphabet *, ith_symbol *);

int ith_add_symbol(ith_alphabet *, ith_symbol *);

ith_symbol * ith_retrieve_nth(int, ith_alphabet *);

int ith_symbol_equals(ith_symbol *, ith_symbol *);


#endif /* _LIBITH_ALPHABET_H */
