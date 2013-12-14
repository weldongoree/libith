#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wchar.h>
#include <string.h>

#include "pmf.h"
#include "load.h"
#include "chisquare.h"
#include "ith.h"
#include "bits.h"
#include "kldiv.h"

void usage()
{
  /*RULER |-----------------------------------------------------------------------------| */
  printf("ith [COMMAND] [OPTIONS]\n\n");
  printf("COMMAND is zero or more of:\n");
  printf("-e entropy (this is the default if no command is specified)\n");
  printf("-c domain coverage\n");
  printf("-k Killback-Leibler divergence\n");
  printf("-x Pearson chi-squared for randomness\n");
  printf("-p print the resulting PMF\n");
  printf("-A equivalent to -e -c -k -x\n\n");
  printf("OPTIONS are zero or more of:\n");
  printf("-a 1 | 8 | 16 | 32 | 64 | char | wchar | word | wword (default is 8)\n");
  printf("-u 2 | e | 10 (default is 2)\n");
  printf("-f FILENAME (default is stdin)\n");
  printf("-t print tersely (just the numbers, no sentences)\n\n");
  printf("See ith(1) for more information.\n");
  return;
}

int main(int argc, char **argv) 
{
  int aflag = 0;
  int cflag = 0;
  int eflag = 1;
  int fflag = 0;
  int pflag = 0;
  int hflag = 0;
  int iflag = 0;
  int kflag = 0;
  int xflag = 0;
  int tflag = 0;
  int uflag = 0;

  unsigned long long miss = 0ULL;
  unsigned long long all_possible = ITH_MAX_BYTE;

  double ent = 0.;
  double kl = 0.;
  double misspercent = 0.;

  char *uval=NULL;
  char *aval=NULL;
  char *fval=NULL;
  char *inval=NULL;
  char *onval=NULL;

  ith_pmf *pmf;

  ith_context cxt;

  chisquare_result chisq;

  cxt.alphabet = BYTES;
  cxt.base = BINARY;
  cxt.ignore_punctuation = 0;


  int c;

  while ((c = getopt (argc, argv, "Aa:cef:hikptu:x")) != -1)
    {
      switch (c)
	{
	case 'A':
	  eflag=1;
	  xflag=1;
	  cflag=1;
	  kflag=1;
	  break;
	case 'a':
	  aflag=1;
	  aval=optarg;
	  break;
	case 'c':
	  cflag=1;
	  eflag=0;
	  break;
	case 'e':
	  break;
	case 'f':
	  fflag=1;
	  fval=optarg;
	  break;
	case 'h':
	  eflag=0;
	  hflag=1;
	  break;
	case 'i':
	  iflag=1;
	  break;
	case 'k':
	  eflag=0;
	  kflag=1;
	  break;
	case 'p':
	  eflag=0;
	  pflag=1;
	  break;
	case 't':
	  tflag=1;
	  break;
	case 'u':
	  uflag=1;
	  uval=optarg;
	  break;
	case 'x':
	  eflag=0;
	  xflag=1;
	  break;
	case '?':
	  if ('a' == optopt || 'f' == optopt || 'u' == optopt)
	    {
	      fprintf(stderr, "Option -%c requires an argument\n", optopt);
	    }
	  else if (isprint (optopt))
	    fprintf (stderr, "Unknown option `-%c'.\n", optopt);
	  else
	    fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt); 
	  return 1;
      	default:
	  abort(); 
	}
    }
  if (hflag) {
    usage();
    return(0);
  }

  if (iflag)
    {
      cxt.ignore_punctuation = 1;
    }

  if (aflag)
    {
      if (!strcmp(aval, "1"))
	{
	  cxt.alphabet=BITS;
	  onval="bit";
	  all_possible = ITH_MAX_BIT;
	}
      else if (!strcmp(aval, "8"))
	{
	  cxt.alphabet=BYTES;
	  onval="byte";
	  all_possible = ITH_MAX_BYTE;
	}
      else if (!strcmp(aval, "16"))
	{
	  cxt.alphabet=UINT16;
	  onval="16-bit short";
	  all_possible=ITH_MAX_UINT16;
	}
      else if (!strcmp(aval, "32"))
	{
	  cxt.alphabet=UINT32;
	  onval="32-bit int";
	  all_possible=ITH_MAX_UINT32;
	}
      else if (!strcmp(aval, "64"))
	{
	  cxt.alphabet=UINT64;
	  onval="64-bit int";
	  all_possible=ITH_MAX_UINT64;
	}
      else if (!strcmp(aval, "char"))
	{
	  cxt.alphabet=CHARS;
	  onval="8-bit character";
	}
      else if (!strcmp(aval, "word"))
	{
	  cxt.alphabet=WORDS;
	  onval="alphabetical word";
	}
      else if (!strcmp(aval, "wchar"))
	{
	  cxt.alphabet=WCHARS;
	  onval="wide character";
	}
      else if (!strcmp(aval, "wword"))
	{
	  cxt.alphabet=WWORDS;
	  onval="wide character word";
	}
    }
  else
    {
      onval="byte";
    }

  if (uflag)
    {
      if (!strcmp(uval, "e"))
	{
	  cxt.base=NATURAL;
	}
      if (!strcmp(uval, "10"))
	{
	  cxt.base=DECIMAL;
	}
      if (!strcmp(uval, "2"))
	{
	  cxt.base=BINARY;
	}
    }

  pmf = load_from_file(fflag, fval, cxt);
  
  calculate_frequencies(pmf);

  if (xflag)
    {
      chisq = chisquare(pmf);
      if (tflag)
	{
	  printf("%f\n", chisq.chisquare);
	}
      else
	{
      printf("chisquare = %f, %llu degrees of freedom\n", chisq.chisquare, chisq.degrees);
	}
    }
  if (cflag)
    {      
      miss = missing_coverage(pmf, cxt);
      misspercent = 100. * ((double) miss / (double) all_possible);
      if (tflag)
	{
	  printf("%llu\n", miss);
	}
      else
	{
	  printf("Sample misses %llu of %llu possibilities, or %f%%\n", miss, all_possible, misspercent);
	}
    }
  if (kflag)
    {
      switch (cxt.base)
	{
	case NATURAL:
	  inval = "nats";
	  kl = kldive(pmf);
	  break;
	case DECIMAL:
	  inval = "digits";
	  kl = kldiv10(pmf);
	  break;
	default:
	  inval = "bits";
	  kl = kldiv2(pmf);
	}
      if (tflag)
	{
	  printf("%f\n", kl);	  
	}
      else
	{
	  printf("Kullback-Leibler divergence is %f %s per %s\n", kl, inval, onval);
	}
    }
  if (pflag)
    {
      print_ith_pmf(pmf, cxt);
    }
  if (eflag)
    {
      switch (cxt.base)
	{
	case NATURAL:
	  inval = "nats";
	  ent = entropye(pmf);
	  break;
	case DECIMAL:
	  inval = "digits";
	  ent = entropy10(pmf);
	  break;
	default:
	  inval = "bits";
	  ent = entropy2(pmf);
	}
      if (tflag)
	{
	  printf("%f\n", ent);	  
	}
      else
	{
	  printf("Entropy is %f %s per %s\n", ent, inval, onval);
	}
    }

  destroy_pmf(pmf);
  return 0;

}

