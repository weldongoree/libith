#include "entropy.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "entropy.h"
/* entropy -u units -a alphabet -w -f FILE -p 
 */

int main(int argc, char **argv) 
{
  int uflag = 0;
  int aflag = 0;
  int dflag = 0;
  int fflag = 0;
  int pflag = 0;
  char *uval=NULL;
  char *aval=NULL;
  char *fval=NULL;
  int c;
  entropy_base base = BINARY;
  entropy_alphabet alphabet = BYTES;
  
  while (c = getopt (argc, argv, "a:df:pu:") != -1)
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
	  /*	default:
		abort(); */
	}
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
    }




  return 0;

}

