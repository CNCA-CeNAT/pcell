#include "forms.h"
#include "convection.c"
#include "convection_cb.c"

int main(int argc, char *argv[])
{
  FD_Convection *fd_Convection;
  
  fl_initialize(&argc, argv, 0, 0, 0);
  fd_Convection = create_form_Convection();
  
  /* fill-in form initialization code */
  
  /* show the first form */
  
  fl_show_form(fd_Convection->Convection, FL_PLACE_CENTERFREE, FL_FULLBORDER, 
	       "Convection");
  fl_do_forms();
  
  return(0);
}
