#include <stdio.h>

int main(void)
{
  int i;
  FILE *fp;
  fp=fopen("./.testbytes","w");
  if (!fp)
    {
      return -1;
    }

  /* test for all bytes */
  for (i=0; i<255; i++)
    {
      fputc(i, fp);
    }

  fclose(fp);

  fp=fopen("./.testbits","w");
  if (!fp)
    {
      return -1;
    }

  fputc(0xFF, fp);
  fputc(0xFF, fp);
  fputc(0xFF, fp);
  fputc(0xFF, fp);
  fputc(0x00, fp);
  fputc(0x00, fp);
  fputc(0x00, fp);
  fputc(0x00, fp);
  fputc(0xFF, fp);
  fputc(0xFF, fp);
  fputc(0xFF, fp);
  fputc(0xFF, fp);
  fputc(0x00, fp);
  fputc(0x00, fp);
  fputc(0x00, fp);
  fputc(0x00, fp);

  fputc(0xFF, fp);
  fputc(0xFF, fp);
  fputc(0xFF, fp);
  fputc(0xFF, fp);
  fputc(0x00, fp);
  fputc(0x00, fp);
  fputc(0x00, fp);
  fputc(0x00, fp);

  fputc(0xFF, fp);
  fputc(0xFF, fp);
  fputc(0xFF, fp);
  fputc(0xFF, fp);
  fputc(0x00, fp);
  fputc(0x00, fp);
  fputc(0x00, fp);
  fputc(0x00, fp);



  fclose(fp);


}
