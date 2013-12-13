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

ith_alphabet *load_from_file(int fflag, char *fval, entropy_context cxt)
{
  FILE *fp;

  ith_alphabet *alph;

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
  uint32_t holder32;
  uint64_t holder64;
  char holderarr[8];
  bytebits bbholder;
  int i;
  switch (cxt.alphabet)
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
      while ( ((holderarr[0] = fgetc(fp)) != EOF) && ((holderarr[1] = fgetc(fp)) != EOF))
	{
	  holder16 = (holderarr[0] << 8) + holderarr[1];
	  ith_add_data(alph, &holder16, sizeof(uint16_t));
	}
      break;
    case UINT32:
      while ( ((holderarr[0] = fgetc(fp)) != EOF) && ((holderarr[1] = fgetc(fp)) != EOF) && ((holderarr[2] = fgetc(fp)) != EOF) && ((holderarr[3] = fgetc(fp)) != EOF))
	{
	  holder32 = (holderarr[0] << 24) + (holderarr[1] << 16) + (holderarr[2] << 8) + holderarr[3];
	  ith_add_data(alph, &holder32, sizeof(uint32_t));
	}
	break;
    case UINT64:
      while ( ((holderarr[0] = fgetc(fp)) != EOF) && ((holderarr[1] = fgetc(fp)) != EOF) && ((holderarr[2] = fgetc(fp)) != EOF) && ((holderarr[3] = fgetc(fp)) != EOF) && ((holderarr[4] = fgetc(fp)) != EOF) && ((holderarr[5] = fgetc(fp)) != EOF) && ((holderarr[6] = fgetc(fp)) != EOF) && ((holderarr[7] = fgetc(fp)) != EOF))
	{
	  holder64 = (holderarr[0] << 56) + (holderarr[1] << 48) + (holderarr[2] << 40) + (holderarr[3] << 32) + (holderarr[4] << 24) + (holderarr[5] << 16) + (holderarr[6] << 8) +holderarr[7];
	  ith_add_data(alph, &holder64, sizeof(uint64_t));	
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
  ith_alphabet *alph;
  double ent;
  entropy_context cxt;

  cxt.alphabet = BYTES;
  cxt.base = BINARY;

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

  if (aflag)
    {
      if (!strcmp(aval, "2"))
	{
	  cxt.alphabet=BITS;
	}
      else if (!strcmp(aval, "16"))
	{
	  cxt.alphabet=UINT16;
	}
      else if (!strcmp(aval, "32"))
	{
	  cxt.alphabet=UINT32;
	}
      else if (!strcmp(aval, "64"))
	{
	  cxt.alphabet=UINT64;
	}
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
    }

  alph = load_from_file(fflag, fval, cxt);
  
  calculate_frequencies(alph);

  switch (cxt.alphabet)
    {
    case BYTES:
      onval = "byte";
      break;
    case UINT16:
      onval = "16-bit short";
      break;
    case UINT32:
      onval = "32-bit word";
      break;
    case UINT64:
      onval = "64-bit word";
      break;
    default:
      onval = "bit";
    }

  switch (cxt.base)
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

