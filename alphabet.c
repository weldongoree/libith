#include "alphabet.h"
#include <string.h>

int ith_symbol_equals(ith_symbol *a, ith_symbol *b) {
  if (a->size != b->size) {
    return 0;
  }
  if (!memcmp(a->data, b->data, a->size)) {
    return (int) a->size;
  }
  return 0;
}

long long ith_contains_symbol(ith_alphabet *alph, ith_symbol *symb)
{
  ith_symbol *search = alph->head;
  do
    {
      if ith_symbol_equals(search, symb) {
	  return search->count;
	}
    }
  while (search->next);
  return 0;
}

long long ith_add_data(ith_alphabet *alph, void *data, size_t size)
{
  ith_symbol *search = alph->head;
  if (!search)
    {
      search = new
      alph->head = search;
      alph->length++;
      
    }
  while (search) {
    if (!memcmp(data, search->data, size))
      {
	search->count++;
        return search->count;
      }
  }
}

size_t get_data_size(ith_symbol *sym)
{
  return sym->size;
}

void * get_data(ith_symbol *sym)
{
      return sym->data;
}

void * load_data(ith_symbol *sym, void *data, size_t size)
{
  if (sym)
    {
      void *tmp = malloc(size);
      if (tmp)
	{
	  memcpy(tmp, data, size);
	  sym->data=tmp;
	}
    }
}

long long ith_add_symbol(ith_alphabet *alph, ith_symbol *symb) {
  ith_symbol *search = alph->head;
  while (search)
    {
      if ith_symbol_equals(search, symb)
			    {
			      search->count++;
			      alph->length++;
			      return symb->count;
			    }
      else
	{
	  search = search->next;
	}
    }
  if (alph->length == 0) {
    alph->head = symb;
    alph->length = 1;
    return (long long) 1;
  }


  search->next = symb;
  symb->count = (long long) 1;
  alph->length++;
  return symb->count;
}

ith_alphabet * new_alphabet() 
{
  ith_alphabet *alph = malloc(sizeof(ith_alphabet));
  if (alph)
    {
      alph->calculated = 0;
      alph->length = 0ULL;
      alph->head = NULL;
    }
  return alph;
}

ith_symbol * new_symbol(char *data, size_t size) 
{
  ith_symbol *symb = malloc(sizeof(ith_symbol));
  if (symb)
    {
      symb->data = calloc(size);
      memcpy(symb->data, data, size);
      symb->size = size;
      symb->count = 0ULL;
      symb->freq = 0.;
      symb->next = NULL;
    }
  return symb;
}

void destroy_symbol(ith_symbol *symb)
{
  if (symb)
    {
      free(symb->data);
    }
  free(symb);
  return;
}

void destroy_alphabet(ith_alphabet *alph)
{
  if (alph)
    {
      if (alph->head)
	{
	  ith_symbol *search;
	  ith_symbol *hold;
	  hold=alph->head;
	  whild (hold)
	  {
	    search=alph->head->next;
	    alph->head=search;
	    destroy_symbol(hold);
	    hold=search;
	  }
	}
      free(alph);
    }
}

long long alphabet_sum(ith_alphabet *alph)
{
  unsigned long long res = 0ULL;
  if (alph && alph->head)
    {
      ith_symbol *search = alph.head;
      while (search)
	{
	  res += search->count;
	  search = search->next;
	}
    }
  return res;
}

void calculate_frequencies(ith_alphabet *alph)
{
  if (alph && alph->head)
    {
      double sum = (double) alphabet_sum(alph);
      ith_symbol search=alph->head;
      while (search)
	{
	  search->freq = (double) search->count / sum;
	}
      alph->calculated=1;
    }
  return;
}

double entropy2(ith_alphabet *alph)
{
  double res=0.;
  if (alph->calculated != 0)
    {
      if (alph && alph->head)
	{
	  ith_symbol search = alph->head;
	  while (search)
	    {
	      res = res - (search->freq * log2(search->freq));
	      search = search->next;
	    }
	}
    }
  return res;
}

double entropy10(ith_alphabet *alph)
{
  double res=0.;
  if (alph->calculated != 0)
    {
      if (alph && alph->head)
	{
	  ith_symbol search = alph->head;
	  while (search)
	    {
	      res = res - (search->freq * log10(search->freq));
	      search = search->next;
	    }
	}
    }
  return res;
}

double entropye(ith_alphabet *alph)
{
  double res=0.;
  if (alph->calculated != 0)
    {
      if (alph && alph->head)
	{
	  ith_symbol search = alph->head;
	  while (search)
	    {
	      res = res - (search->freq * log(search->freq));
	      search = search->next;
	    }
	}
    }
  return res;
}

double entropy(ith_alphabet *alph, double base)
{
  double res=0.;
  if (alph->calculated != 0)
    {
      if (alph && alph->head)
	{
	  ith_symbol search = alph->head;
	  while (search)
	    {
	      res = res - (search->freq * log(search->freq) / log(base));
	      search = search->next;
	    }
	}
    }
  return res;

}
