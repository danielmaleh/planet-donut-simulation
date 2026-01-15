/*!
  \file   projet.cc
  \author Imane Jennane , Daniel Elmaleh
			310900			311287
  \date   Mai 2021
*/

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <gtkmm.h>

#include "geomod.h"
#include "simulation.h"
#include "gui.h"


////// NOUS AVONS CREE LES FONCTION POUR CREATION ET UPDATE MAIS NOUS N"AVONS PAS EUT LE TEMPS DE DEBUGER CREATION ET LA UPDATE NEST PAS OPTIMALE ////
////// LE SCROLL EXISTE MAIS SANS INFORMTIONS AFFICHER ////

using namespace std;

int main(int argc, char* argv[])
{
	
	int a(1);
	
	auto app = Gtk::Application::create(a, argv, "org.gtkmm.example");
	
	Gui PDWindow;
	
	if (argc == 2) { 
		string argv_string = argv[1];
		PDWindow.setSim_filename(argv_string);
	}else if (argc > 2) {
		exit(EXIT_FAILURE); 
	}

	return app->run(PDWindow);

}










