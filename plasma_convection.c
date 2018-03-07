/* convection.f -- translated by f2c (version 20020621). */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* Table of constant values */

#define xdim        101
#define ydim        101
#define tdim        201
#define vdim        xdim * ydim

// #define ndim        3 * 999

#define adim        vdim * tdim

// #define pdim        3 * vdim

#define vx(i, j)    vx[(i) + (j) * xdim]
#define vy(i, j)    vy[(i) + (j) * xdim]
#define b(i, j)     b[(i) + (j) * xdim]
#define diff(i, j)  diff[(i) + (j) * xdim]
#define em(i, j)    em[(i) + (j) * xdim]
#define em2(i, j)   em2[(i) + (j) * xdim]
#define a(i, j, k)  a[(i) + ((j) + (k) * ydim) * xdim]
#define a2(i, j, k) a2[(i) + ((j) + (k) * ydim) * xdim]

int convec_plasma(double reyn, double parm, int nf);
int convect(double *, double *, int);
void itoa(int n, char *s);
void reverse(char *s);
int mean_field(double nx_i, double nx_f, double ny_i, double ny_f);
double nx_i, nx_f, ny_i, ny_f;

/* Main program */ 

int convec_plasma(double reyn, double parm, int nf)
{  
  int n;
  for(n = 1; n <= nf; ++n) {
    convect(&reyn, &parm, n);
  } 
  return 0;
} 

/*
 *
 * Input parameters:
 *
 * Grid step size [DX, DY], number of steps [NX, NY]
 * Magnetic Reynolds number as a function of the resistivity, RE
 * RM = 1/RE
 * Time interval DT
 *
 */

/* Subroutine */ 

