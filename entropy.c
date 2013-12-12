#include "entropy.h"
#include "string.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "entropy.h"
/* entropy -u units -a alphabet -w -f FILE -p 
 */

void usage()
{
  printf("Entropy: compute the entropy of a file\n");
  printf("entropy -h | [-a bytes] [-u binary | natural | decimal] [-p]\n");
  printf("Options: -a bytes (currently the only alphabet)\n");
  printf("\t-u binary | natural | decimal (compute in bits, nats, or digits)\n");
  printf("-p print results (you probably want to do this)\n");
  printf("-h print this usage message\n");
  return;
}

int main(int argc, char **argv) 
{
  FILE *fp;
  int uflag = 0;
  int aflag = 0;
  int dflag = 0;
  int fflag = 0;
  int pflag = 0;
  int hflag = 0;
  char *uval=NULL;
  char *aval=NULL;
  char *fval=NULL;
  char *inval=NULL;
  char *onval=NULL;
  int c;
  entropy_base base = BINARY;
  entropy_alphabet alphabet = BYTES;
  ith_alphabet *alph;
  double ent;

  while ((c = getopt (argc, argv, "a:df:hpu:")) != -1)
    {
      switch (c)
	{
	case 'a':
	  aflag=1;
	  aval=optarg;
	  break;
	case 'd':
	  dflag=1;
	  break;
	case 'f':
	  fflag=1;
	  fval=optarg;
	  break;
	case 'h':
	  hflag=1;
	  break;
	case 'p':
	  pflag=1;
	  break;
	case 'u':
	  uflag=1;
	  uval=optarg;
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
  
  if (aflag)
    {
      if (!strcmp(aval, "bits"))
	{
	  alphabet=BITS;
	}
    }
  if (uflag)
    {
      if (!strcmp(uval, "e"))
	{
	  base=NATURAL;
	}
      if (!strcmp(uval, "10"))
	{
	  base=DECIMAL;
	}
    }
  
  if (dflag)
    {
      printf("Debugging option information:\n");
      printf("Aflag is %d\n", aflag);
      if (aflag)
	printf("Aval is %s\n", aval);
      printf("Uflag is %d\n", uflag);
      printf("Dflag is %d\n", dflag);
      if (uflag)
	printf("Uval is %s\n", uval);
      printf("Fflag is %d\n", fflag);
      if (fflag)
	printf("Fval is %s\n", fval);
      else
	printf("Entropy will read from stdin\n");
      if (base==DECIMAL)
	printf("Entropy will be computed in decimal digits\n");
      if (base==BINARY)
	printf("Entropy will be computed in bits\n");
      if (base==NATURAL)
	printf("Entropy will be computed in nats\n");
      if (alphabet==BITS)
	printf("Entropy will be calculated on bits\n");
      if (alphabet==BYTES)
	printf("Entropy will be calculated on bytes\n");
    }

  if (!fflag)
    {
      fp = stdin;
    }
  else
    {
      fp = fopen(fval, "r");
    }
  if (!fp)
    {
      printf("Error opening file %s\n", fval);
      return 1;
    }
  alph = new_alphabet();
  if (!alph)
    {
      printf("Cannot make new alphabet\n");
      return 1;
    }

  char holder;

  switch (alphabet)
    {
    case BYTES:
      onval = "byte";
      while ((holder = fgetc(fp)) != EOF)
	{
	  ith_add_data(alph, &holder, sizeof(char));
	}
      break;
    default:
      onval = "bit";
      printf("Not really doing anything...\n");
      
    }

  calculate_frequencies(alph);

  switch (base)
    {
    case NATURAL:
      inval = "nats";
      ent = entropye(alph);
      break;
    case DECIMAL:
      inval = "digits";
      ent = entropy10(alph);
      break;
    default:
      inval = "bits";
      ent = entropy2(alph);
    }

  if (pflag)
    {
      printf("Entropy is %f %s per %s\n", ent, inval, onval);
    }

  if (fflag)
    {
      fclose(fp);
    }
  destroy_alphabet(alph);
  return 0;

}

