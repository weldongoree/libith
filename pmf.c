#include "pmf.h"
#include "bits.h"
#include "ith.h"
#include <string.h>
#include <stdio.h>

void debug_pmf(ith_pmf *);

size_t lesser_size(ith_symbol *, ith_symbol *);
void sort_pmf(ith_pmf *);
void selection_sort(ith_pmf *);
/* yes, yes, I know... these are generally short enough that it's a better way */
int compare_symbols(ith_symbol *, ith_symbol *);
void debug_symbol(ith_symbol *);

void debug_symbol(ith_symbol *sym)
{
  if (!(sym->data))
    {
      printf("[NULL] ");
    }
  else
    {
      int *foo = sym->data;
      printf("[%c] ", *foo); 
    }
}

int compare_symbols(ith_symbol *a, ith_symbol *b)
{
  size_t sz = lesser_size(a, b);
  int res = memcmp(a->data, b->data, sz);
  if (res < 0)
    {
      return(1);
    }
  else
    {
      return(0);
    }
}

void selection_sort(ith_pmf *pmf)
{
  ith_symbol *start = malloc(sizeof(ith_symbol));
  start->data = NULL;
  start->next = pmf->head;
  pmf->head = start;
  
  ith_symbol *last_sorted = start;
  ith_symbol *search = start->next;
  ith_symbol *min = search;
  ith_symbol *min_prev = start;

  while (last_sorted->next)
    {
      search = last_sorted->next;
      min = search;
      min_prev=last_sorted;
      while (search->next)
	{
	  if (compare_symbols(search->next, min))
	    {
	      min = search->next;
	      min_prev = search;
	    }
	  search = search->next;	  
	}
      min_prev->next = min->next;
      min->next = last_sorted->next;
      last_sorted->next = min;
      last_sorted=min;
    }
  start = pmf->head;
  pmf->head = pmf->head->next;
  free(start);
  return;
}

size_t lesser_size(ith_symbol *a, ith_symbol *b)
{
  if (a->size < b->size)
    {
      return a->size;
    }
  else
    {
      return b->size;
    }
}


void sort_pmf(ith_pmf *pmf)
{
  if (!pmf || !(pmf->head))
    {
      return;
    }
  else
    {
      selection_sort(pmf); 
    }
  return;
}

unsigned long long missing_coverage(ith_pmf *pmf, ith_context ctx)
{
  unsigned long long missing = 0ULL;
  unsigned long long fencepost = pmf->length - 1ULL;
  switch (ctx.alphabet)
    {
    case BITS:
      missing = ITH_MAX_BIT - fencepost;
      break;
    case BYTES:
      missing = ITH_MAX_BYTE - fencepost;
      break;
    case UINT16:
      missing = ITH_MAX_UINT16 - fencepost;
      break;
    case UINT32:
      missing = ITH_MAX_UINT32 - fencepost;
      break;
    case UINT64:
      missing = ITH_MAX_UINT64 - fencepost;
      break;
    default:
      printf("Coverage requires an integer alphabet\n");
    }
  return missing;
}


void print_ith_context(ith_context ctx)
{
  switch (ctx.alphabet)
    {
    case BITS:
      printf("Alphabet: bits\n");
      break;
    case BYTES:
      printf("Alphabet: bytes\n");
      break;
    case UINT16:
      printf("Alphabet: UINT16\n");
      break;
    case UINT32:
      printf("Alphabet: UINT32\n");
      break;
    case UINT64:
      printf("Alphabet: UINT64\n");
      break;
    case CHARS:
      printf("Alphabet: chars\n");
      break;
    case WORDS:
      printf("Alphabet: words\n");
      break;
    case WCHARS:
      printf("Alphabet: wide chars\n");
      break;
    case WWORDS:
      printf("Alphabet: wide words\n");
      break;
    }
  switch (ctx.base)
    {
    case BINARY:
      printf("Base: binary\n");
      break;
    case NATURAL:
      printf("Base: natural\n");
      break;
    case DECIMAL:
      printf("Base: decimal\n");
      break;
    case CUSTOM:
      printf("Base: custom\n");
      break;
    }
}