int convect(double *rey, double *param, int nf)
{
  /* System generated locals */
  
  int i_1, i_2, i_3, i_4;
  double d_0; 
  /* Local variables */
  /* a[2050401] was [101][101][201] */
  
  static float a[adim];	

  static int i, j;
  static double l, m;
  static int n, r, s, u, z;
  static double ca, cb, cc, cd, fa, fe, ka, la, fi, na, md, mc, qa, ta;
  static int dr, cs, cu;
  static double re, dt, dx, dy, ex, ye, ms, mt, mu, qb, qc, qd, nx, ny;
  
  /* vx[10201] was vx[101][101] */ 
  /* vy[10201] was vy[101][101] */ 

  static float vx[vdim], vy[vdim], cda, cdb;
  static int cha, che, can;
  static double pad;
  static int cen;
  static double rad, qac, ped, qbc, red, qcc, pid, qdc, rid;
  static int con;
  static double rod, pau, rau, peu, reu, piu, riu, rou;
  static int crfx, crfy, crix, criy;
  char s1[20], s2[10], s3[5];

  FILE *test, *test1, *test2, *pcell;

  dx = 0.01;
  dy = 0.01;
  nx = 100.0;
  ny = 100.0;
  re = 1.0f / *rey;
  dt = 0.01;

  /* Input the initial values T_N and T_[N + 1/2] of the vector potential */
  
  test1 = fopen("TEST1.DAT", "r");

  i_1 = (int)nx;
  
  for(i = 0; i <= i_1; ++i) {
    i_2 = (int) ny;
	
    for(j = 0; j <= i_2; ++j) {
      fscanf(test1, "%f", (float *) &a(i, j, 0));
    }
  }
  
  fclose(test1);

  test = fopen("TEST.DAT", "r");

  i_2 = (int) nx;
  
  for(i = 0; i <= i_2; ++i) {
    i_1 = (int) ny;
	
    for(j = 0; j <= i_1; ++j) {
      fscanf(test, "%f", (float *) &a(i, j, 1));
    }
  }
   
  fclose(test);

  /* Calculation of the plasma velocity components */

  i_1 = (int) nx;
  
  for(i = 0; i <= i_1; ++i) {
    i_2 = (int) ny;
    
    for(j = 0; j <= i_2; ++j) {
      /* Computing 2nd power */
	  
      d_0 = i * dx - 0.5;
      la = (1.0 - *param) * (d_0 * d_0) * 4.0 + *param;
      
      /* Computing 2nd power */
	    
      d_0 = j * dy - 0.5;
      ta = 1.0 - d_0 * d_0 * 4.0;
      ka = cos((i * dx - 0.5) * M_PI);
      na = sin((i * dx - 0.5) * M_PI);

      /* Computing 3rd power */
      
      d_0 = ta;

      vx(i, j) = la * (8.0 / M_PI) * (d_0 * (d_0 * d_0)) * (j * dy - 0.5) * ka;

      /* Computing 4th power */
      
      d_0 = ta, d_0 *= d_0;
      
      vy(i, j) = d_0 * d_0 * (1.0 / (4.0 * M_PI)) 
	* (- M_PI * la * na + (1.0 - *param) * 8.0 * ka * (i * dx - 0.5));
    }
  }

  /*
   * EX, YE, L and M are terms that appear frequently in the recurrence 
   *  relations
   *
   */
  
  ex = dt / (dx * 12);
  ye = dt / (dy * 12);
  
  /* Computing 2nd power */
  
  d_0 = dx;
  l = re * dt / (d_0 * d_0);

  /* Computing 2nd power */
  
  d_0 = dy;
  m = re * dt / (d_0 * d_0);
  che = 2;
  
  /* N is the number of time intervals for the magnetic field evolution */
  
  for(n = 0; n <= 4; ++n) {
    r = 0;
    z = 1;

    /*
     * CHA measures if the current iteration is even (CHA = 0) or odd
     * (CHA = 1). It is use to control the sweep direction
     *
     */
    
    cha = n % che;
    
    /*
     * The grid sweep is defined as follows
     *
     * 1. X: from 0 to NX      Y: from 1 to NY - 1
     * 2. X: from 1 to NX - 1  Y: from 1 to NY - 1
     * 3. X: from 0 to NX      Y: from 2 to NY - 2
     * 4. X: from 0 to NX - 1  Y: from 2 to NY - 2
     *
     * In general
     *
     * X: from CRIX to CRFX    Y: from CRIY to CRFY
     *
     * Forward step example
     *
     * 0, 2, 4, ..., NX
     *
     * 1, 3, 5, ..., NY - 1 (first)
     *
     * The direction of the sweep is inverted in every time interval.
     * DR controls this invertion.
     *
     */

    for(con = 1; con <= 2; ++con) {
      u = 0;
      
      for(cen = 1; cen <= 2; ++cen) {
	if(cha == 0) {
	  cs = 1;
	  criy = r + 1;
	  crfy = (int) (ny - 1 - r);
	  dr = 2;
	  crix = u;
	  crfx = (int) (nx - u);
	} else {
	  cs = -1;
	  criy = (int) (ny - 1 - r);
	  crfy = r + 1;
	  crix = (int) (nx - u);
	  crfx = u;
	  dr = -2;
	}

	/* Calculation of the vector potential */

	i_1 = crfy;
	i_2 = dr;
	
	for(j = criy; i_2 < 0 ? j >= i_1 : j <= i_1; j += i_2) {
	  i_3 = crfx;
	  i_4 = dr;
	  
	  for(i = crix; i_4 < 0 ? i >= i_3 : i <= i_3; i += i_4) {
	    fa = 0.0;
	    
	    /*
	     * The potential and velocity coordinates in each grid point are 
	     * adjusted by means of parameters. Defining the variables as 
	     * function of certain symmetries each term of the potential can 
	     * be decomposed in two simmetric parts which can be calculated 
	     * from one equation. The parameters S and Z are adjusted 
	     * according to the calculated term and the sweep direction.
	     *
	     */

	    for(can = 1; can <= 2; ++can) {
	      if(can == 1) {
		s = -1;
	      } else {
		s = 1;
	      }
		
	      if(cha == 0) {
		if(can == 1) {
		  z = 1;
		} else {
		  z = 0;
		}
	      } else {
		if(can == 2) {
		  z = 1;
		} else {
		  z = 0;
		}
	      }
	      
	      cu = 0;
	      mu = (double) (i + s);
	      md = (double) (i - 2);
	      mt = (double) (i + 2);
	      mc = (double) (j - 2);
	      ms = (double) (j + 2);
	      qac = mt - 1;
	      qbc = md + 1;
	      qcc = ms - 1;
	      qdc = mc + 1;
	      
	      /* 
	       * The values of each coordinate are assigned according to 
	       * the boundary conditions. 
	       *
	       */

	      if((double) i == nx && s == 1) {
		mu = 0.0;
		cu = 1;
	      }
	      
	      if(i == 0 && s == -1) {
		mu = 0.0;
		cu = 2;
	      }
		
	      if(i == 0) {
		md = 0.0;
		qbc = 0.0;
	      }
		
	      if(i == 1) {
		md = 0.0;
	      }
			
	      if((double) i == nx) {
		mt = 0.0;
		qac = 0.0;
	      }
			 
	      if((double) i == nx - 1) {
		mt = 0.0;
	      }
		
	      if(j == 1) {
		mc = 0.0;
		qdc = 0.0;
		
		if((double) i != nx && s != 1) {
		  if (i != 0 && s != -1) {
		    cu = 3;
		  }
		}
	      }
		
	      if((double) j == ny - 1) {
		ms = 0.0;
		qcc = ny;
		
		if((double) i != nx && i != 1) {
		  if(i != 0 && i != -1) {
		    cu = 4;
		  }
		}
	      }

	      /* Values of each term used to calculate the potential */
	      
	      pau = vx((int) mu, j);
	      peu = vx((int) mu, (int) ms);
	      piu = vx((int) mu, (int) mc);
	      pad = vy(i, (j + s));
	      ped = vy((int) mt, (j + s));
	      pid = vy((int) md, (j + s));
	      rau = a((int) mu, j, (n + 1));
	      reu = a((int) md, j, (n + z));
	      riu = a((int) mu, (int) ms, (n + 1));
	      rou = a((int) mu, (int) mc, (n + 1));
	      rad = a(i, (j + s), (n + 1));
	      red = a(i, (int) mc, (n + z));
	      rid = a((int) mt, (j + s), (n + 1));
	      rod = a((int) md, (j + s), (n + 1));
	      qa = a((int) qac, j, (n + 1));
	      qb = a((int) qbc, j, (n + 1));
	      qc = a(i, (int) qcc, (n + 1));
	      qd = a(i, (int) qdc, (n + 1));
	      
	      /* Values of these term at the boundaries */

	      if(cu == 1) {
		pau = vx((int) (nx - 1), j) - vy((int) nx, (j + 1)) 
		  + vy((int) nx, (j - 1));
		
		if((double) j != ny - 1 && (double) j != ny - 2) {
		  peu = vx((int) (nx - 1), (j + 2)) - vy((int) nx, (j + 3)) 
		    + vy((int) nx, (j + 1));
		}
		
		if(j != 1 && j != 2) {
		  piu = vx((int) (nx - 1), (j - 2)) - vy((int) nx, (j - 1)) 
		    + vy((int) nx, (j - 3));
		}
		
		if((double) j == ny - 2) {
		  peu = vx((int) (nx - 1), (int) ny);
		}
		
		if(j == 2) {
		  piu = vx((int) (nx - 1), 0);
		}
		
		if(j == 1 || (double) j == ny - 1) {
		  peu = 0.0;
		  piu = 0.0;
		}
		
		rau = 8.99f;
		riu = 8.99f;
		rou = 8.99f;
	      }
		
	      if(cu == 2) {
		pau = vx(1, j) + vy(0, (j + 1)) - vy(0, (j - 1));
		
		if((double) j != ny - 1 && (double) j != ny - 2) {
		  peu = vx(1, (j + 2)) + vy(0, (j + 3)) - vy(0, (j + 1));
		}
		
		if(j != 1 && j != 2) {
		  piu = vx(1, (j - 2)) + vy(0, (j - 1)) - vy(0, (j - 3));
		}
		
		if((double) j == ny - 2) {
		  peu = vx(1, (int) ny);
		}
		
		if(j == 2) {
		  piu = vx(1, 0);
		}
		
		if(j == 1 || (double) j == ny - 1) {
		  peu = 0.0;
		  piu = 0.0;
		}
				
		rau = 10.01f;
		riu = 10.01f;
		rou = 10.01f;
	      }
	      
	      if(i == 0) {
		pid = ped;
		reu = 10.02f;
		rod = 10.02f;
		qb = 10.01f;
	      }
		
	      if(i == 1) {
		pid = ped;
		reu = 10.01f;
		rod = 10.01f;
	      }
	      
	      if((double) i == nx) {
		ped = pid;
		rid = 8.98f;
		qa = 8.99f;
	      }
	      
	      if((double) i == nx - 1) {
		ped = pid;
		rid = 8.99f;
	      }
		
	      if(cu == 3) {
		piu = 0.0;
		rou = a((int) mu, 1, (n + 1));
		red = a(i, 1, (n + z));
	      }
	      
	      if(cu == 4) {
		peu = 0.0;
		riu = a((int) mu, (int) (ny - 1), (n + 1));
	      }
	      
	      /* Calculation of the potencial */

	      ca = -s * ex * (pau * (rau * 8 - reu) 
			      + (riu - rou) * (peu - piu) / 8);
	      cb = -s * ye * (pad * (rad * 8 - red) 
			      + (rid - rod) * (ped - pid) / 8);
	      fa = fa + ca + cb;
	      cd = 1 - cs * (ex * pau + ye * pad) + cs * s * (l + m);

	      if(cs == 1) {
		if(s == -1) {
		  cda = cd;
		} else {
		  cdb = cd;
		}
	      }
	      
	      if(cs == -1) {
		if(s == 1) {
		  cda = cd;
		} else {
		  cdb = cd;
		}
	      }
	    }
		
	    cc = l * (qa + qb) + m * (qc + qd);
	    fe = fa + cc;
	    fi = fe + a(i, j, n) * cda;
	    a(i, j, (n + 2)) = fi / cdb;
	  }
	}
	
	u = 1;
      }
	
      r = 1;
    }

    /*
     * Calculation of the potential values that remain fixed 
     * (lower and upper row)
     *
     */
      
    i_2 = (int) nx;
	
    for(i = 0; i <= i_2; ++i) {
      a(i, 0, (n + 2)) = a(i, 0, n);
      a(i, (int) ny, (n + 2)) = a(i, (int) ny, n);
    }
  }
    
  /* Storage of the new potential values at times T_N and T_[N - 1] */

  test1 = fopen("TEST1.DAT", "w");

  i_2 = (int) nx;
  
  for(i = 0; i <= i_2; ++i) {
    i_1 = (int) ny;
	
    for(j = 0; j <= i_1; ++j) {
      fprintf(test1, " %11.8f ", a(i, j, n));
    }
  }

  test2 = fopen("TEST2.DAT", "w");

  i_2 = (int) nx;
  
  for(i = 0; i <= i_2; ++i) {
    i_1 = (int) ny;
	
    for(j = 0; j <= i_1; ++j) {
      fprintf(test2, " %11.8f \n", a(i, j, n));
    }
  }

  fclose(test2);
  
  test = fopen("TEST.DAT", "w");

  i_1 = (int) nx;
  
  for(i = 0; i <= i_1; ++i) {
    i_2 = (int) ny;
    
    for(j = 0; j <= i_2; ++j) {
      fprintf(test, " %11.8f \n", a(i, j, (n + 1)));
      
      if((double) j == ny) {
	fprintf(test, "\n");
      }
    }
  }

  fclose(test);

  mean_field(nx_i, nx_f, ny_i, ny_f);
  
  /* Writing concatenation */
  
  s1[0] = 'P';
  s1[1] = 'C';
  s1[2] = 'E';
  s1[3] = 'L';
  s1[4] = 'L';
  s1[5] = '\0';

  s3[0] = '.';
  s3[1] = 'D';
  s3[2] = 'A';
  s3[3] = 'T';
  s3[4] = '\0';

  itoa(nf,  s2);
  strcat(s1, s2);
  strcat(s1, s3);

  // printf("%s \n", s1);
  // pcell = fopen((const char *) s1, "w");

  pcell = fopen(s1, "w");

  i_1 = (int) nx;
    
  for(i = 0; i <= i_1; ++i) {
    i_2 = (int) ny;
       
    for(j = 0; j <= i_2; ++j) {
      fprintf(pcell, "%f \n", a[i + (j + (n + 1) * 101) * 101]);
      
      if((double) j == ny) {
	fprintf(pcell, "\n");
      }
    }
  }

  fclose(pcell);

  return(0);
} /* convect */

