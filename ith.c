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
  printf("Entropy: compute the entropy of a file\n");
  printf("entropy -h | [-a byte bit uint16_t uint32_t uint64_t] [-u binary | natural | decimal] [-p]\n");
  printf("Options: -a bytes etc. (the alphabet you're reading over)\n");
  printf("\t-u binary | natural | decimal (compute in bits, nats, or digits)\n");
  printf("-p print summary of the probability distribution from the sample\n");
  printf("-h print this usage message\n");
  return;
}

int main(int argc, char **argv) 
{
  int uflag = 0;
  int aflag = 0;
  int fflag = 0;
  int pflag = 0;
  int hflag = 0;
  int iflag = 0;
  int kflag = 0;
  int xflag = 0;
  int tflag = 0;

  double ent = 0.;
  double kl = 0.;

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

  while ((c = getopt (argc, argv, "a:f:hikptu:x")) != -1)
    {
      switch (c)
	{
	case 'a':
	  aflag=1;
	  aval=optarg;
	  break;
	case 'f':
	  fflag=1;
	  fval=optarg;
	  break;
	case 'h':
	  hflag=1;
	  break;
	case 'i':
	  iflag=1;
	  break;
	case 'k':
	  kflag=1;
	  break;
	case 'p':
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
	}
      else if (!strcmp(aval, "8"))
	{
	  cxt.alphabet=BYTES;
	  onval="byte";
	}
      else if (!strcmp(aval, "16"))
	{
	  cxt.alphabet=UINT16;
	  onval="16-bit short";
	}
      else if (!strcmp(aval, "32"))
	{
	  cxt.alphabet=UINT32;
	  onval="32-bit int";
	}
      else if (!strcmp(aval, "64"))
	{
	  cxt.alphabet=UINT64;
	  onval="64-bit int";
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
      printf("chisquare = %f, %llu degrees of freedom\n", chisq.chisquare, chisq.degrees);
    }
  else if (kflag)
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
  else if (pflag)
    {
      print_ith_pmf(pmf, cxt);
    }
  else
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

