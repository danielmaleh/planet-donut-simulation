/*!
  \file   geomod.h
  \author Imane Jennane , Daniel Elmaleh
			310900			311287
  \date   Mai 2021
*/

#include "gisement.h"
#include <string>


using namespace std;

Gisement::Gisement (Cercle c, double res)  
	: cercleGis(c), gisementR(res), gisementR_mod(res){
	//gisementR = 1000*(pow((cercleGis.rayon/rayon_min),2));
}

//surcharge
Gisement::Gisement (double xg, double yg, double rayon, double res) 
	: Gisement(setCercle(xg,yg,rayon), res)	
{}

bool Gisement::inter_gisements (const Gisement* ptr_gis2) {
	
	if (intersection_cercles(cercleGis, (*ptr_gis2).cercleGis)) {
		return true;
	}
	return false;
}

void Gisement::inter_gis_bas (const Tab_ptr_Gisements& tab_ptr_Gis,const Cercle& c_bas) { 
	for (auto& elem : tab_ptr_Gis) {
		if (intersection_cercles((*elem).cercleGis, c_bas)) {
			cout << message::base_field_superposition(c_bas.centre.X, c_bas.centre.Y, 
													  (*elem).cercleGis.centre.X, 
													  (*elem).cercleGis.centre.Y);
		}
	}
}

void Gisement::lectureGis(istringstream& ligne_dec, Tab_ptr_Gisements& tab_ptr_Gis) {
	double xg, yg, rayon_g, resource_g;
	ligne_dec >> xg >> yg >> rayon_g >> resource_g;
	Gisement* ptr_gisement = new Gisement (xg, yg, rayon_g, resource_g); 
	
	if(!(tab_ptr_Gis.empty())) {
		for (auto& elem : tab_ptr_Gis) {
			if ((*ptr_gisement).inter_gisements(elem)) {
				cout << message::field_superposition(xg, yg, 
													 (*elem).cercleGis.centre.X, 
													 (*elem).cercleGis.centre.Y);
			}
		}
	}
	tab_ptr_Gis.push_back(ptr_gisement);
}

Gisement* Gisement::find_gis(P2D pos_gis, Tab_ptr_Gisements& tab_ptr_Gis) {
	double xg = pos_gis.X;
	double yg = pos_gis.Y;
	for (auto& elem : tab_ptr_Gis) {
		if ((*elem).cercleGis.centre.X == xg && (*elem).cercleGis.centre.Y == yg) {
			return elem;
		}
	}
	return nullptr;
} 

string Gisement::gisement_info_string() {
	
	string info_gis = to_string(cercleGis.centre.X) + "  " 
					  + to_string(cercleGis.centre.Y) + 
					  "  " + to_string(cercleGis.rayon) + "  " + to_string(gisementR);
	
	return info_gis;
}

Cercle Gisement::getCercleGis() {
	return cercleGis;
}

double Gisement::getResources() {
	return gisementR;
}

void Gisement::dessin_Gisement() { 
	
	dessin_cercle_geomod(C_GISEMENT, cercleGis);
}

void Gisement::reduce_resource() {
	
	if(gisementR_mod > deltaR) {
		gisementR_mod -= deltaR;
	}
}
