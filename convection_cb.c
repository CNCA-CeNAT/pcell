#include "forms.h"
#include "convection.h"
#include "potinc.c"
#include "stream.c"
#include "plasma_convection.c"
#include "create_gnuplot.c"
#include "create_movie.c"
#include "create_avenergy.c"

double reynolds_number = 500.0, run_time = 20, vfieldparm = 0.5; 

/*** callbacks and freeobj handles for form Convection ***/

void Reyno(FL_OBJECT *ob, long data)
{
  /* fill-in code for callback */
  
  reynolds_number = atof(fl_get_input(ob)); 

  printf("Reynolds Number = %g \n", reynolds_number);
}

void r_time(FL_OBJECT *ob, long data)
{
  /* fill-in code for callback */

  run_time = atof(fl_get_input(ob)); 

  printf("Running Time = %g \n", run_time);
}

void mag_fiel_conf(FL_OBJECT *ob, long data)
{
  /* fill-in code for callback */

  printf("Not yet implemented \n");
}

void vf_p(FL_OBJECT *ob, long data)
{
  /* fill-in code for callback */
  
  vfieldparm = atof(fl_get_input(ob)); 

  printf("M = %g \n", vfieldparm);
}

void drawing(FL_OBJECT *ob, long data)
{
  /* fill-in code for callback */
  
  potinc(nx_f - nx_i, ny_f - ny_i, 50);
  convec_plasma(reynolds_number, vfieldparm, run_time, nx_f - nx_i, ny_f - ny_i);
  create_gnuplot(run_time);

  system("gnuplot -background white prog_gnuplot");
}

void redrawing(FL_OBJECT *ob, long data)
{
  /* fill-in code for callback */

  system("gnuplot -background white prog_gnuplot");
}

void streaming(FL_OBJECT *ob, long data)
{
  /* fill-in code for callback */

  stream(vfieldparm);

  system("gnuplot -background white stream_gnuplot");
}

void make_movie(FL_OBJECT *ob, long data, int id, int jd, int runtime)
{
  /* fill-in code for callback */

  potinc(id, jd, runtime);
  convec_plasma(reynolds_number, vfieldparm, run_time, nx_f - nx_i, ny_f - ny_i);
  create_gnuplot(run_time);
  create_movie(run_time);

  system("gnuplot -background white prog_movie");

  // system("chmod +x convertion");
  // system("./convertion");
  // system("mpeg_encode Movie");

  system("ffmpeg -f image2 -r 10 -i ./convection%d.png -b 600k ./convection.mp4");
}

void average_energy(FL_OBJECT *ob, long data)
{
  create_avenergy();

  system("gnuplot -background white prog_avenergy");  
  system("mv MeanField.DAT Meanfield.DAT");
}

void helping(FL_OBJECT *ob, long data)
{
  /* fill-in code for callback */

  printf("Not yet implemented \n");
}

void quit(FL_OBJECT *ob, long data)
{
  /* fill-in code for callback */

  fl_finish();
  exit(0); 
}

void nx_initial(FL_OBJECT *ob, long data)
{
  /* fill-in code for callback */

  nx_i = atof(fl_get_input(ob)); 

  printf("nx_initial = %g \n", nx_i);
}
void nx_final(FL_OBJECT *ob, long data)
{
  /* fill-in code for callback */

  nx_f = atof(fl_get_input(ob)); 

  printf("nx_final = %g \n", nx_f);
}

void ny_initial(FL_OBJECT *ob, long data)
{
  /* fill-in code for callback */

  ny_i = atof(fl_get_input(ob)); 

  printf("ny_initial = %g \n", ny_i);
}

void ny_final(FL_OBJECT *ob, long data)
{
  /* fill-in code for callback */

  ny_f = atof(fl_get_input(ob)); 

  printf("ny_final = %g \n", ny_f);
}
