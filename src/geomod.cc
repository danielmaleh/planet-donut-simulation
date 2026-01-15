/*!
  \file   geomod.cc
  \author Imane Jennane , Daniel Elmaleh
			310900			311287
  \date   Mai 2021
*/

#include <cmath>
#include <array>
#include <string>
#include "geomod.h"
#include "graphic.h"
#include "constantes.h"
#include <iostream>

using namespace std;

namespace 				
{
	double maximum(0.0);
	double epsilon_zero(0.0);
	Vecteur vect_null; 
}

Cercle setCercle (double cx, double cy, double r)
{
	Cercle c;
	c.centre = {cx,cy};
	c.rayon = r;
	return c;
}

Cercle setCercle (P2D centre, double r)
{
	Cercle c;
	c.centre = centre;
	c.rayon = r;
	return c;
}

//2.1
bool equal_zero (double coord)									
{
	if (abs(coord) < epsilon_zero) return true;
	return false;
}

//2.2
void setMaximum(double val)										
{
	maximum = abs(val);
	epsilon_zero = maximum*(1E-10);
}

//2.2
double getMaximum()												
{
	return maximum;
}

//2.2
double getEpsilon_zero()										
{
	return epsilon_zero;
}

//2.3
tab_equiv point_equiv(const P2D& point)								
{
	P2D pt = point;
	init_pt(pt);
	tab_equiv tab;
	tab[0] = {pt.X-(2*maximum), pt.Y-(2*maximum)};
	tab[1] = {pt.X-(2*maximum), pt.Y};
	tab[2] = {pt.X-(2*maximum), pt.Y+(2*maximum)};
	tab[3] = {pt.X, pt.Y-(2*maximum)};
	tab[4] = {pt.X, pt.Y};
	tab[5] = {pt.X, pt.Y+(2*maximum)};
	tab[6] = {pt.X+(2*maximum), pt.Y-(2*maximum)};
	tab[7] = {pt.X+(2*maximum), pt.Y};
	tab[8] = {pt.X+(2*maximum), pt.Y+(2*maximum)};
	return tab;
}

//2.4
P2D init_pt(P2D& point)										
{
	if (abs(point.X) > maximum) 
	{
		if (point.X < 0) point.X += 2*maximum;
		else if (point.X > 0) point.X -= 2*maximum;
	}
	if (abs(point.Y) > maximum) 
	{
		if (point.Y < 0) point.Y += 2*maximum;
		else if (point.Y > 0) point.Y -= 2*maximum;
	}
	return point;
}

//2.4 surcharge
P2D init_pt(double X, double Y)								
{
	P2D point{X,Y};
	init_pt(point);
	return point;
}

//2.5
double norme_init_vect(const P2D A, const P2D B, Vecteur& vect)	
{
	Vecteur* vect_pt = &vect;
	*vect_pt = {B.X-A.X, B.Y-A.Y};
	double norme(sqrt(pow((B.X)-(A.X),2)+pow((B.Y)-(A.Y),2)));
	tab_equiv tab;
	tab = point_equiv(B);
	for (auto& Bt : tab)
	{
	double norme_temp (sqrt(pow((Bt.X)-(A.X),2)+pow((Bt.Y)-(A.Y),2)));
	if (norme_temp < norme)
		{
		norme = norme_temp;
		*vect_pt = {Bt.X-A.X, Bt.Y-A.Y};
		}
	}
	return norme;	
}

//2.5 surcharge
double norme_init_vect(const P2D  A, const P2D  B)				
{
	Vecteur vect = vect_null;
	return norme_init_vect(A, B, vect);
}

//2.6
bool test_egalite(const P2D  A, const P2D  B)						
{
	if (norme_init_vect(A,B) < epsilon_zero) 
		{return true;}
	return false;
}

//2.7
bool appartient_cercle(const Cercle  c, const P2D  p)				
{
	if(norme_init_vect(p,c.centre) < (c.rayon - epsilon_zero)) 
		{return true;}
	return false;
}

//2.8
bool intersection_cercles(Cercle const  A, Cercle const  B)					
{
	if(norme_init_vect(A.centre,B.centre) < (A.rayon+B.rayon)-epsilon_zero) 
		{return true;}
	return false;
}

void dessin_conexions (P2D p1, P2D p2) {  
	
	dessin_lignes(p1.X, p1.Y, p2.X, p2.Y);
}

void dessin_cercle_geomod (TypeCercle tc, Cercle c, int index_bas) { 

	CouleurDessin couleur = BLACK;
	if (index_bas >= 0) couleur = tab_coul_bas[index_bas];
	tab_equiv tab_pts = point_equiv(c.centre);
	for(auto& pt : tab_pts) {
		
		double xc = pt.X;
		double yc = pt.Y; 
		
		switch(tc) {
		case  C_GISEMENT:
			
			dessin_cercle(xc, yc, c.rayon, couleur);
			break;
			
		case  C_BASE:
			dessin_cercle(xc, yc, c.rayon, couleur);
			dessin_cercle_vide(xc, yc, rayon_min*(c.rayon), couleur);
			break;
			
		case  C_ROBOT_P:
			dessin_cercle(xc, yc, c.rayon, couleur);
			dessin_prosp(xc, yc, c.rayon, couleur);
			break;
			
		case  C_ROBOT_F:
			dessin_cercle(xc, yc, c.rayon, couleur);
			dessin_forag(xc, yc, c.rayon, couleur);
			break;
			
		case  C_ROBOT_T:
			dessin_cercle(xc, yc, c.rayon, couleur);
			dessin_trans(xc, yc, c.rayon, couleur);
			break;
			
		case  C_ROBOT_C:
			dessin_cercle(xc, yc, c.rayon, couleur);
			dessin_comm(xc, yc, c.rayon, couleur);
			break;
			
		case  C_CONNEXION:
			dessin_cercle(xc, yc, c.rayon, PURPULE);
			break;
			
		}
	}
}

void dessin_toggle_link(P2D p1, P2D p2) {  
	
		double x1 = p1.X;
		double y1 = p1.Y;
		double x2 = p2.X;
		double y2 = p2.Y;
		dessin_lignes(x1, y1, x2, y2);
}

P2D direction(Dir d, double norme) { 
	
	double pas_angle = (2*M_PI)/16;
	P2D vect;
	int multiple = d%16;
	vect.X = norme*cos(multiple*pas_angle);
	vect.Y = norme*sin(multiple*pas_angle);
	return vect;
}

