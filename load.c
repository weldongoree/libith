#include "load.h"

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
  char *buff;
  long file_length;
  size_t bytes_read;
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
	/* TODO: this is wrong; holderarr[0] can't be shifted that much */

	  holder64 = (holderarr[0] << 56) + (holderarr[1] << 48) + (holderarr[2] << 40) + (holderarr[3] << 32) + (holderarr[4] << 24) + (holderarr[5] << 16) + (holderarr[6] << 8) +holderarr[7];
	  ith_add_data(alph, &holder64, sizeof(uint64_t));	
	}
      break;
    case CHARS:
      while ((wholder = fgetwc(fp)) != WEOF)
	{
	  ith_add_data(alph, &wholder, sizeof(wchar_t));
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

