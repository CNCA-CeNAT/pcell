/* create_avenergy.c */

#include <stdio.h>
#include <math.h>

int create_avenergy();

int create_avenergy()
{
  FILE *file;

  file = fopen("prog_avenergy", "w");
 
  fprintf(file, "set terminal x11 \n");  
  fprintf(file, "plot \"MeanField.DAT\" w l 9 \n");
  fprintf(file, "pause 5 \n");
  fprintf(file, "quit \n");
  fclose(file);
  
  return(0);
}