int ith_symbol_equals(ith_symbol *a, ith_symbol *b) {
  if (a->size != b->size) {
    return 0;
  }
  if (!memcmp(a->data, b->data, a->size)) {
    return (int) a->size;
  }
  return 0;
}

unsigned long long ith_add_data(ith_pmf *alph, void *data, size_t size)
{
  ith_symbol *search = alph->head;
  if (!search)
    {
      search = new_symbol(data, size);
	if (search)
	  {
	    search->count=1ULL;
	    alph->head = search;
	    alph->length++;
	  }
    }
  else 
    {
      while (search) {
	if (!memcmp(data, search->data, size))
	  {
	    search->count++;
	    return search->count;
	  }
	else
	  {
	    if (search->next)
	      {
		search = search->next;
	      }
	    else
	      {
		ith_symbol *tmp = new_symbol(data, size);
		tmp->count = 1ULL;
		search->next = tmp;
		alph->length++;
		return tmp->count;
	      }
	  }
      }
    }
  return 0ULL;
}

size_t get_data_size(ith_symbol *sym)
{
  return sym->size;
}

void * get_data(ith_symbol *sym)
{
      return sym->data;
}

void load_data(ith_symbol *sym, void *data, size_t size)
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

ith_pmf * new_pmf() 
{
  ith_pmf *alph = malloc(sizeof(ith_pmf));
  if (alph)
    {
      alph->calculated = 0;
      alph->length = 0ULL;
      alph->head = NULL;
    }
  return alph;
}

ith_symbol * new_symbol(void *data, size_t size) 
{
  ith_symbol *symb = malloc(sizeof(ith_symbol));
  if (symb)
    {
      symb->data = malloc(size);
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

void destroy_pmf(ith_pmf *alph)
{
  if (alph)
    {
      if (alph->head)
	{
	  ith_symbol *search;
	  ith_symbol *hold;
	  hold=alph->head;
	  while (hold)
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

unsigned long long pmf_sum(ith_pmf *alph)
{
  unsigned long long res = 0ULL;
  if (alph && alph->head)
    {
      ith_symbol *search = alph->head;
      while (search)
	{
	  res += search->count;
	  search = search->next;
	}
    }
  return res;
}

void calculate_frequencies(ith_pmf *alph)
{
  if (alph && alph->head)
    {
      double sum = (double) pmf_sum(alph);
      ith_symbol *search=alph->head;
      while (search)
	{
	  search->freq = (double) search->count / sum;
	  search = search->next;
	}
      alph->calculated=1;
    }
  return;
}
void print_ith_pmf(ith_pmf *pmf, ith_context cxt)
{
  int *dataptr;
  int count;
  if (!pmf)
    {
      printf("Trying to print void PMF; bye\n");
      return;
    }
  if (!(pmf->head))
    {
      printf("Trying to print PMF with no nodes; bye\n");
      return;
    }
  ith_symbol *search = pmf->head;

  while (search)
    {
      dataptr = search->data;
      count = (int) search->count;
      if (cxt.alphabet == WORDS)
	{
	  printf("Node: %s\n", (char *) dataptr);
	  printf("Strlen: %d\n", (int) (search->size));
	}
      else
	{
	  printf("Node: %d\n", *dataptr);
	}
      printf("Count: %d\n", count);
      printf("Freq: %f\n", search->freq);
      printf("\n");
      search = search->next;
    }
  printf("Total length: %llu\n", pmf->length);
  printf("Sum: %d\n", (int) pmf_sum(pmf));
}


void debug_pmf(ith_pmf *pmf)
{
  ith_symbol *search = pmf->head;
  while(search)
    {
      debug_symbol(search);
      search = search->next;
    }
  printf("\n");
}
