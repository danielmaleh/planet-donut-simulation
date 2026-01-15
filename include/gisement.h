/*!
  \file   gisement.h
  \author Imane Jennane , Daniel Elmaleh
			310900			311287
  \date   Mai 2021
*/

#ifndef GISEMENT_H_INCLUDED
#define GISEMENT_H_INCLUDED

#include "geomod.h"
#include "constantes.h"
#include "message.h"

#include <cmath>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>

class Gisement;
typedef std::vector<Gisement*> Tab_ptr_Gisements;

class Gisement {

public:
	
	Gisement (double xg, double yg, double rayon, double res); 
	Gisement (Cercle c, double res); //surcharge
	static void lectureGis(std::istringstream& ligne_dec, Tab_ptr_Gisements& tab_gis);
	bool inter_gisements (const Gisement* gis2); 
	static void inter_gis_bas (const Tab_ptr_Gisements& tab_ptr_Gis, 
							   const Cercle& c_bas);
	static Gisement* find_gis(P2D pos_gis, Tab_ptr_Gisements& tabG);
	std::string gisement_info_string();
	Cercle getCercleGis();
	double getResources();
	void reduce_resource();
	void dessin_Gisement();

private:
	Cercle cercleGis;
	const double gisementR;	
	double gisementR_mod;	
};


#endif	//GISEMENT_H_INCLUDED	
