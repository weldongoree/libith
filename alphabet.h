#include <stdlib.h>

typedef struct ith_symbol_ {
  void * data;
  size_t size;
  struct ith_symbol_ *next;
  unsigned long long count;
  double freq;
} ith_symbol;

typedef struct ith_alphabet_ {
  int length;
  ith_symbol *head;
  int calculated;
} ith_alphabet;

int ith_symbol_equals(ith_symbol *, ith_symbol *);

size_t get_data_size(ith_symbol *);

void * get_data(ith_symbol *);

ith_alphabet * new_alphabet();

ith_symbol * new_symbol(void *, size_t);

void destroy_symbol(ith_symbol *);

void destroy_alphabet(ith_alphabet *);

unsigned long long alphabet_sum(ith_alphabet *);

void calculate_frequencies(ith_alphabet *);

unsigned long long ith_add_data(ith_alphabet *alph, void *data, size_t size);

void load_data(ith_symbol *, void *, size_t);

double entropy2(ith_alphabet *);

double entropy10(ith_alphabet *);

double entropye(ith_alphabet *);

double entropy(ith_alphabet *, double base);

