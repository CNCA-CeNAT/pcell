/* Potinc.f -- translated by f2c (version 19991025). */

/* adim = idim * jdim * kdim = 111 * 111 * 51 = 628371 */

#define idim        111
#define jdim        111
#define kdim        51
#define andim       idim * jdim * kdim
#define an(i, j, k) an[(i) + ((j) + (k) * kdim) * jdim]

/* Table of constant values */

/* Main program */ 

//int potinc(void);

int potinc()
{
  /* System generated locals */

  //float r_1, r_2;

  /* Local variables */
  
  /* a[628371] was [111][111][51] */

  //static float an[andim], c, i, j, dx, dy, nx, ny;
  static float an[andim], dx, dy, c, nx, ny;
  int i,j;  
  /* Fortran I/O blocks */

  FILE *test, *test1, *pcell;

  dx = (float) 0.01;
  dy = (float) 0.01;
  c = (float) 1.0;

  an(0, 0, 0) = (float) 10.0;
  an(0, 1, 0) = (float) 10.0;
  an(1, 0, 0) = an(0, 0, 0) - dx * c;
  an(1, 1, 0) = an(0, 1, 0) - dx * c;

  //nx = 1.0 / dx;
  //ny = 1.0 / dy;
  nx = 100.0;
  ny = 100.0;
  
  
  //for(j = (float) 0.0; j <= (float) 1.0; j += (float) 1.0) {
  for(j = 0; j <= 1; j += 1) {
    
    //for(i = (float) 0.0; i <= nx; i += (float) 2.0) {
    for(i = 0; i <= nx; i += 2) {
      an(i, j, 0) = an(0, j, 0) - i * dx * c;
    }
    
    for(i = 1; i <= nx; i += 2) {
      an(i, j, 0) = an(1, j, 0) - (i - 1) * dx * c;
    }
  }
    
  for(i = 0; i <= nx; i += 1) {
    
    for(j = 2; j <= ny; j += 2) {
      an(i, j, 0) = an(i, 0, 0);
    }
    
    
    for(j = 1; j <= ny; j += 2) {
      an(i, j, 0) = an(i, 1, 0 );
    }
  }

  test1 = fopen("TEST1.DAT", "w");
  
  
  for(i = 0; i <= nx; i += 1) {
    for(j = 0; j <= ny; j += 1) {
      fprintf(test1, " %11.8f ", an((int) i, (int) j, 0));
    }
  }

  fclose(test1);

  test = fopen("TEST.DAT", "w");
  
    
  for(i = 0; i <= nx; i += 1) {
        
    for(j = 0; j <= ny; j += 1) {
      fprintf(test, " %11.8f ", an( i, j, 0));
    }
  }

  fclose(test);

  pcell = fopen("PCELL0.DAT", "w");
  
  
  for(i = 0; i <= nx; i += 1) {    
    for(j = 0; j <= ny; j += 1) {
      fprintf(pcell, " %11.8f \n", an(i, j, 0));
	
      if(j == ny) {
	fprintf(pcell, "\n");
      }
    }
  }
  
  fclose(pcell);

  return(0);
} /* MAIN */

