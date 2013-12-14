#include "load.h"
#include "bits.h"
#include "pmf.h"


int next_wword(FILE *fp, wchar_t *wbuff, int len)
{
  int i;
  int in_word = 0;
  int word_length = 0;
  wchar_t w;
  for (i = 0; i < len; i++)
    {
      wbuff[i] = (wchar_t) 0;
    }
  for (i = 0; i < len; i++)
    {
      w = fgetwc(fp);
      if (w == WEOF)
	{
	  return word_length;
	}
      else if (!iswspace(w) && !iswpunct(w))
	{
	  in_word=1;
	  wbuff[word_length] = w;
	  word_length++;
	}
      else if (iswspace(w) || iswpunct(w))
	{
	  if (in_word)
	    {
	      return word_length;
	    }
	}
    }
  return word_length;
}

int next_word(FILE *fp, char *buff, int len)
{
  int i;
  int in_word = 0;
  int word_length = 0;
  char w;
  for (i = 0; i < len; i++)
    {
      buff[i] = (char) 0;
    }
  for (i = 0; i < len; i++)
    {
      w = fgetc(fp);
      if (w == EOF)
	{
	  return word_length;
	}
      else if (!isspace(w) && !ispunct(w))
	{
	  in_word=1;
	  buff[word_length] = w;
	  word_length++;
	}
      else if (isspace(w) || ispunct(w) )
	{
	  if (in_word)
	    {
	      return word_length;
	    }
	}
    }
  return word_length;
}


ith_pmf *load_from_file(int fflag, char *fval, ith_context cxt)
{
  FILE *fp;

  ith_pmf *alph;

  int word_length;

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
  wchar_t wbuff[255];
  char buff[255];
  int i;

  wchar_t wholder;

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
      while ((holder = fgetc(fp)) != EOF)
	{
	  ith_add_data(alph, &holder, sizeof(char));
	}
    case WCHARS:
      while ((wholder = fgetwc(fp)) != WEOF)
	{
	  ith_add_data(alph, &wholder, sizeof(wchar_t));
	}
      break;
    case WWORDS:
      while ((word_length = next_wword(fp, wbuff, 255)))
	{
	  ith_add_data(alph, wbuff, word_length * sizeof(wchar_t));
	}
      break;
    case WORDS:
      while ((word_length = next_word(fp, buff, 255)))
	{
	  ith_add_data(alph, buff, word_length * sizeof(char));
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