/* mean_field */

int mean_field(double nx_i, double nx_f, double ny_i, double ny_f)
{
  /* System generated locals */
  
  int i_1, i_2;
  double d_1, d_2, d_3;
  double f_1, f_2;
  
  /* Builtin functions */

  double sqrt(double);

  /* Local variables */
  
  /* a[30603] was a[101][101][3] */
  /* b[10201] was b[101][101]     */

  // static float a[pdim], a2[pdim], b[vdim];

  static float a[adim], a2[adim], b[vdim];
  static int i, j;
  static double l, l2, m, m2;
  static int n;

  /* em[10201] was em[101][101] */

  static double ee, em[vdim], em2[vdim], diff[vdim], dx, nx, ny, eme;

  FILE *potential, *meanfield, *difference;
  
  nx = 100.0;
  ny = 100.0;
  n  = 0;
  dx = 1.0f / nx;

  potential = fopen("TEST.DAT", "r");
  
  i_1 = (int) nx;
  
  for(i = 0; i < vdim; ++i) {
    diff[i] = 0.0;
    em[i]   = 0.0;
    em2[i]  = 0.0;
  }

  for(i = 0; i <= i_1; ++i) {
    i_2 = (int) ny;

    for(j = 0; j <= i_2; ++j) {
      fscanf(potential, "%f", (float *) &a(i, j, n));
    }
  }
  
  fclose(potential);

  difference = fopen("TEST2.DAT", "r");
  
  for(i = 0; i <= i_1; ++i) {
    i_2 = (int) ny;

    for(j = 0; j <= i_2; ++j) {
      fscanf(difference, "%f", (float *) &a2(i, j, n));
    }
  }
  
  fclose(difference);

  i_2 = (int) nx_f;
  
  for(i = (int) nx_i; i <= i_2; ++i) {
    i_1 = (int) ny_f;
    
    for(j = (int) ny_i; j <= i_1; ++j) {
      if((double) i == nx) {
	m  = 8.99f;
	m2 = 8.99f;
      } else {
	// [i + 1 + (j + n * 101) * 101]

	m  = a(i + 1, j, n); 
	m2 = a2(i + 1, j, n); 
      }
      
      if((double) j == ny) {
	// [i + (j - 1 + n * 101) * 101]
	
	l  = a(i, j - 1, n); 
	l2 = a2(i, j - 1, n); 
      } else {
	// [i + (j + 1 + n * 101) * 101]

	l  = a(i, j + 1, n);
	l2 = a2(i, j + 1, n);
      }
      
      /* Computing 2nd power */
      
      // [i + (j + n * 101) * 101]
      
      d_1 = l - a(i, j, n);
      f_1 = l2 - a2(i, j, n);

      /* Computing 2nd power */
      
      // [i + (j + n * 101) * 101]

      d_2 = m - a(i, j, n);
      f_2 = m2 - a2(i, j, n);

      /* Computing 2nd power */
      
      d_3 = dx;
      
      // em[i + j * 101] 
      //  b[i + j * 101] 

      em(i, j)   = (d_1 * d_1 + d_2 * d_2) / (d_3 * d_3);
      em2(i, j)  = (f_1 * f_1 + f_2 * f_2) / (d_3 * d_3);
      diff(i, j) = (em2(i, j) - em(i, j)) / em(i, j);
      b(i, j)    = sqrt(em(i, j));      
    }
  }
  
  ee = 0.0;

  i_2 = (int) nx_f;
  
  for(i = (int) nx_i; i <= i_2; ++i) {
    i_1 = (int) ny_f;
    
    for(j = 0; j <= i_1; ++j) {
      // [i + j * 101]
      
      ee += em(i, j);
    }
  }
  
  eme = ee / ((nx_f - nx_i + 1) * (ny_f - ny_i + 1));

  printf("Mean Energy Density \n");
  printf("MED = %g \n", eme);

  // meanfield = fopen("MeanField.DAT", "a+");
  
  meanfield = fopen("MeanField.DAT", "a");

  fprintf(meanfield, " %11.8f \n", eme);
  fclose(meanfield);

  difference = fopen("DIFF.DAT", "w");

  i_2 = (int) nx_f;
  
  for(i = (int) nx_i; i <= i_2; ++i) {
    i_1 = (int) ny_f;
	
    for(j = (int) ny_i; j <= i_1; ++j) {
      fprintf(difference, " %d %d %11.8f \n", i, j, diff(i, j));
    }
  }
  
  fclose(difference);

  return(0);
} /* mean_field */

/* itoa: n in Text in s wandeln -- Variante */

void itoa(int n, char *s)
{
  int i, sign;
  
  /* Vorzeichen notieren */

  sign = n;
  i = 0;

  /* Ziffern in ungekehrter Reihenfolge */

  do {
    /* naechster Ziffer wegdividieren */

    s[i++] = abs(n % 10) + '0';
  } while((n /= 10) != 0);
  
  if(sign < 0) 
    s[i++] = '-';

  s[i] = '\0';

  reverse(s);
}

/* reverse: Zeichenkette s umkehren */

void reverse(char *s) 
{
  int i, j;
  char temp;

  i = 0;

  /* Ende von s finden */

  while(s[i] != '\0')
    ++i;

  /* ein Element vor "\0" */

  --i;

  /* Zeilentrenner stehenlassen */

  if(s[i] == '\n')
    --i;

  /* Anfang von s */

  j = 0; 

  while(j < i) {
    temp = s[j];

    /* Zeichen tauschen */

    s[j] = s[i];
    s[i] = temp;
    
    --i;
    ++j;
  }
}
