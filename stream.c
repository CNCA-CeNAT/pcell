/* Stream.f -- translated by f2c (version 19991025). */

#include <stdio.h>
#include <math.h>

/* Table of constant values */

static double c_b3 = 2.0;
static double c_b4 = 4.0;

/* Main program */ 

int stream(double pm);
double pow_dd(double *ap, double *bp);

int stream(double pm)
{
  /* Format strings */
  /* System generated locals */
  
  int i1, i2;
  double d1, d2, d3;

  /* Builtin functions */

  double pow_dd();

  /* Local variables */
  
  static int i, j;
  
  /* z[10000] was [100][100] */

  static float z[10000];	
  static double dx, dy, nx, ny;

  /* Fortran I/O blocks */

  FILE *stream = fopen("STREAM.DAT", "w");

  dx = 0.01;
  dy = 0.01;
  nx = (double) ((int) (1.0 / dx));
  ny = (double) ((int) (1.0 / dy));

  for(i = 1; i <= 100; ++i) {
    for(j = 1; j <= 100; ++j) {
      d1 = (i * dx - 0.5);
      d3 = (j * dy - 0.5);
      d2 = (1.0 - pow_dd(&d3, &c_b3) * 4.0);
      z[i + j * 100 - 101] = 
	((pm - 1.0) * 4.0 * pow_dd(&d1, &c_b3) - pm) * (1.0 / (4.0 * M_PI)) 
	* pow_dd(&d2, &c_b4) * cos(M_PI * (i * dx - 0.5));
    }
  }
   
 i1 = (int) nx;
 
 for(i = 1; i <= i1; ++i) {
   i2 = (int) ny;
	
   for(j = 1; j <= i2; ++j) {
     fprintf(stream, "%f \n", z[i + j * 100 - 101]);
	
     if((double) j == ny) {
       fprintf(stream, "\n");
     }
   }
 }
 
 fclose(stream);

 return(0);
} /* MAIN */

double pow_dd(double *ap, double *bp)
{
  return(pow(*ap, *bp));
}






