#include "load.h"
#include "pmf.h"

int next_word(FILE *fp, wchar_t *wbuff, int len)
{
  int i;
  wchar_t w;
  for (i=0; i<len; i++)
    {
      wbuff[i] = (wchar_t) 0;
    }
  for (i=0; i<len; i++)
    {
      w = fgetwc(fp);
      if (w == WEOF)
	{
	  if (i == 0)
	    return -1;
	  else
	    return i;
	}
      else if ((!iswalpha(w)) && (i > 0))
	{
	  return i;
	} 
      else 
	{
	  wbuff[i] = w;
	}
    }
  /* shouldn't get here */
  return 0;
}

ith_pmf *load_from_file(int fflag, char *fval, entropy_context cxt)
{
  FILE *fp;

  ith_pmf *alph;

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
  alph = new_pmf();
  if (!alph)
    {
      printf("Cannot make new pmf\n");
      return NULL;
    }
  
  char holder;
  uint16_t holder16;
  uint32_t holder32;
  uint64_t holder64;
  char holderarr[8];
  bytebits bbholder;
  int i;

  wchar_t wholder;
  wchar_t wbuff[255];
  int word_length;

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
	  holder16 = (((uint16_t)holderarr[0]) << 8) + holderarr[1];
	  ith_add_data(alph, &holder16, sizeof(uint16_t));
	}
      break;
    case UINT32:
      while ( ((holderarr[0] = fgetc(fp)) != EOF) && ((holderarr[1] = fgetc(fp)) != EOF) && ((holderarr[2] = fgetc(fp)) != EOF) && ((holderarr[3] = fgetc(fp)) != EOF))
	{
	  holder32 = (((uint32_t)holderarr[0]) << 24) + (((uint32_t)holderarr[1]) << 16) + (((uint32_t)holderarr[2]) << 8) + holderarr[3];
	  ith_add_data(alph, &holder32, sizeof(uint32_t));
	}
	break;
    case UINT64:
      while ( ((holderarr[0] = fgetc(fp)) != EOF) && ((holderarr[1] = fgetc(fp)) != EOF) && ((holderarr[2] = fgetc(fp)) != EOF) && ((holderarr[3] = fgetc(fp)) != EOF) && ((holderarr[4] = fgetc(fp)) != EOF) && ((holderarr[5] = fgetc(fp)) != EOF) && ((holderarr[6] = fgetc(fp)) != EOF) && ((holderarr[7] = fgetc(fp)) != EOF))
	{
	  holder64 = (((uint64_t)holderarr[0]) << 56) + (((uint64_t)holderarr[1]) << 48) + (((uint64_t)holderarr[2]) << 40) + (((uint64_t)holderarr[3]) << 32) + (((uint64_t)holderarr[4]) << 24) + (((uint64_t)holderarr[5]) << 16) + (((uint64_t)holderarr[6]) << 8) +holderarr[7];
	  ith_add_data(alph, &holder64, sizeof(uint64_t));	
	}
      break;
    case CHARS:
      while ((wholder = fgetwc(fp)) != WEOF)
	{
	  ith_add_data(alph, &wholder, sizeof(wchar_t));
	}
      break;
    case WORDS:
      /* TODO: fix this */
      /*      while ((word_length = next_word(fp, wbuff, 255)) != 0)
	{
	  ith_add_data(alph, wbuff, word_length * sizeof(wchar_t));
	  } */ 
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


