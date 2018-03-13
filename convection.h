/** Header file generated with fdesign on Mon Dec  2 18:59:13 2002.**/

#ifndef FD_Convection_h_
#define FD_Convection_h_

/** Callbacks, globals and object handlers **/

extern void Reyno(FL_OBJECT *, long);
extern void r_time(FL_OBJECT *, long);
extern void mag_fiel_conf(FL_OBJECT *, long);
extern void drawing(FL_OBJECT *, long);
extern void quit(FL_OBJECT *, long);
extern void helping(FL_OBJECT *, long);
extern void vf_p(FL_OBJECT *, long);
extern void redrawing(FL_OBJECT *, long);
extern void streaming(FL_OBJECT *, long);
extern void make_movie(FL_OBJECT *, long, int, int, int);
extern void nx_initial(FL_OBJECT *, long);
extern void nx_final(FL_OBJECT *, long);
extern void ny_initial(FL_OBJECT *, long);
extern void ny_final(FL_OBJECT *, long);
extern void average_energy(FL_OBJECT *, long);

/**** Forms and Objects ****/

typedef struct {
  FL_FORM *Convection;
  void *vdata;
  char *cdata;
  long  ldata;
  FL_OBJECT *Reynolds;
  FL_OBJECT *run_time;
  FL_OBJECT *init_mf;
  FL_OBJECT *draw;
  FL_OBJECT *exit_p;
  FL_OBJECT *help;
  FL_OBJECT *speed;
  FL_OBJECT *nx_i;
  FL_OBJECT *nx_f;
  FL_OBJECT *ny_i;
  FL_OBJECT *ny_f;
  FL_OBJECT *average;
} FD_Convection;

extern FD_Convection * create_form_Convection(void);

#endif /* FD_Convection_h_ */
