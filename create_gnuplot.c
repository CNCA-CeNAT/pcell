/* create_gnuplot.c */

#include <stdio.h>
#include <math.h>

int create_gnuplot(int n);

int create_gnuplot(int n)
{
  static int i;

  FILE *file;

  file = fopen("prog_gnuplot", "w");
 
  fprintf(file, "set terminal x11 \n");  
  fprintf(file, "set parametric \n");  
  fprintf(file, "set cntrparam levels 40 \n");
  fprintf(file, "set cntrparam bspline \n");
  fprintf(file, "set pointsize 0.1 \n");
  fprintf(file, "set contour base \n");
  fprintf(file, "set view 0,90 \n");
  fprintf(file, "set nosurface \n");
  fprintf(file, "set noxtics \n");
  fprintf(file, "set noytics \n");
  fprintf(file, "set noztics \n");
  fprintf(file, "set nolabel \n");
  fprintf(file, "set noclabel \n");  
  
  // fprintf(file, "set linestyle 9 lt 9 lw 5 \n");

  fprintf(file, "set style line 1 \n");

  fprintf(file, "set style function lines \n");

  for(i = 0; i < n; i++) {
    fprintf(file, "splot \"PCELL%d.DAT\" notitle w lines \n", i);
    fflush(file);
  }    

  fprintf(file, "pause 5 \n");
  fprintf(file, "quit \n");
  fclose(file);
  
  return(0);
}






