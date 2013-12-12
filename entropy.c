#include "entropy.h"
#include "string.h"
#include "bits.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

ith_alphabet *load_from_file(int fflag, char *fval, int aflag, char *aval)
{
  FILE *fp;
  entropy_alphabet alphabet=BYTES;

  ith_alphabet *alph;
  if (aflag)
    {
      if (!strcmp(aval, "bits"))
	{
	  alphabet=BITS;
	}
      else if (!strcmp(aval, "uint16"))
	{
	  alphabet=UINT16;
	}
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
      return NULL;
    }
  alph = new_alphabet();
  if (!alph)
    {
      printf("Cannot make new alphabet\n");
      return NULL;
    }
  
  char holder;
  uint16_t holder16;
  char holder1, holder2;
  bytebits bbholder;
  int i;
  switch (alphabet)
    {
    case BYTES:
      while ((holder = fgetc(fp)) != EOF)
	{
	  ith_add_data(alph, &holder, sizeof(char));
	}
      break;
    case BITS:
      while ((holder = fgetc(fp)) != EOF)
	{
	  bbholder = explode_byte((uint8_t) holder);
	  for (i = 0; i < 8; i++)
	    {
	      ith_add_data(alph, &(bbholder.bits[i]), sizeof(uint8_t));
	    }
	}
      break;
    case UINT16:
      while ( ((holder1 = fgetc(fp)) != EOF) && ((holder2 = fgetc(fp)) != EOF))
	{
	  holder16 = holder1;
	  holder16 = holder16 << 8;
	  holder16 += holder2;
	  ith_add_data(alph, &holder16, sizeof(uint16_t));
	}
      break;
    default:
      printf("Not really doing anything...\n");
      if (fflag)
	{
	  fclose(fp);
	}
      return NULL;
    }

  if (fflag)
    {
      fclose(fp);
    }


  return alph;
}

int main(int argc, char **argv) 
{
  int uflag = 0;
  int aflag = 0;
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

  while ((c = getopt (argc, argv, "a:f:hpu:")) != -1)
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

  alph = load_from_file(fflag, fval, aflag, aval);
  
  calculate_frequencies(alph);

  if (aflag)
    {
      if (!strcmp(aval, "bits"))
	{
	  alphabet=BITS;
	}
      else if (!strcmp(aval, "uint16"))
	{
	  alphabet=UINT16;
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
  


  switch (alphabet)
    {
    case BYTES:
      onval = "byte";
      break;
    case UINT16:
      onval = "16-bit short";
      break;
    default:
      onval = "bit";
    }

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

      printf("Entropy is %f %s per %s\n", ent, inval, onval);


  if (pflag)
    {
      print_ith_alphabet(alph);
    }

  destroy_alphabet(alph);
  return 0;

}
