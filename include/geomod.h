/*!
  \file   gisement.cc
  \author Imane Jennane , Daniel Elmaleh
			310900			311287
  \date   Mai 2021
*/

#ifndef GEOMOD_H_INCLUDED
#define GEOMOD_H_INCLUDED

#include <array>
#include <string>
#include "graphic_gui.h"

enum TypeCercle {C_GISEMENT, C_BASE, C_ROBOT_P, C_ROBOT_F, C_ROBOT_T, C_ROBOT_C, C_CONNEXION};

typedef std::array<CouleurDessin,6> CouleurBases;
constexpr CouleurBases tab_coul_bas = {RED, GREEN, BLUE, YELLOW, MAGENTA, CYAN};
enum Dir {D0,D1,D2,D3,D4,D5,D6,D7,D8,D9,D10,D11,D12,D13,D14,D15};


struct P2D
{
	double X ;
	double Y ;
};

struct Vecteur
{
	double x ;
	double y ;
};

struct Cercle
{
	P2D centre;
	double rayon = 0.0;
};

typedef std :: array <P2D,9> tab_equiv;

Cercle setCercle (double x, double y, double rayon);	

Cercle setCercle (P2D point, double rayon);	

//2.1
bool equal_zero (double nb);	
									
//2.2
void setMaximum(double max);	
									
//2.2
double getMaximum();	
										
//2.2
double getEpsilon_zero();	
									
//2.3
tab_equiv point_equiv(const P2D& point);	
							
//2.4
P2D init_pt(P2D& point);		
									
//2.4 surcharge
P2D init_pt(double x, double y);	
								
//2.5
double norme_init_vect(const P2D point1, const P2D point2, Vecteur& vect);	
	
//2.5 surcharge
double norme_init_vect(const P2D  A, const P2D  B);		
			
//2.6
bool test_egalite(const P2D point1, const P2D point2);	
					
//2.7
bool appartient_cercle(const Cercle c, const P2D  p);	
			
//2.8
bool intersection_cercles(Cercle cercle1, Cercle cercle2);	

void dessin_conexions (P2D p1, P2D p2);

void dessin_cercle_geomod (TypeCercle tc, Cercle c, int index_bas=-1);

void dessin_toggle_link(P2D p1, P2D p2);

P2D direction(Dir d, double norme=1);



#endif	//GEOMOD_H_INCLUDED	
