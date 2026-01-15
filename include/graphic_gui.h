/*!
  \file   graphic_gui.h
  \author Imane Jennane , Daniel Elmaleh
			310900			311287
  \date   Mai 2021
*/

#ifndef GRAPHIC_GUI_H_INCLUDED
#define GRAPHIC_GUI_H_INCLUDED

#include "graphic.h"
#include <gtkmm/drawingarea.h>

void graphic_set_context(const Cairo::RefPtr<Cairo::Context>& cr);


#endif // GRAPHIC_GUI_H_INCLUDED
