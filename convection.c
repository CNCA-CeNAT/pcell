/* Form definition file generated with fdesign. */

#include "forms.h"
#include <stdlib.h>
#include "convection.h"

/*

static FL_PUP_ENTRY fdmenu_init_mf_0[] =
{ 

**/

/*  itemtext   callback  shortcut   mode */

/*
  
  { "Configuration 1",	0,	"conf1",	 FL_PUP_RADIO},
  { "Configuration 2",	0,	"conf2",	 FL_PUP_RADIO},
  {0}
};

**/

FD_Convection *create_form_Convection(void)
{
  FL_OBJECT *obj;
  FD_Convection *fdui = (FD_Convection *) fl_calloc(1, sizeof(*fdui));

  fdui->Convection = fl_bgn_form(FL_NO_BOX, 460, 540);
  obj = fl_add_box(FL_UP_BOX, 0, 0, 460, 540, "");
  obj = fl_add_box(FL_UP_BOX, 20, 10, 430, 60, "Plasma Cell");
  fl_set_object_lsize(obj, FL_HUGE_SIZE);
  fl_set_object_lstyle(obj, FL_NORMAL_STYLE + FL_ENGRAVED_STYLE);

  fdui->Reynolds = obj = 
    fl_add_input(FL_NORMAL_INPUT, 20, 100, 180, 40, "Reynolds Number");
  fl_set_object_lsize(obj, FL_NORMAL_SIZE);
  fl_set_object_lalign(obj, FL_ALIGN_TOP);
  fl_set_object_lstyle(obj, FL_BOLD_STYLE);
  fl_set_object_callback(obj, Reyno, 0);

  fdui->run_time = obj = 
    fl_add_input(FL_NORMAL_INPUT, 20, 170, 180, 40, "Running Time");
  fl_set_object_lsize(obj, FL_NORMAL_SIZE);
  fl_set_object_lalign(obj, FL_ALIGN_TOP);
  fl_set_object_lstyle(obj, FL_BOLD_STYLE);
  fl_set_object_callback(obj, r_time, 0);
  
  fdui->speed = obj = fl_add_input(FL_NORMAL_INPUT, 20, 240, 180, 40, 
				   "Velocity Field Parameter");
  fl_set_object_lsize(obj, FL_NORMAL_SIZE);
  fl_set_object_lalign(obj, FL_ALIGN_TOP);
  fl_set_object_lstyle(obj, FL_BOLD_STYLE);
  fl_set_object_callback(obj, vf_p, 0);

  /*

  fdui->init_mf = obj = fl_add_menu(FL_PULLDOWN_MENU, 20, 300, 180, 40, 
				    "Initial MF Configuration");
  fl_set_object_boxtype(obj, FL_UP_BOX);
  fl_set_object_lsize(obj, FL_NORMAL_SIZE);
  fl_set_object_callback(obj, mag_fiel_conf, 0);
  fl_set_menu_entries(obj, fdmenu_init_mf_0);

  **/

  fdui->average = obj = 
    fl_add_button(FL_NORMAL_BUTTON, 20, 300, 180, 40, "Average Energy");
  fl_set_object_lsize(obj, FL_NORMAL_SIZE);
  fl_set_object_lstyle(obj, FL_BOLD_STYLE);
  fl_set_object_callback(obj, average_energy, 0);

  fdui->draw = obj = 
    fl_add_button(FL_NORMAL_BUTTON, 20, 360, 180, 40, "Draw");
  fl_set_object_lsize(obj, FL_NORMAL_SIZE);
  fl_set_object_lstyle(obj, FL_BOLD_STYLE);
  fl_set_object_callback(obj, drawing, 0);

  obj = fl_add_button(FL_NORMAL_BUTTON, 20, 420, 180, 40, "Redraw");
  fl_set_object_lsize(obj, FL_NORMAL_SIZE);
  fl_set_object_lstyle(obj, FL_BOLD_STYLE);
  fl_set_object_callback(obj, redrawing, 0);

  obj = fl_add_button(FL_NORMAL_BUTTON, 20, 480, 180, 40, "Stream");
  fl_set_object_lsize(obj, FL_NORMAL_SIZE);
  fl_set_object_lstyle(obj, FL_BOLD_STYLE);
  fl_set_object_callback(obj, streaming, 0);

  obj = fl_add_button(FL_NORMAL_BUTTON, 260, 360, 180, 40, "Movie");
  fl_set_object_lsize(obj, FL_NORMAL_SIZE);
  fl_set_object_lstyle(obj, FL_BOLD_STYLE);
  fl_set_object_callback(obj, make_movie, 0);  

  fdui->help = obj = 
    fl_add_button(FL_NORMAL_BUTTON, 260, 420, 180, 40, "Help");
  fl_set_object_lsize(obj, FL_NORMAL_SIZE);
  fl_set_object_lstyle(obj, FL_BOLD_STYLE);
  fl_set_object_callback(obj, helping, 0);

  fdui->exit_p = obj = 
    fl_add_button(FL_NORMAL_BUTTON, 260, 480, 180, 40, "Exit");
  fl_set_object_lsize(obj, FL_NORMAL_SIZE);
  fl_set_object_lstyle(obj, FL_BOLD_STYLE);
  fl_set_object_callback(obj, quit, 0);

  fdui->nx_i = obj = 
    fl_add_input(FL_NORMAL_INPUT, 260, 100, 180, 40, "NX_i ");
  fl_set_object_lsize(obj, FL_NORMAL_SIZE);
  fl_set_object_lstyle(obj, FL_BOLD_STYLE);
  fl_set_object_callback(obj, nx_initial, 0);

  fdui->nx_f = obj = 
    fl_add_input(FL_NORMAL_INPUT, 260, 170, 180,40, "NX_f ");
  fl_set_object_lsize(obj, FL_NORMAL_SIZE);
  fl_set_object_lstyle(obj, FL_BOLD_STYLE);
  fl_set_object_callback(obj, nx_final, 0);

  fdui->ny_i = obj = 
    fl_add_input(FL_NORMAL_INPUT, 260, 240, 180, 40, "NY_i ");
  fl_set_object_lsize(obj, FL_NORMAL_SIZE);
  fl_set_object_lstyle(obj, FL_BOLD_STYLE);
  fl_set_object_callback(obj, ny_initial, 0);
  
  fdui->ny_f = obj = 
    fl_add_input(FL_NORMAL_INPUT, 260, 300, 180, 40, "NY_f ");
  fl_set_object_lsize(obj, FL_NORMAL_SIZE);
  fl_set_object_lstyle(obj, FL_BOLD_STYLE);
  fl_set_object_callback(obj, ny_final, 0);

  fl_end_form();
    
  fdui->Convection->fdui = fdui;

  return fdui;
}
/*---------------------------------------*/

